from copy import deepcopy

people = ["Mr. Adams", "Mrs. Barber", "Mr. Cox", "Miss Duke", "Miss Evans"]
dogs = ["beagle", "collie", "dachshund", "poodle", "retriever"]

pairs = []
for p in people:
    for d in dogs:
        pairs.append([p, d, list(range(1, 6))])


# -------------------------------- RESTRICTIONS -------------------------------

# each function
# returns True if restriction is violated
# returns False otherwise

def restriction1(p, d, v):
    if p == "Mr. Cox" or p == "Miss Duke":
        return v not in [1, 5]
    else:
        return v not in [2, 3, 4]


def restriction2(p, d, v):
    if d != "retriever":
        return False
    if not ("Miss" in p or "Mrs." in p):
        return True
    return False


def restriction3(p, d, v):
    if d != "collie":
        return v == 3
    else:
        return v != 3


def restriction4(p, d, v):
    if d == "poodle" and p == "Miss Duke":
        return True
    return False


def restriction5(p, d, v):
    if d != "dachshund":
        return False
    if not ("Miss" in p or "Mrs." in p):
        return True
    return False

def restriction6(p, d, v):
    if d != "retriever": return False
    # should be retriever
    return v not in [2,4]

def restriction7(p, d, v):
    if d != "beagle": return False
    # should be beagle
    return v not in [1,5]

# -------------------------------- MAIN --------------------------------------


unary_restrictions = [
    restriction1,
    restriction2,
    restriction3,
    restriction4,
    restriction5,
    restriction6,
    restriction7,
]


# _____________________ ENFORCE NODE CONSISTENCY ________________________

nodes = []
for p, d, vals in pairs:
    new_vals = []
    for val in vals:
        violates = False
        for restriction in unary_restrictions:
            violates = violates or restriction(p, d, val)

        if not violates:
            new_vals.append(val)
    if len(new_vals) > 0:
        nodes.append([p, d, new_vals])

print(nodes)

# _____________________ PRINT NODES _____________________ 

for node in nodes:
    p, d, vals = node
    if len(vals) > 0:
        print("values:")
        print(vals)
        for val in vals:
            print(f"person: {p} -> dog: {d}, index: {val}")

# _____________________ BACKTRACKING ____________________

def linearize(nodes):
    linearized = []
    for p,d,vals in nodes:
        for v in vals:
            linearized.append([p,d,v])
    return linearized

def check(L):
    ps = [p for p,d,v in L]
    ds = [d for p,d,v in L]
    vs = [v for p,d,v in L]

    return (
            len(ps) == len(set(ps)) and
            len(ds) == len(set(ds)) and
            len(vs) == len(set(vs))
            )

candidates = linearize(nodes)
sols = []

print(candidates)

def back(L):
    global candidates
    
    if len(L) == 5:
        sols.append(deepcopy(L))
        return

    for candidate in candidates:
        L.append(candidate)
        if check(L):
            back(L)
        L.pop()

back([])

print(len(sols))
print(sols[1])
