from scoss.metrics.metric import Metric
import torch
import torch.nn.functional as F
import json
from anytree import AnyNode
import javalang
import os

from scoss.metrics.graph_network.createclone_java import (
    get_edge_next_sib,
    get_edge_flow,
    getedge_nextstmt,
    getedge_nexttoken,
    getedge_nextuse,
    getnodeandedge_astonly,
    get_node_and_edge,
    get_child,
    get_token
)


def create_tree(root, node, nodelist, parent=None):
    node_id = len(nodelist)
    token, children = get_token(node), get_child(node)
    if node_id == 0:
        root.token = token
        root.data = node
    else:
        new_node = AnyNode(id=node_id, token=token, data=node, parent=parent)
    nodelist.append(node)
    for child in children:
        if node_id == 0:
            create_tree(root, child, nodelist, parent=root)
        else:
            create_tree(root, child, nodelist, parent=new_node)


def create_gmn_data(
        source,
        vocab_dict,
        mode="astandnext",
        nextsib=False,
        ifedge=False,
        whileedge=False,
        foredge=False,
        blockedge=False,
        nexttoken=False,
        nextuse=False):
    program_tokens = javalang.tokenizer.tokenize(source)
    parser = javalang.parse.Parser(program_tokens)
    tree = parser.parse_member_declaration()

    nodelist = []
    new_tree = AnyNode(id=0, token=None, data=None)
    create_tree(new_tree, tree, nodelist)

    x = []
    edgesrc = []
    edgetgt = []
    edge_attr = []
    if mode == "astonly":
        getnodeandedge_astonly(new_tree, x, vocab_dict, edgesrc, edgetgt)
    else:
        get_node_and_edge(new_tree, x, vocab_dict, edgesrc, edgetgt, edge_attr)
        if nextsib:
            get_edge_next_sib(new_tree, vocab_dict, edgesrc, edgetgt, edge_attr)
        get_edge_flow(new_tree, vocab_dict, edgesrc, edgetgt, edge_attr, ifedge, whileedge, foredge)
        if blockedge:
            getedge_nextstmt(new_tree, vocab_dict, edgesrc, edgetgt, edge_attr)
        tokenlist = []
        if nexttoken:
            getedge_nexttoken(
                new_tree, vocab_dict, edgesrc, edgetgt, edge_attr, tokenlist
            )
        variabledict = {}
        if nextuse:
            getedge_nextuse(
                new_tree, vocab_dict, edgesrc, edgetgt, edge_attr, variabledict
            )
    edge_index = [edgesrc, edgetgt]
    ast_length = len(x)

    return x, edge_index, edge_attr, ast_length


def get_similar_score(model, source1, source2, vocab_dict, device):
    x1, edge_index1, edge_attr1, ast1length = create_gmn_data(source1.source_str, vocab_dict)

    x2, edge_index2, edge_attr2, ast2length = create_gmn_data(source2.source_str, vocab_dict)

    x1 = torch.tensor(x1, dtype=torch.long, device=device)
    x2 = torch.tensor(x2, dtype=torch.long, device=device)
    edge_index1 = torch.tensor(edge_index1, dtype=torch.long, device=device)
    edge_index2 = torch.tensor(edge_index2, dtype=torch.long, device=device)
    if edge_attr1 is not None:
        edge_attr1 = torch.tensor(edge_attr1, dtype=torch.long, device=device)
        edge_attr2 = torch.tensor(edge_attr2, dtype=torch.long, device=device)
    data = [x1, x2, edge_index1, edge_index2, edge_attr1, edge_attr2]
    prediction = model(data)
    output = F.cosine_similarity(prediction[0], prediction[1])
    prediction = torch.sign(output).item()

    return prediction


class GMNMetric(Metric):
    name = 'gmn_based'

    def __init__(self):
        super().__init__()
        self.path_weight = "/saved_weights/gmnbcb10"
        self.path_vocal_dict = "/saved_weights/BCB_vocab_dict.json"
        self.device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

    def evaluate(self, source1, source2):
        if source1.lang != source2.lang:
            raise ValueError(
                'source1 and source2 is written on different language')

        if source1.lang != 'cpp' and source1.lang != 'java':
            raise ValueError("Unsupported languge: {}".format(source1.lang))\

        folder_path = os.path.dirname(__file__)
        model = torch.load(folder_path + self.path_weight)
        model = model.to(self.device)
        model.eval()

        with open(self.path_vocal_dict, encoding='utf-8') as f:
            vocab_dict = json.load(f)

        return get_similar_score(model, source1, source2, vocab_dict, self.device)
