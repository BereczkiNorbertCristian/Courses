

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
	return res

def decrypt(cypherText,encryptionKey):
	
	decryptionKey = getDecryptionKey(encryptionKey)
	n = len(cypherText)
	res = ["0"]*n	
	for i in range(0,n):
		res[i] = decryptionKey[cypherText[i]]
	return "".join(res)


