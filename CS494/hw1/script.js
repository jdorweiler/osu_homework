var http = require("http");
var url = 'http://www.reddit.com/r/homebrewing.json';

http.get(url, function(res) {
    var body = '';

    res.on('data', function(chunk) {
        body += chunk;
    });

    res.on('end', function() {
        var fbResponse = JSON.parse(body)
        console.log("Got response: ", fbResponse.data.children.data.score);
    });
}).on('error', function(e) {
      console.log("Got error: ", e);
});
