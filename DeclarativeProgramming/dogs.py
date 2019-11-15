from itertools import permutations

people = ["Mr. Adams", "Mrs. Barber", "Mr. Cox", "Miss Duke", "Miss Evans"]
dogs = ["beagle", "collie", "dachshund", "poodle", "retriever"]

# ------------------- RESTRICTION FUNCTIONS ------------------

def is_owner_woman(dog, p_perm, d_perm):
    prefixes = ["Mrs.", "Miss"]
    p_idx = d_perm.index(dog)
    for pref in prefixes:
        if pref in p_perm[p_idx]:
            return True
    return False

def restriction1(p_perm, d_perm):
    for i in [0, 4]:
        if p_perm[i] not in ["Mr. Cox", "Miss Duke"]: return False
    return True

def restriction2(p_perm, d_perm):
    return is_owner_woman("retriever", p_perm, d_perm)

def restriction3(p_perm, d_perm):
    return 2 == d_perm.index("collie")

def restriction4(p_perm, d_perm):
    return p_perm.index("Miss Duke") != d_perm.index("poodle")

def restriction5(p_perm, d_perm):
    return is_owner_woman("dachshund", p_perm, d_perm)

def restriction6(p_perm, d_perm):
    restriction_dogs_subset = ["collie", "beagle"]
    retriever_idx = d_perm.index("retriever")
    if retriever_idx == 0 or retriever_idx == 4: return False
    for adder in [-1,1]:
        if d_perm[retriever_idx+adder] not in restriction_dogs_subset: return False
    return True

# ------------------- MAIN FUNCTIONS -------------------------

RESTRICTIONS = [
        restriction1,
        restriction2,
        restriction3,
        restriction4,
        restriction5, 
        restriction6,
]

def check_solution(people_perm, dogs_perm):
    global RESTRICTIONS
    for restriction in RESTRICTIONS:
        if not restriction(people_perm, dogs_perm): return False
    return True

found = False 

for people_perm in permutations(people):
    if found: break
    for dogs_perm in permutations(dogs):
        if found: break
        if check_solution(people_perm, dogs_perm):
            print(people_perm)
            print(dogs_perm)
            found = True

if found: print("Solution was found!")
else: print("No solution was found!")



