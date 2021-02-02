def loadData(DBG=False):
    if(DBG):
        path = "./data.DBG"
    else:
        path = "./data"
    
    f = open(path,"r")
    data = f.read()
    data = data.split("\n")

    return data


def splitRules(fullStr):
    sp = fullStr.split(": ");
    
    tar = sp[0].split(" ")[1]
    rangee = sp[0].split(" ")[0]

    tarMin = int(rangee.split("-")[0])
    tarMax = int(rangee.split("-")[1])

    return (tarMin,tarMax,tar,sp[1])   

def rule1(fullStr):

    (tarMin,tarMax,tar,pas) = splitRules(fullStr);

    count = pas.count(tar)

    if(count <= tarMax and count >= tarMin):
        return True
    else:
        return False

def rule2(fullStr):
    (A,B,tar,pas) = splitRules(fullStr);
    try:
        posA = pas[A-1] == tar
        posB = pas[B-1] == tar
        res = (posA and not posB) or (posB and not posA)
    except IndexError:
        res = False # <---- pass is to short and cant be valid
    except Exception as err:
        raise err
    finally:
        return res

if __name__ == "__main__":
    valid1 = 0
    valid2 = 0
    for passInfo in loadData(False):
        r1 = rule1(passInfo)
        r2 = rule2(passInfo)
        if(r1): valid1 += 1
        if(r2): valid2 += 1

    print("part 1 %s is valid" % valid1)
    print("part 2 %s is valid" % valid2)
