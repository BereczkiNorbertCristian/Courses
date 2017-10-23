
import random

digs = [1,2,3,4,6,10,13,15]
howMany = [4,5,10,15,20,20,20,20]

print(sum(howMany))

for i in range(0,8):
	d = digs[i]
	n = howMany[i]
	for j in range(0,n):
		toPut1 = random.randint(10**(d-1),10**(d))
		toPut2 = random.randint(10**(d-1),10**(d))
		putter = str(toPut1) + " " + str(toPut2)
		print(putter)



