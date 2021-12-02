let fs = require("fs");

fs.readFile("../input", "utf8", (err,data) => {
    if(err) throw err;

    let lines = data.split("\n");

    //Part 1
    let res = 0;
    for(let i = 1; i < lines.length; i++) {
        if(parseInt(lines[i]) > parseInt(lines[i-1])) res++;
    }

    console.log("Part 1: " + res);


    //Part 2

    res = 0;
    let currentWin;
    let lastWin = parseInt(lines[0]) + parseInt(lines[1]) + parseInt(lines[2]);
    for(let i = 1; i < lines.length; i++) {

        if(lines.length - i < 3) {
            break;
        }

        currentWin = parseInt(lines[i]) + parseInt(lines[i+1]) + parseInt(lines[i+2]);


        if(currentWin > lastWin) {
            res++;
        }
        lastWin = currentWin;
    }

    console.log("Part 2: " + res);
});