import a from "fs";

class planet {
    
    orbit: planet;
    is_global_com: boolean = false;

    children: planet[] = [];
    
    constructor(parent: planet) {

    }
}

fs.read();