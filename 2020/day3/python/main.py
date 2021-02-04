import re

from passport import passport

heigthReg = re.compile(r"hgt:(\d{1,})(cm|in){0,}")
bYearReg = re.compile(r"byr:(\d{4})")
iYearReg = re.compile(r"iyr:(\d{4})")
eYearReg = re.compile(r"eyr:(\d{4})")
hColorReg = re.compile(r"hcl:(\w{1,}|[#|0-9|a-f]{1,})")
eColorReg = re.compile(r"ecl:(\w{1,}|[#|0-9|a-f]{1,})")
CID = re.compile(r"cid:(\d{1,})") # <------ set length?
PID = re.compile(r"pid:([{\d{1,}}|#])") # <------ set length?





def makePass(data):
    global heigthReg
    global bYearReg 
    global iYearReg 
    global eYearReg 
    global hColorReg
    global eColorReg
    global CID
    global PID
    # to not recompile

    out = passport()
    out.OG = data

    for i in range(8):

        if(i == 0): curr = PID
        elif(i == 1): curr = CID
        elif(i == 2): curr = eColorReg
        elif(i == 3): curr = hColorReg
        elif(i == 4): curr = eYearReg
        elif(i == 5): curr = iYearReg
        elif(i == 6): curr = bYearReg
        elif(i == 7): curr = heigthReg

        res = curr.search(data)

        if(res == None):
            continue

        if(i == 0): out.PID = res.group(1)
        elif(i == 1): out.CID = res.group(1)
        elif(i == 2): out.eyeColor = res.group(1)
        elif(i == 3): out.hairColor = res.group(1)
        elif(i == 4): out.expirationYear = res.group(1)
        elif(i == 5): out.issueYear = res.group(1)
        elif(i == 6): out.birthYear = res.group(1)
        elif(i == 7): out.height = res.group(1)

    return out;

if __name__ == "__main__":
    data = None
    isValid = 0

    with open("data","r") as file:
        data = file.read()
        data = data.split("\n\n")

    

    for passStr in data:
        passStr = makePass(passStr)

        if(passStr.isValid() == "GOOD"):
            isValid += 1
        else:
            print(passStr)
            print()
            print(passStr.OG)
            print("########################")

    
    print("%s valid passports" % isValid)