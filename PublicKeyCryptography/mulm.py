

def mulmod(x,exp,md):

	res = 1
	for i in range(0,exp):
		res = (res * x)%md
	return res
