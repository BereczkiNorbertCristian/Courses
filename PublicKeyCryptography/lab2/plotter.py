
import matplotlib.pyplot as plt
import numpy as np
import sys

filename = "algo3/algo3.out"

hsSum = {}
hsNo = {}
counter = 0
with open(filename,"r") as f:
	for line in f:
		counter+=1
		key,val = line.split(" ")
		if key in hsSum.keys():
			hsSum[key]+= int(val)
			hsNo[key]+=1
		else:
			hsSum[key] = int(val)
			hsNo[key] = 1
arr = list(hsSum.keys())
res = []
sorted(arr)
for a in arr:
	res.append(hsSum[a]/hsNo[a])

plt.scatter(arr,res)
plt.title('GCD Euclid with large numbers')
plt.xlabel('Number of digits')
plt.ylabel('Average time of gcd')
plt.savefig("GCDEuclidManyBigger.png")
plt.show()








