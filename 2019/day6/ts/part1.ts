import * as fs from 'fs';

class planet {
    
    me : string = "";

    orbit: planet = null;
    is_global_com: boolean = false;
    is_end_point : boolean = false;

    children: planet[] = [];
    
    constructor(mme : string) {
        this.me = mme;
    }

    find_pos() : void {
        //SHAUN!!! SHAUN!!!! SHAUN!!!!!!!
        let l = find_child(this.me);
        this.orbit = planets[find_parent(this.me)];
        if(l.length == 0) {
            this.is_end_point = true;
            return;
        }


        l.forEach(el => {
            this.children.push(new planet(el));
        });
    }
}

const raw_data : string = fs.readFileSync("../map", "utf8");

let orbits : string[] = raw_data.split("\r\n");
let planets_raw : string[] = [];
let planets = {};

orbits.forEach(element => {
    let hold = element.split(")");

    if(planets_raw.indexOf(hold[0]) == -1) {
        planets_raw.push(hold[0]);
        planets[hold[0]] = new planet(hold[0]);
    }

    if(planets_raw.indexOf(hold[1]) == -1) {
        planets_raw.push(hold[1]);
        planets[hold[1]] = new planet(hold[1]);
    }

});

function find_child(target : string) : string[] {
    let ret : string[] = [];
    orbits.forEach(el => {
        if(el.startsWith(target)) {
            ret.push(el.split(")")[1]);
        }
    });
    return ret;
}

function find_parent(target : string) : string {
    let ret = null;
    orbits.forEach(el => {
        if(el.endsWith(target)) {
            ret = el.split(")")[0];
        }
    });
    return ret; 
}

function length_to_com(mark : planet) : planet[] {
    let curr : planet = mark;
    let path : planet[] = [];
    while(curr.me != "COM") {
        path.push(curr);
        curr = curr.orbit;
    }
    path.push(curr);
    return path;
}

let c = planets["COM"];
planets_raw.forEach(el => {
    planets[el].find_pos();
});

console.log("==================================");
console.log("Part 1");
console.log("----------------------------------");

let x = 0;
planets_raw.forEach(el => {
    x += length_to_com(planets[el]).length - 1;
});
console.log("orbit: " + x);

console.log("==================================");
console.log("Part 2");
console.log("----------------------------------");

let p1 = length_to_com(planets["YOU"]);
let p2 = length_to_com(planets["SAN"]);

try {
    p1.forEach(el => {
        if(p2.indexOf(el) != -1) {
            let i = p1.indexOf(el);
            p1 = p1.slice(0,i);
            i = p2.indexOf(el);
            p2 = p2.slice(0,i+1);
            
            throw new Error("BREAK");
        }
    });
} catch(err) {
    if(err.message != "BREAK") {
        console.log(err);
    }
}

p2.reverse();
p2.forEach(el => {
    p1.push(el);
});
console.log(p1.length-3);
