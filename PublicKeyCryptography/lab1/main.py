
from tkinter import *
import string
import tkinter.messagebox
from myfunctions import *

ALPH_LEN = 27

def getText(entry):
	return entry.get("1.0",END).strip()

def validateKey(key):

	if not key == key.upper():
		raise Exception("Key is not in upper characters!")
	n = len(key)
	if n != ALPH_LEN:
		raise Exception("Size not good!")
	st = []
	for i in range(0,n):
		if key[i] in st:
			raise Exception("Duplicated element in key!") 
		if (key[i]>="A" and key[i]<="Z") or key[i]=="_":
			ccc = 0
		else:
			raise Exception("Invalid keys inserted")
		st.append(key[i])

def computeEnKey(enKey):

	alf = "_" + string.ascii_uppercase
	n = len(enKey)
	ret = {}
	for i in range(0,n):
		ret[alf[i]] = enKey[i]
	return ret	

def validateText(itext):
	
	text = itext.upper()
	n = len(text)
	for i in range(0,n):
		if (not (text[i]>="A" and text[i]<="Z")) and (not text[i]=="_"):
			raise Exception("Invalid characters introduced!")

def doEncrypt():
	
	print("Encrypting...")

	global entryPlainText
	global entryEncryptionKey
	global entryCypherText	

	plainText = getText(entryPlainText)
	enKey = entryEncryptionKey.get()
	
	try:
		validateKey(enKey)
		validateText(plainText)
	except Exception as e:
		tkinter.messagebox.showinfo("Invalid Key!",str(e))
		return

	computedKey = computeEnKey(enKey)

	entryCypherText.delete("1.0",END)
	entryCypherText.insert(END,encrypt(plainText.upper(),computedKey))

	print("Done encrypting...")

def validateCypherText(ctext):

	if not ctext.upper() == ctext:
		raise Exception("Cypher text is not in upper format")

def doDecrypt():
	
	print("Decrypting...")

	global entryPlainText
	global entryCypherText
	global entryEncryptionKey
	
	cypherText = getText(entryCypherText)
	enKey = entryEncryptionKey.get()
	try:
		validateKey(enKey)
		validateCypherText(cypherText)
		validateText(cypherText)
	except Exception as e:
		tkinter.messagebox.showinfo("Invalid Input!",str(e))
		return
	
	computedKey = computeEnKey(enKey)
	
	entryPlainText.delete("1.0",END)
	entryPlainText.insert(END,decrypt(cypherText,computedKey).lower())

	print("Done dercyption...")
#PPP



root = Tk()

labelPlainText = Label(root,text="Plain Text: ")
labelCypherText = Label(root,text = "Cypher Text: ")
labelEncryptionKey = Label(root,text = "Encryption Key: ")

entryPlainText = Text(root,height=10,width=100)
entryCypherText = Text(root,height=10,width=100)
entryEncryptionKey = Entry(root)

entryPlainText.insert(END,"second_example")
entryEncryptionKey.insert(END,"PYNWLZTXRVUOSMQFJDHBK_ICGAE")

labelPlainText.grid(row=0,column=0)
labelCypherText.grid(row=1,column=0)
labelEncryptionKey.grid(row=2,column=0)

entryPlainText.grid(row=0,column=1)
entryCypherText.grid(row=1,column=1)
entryEncryptionKey.grid(row=2,column=1)

buttonEncrypt = Button(root, text="Encrypt",command=doEncrypt)
buttonDecrypt = Button(root, text="Decrypt",command=doDecrypt)

buttonEncrypt.grid(row=3,column=0)
buttonDecrypt.grid(row=3,column=1)

root.mainloop()

#PPP


