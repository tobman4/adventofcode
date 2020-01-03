import os;
path = os.path.realpath(__file__);

path = path.split("/");
path = path[:len(path)-1]
path = "/".join(path);


with open(path + "/../data") as file:
    data = file.read();
    print(data);
    pass;