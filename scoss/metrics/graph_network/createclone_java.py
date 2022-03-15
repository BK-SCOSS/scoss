import os
import javalang
import javalang.tree
import javalang.ast
import javalang.util
from javalang.ast import Node
from anytree import AnyNode
from .edge_index import edges


def get_token(node):
    token = ""
    if isinstance(node, str):
        token = node
    elif isinstance(node, set):
        token = "Modifier"
    elif isinstance(node, Node):
        token = node.__class__.__name__
    return token


def get_child(root):
    if isinstance(root, Node):
        children = root.children
    elif isinstance(root, set):
        children = list(root)
    else:
        children = []

    def expand(nested_list):
        for item in nested_list:
            if isinstance(item, list):
                for sub_item in expand(item):
                    yield sub_item
            elif item:
                yield item

    return list(expand(children))


def get_sequence(node, sequence):
    token, children = get_token(node), get_child(node)
    sequence.append(token)
    for child in children:
        get_sequence(child, sequence)


def get_nodes(node, nodelist):
    nodelist.append(node)
    children = get_child(node)
    for child in children:
        get_nodes(child, nodelist)


class Queue:
    def __init__(self):
        self.__list = list()

    def isEmpty(self):
        return self.__list == []

    def push(self, data):
        self.__list.append(data)

    def pop(self):
        if self.isEmpty():
            return False
        return self.__list.pop(0)


def traverse(node, index):
    queue = Queue()
    queue.push(node)
    result = []
    while not queue.isEmpty():
        node = queue.pop()
        result.append(get_token(node))
        result.append(index)
        index += 1
        for (child_name, child) in node.children():
            # print(get_token(child),index)
            queue.push(child)
    return result


def createtree(root, node, nodelist, parent=None):
    id = len(nodelist)
    token, children = get_token(node), get_child(node)
    if id == 0:
        root.token = token
        root.data = node
    else:
        newnode = AnyNode(id=id, token=token, data=node, parent=parent)
    nodelist.append(node)
    for child in children:
        if id == 0:
            createtree(root, child, nodelist, parent=root)
        else:
            createtree(root, child, nodelist, parent=newnode)


def getnodeandedge_astonly(node, nodeindexlist, vocabdict, src, tgt):
    token = node.token
    nodeindexlist.append([vocabdict[token]])
    for child in node.children:
        src.append(node.id)
        tgt.append(child.id)
        src.append(child.id)
        tgt.append(node.id)
        getnodeandedge_astonly(child, nodeindexlist, vocabdict, src, tgt)


def get_node_and_edge(node, nodeindexlist, vocabdict, src, tgt, edgetype):
    token = node.token
    nodeindexlist.append([vocabdict[token]])
    for child in node.children:
        src.append(node.id)
        tgt.append(child.id)
        edgetype.append([0])
        src.append(child.id)
        tgt.append(node.id)
        edgetype.append([0])
        get_node_and_edge(child, nodeindexlist, vocabdict, src, tgt, edgetype)


def get_edge_next_sib(node, vocabdict, src, tgt, edgetype):
    token = node.token
    for i in range(len(node.children) - 1):
        src.append(node.children[i].id)
        tgt.append(node.children[i + 1].id)
        edgetype.append([1])
        src.append(node.children[i + 1].id)
        tgt.append(node.children[i].id)
        edgetype.append([edges["Prevsib"]])
    for child in node.children:
        get_edge_next_sib(child, vocabdict, src, tgt, edgetype)


def get_edge_flow(
        node, vocab_dict, src, tgt, edgetype, ifedge=False, whileedge=False, foredge=False
):
    token = node.token
    if whileedge == True:
        if token == "WhileStatement":
            src.append(node.children[0].id)
            tgt.append(node.children[1].id)
            edgetype.append([edges["While"]])
            src.append(node.children[1].id)
            tgt.append(node.children[0].id)
            edgetype.append([edges["While"]])
    if foredge == True:
        if token == "ForStatement":
            src.append(node.children[0].id)
            tgt.append(node.children[1].id)
            edgetype.append([edges["For"]])
            src.append(node.children[1].id)
            tgt.append(node.children[0].id)
            edgetype.append([edges["For"]])
            """if len(node.children[1].children)!=0:
                src.append(node.children[0].id)
                tgt.append(node.children[1].children[0].id)
                edgetype.append(edges['For_loopstart'])
                src.append(node.children[1].children[0].id)
                tgt.append(node.children[0].id)
                edgetype.append(edges['For_loopstart'])
                src.append(node.children[1].children[-1].id)
                tgt.append(node.children[0].id)
                edgetype.append(edges['For_loopend'])
                src.append(node.children[0].id)
                tgt.append(node.children[1].children[-1].id)
                edgetype.append(edges['For_loopend'])"""
    # if token=='ForControl':
    # print(token,len(node.children))
    if ifedge == True:
        if token == "IfStatement":
            src.append(node.children[0].id)
            tgt.append(node.children[1].id)
            edgetype.append([edges["If"]])
            src.append(node.children[1].id)
            tgt.append(node.children[0].id)
            edgetype.append([edges["If"]])
            if len(node.children) == 3:
                src.append(node.children[0].id)
                tgt.append(node.children[2].id)
                edgetype.append([edges["Ifelse"]])
                src.append(node.children[2].id)
                tgt.append(node.children[0].id)
                edgetype.append([edges["Ifelse"]])
    for child in node.children:
        get_edge_flow(child, vocab_dict, src, tgt, edgetype, ifedge, whileedge, foredge)


def getedge_nextstmt(node, vocabdict, src, tgt, edgetype):
    token = node.token
    if token == "BlockStatement":
        for i in range(len(node.children) - 1):
            src.append(node.children[i].id)
            tgt.append(node.children[i + 1].id)
            edgetype.append([edges["Nextstmt"]])
            src.append(node.children[i + 1].id)
            tgt.append(node.children[i].id)
            edgetype.append([edges["Prevstmt"]])
    for child in node.children:
        getedge_nextstmt(child, vocabdict, src, tgt, edgetype)


def getedge_nexttoken(node, vocabdict, src, tgt, edgetype, tokenlist):
    def gettokenlist(node, vocabdict, edgetype, tokenlist):
        token = node.token
        if len(node.children) == 0:
            tokenlist.append(node.id)
        for child in node.children:
            gettokenlist(child, vocabdict, edgetype, tokenlist)

    gettokenlist(node, vocabdict, edgetype, tokenlist)
    for i in range(len(tokenlist) - 1):
        src.append(tokenlist[i])
        tgt.append(tokenlist[i + 1])
        edgetype.append([edges["Nexttoken"]])
        src.append(tokenlist[i + 1])
        tgt.append(tokenlist[i])
        edgetype.append([edges["Prevtoken"]])


def getedge_nextuse(node, vocabdict, src, tgt, edgetype, variabledict):
    def getvariables(node, vocabdict, edgetype, variabledict):
        token = node.token
        if token == "MemberReference":
            for child in node.children:
                if child.token == node.data.member:
                    variable = child.token
                    variablenode = child
            if not variabledict.__contains__(variable):
                variabledict[variable] = [variablenode.id]
            else:
                variabledict[variable].append(variablenode.id)
        for child in node.children:
            getvariables(child, vocabdict, edgetype, variabledict)

    getvariables(node, vocabdict, edgetype, variabledict)
    # print(variabledict)
    for v in variabledict.keys():
        for i in range(len(variabledict[v]) - 1):
            src.append(variabledict[v][i])
            tgt.append(variabledict[v][i + 1])
            edgetype.append([edges["Nextuse"]])
            src.append(variabledict[v][i + 1])
            tgt.append(variabledict[v][i])
            edgetype.append([edges["Prevuse"]])


def createast():
    asts = []
    paths = []
    alltokens = []
    dirname = "googlejam4_src/"
    for i in range(1, 13):
        for rt, dirs, files in os.walk(dirname + str(i)):
            for file in files:
                programfile = open(os.path.join(rt, file), encoding="utf-8")
                # print(os.path.join(rt,file))
                programtext = programfile.read()
                # programtext=programtext.replace('\r','')
                programtokens = javalang.tokenizer.tokenize(programtext)
                # print(list(programtokens))
                programast = javalang.parser.parse(programtokens)
                paths.append(os.path.join(rt, file))
                asts.append(programast)
                get_sequence(programast, alltokens)
                programfile.close()
                # print(programast)
                # print(alltokens)
    astdict = dict(zip(paths, asts))
    ifcount = 0
    whilecount = 0
    forcount = 0
    blockcount = 0
    docount = 0
    switchcount = 0
    for token in alltokens:
        if token == "IfStatement":
            ifcount += 1
        if token == "WhileStatement":
            whilecount += 1
        if token == "ForStatement":
            forcount += 1
        if token == "BlockStatement":
            blockcount += 1
        if token == "DoStatement":
            docount += 1
        if token == "SwitchStatement":
            switchcount += 1
    print(ifcount, whilecount, forcount, blockcount, docount, switchcount)
    print("allnodes ", len(alltokens))
    alltokens = list(set(alltokens))
    vocabsize = len(alltokens)
    tokenids = range(vocabsize)
    vocabdict = dict(zip(alltokens, tokenids))
    print(vocabsize)
    return astdict, vocabsize, vocabdict


def createseparategraph(
        astdict,
        vocablen,
        vocabdict,
        device,
        mode="astonly",
        nextsib=False,
        ifedge=False,
        whileedge=False,
        foredge=False,
        blockedge=False,
        nexttoken=False,
        nextuse=False,
):
    pathlist = []
    treelist = []
    print("nextsib ", nextsib)
    print("ifedge ", ifedge)
    print("whileedge ", whileedge)
    print("foredge ", foredge)
    print("blockedge ", blockedge)
    print("nexttoken", nexttoken)
    print("nextuse ", nextuse)
    print(len(astdict))
    for path, tree in astdict.items():
        # print(tree)
        # print(path)
        nodelist = []
        newtree = AnyNode(id=0, token=None, data=None)
        createtree(newtree, tree, nodelist)
        # print(path)
        # print(newtree)
        x = []
        edgesrc = []
        edgetgt = []
        edge_attr = []
        if mode == "astonly":
            getnodeandedge_astonly(newtree, x, vocabdict, edgesrc, edgetgt)
        else:
            get_node_and_edge(newtree, x, vocabdict, edgesrc, edgetgt, edge_attr)
            if nextsib:
                get_edge_next_sib(newtree, vocabdict, edgesrc, edgetgt, edge_attr)
            get_edge_flow(newtree, vocabdict, edgesrc, edgetgt, edge_attr, ifedge, whileedge, foredge)
            if blockedge:
                getedge_nextstmt(newtree, vocabdict, edgesrc, edgetgt, edge_attr)
            token_list = []
            if nexttoken:
                getedge_nexttoken(
                    newtree, vocabdict, edgesrc, edgetgt, edge_attr, token_list
                )
            variabledict = {}
            if nextuse:
                getedge_nextuse(
                    newtree, vocabdict, edgesrc, edgetgt, edge_attr, variabledict
                )
        edge_index = [edgesrc, edgetgt]
        astlength = len(x)
        pathlist.append(path)
        treelist.append([[x, edge_index, edge_attr], astlength])
        astdict[path] = [[x, edge_index, edge_attr], astlength]

    return astdict


def creategmndata(id, treedict, vocablen, vocabdict, device):
    indexdir = "javadata/"
    if id == "0":
        trainfile = open(indexdir + "trainall.txt")
        validfile = open(indexdir + "valid.txt")
        testfile = open(indexdir + "test.txt")
    elif id == "13":
        trainfile = open(indexdir + "train13.txt")
        validfile = open(indexdir + "valid.txt")
        testfile = open(indexdir + "test.txt")
    elif id == "11":
        trainfile = open(indexdir + "train11.txt")
        validfile = open(indexdir + "valid.txt")
        testfile = open(indexdir + "test.txt")
    elif id == "0small":
        trainfile = open(indexdir + "trainsmall.txt")
        validfile = open(indexdir + "valid.txt")
        testfile = open(indexdir + "test.txt")
    elif id == "13small":
        trainfile = open(indexdir + "train13small.txt")
        validfile = open(indexdir + "validsmall.txt")
        testfile = open(indexdir + "testsmall.txt")
    elif id == "11small":
        trainfile = open(indexdir + "train11small.txt")
        validfile = open(indexdir + "validsmall.txt")
        testfile = open(indexdir + "testsmall.txt")
    else:
        print("file not exist")
        quit()
    trainlist = trainfile.readlines()
    validlist = validfile.readlines()
    testlist = testfile.readlines()

    print("train data")
    traindata = createpairdata(treedict, trainlist, device=device)
    print("valid data")
    validdata = createpairdata(treedict, validlist, device=device)
    print("test data")
    testdata = createpairdata(treedict, testlist, device=device)
    return traindata, validdata, testdata


def createpairdata(treedict, pathlist, device):
    datalist = []
    countlines = 1
    for line in pathlist:
        countlines += 1
        pairinfo = line.split()
        code1path = pairinfo[0].replace("\\", "/")
        code2path = pairinfo[1].replace("\\", "/")
        label = int(pairinfo[2])

        data1 = treedict[code1path]
        data2 = treedict[code2path]
        x1, edge_index1, edge_attr1, ast1length = (
            data1[0][0],
            data1[0][1],
            data1[0][2],
            data1[1],
        )
        x2, edge_index2, edge_attr2, ast2length = (
            data2[0][0],
            data2[0][1],
            data2[0][2],
            data2[1],
        )

        if edge_attr1 == []:
            edge_attr1 = None
            edge_attr2 = None
        data = [[x1, x2, edge_index1, edge_index2, edge_attr1, edge_attr2], label]
        datalist.append(data)
    return datalist
