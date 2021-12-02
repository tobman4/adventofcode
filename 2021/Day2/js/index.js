let fs = require("fs");

fs.readFile("../input", "utf8", (err, data) => {
    if(err) throw err;

    let lines = data.split("\n");

    let x = 0;
    let y = 0;
    let z = 0;

    for(let i = 0; i < lines.length; i++) {
        let splitLine = lines[i].split(" ");

        let command = splitLine[0];
        let speed = parseInt(splitLine[1]);

        switch(command) {
            case "forward":
                x += speed;
                y += z*speed;
                break;
            
            case "down":
                z += speed;
                break;
            
            case "up":
                z -= speed;
                break;
            
            default:
                throw new Error("Bad command: " + command);
        }
    }
    console.log("End at X: " + x + " Y: " + y + " - (" + x*y + ")");
});