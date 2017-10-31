
def mulmod(n,exp,md):
	res = 1
	for i in range(0,exp):
		res = (res * n)%md
	return res

def gcd(a,b):

	if b < a :
		aux = b
		b = a
		a = aux
	for i in range(2,a):
		if a%i ==0 and b%i == 0:
			return False
	return True
