import numpy as np
import threading
import time

n=k=m=0
a=b=0
nworkers = 0
res = 0
def readInput():
	global n
	global k
	global m
	global nworkers

	n=int(input("Give N: "))
	k=int(input("Give K: "))
	m=int(input("Give M: "))
	nworkers=int(input("Give number of workers: "))

def initAll():

	global a	
	global b
	global res

	a=np.random.randint(20,size=(n,k))
	b=np.random.randint(20,size=(k,m))

	res=np.zeros((n,m))

	print(a.shape)

def do_dot(row, end):
	global a
	global b
	global res

	res[row:end]=np.dot(a[row:end],b)

def doOneThread():
	global n

	start=time.time()
	do_dot(0,n)
	end=time.time()
	print("1 thread: %s" % str(end-start))

def doMoreThreads():
	global nworkers
	global n
	
	start=time.time()
	threads = []

	for i in range(0, n,int(n/nworkers)):
		th=threading.Thread(target=do_dot, args=(i,int(min(i+n/nworkers+1,n))))
		threads.append(th)
		th.start()
	for th in threads:
		th.join()
	end=time.time()
	print(str(nworkers)+" threads: %s" % str(end-start))

readInput()
initAll()
doOneThread()
doMoreThreads()
if n < 5 and m < 5 and k < 5:
	print(res)

