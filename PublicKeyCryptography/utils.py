
def inv(x,n):

	for i in range(1,n):
		if (x*i)%n == 1:
			return i

def powmod(x,exp,n):

	res = 1
	idx = 0
	while exp > 0:
		if exp%2 == 1:
			res=(res*x)%n
			print(str(idx) + "_" + str(x))
		aux= (x*x)%n
		x = aux
		exp= exp//2
		idx+=1
	return res

e = 1453
n = 2201

def check():

	miu = 30 * 70
	e = 1453
	lst = []
	for i in range(1,e+1):
		if miu%i ==0 and e%i == 0:
			lst.append(i)

	print(lst)

print("-------------")
#print(inv(e,n))
#print("FIRST")
#print(powmod(2115,1717,2201))
print("SECOND")
print(powmod(336,1717,2201))

