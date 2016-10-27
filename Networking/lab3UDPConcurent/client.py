import socket
import random
import time

s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
addrTo="172.30.112.189"
portTo=5454
random.seed(None)
time.sleep(random.randint(1,8))
s.sendto(str("Connected#"),(addrTo,portTo))

newPort,other=s.recvfrom(200)
newIntPort=int(newPort)
s.sendto(str(123)+"#",(addrTo,newIntPort))
s.sendto(str(453)+"#",(addrTo,newIntPort))

print(s.recvfrom(200))

