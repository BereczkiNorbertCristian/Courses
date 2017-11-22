
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
			print(str(idx) + "_" + str(res) + "_" + str(x))
		aux= (x*x)%n
		x = aux
		exp= exp//2
		idx+=1
	return res

def powmod2(x,exp,n):

	res = 1
	idx = 0
	while exp > 0:
		if exp%2 == 1:
			res=(res*x)%n
		aux= (x*x)%n
		x = aux
		exp= exp//2
		idx+=1
	return res

e = 1453
n = 2201

def normalpow(x,exp,n):
	res = 1
	for i in range(0,exp):
		res = (res * x) % n
	return res	

def check():

	miu = 30 * 70
	e = 1453
	lst = []
	for i in range(1,e+1):
		if miu%i ==0 and e%i == 0:
			lst.append(i)

	print(lst)

#print("-------------")
#print(inv(e,n))
#print("FIRST")
#print(powmod(2115,1717,2201))
#print("SECOND")
#print(powmod(336,1717,2201))



pww = 2
md = 247
s = 123

for i in range(2,md):
	if md%i == 0:
		print("YESSSSSSS" + str(i))

print(powmod(2,s,md))

print(normalpow(pww,s,md))
print(powmod2(pww,s,md))

print(normalpow(pww,2*s,md))
print(powmod2(pww,2*s,md))


