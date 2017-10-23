
import string

def encrypt(plainText,encryptionKey):

	print(plainText)
	print(encryptionKey)

	n = len(plainText)
	res = ["0"]*n
	for i in range(0,n):
		res[i]=encryptionKey[plainText[i]]
	return "".join(res)

def getDecryptionKey(encryptionKey):
	
	res = {}
	for k in encryptionKey.keys():
		res[encryptionKey[k]] = k
	printDecr(res)
	return res

def printDecr(decrKey):

	ans = ""
	alph = "_" + string.ascii_uppercase
	for i in range(0,27):
		ans += decrKey[alph[i]]
	print(ans)

def decrypt(cypherText,encryptionKey):
	
	decryptionKey = getDecryptionKey(encryptionKey)
	n = len(cypherText)
	res = ["0"]*n	
	for i in range(0,n):
		res[i] = decryptionKey[cypherText[i]]
	return "".join(res)


