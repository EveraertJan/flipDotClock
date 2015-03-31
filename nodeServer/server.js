var http = require('http');
var osc = require('node-osc');

var TogglClient = require('toggl-api')
, toggl = new TogglClient({apiToken: '3474e45372cd1c78efd44357e9df042b'})


var client = new osc.Client('127.0.0.1', 12345); 
//client.send('pc', "init");

var oscServer = new osc.Server(3333, '0.0.0.0'); oscServer.on("message", function (msg, rinfo) { console.log("TUIO message:"); console.log(msg); });



http.createServer(function (req, res) {
	res.writeHead(200, {'Content-Type': 'text/plain'});
	res.end('Hello World\n');
}).listen(8080, '192.168.0.230');

var json = {
	data: "192.168.0.230",
	da: "192.168.0.0",
	dta: "192.168.0.1"
}
var tr = new Array();
for(var i = 0; i<28; i++){
	tr.push(parseInt("000000", 2));
}

setInterval(function() {
	
	var wId = 376248;
	toggl.getCurrentTimeEntry(function(err, d){
		if(err)
			console.log(err);
		if(d){
			client.send("pc", "online");
			tr[1] = parseInt("0001100", 2);
			tr[2] = parseInt("0111110", 2);
			tr[3] = parseInt("0001100", 2);
		} else {
			client.send("pc", "offline");
		}
	});
	sendArr();
}, 3000);

function sendArr(){
	//console.log(tr.length);
	for(var i  = 0; i<tr.length; i++){
		tr[i].toString(16);
	}
	client.send("pc", tr);
	//console.log("send "+tr);
	for(var i = 0; i<tr.length; i++){
		tr[i] = parseInt("0000000", 2);	
	}	
}

