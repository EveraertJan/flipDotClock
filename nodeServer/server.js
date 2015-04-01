
var http = require('http');
var osc = require('node-osc');
var io = require('socket.io');
var fs = require('fs');
var url = require('url');


var TogglClientJ = require('toggl-api'), togglJ = new TogglClientJ({apiToken: '3474e45372cd1c78efd44357e9df042b'});
var TogglClientA = require('toggl-api'), togglA = new TogglClientA({apiToken: '1c75c215753d080a53c71c3d3658eb7c'});
var TogglClientK = require('toggl-api'), togglK = new TogglClientK({apiToken: '06d85cafaeaa093719ca85b1f478dcba'});
var TogglClientW = require('toggl-api'), togglW = new TogglClientW({apiToken: '52c926f621a6af63ea0b31b26207168d'});

var client = new osc.Client('127.0.0.1', 12345); 
var oscServer = new osc.Server(3333, '0.0.0.0'); oscServer.on("message", function (msg, rinfo) { console.log("TUIO message:"); console.log(msg); });

var file = __dirname + '/chars.json';
var chars;
fs.readFile(file, 'utf8', function (err, data) {chars = JSON.parse(data);});


var timed = new Array();


totalTrackers = new Array();

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
			marquee(makeMarqueeStr(str));
		}	
	});
	srvr.on("newTimer", function(length){
		if(!marqueeRunning && !timerRunning){
			totalLength = length;
			timer(0);
		}	
	});
	srvr.on("newTimedMarquee", function(str, dly){
		addTimed("marquee", dly, str);
	});
	srvr.on("newTimedTimer", function(lngth, dly){
		addTimed("timer", dly, lngth);
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




/* ----------- timed --------------- */

function addTimed(tpe, tme, v){
	timed.push({
		"typ": tpe,
		"tim": tme,
		"val": v
	})
}

function getTimed(){
	var d = new Date();
	var h = d.getHours();
	var m = d.getMinutes();
	if(h<10){h = "0"+h;}
	if(m<10){m = "0"+m;}
	var timeStr = h+""+m;

	for(var i = 0; i<timed.length; i++){
		if(timed[i].typ == "marquee"){
			if(timed[i].tim == timeStr){
				marquee(makeMarqueeStr(timed[i].val));
				timed.splice(i, 1);
				return(true);
			}
		} else if(timed[i].typ == "timer"){
			if(timed[i].tim == timeStr){
				totalLength = parseInt(timed[i].val);
				timer(0);
				timed.splice(i, 1);
				return(true);
			}
		}

	}

	return(false);
}

/* ----------- toggl --------------- */

setInterval(function() {
	getTimed();
	if(!marqueeRunning && !timerRunning){
		getTimeTrackers(function(){
				totalTrackers.sort();
				var onlineStr = totalTrackers.toString();
				onlineStr.replace(",", " ");
				var onlineA = makeMarqueeStr(onlineStr);
				for(var i = 0; i<onlineA.length; i++){
					tr[i] = onlineA[i];
				}
				onlineStr = " ";
				totalTrackers = new Array();
			});
			sendArr();
		}
}, 1000);

function getTimeTrackers(_callback){
	totalTrackers.push(" ");
	togglW.getCurrentTimeEntry(function(err, d){
		if(err)
			console.log(err);

		if(d){
			totalTrackers.push("w");
		} 
	});
	togglA.getCurrentTimeEntry(function(err, d){
		if(err)
			console.log(err);

		if(d){
			totalTrackers.push("a");
		} 
	});

	togglK.getCurrentTimeEntry(function(err, d){
		if(err)
			console.log(err);

		if(d){

			totalTrackers.push("k");
		} 
	});

	togglJ.getCurrentTimeEntry(function(err, d){
		if(err)
			console.log(err);
		if(d){
			totalTrackers.push("j");
		} 
	});	
	_callback();

}

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
var scrollArr;
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
	scrollAr = new Array();
	sendArr();
}


function makeMarqueeStr(str){
	strArr = str.split('');
	scrollArr = new Array();
	for(var i = 0; i<strArr.length; i++){
		var c = 0;
		if(strArr[i] == " "){
			scrollArr.push(parseInt("0000000", 2));
		} else {
			for(var j = 0; j<chars.alphabet.length; j++){
				if(chars.alphabet[j].name == strArr[i]){
					var bin = chars.alphabet[j].value;
					var bina = bin.split(',');
					for(var k = 0; k<bina.length; k++){
						scrollArr.push(parseInt(bina[k], 2));
					}  
					scrollArr.push(parseInt("0000000", 2));
				} 
			}
		}
	}
	marqueePos = 28;
	return(scrollArr);
}

