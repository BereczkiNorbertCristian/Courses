
import matplotlib.pyplot as plt
import numpy as np
import sys

filename = sys.argv[1]

hsSum = {}
hsNo = {}
with open(filename,"r") as f:
	for line in f:
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
plt.title('GCD by euclid')
plt.xlabel('Number of digits')
plt.ylabel('Average time of gcd')
plt.savefig("GCDeuclid.png")
plt.show()








