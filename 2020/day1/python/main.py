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

for nr1 in bigData:
    for nr2 in smallData:
        s = nr1+nr2
        print("%s+%s=%s" % (nr1,nr2,s))
        if(s == 2020):
            print("Found it!!!")
            print("%s+%s=%s" % (nr1,nr2,s))
            print("%s*%s=%s" % (nr1,nr2,nr1*nr2))
            exit()
        elif(s > 2020):
            break