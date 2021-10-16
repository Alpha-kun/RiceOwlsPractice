mp = dict()
flag = False
F = []
I = []

while True:
    try :
        line = input()
        if line == "":
            flag = True
        elif flag:
            info = line.split("_")
            file = "_".join(info[:-2:])
            if file in mp:
                mp[file] = True
            else:
                F.append(line)
        else:
            mp[line] = False
    except EOFError:
        break
for it in mp.keys():
    if mp[it] == False:
        I.append(it)
I.sort()
F.sort()
if len(I) == 0 and len(F) == 0:
    print("No mismatches.")
else:
    for f in F:
        print("F {}".format(f))
    for i in I:
        print("I {}".format(i))