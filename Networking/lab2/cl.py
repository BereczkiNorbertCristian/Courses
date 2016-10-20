import socket

s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
addrTo="127.0.0.1"
while(1):
	sender=str(raw_input("Give something:"))
	s.sendto(sender,(addrTo,4444))
	print(s.recvfrom(200))

