COMPARISON_HTML=r'''<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <!-- <meta name="viewport" content="width=device-width, initial-scale=1.0"> -->
    <title>Result</title>
    <style>
        table {
        font-family: arial, sans-serif;
        border-collapse: collapse;
        }

        a {
            text-decoration: none;
        }
        td, th {
        min-width: 150px;
        border: 1px solid #dddddd;
        padding: 8px;
        }
        

        </style>
</head>
<body>
<h2>File Result</h2>
<table style="text-align: center">
    <tr>
        <th>source1</th>
        <th>source2</th>
        <th>{{metric}}</th>
    </tr>
    <tr>
    <td>{{file1}}</a></td>
    <td>{{file2}}</a></td>
    <td>{{score}}</a></td>
    </tr>

</table>

<table style="width:100%; margin-top: 50px;">
<tr>
    <th>{{file1}}</th>
    <th>{{file2}}</th> 
</tr>
<tr>
    <td>{{data1}}</td>
    <td>{{data2}}</td>
</tr>
</table>
</body>
</html>'''

SMOSS_COMPARISON_HTML=r'''<!DOCTYPE html>
<html>
<head>
	<title>Matches for submission/a01-sample.py and submission/a01-sample.py</title>
	<script type="text/javascript">
	const setFrame = (el, html) => {
	  if (el.contentDocument) {
	    el.document = el.contentDocument;
	  }
	  if (el.document !== null) {
	    el.document.open();
	    el.document.writeln(html);
	    el.document.close();
	  }
	};

	const loadFrameContent = function(frame ,text) {
	  const waitForEl = () => {
	    const frameEl = document.getElementById(frame);
	    if (frameEl === null) {
	      setTimeout(waitForEl, 10);
	      return;
	    }
	    setFrame(frameEl, text);
	  };
	  setTimeout(waitForEl, 10);
	};

	const top_html = String.raw`
<<<>>>
`;

	const left_html = String.raw`
<<<>>>
`;

	const right_html = String.raw`
<<<>>>
`;	
	
	loadFrameContent("top", top_html);
	loadFrameContent("content0", left_html);	
	loadFrameContent("content1", right_html);
</script>
</head>
<!-- <body> -->
<frameset rows="150,*"><frameset cols="1000,*"><frame frameborder="0" name="top" id="top" /></frameset><frameset cols="50%,50%"><frame name="0" id="content0" /><frame name="1" id="content1" /></frameset></frameset>
  <!-- <iframe id="content" src="#" frameBorder="0"></iframe> -->
<!-- </body> -->
</html>'''

SUMMARY_HTML=r'''<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <!-- <meta name="viewport" content="width=device-width, initial-scale=1.0"> -->
    <title>Result</title>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <script src="https://www.w3schools.com/lib/w3.js"></script>
    <link href="https://www.w3schools.com/w3css/4/w3.css" rel="stylesheet" />
    <style>
        table {
        font-family: arial, sans-serif;
        border-collapse: collapse;
        text-align: center;
        }
        a {
            text-decoration: none;
        }
        td, th {
        min-width: 150px;
        border: 1.5px solid #000000;
        padding: 8px;
        }
        
        th {
        cursor: pointer;
        background-color: rgb(39, 37, 36);
        color: #fff;
        }
        body{
            background-color: rgb(233, 233, 233);
        }

        </style>
</head>
<body>

<h2>Result</h2>

<table id="usersTable">
    <tr>
        {%for head in heads%}
        <th>{{head}} <i class="fa fa-sort"></i></th>
        {%endfor%}
    </tr>
    {%for link in links%}
    <tr class="item">
    <td>{{link['source1']}}</a></td>
    <td>{{link['source2']}}</a></td>
    {%for metric in link['scores'] %}
        {% if metric in link['alignments'] %}
            <td><a href="{{link['alignments'][metric]}}"  target="_blank" >{{link['scores'][metric]}}</a></td>
        {% else %}
            <td><span>{{link['scores'][metric]}}</span></td>
        {% endif %}
    {%endfor%}
    </tr>
    {%endfor%}
</table>
<script>
    let tid = "#usersTable";
    let headers = document.querySelectorAll(tid + " th");

    // Sort the table element when clicking on the table headers
    headers.forEach(function(element, i) {
        element.addEventListener("click", function() {
        w3.sortHTML(tid, ".item", "td:nth-child(" + (i + 1) + ")");
        });
    });
</script>
</body>
</html>'''