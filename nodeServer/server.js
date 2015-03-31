
var http = require('http');
var osc = require('node-osc');
var io = require('socket.io');
var fs = require('fs');
var url = require('url');
var TogglClientJ = require('toggl-api'), togglJ = new TogglClientJ({apiToken: '3474e45372cd1c78efd44357e9df042b'});
var TogglClientA = require('toggl-api'), togglA = new TogglClientA({apiToken: '1c75c215753d080a53c71c3d3658eb7c'});
var TogglClientK = require('toggl-api'), togglK = new TogglClientK({apiToken: '06d85cafaeaa093719ca85b1f478dcba'});
var TogglClientW = require('toggl-api'), togglW = new TogglClientW({apiToken: '52c926f621a6af63ea0b31b26207168d'});


var togglArr = new Array(togglJ, togglA);



var client = new osc.Client('127.0.0.1', 12345); 

var oscServer = new osc.Server(3333, '0.0.0.0'); oscServer.on("message", function (msg, rinfo) { console.log("TUIO message:"); console.log(msg); });


var server = http.createServer(function(req, res){
	var pathname = url.parse(req.url).pathname;
	if(pathname == "/"){
		var query = url.parse(req.url).query;
		if(query){
			console.log(query);
		}
		res.writeHead(200, {'Content-Type': 'text/html'});
		fs.readFile('index.html', function(err, content) {
			res.end(content);
		});
	} 
}).listen(8080, '192.168.0.230');

var tr = new Array("0000000");
for(var i = 0; i<27; i++){
	tr.push(parseInt("000000", 2));
}


io = io(server);
server.listen(8080);

io.on('connection', function(srvr) {
	srvr.emit('connected');

	srvr.on("newMarquee", function(str){
		if(!timerRunning && !marqueeRunning){
			scrollArr = new Array(parseInt("0001100", 2), parseInt("0111110", 2), parseInt("0001100", 2));
			marqueePos = 28;
			marquee(scrollArr);
		}	
	});
	srvr.on("newTimer", function(length){
		if(!marqueeRunning && !timerRunning){
			totalLength = length;
			timer(0);
		}	
	});


});


function sendArr(){
	for(var i  = 0; i<tr.length; i++){
		tr[i].toString(16);
	}
	client.send("pc", tr);
	for(var i = 0; i<tr.length; i++){
		tr[i] = parseInt("0000000", 2);	
	}	
}




/* ----------- toggl --------------- */

setInterval(function() {
	
	if(!marqueeRunning && !timerRunning){
		togglW.getCurrentTimeEntry(function(err, d){
			if(err)
				console.log(err);

			if(d){
				tr[1] = parseInt("0001100", 2);
				tr[2] = parseInt("0111110", 2);
				tr[3] = parseInt("0001100", 2);
			} 
		});
		togglA.getCurrentTimeEntry(function(err, d){
			if(err)
				console.log(err);

			if(d){
				tr[5] = parseInt("0001100", 2);
				tr[6] = parseInt("0111110", 2);
				tr[7] = parseInt("0001100", 2);
			} 
		});

		togglK.getCurrentTimeEntry(function(err, d){
			if(err)
				console.log(err);

			if(d){
				tr[9] = parseInt("0001100", 2);
				tr[10] = parseInt("0111110", 2);
				tr[11] = parseInt("0001100", 2);
			} 
		});

		togglJ.getCurrentTimeEntry(function(err, d){
			if(err)
				console.log(err);

			if(d){
				tr[13] = parseInt("0001100", 2);
				tr[14] = parseInt("0111110", 2);
				tr[15] = parseInt("0001100", 2);
			} 
		});


		sendArr();
	}
}, 1000);

/* ----------- timer --------------- */
var totalLength;
var timerRunning = false;
function timer(length){
	timerRunning = true;
	for(var i = 0; i<28; i++){
		if(i<Math.floor((length/totalLength)*28)){
			tr[i] = parseInt("1111111", 2);
		} else {
			tr[i] = parseInt("0000000", 2);
		}
	}
	length++;
	if(Math.floor((length/totalLength)*28)<28){
		setTimeout(function(){timer(length)}, 1000);
		sendArr();
	} else {
		timerRunning = false;
	}
}


/* ----------- marquee --------------- */

var marqueePos = 28;
var marqueeRunning = false;
var scrollAr;
function marquee(){
	marqueeRunning = true;
	for(var i = 0; i<tr.length; i++){
		tr[i] = parseInt("0000000", 2);
		
	}
	for(var j = 0; j<scrollArr.length; j++){
		if(marqueePos+j>=0 && marqueePos+j<=28){
			tr[marqueePos+j] = scrollArr[j];
		}
	}
	marqueePos--;
	if(marqueePos+scrollArr.length >= 0){
		setTimeout(function(){marquee()}, 100);
	} else {
		marqueeRunning = false;
	}
	sendArr();
}




