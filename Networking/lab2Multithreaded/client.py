import socket
from threading import Thread

s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
addrTo="192.168.1.105"
portTo=4444

s.sendto(str("Connected#"),(addrTo,portTo))

exiCode=1

def client_receiver() :
	
	while(1):
		print(s.recvfrom(200))

def client_sender() :

	while(1):
		sender=str(raw_input("Write something:")+"#")
		s.sendto(sender,(addrTo,portTo))
		if sender == "exit" :
			exiCode=0

def client_listener() :

	th1=Thread(target=client_receiver)
	th2=Thread(target=client_sender)
	th1.start()
	th2.start()

	while exiCode == 1 :
		continue

client_listener()

