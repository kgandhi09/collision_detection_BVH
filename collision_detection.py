import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# print(socket.gethostname())
s.connect(('', 5556))
# s.bin


msg = s.recv(1024)
msg.decode('utf-8')

print(msg)