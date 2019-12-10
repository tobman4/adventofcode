from math import floor;

weights = None;
weigth_tot = 0;
modules = [];

with open("../modules") as module_list:
    weights = module_list.readlines();

# weights = ["1969"];

for weight in weights:
    modules.append(int(weight.replace("\n","")));
    weigth_tot += floor(int(weight.replace("\n",""))/3) - 2;

print("part 1: %s" % weigth_tot);


weigth_tot = 0;

for module in modules:
    req = max(floor(module/3) - 2,0);
    while req > 0:
        weigth_tot += req;
        req = max(floor(req/3) - 2, 0);

print("part 2: %s" % weigth_tot);