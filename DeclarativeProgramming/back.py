
from copy import deepcopy

people = ["Mr. Adams", "Mrs. Barber", "Mr. Cox", "Miss Duke", "Miss Evans"]
dogs = ["beagle", "collie", "dachshund", "poodle", "retriever"]


nodes = []
for p in people:
    for d in dogs:
        nodes.append([p,d])

# --------------------------- RESTRICTIONS --------------------------

# restriction returns true if restriction is respected

def restriction1(L):
    if len(L) == 0: return True
    p,d = L[0]
    if p not in ["Mr. Cox", "Miss Duke"]:
        return False
    
    if len(L) < 5: return True
    p,d = L[4]
    return p in ["Mr. Cox", "Miss Duke"]

def restriction2(L):
    for p,d in L:
        if d == "retriever" and "Mrs." not in p and "Miss" not in p:
            return False
    return True

def restriction3(L):
    if len(L) < 3:
        return True
    p,d = L[2]
    if d == "collie":
        return True
    else:
        return False

def restriction4(L):
    for p,d in L:
        if p == "Mrs. Duke" and d == "poodle":
            return False
    return True

def restriction5(L):
    for p,d in L:
        if d == "dachshund" and "Mrs." not in p and "Miss" not in p:
            return False
    return True

def restriction6(L):
    if "retriever" not in L: return True
    ds = [d for p,d in L]

    idx = ds.index("retriever")
    return idx in [1,3]

def restriction7(L):
    if "beagle" not in L: return True
    ds = [d for p,d in L]

    idx = ds.index("beagle")
    return idx in [0,4]

def additional_restriction(L):
    # should be len == 5
    
    ds = [d for p,d in L]
    idx_r = ds.index("retriever")
    idx_c = ds.index("collie")
    idx_b = ds.index("beagle")

    return abs(idx_r - idx_b) == 1 and abs(idx_r - idx_c) == 1
    

def check_same(L):
    ps = [l[0] for l in L]
    ds = [l[1] for l in L]
    return len(ps) == len(set(ps)) and len(ds) == len(set(ds))

RESTRICTIONS = [
        restriction1,
        restriction2,
        restriction3,
        restriction4,
        restriction5,
        restriction6,
        restriction7,
        ]

def check(L):
    global RESTRICIONS
    if not check_same(L):
        return False
    is_ok = True
    for restriction in RESTRICTIONS:
        is_ok = is_ok and restriction(L)
    return is_ok

# --------------------------- MAIN ---------------------------

L = []

sols = []

def back(L):
    global nodes
    if len(L) == 5:
        if check(L) and additional_restriction(L):
            sols.append(deepcopy(L))
        return

    for node in nodes:
        L.append(node)
        if check(L):
            back(L)
        L.pop()

back([])

print("Number of solutions:")
print(len(sols))
print(sols)


