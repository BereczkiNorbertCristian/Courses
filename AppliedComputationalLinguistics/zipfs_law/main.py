

D = {}

with open("pb2_1_full.txt", "r") as f:
    itr = 0
    for line in f.readlines():
        elems = line.strip().split(' ')
        itr+=1
        s = elems[1].lower()
        if s not in D.keys():
            D[s] = 0
        D[s] += int(elems[0])

        if itr == 10: break

print(D)


