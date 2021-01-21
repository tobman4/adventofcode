import os;
import re;
path = os.path.realpath(__file__);

path = path.split("/");
path = path[:len(path)-1]
path = "/".join(path);

class wire:
    def __init__(self):
        self.pos = {
            "X": 0,
            "Y": 0
        }
        self.log = [];
        pass;
    
    def step(self,s):
        group = re.findall("(U|R|D|L)([0-9]{,9})",s);
        dir = group[0][0];
        length = int(group[0][1]);
        l = [[self.pos["X"],self.pos["Y"]]];
        if(dir == "U"):
            self.pos["Y"] += length
        elif(dir == "R"):
            self.pos["Y"] += length
        elif(dir == "D"):
            self.pos["Y"] -= length
        elif(dir == "L"):
            self.pos["X"] -= length
        l.append([self.pos["X"],self.pos["Y"]]);
        self.log.append(l);
        return;




    def get_pos(self):
        return self.pos;
        pass;
#black box
########################################################################
def line_intersection(line1, line2):
    xdiff = (line1[0][0] - line1[1][0], line2[0][0] - line2[1][0])
    ydiff = (line1[0][1] - line1[1][1], line2[0][1] - line2[1][1])

    def det(a, b):
        return a[0] * b[1] - a[1] * b[0]

    div = det(xdiff, ydiff)
    if div == 0:
       raise Exception('lines do not intersect')

    d = (det(*line1), det(*line2))
    x = det(d, xdiff) / div
    y = det(d, ydiff) / div
    return x, y

########################################################################

with open(path + "/../data_test") as file:
    data = file.read();
    data = data.split("\n");
    data[0] = data[0].split(",");
    data[1] = data[1].split(",");
    pass;

map = {};
pos = {
    "X": 0,
    "Y": 0
}

meet = [];

for step in data[0]:
    group = re.findall("(U|R|D|L)([0-9]{,9})",step);
    dir = group[0][0];
    length = int(group[0][1]);

    mod = 1;

    if(dir in "RD"):
        mod = -1;

    for i in range(length):
        
        tmp_pos = {
            "X": pos["X"],
            "Y": pos["Y"]
        }
        
        if(dir in "LR"):
            tmp_pos["X"] = pos["X"] + i*mod;
        else:
            tmp_pos["Y"] = pos["Y"] + i*mod;

        try:
            map[tmp_pos["X"]] == 1;
        except:
            map[tmp_pos["X"]] = {};

        try:
            map[tmp_pos["X"]][tmp_pos["Y"]] += 1;
        except:
            map[tmp_pos["X"]][tmp_pos["Y"]] = 1;
            pass;


    if(dir in "LR"):
        pos["X"] += i;
    else:
        pos["Y"] += i;

pos = {
    "X": 0,
    "Y": 0
}

for step in data[1]:
    group = re.findall("(U|R|D|L)([0-9]{,9})",step);
    dir = group[0][0];
    length = int(group[0][1]);

    mod = 1;

    if(dir in "RD"):
        mod = -1;

    for i in range(length):

        tmp_pos = {
            "X": pos["X"],
            "Y": pos["Y"]
        }

        if(dir in "LR"):
            tmp_pos["X"] = pos["X"] + i*mod;
        else:
            tmp_pos["Y"] = pos["Y"] + i*mod;

        try:
            if(map[tmp_pos["X"]][tmp_pos["Y"]] == 1):
                meet.append(tmp_pos);
        except:
            pass;
print(len(meet));