
from queue import Queue
from threading import Thread


def add(begIdx,endIdx,res):

	if begIdx == endIdx :
		x = numbers[begIdx]
		while x!=0:
			toPut = x%10
			res.put(toPut)
			x//=10
		res.put(None)
		return

	mid = (begIdx + endIdx) >> 1;
	q1 = Queue()
	q2 = Queue()
	t1 = Thread(target=add,args=(begIdx,mid,q1))
	t2 = Thread(target=add,args=(mid+1,endIdx,q2))
	t1.start()
	t2.start()

	x1 = q1.get()
	x2 = q2.get()
	carry = 0
	while True :
		if x1 == None and x2 == None:
			t1.join()
			t2.join()
			if carry != 0:
				res.put(carry)
			res.put(None)
			break 
		add1 = 0
		add2 = 0
		if x1 != None:
			add1 = x1
			x1 = q1.get()
		if x2 != None:
			add2 = x2
			x2 = q2.get()
		ans = (carry + add1 + add2) % 10
		carry = (carry + add1 + add2) // 10
		res.put(ans)


def main():

	global numbers
	numbers = [1234567891011,1234567891011,1234567891011,1234567891011,1234567891011,1234567891011,1234567891011,1234567891011,1234567891011]

	size_n = len(numbers)

	res = Queue()
	add(0,size_n-1,res)
	ans = 0
	cnt = 0
	p = 1
	while not res.empty():
		x = res.get()
		if x!= None : ans += p*x
		p *= 10
	print(ans)

main()
