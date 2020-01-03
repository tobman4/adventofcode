function no_decrease(data: number): boolean {
    let str : string = String(data);
    let last : number = null;
    for(let i = 0; i < str.length; i++) {
        if(last) {
            if(last > Number(str[i])) {
                return false;
            }
        }
        last = Number(str[i]);
    }
    return true;
}

function adjacent_V1(data: number): boolean {
    let str: String = String(data);

    for(let i = 0; i < str.length-1; i++) {
      if(str[i] == str[i+1]) {
          return true;
      }
    }
    return false;
}


function adjacent_V2(data: number): boolean {
    let str: String = String(data);

    let last: String = "X";

    for(let i = 0; i < str.length-1; i++) {
      if(str[i] == str[i+1] && i == str.length-1) {
          return true;
      } else if(str[i] == str[i+1] && (str[i] != str[i+2] && str[i] != last)) {
        return true;
      }
      last = str[i];
    }
    return false;
}

function len(data: number, len: number = 6): boolean {
    return (String(data).length == len);
}

function val(data: number, min: number = 28439,max: number = 748759): boolean {
    return (data <= max && data >= min);
}

function rule_book() {
    this.rules = [
        val,
        len,
        adjacent_V2,
        no_decrease
    ]
    this.log = [

    ]

    this.set_log = (data: number,res: boolean) => {
        let h = {
            "in": data,
            "out": res
        }
        this.log.push(h);
    }

    this.test = (data: number) => {
        for(let i = 0; i < this.rules.length; i++) {
            let res: boolean= this.rules[i](data);
            if(!res) {
                try {
                    this.rules[i].rule();
                } catch {
                    console.log("rule broken: " + this.rules[i].name);
                }
                this.set_log(data,false);
                return false;
            }
        }
        this.set_log(data,true);
        return true;
    }
}


let r = new rule_book();

let valid = 0;
for(let i = 284639; i <= 748759; i++) {
    let res = r.test(i);
    if(!res) {
        console.log(i);
    } else {
        valid++;
    }
}

console.log(String(valid) + " was valid");