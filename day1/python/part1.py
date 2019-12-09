from math import floor;

weights = None;
weigth_tot = 0;

with open("../modules") as modules:
    weights = modules.readlines();

for weight in weights:
    weigth_tot += floor(int(weight.replace("\n",""))/3) - 2;

print(weigth_tot);