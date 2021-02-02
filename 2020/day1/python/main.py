def loadData(DBG=False):
    if(DBG):
        path = "./data.DBG"
    else:
        path = "./data"
    
    f = open(path,"r")
    data = f.read()
    data = data.split("\n")

    data = [int(numeric_string) for numeric_string in data]

    data.sort()
    #data.reverse()

    return data

smallData = loadData()

bigData = smallData.copy()
bigData.reverse()

def part1():
    for nr1 in bigData:
        for nr2 in smallData:
            s = nr1+nr2
            if(s == 2020):
                print("Part 1:")
                print("%s+%s=%s" % (nr1,nr2,s))
                print("%s*%s=%s" % (nr1,nr2,nr1*nr2))
                return
            elif(s > 2020):
                break

def part2():
    for nr1 in bigData:
        for nr2 in smallData:
            if(nr1+nr2 >= 2020):
                break
            else:
                for nr3 in smallData:
                    s = nr1+nr2+nr3;
                    if(s == 2020):
                        print("part 2")
                        print("%s+%s+%s=%s" % (nr1,nr2,nr3,s))
                        print("%s*%s*%s=%s" % (nr1,nr2,nr3,(nr1*nr2*nr3)))
                        return


if __name__ == "__main__":
    part1()
    part2()