const http = require('http');
const fs = require("fs")

const port = 8080;
const hostname = "10.4.1.2"; // IP da placa aqui
const server = http.createServer((req, res) => {
    if (req.method === "GET" && req.url === "/") {
        fs.promises.readFile("./index.html")
            .then(contents => {
                res.setHeader("Content-Type", "text/html");
                res.writeHead(200);
                res.end(contents);
            })
    } else if (req.method === "POST" && req.url === "/leds") {
        let body = [];

        req.on("data", (chunk) => {
            body.push(chunk);
        }).on("end", () => {
            body = Buffer.concat(body).toString()
            const data = JSON.parse(body)
            res.writeHead(200, { 'Content-Type': 'application/json' })
            fs.writeFileSync(`/sys/class/leds/beaglebone:green:usr${data.nameLed[3]}/brightness`, data.valor ? "1":"0");
            res.end(JSON.stringify([]));
        })
    }
});


server.listen(port, () => {
    // console.log(`Server running at http://${hostname}:${port}/`);
});
