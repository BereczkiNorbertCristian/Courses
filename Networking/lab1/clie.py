#TCP client
import socket
from threading import Thread
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect(("172.30.119.50",6666))
s.send("hey")

def client_receiver() :

	while 1 :
		print(s.recv(100))

def client_sender() :

	while 1 :
		tosend=str(raw_input())
		s.send(tosend)

def client_listener() :
	th = Thread(target=client_receiver)
	th1 = Thread(target=client_sender)
	th.start()
	th1.start()

	while 1 :
		continue

client_listener()
