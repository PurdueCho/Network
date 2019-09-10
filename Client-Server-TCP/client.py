import socket
import sys

isRunning = False

BUFSIZE = 1024

def main():
    if len(sys.argv) < 3 or len(sys.argv) > 3:
        usage()
    else:
        client()

def usage():
    sys.stdout = sys.stderr
    print('Usage: python client.py [serverIP] [serverPort]')
    sys.exit(2)

def client():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    host = sys.argv[1]
    port = eval(sys.argv[2])

    try:
        s.connect((host, port))
    except Exception as e:
        print("Connection Error")
        sys.exit(2)

    print("Connect to "+host+":"+str(port))
    print("Client is ready!")
    print("Enter :exit to close the connection.")

    isRunning = True

    while isRunning:
        msg = sys.stdin.readline()

        if not msg:
            break

        msg = msg.replace('\n', '')
     
        sent = s.send(msg.encode())

        if sent == 0:
            print("socket connection broken")
            break
        
        if msg == ':exit':
            print("Exit")
            break

        chunks = []
        bytes_cnt = 0
        while bytes_cnt < sent:
            chunk = s.recv(BUFSIZE)
            if chunk == b'':
                isRunning = False
                print("read error")
                break
            chunks.append(chunk)
            bytes_cnt = bytes_cnt + len(chunk)

        data = b''.join(chunks)

        print('Echo message: {}'.format(data))

    s.close()
    print('bye')

if __name__ == "__main__":
   main()
