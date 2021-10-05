import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# print(socket.gethostname())
s.connect(('', 5556))

# while True:
#     msg = s.recv(1024)
#     msg.decode('utf-8')

#     print(msg)

full_msg = ''
while True:
    msg = s.recv(8)
    if len(msg) <= 0:
        break
    full_msg += msg.decode("utf-8")

    print(full_msg)