import socket
import threading
import sys

BUFFSIZE = 1024

QUEUE_LIMIT = 5


def main():
    if len(sys.argv) < 2 or len(sys.argv) >2:
        usage()
    else:
        server()

def usage():
    sys.stdout = sys.stderr
    print('Usage: python server.py [portno]')
    sys.exit(2)

def server():
    # multi-client thread
    class ClientThread(threading.Thread):
        def __init__(self, ip, port, clientsocket):
            threading.Thread.__init__(self)
            self.ip = ip
            self.port = port
            self.csocket = clientsocket

        def run(self):
            print("Connect: "+ip+":"+str(port))

            while True:
                data = self.csocket.recv(BUFFSIZE)
                if len(data) == 0:
                    break
                print("Message from [%s, %s]: %s" % (self.ip, str(self.port), data))
                self.csocket.send(data)
                print("Message to [%s, %s]: %s" % (self.ip, str(self.port), data))


            print("Disconnect: "+self.ip+":"+str(self.port))

    # host = "127.0.0.1"
    port = eval(sys.argv[1])

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    s.bind(('', port))
    print("Binding to port: " + str(port))


    print("Listening...")
    while True:
        s.listen(QUEUE_LIMIT)
        
        (clientsock, (ip, port)) = s.accept()
        
        # create thread for incoming client
        newthread = ClientThread(ip, port, clientsock)
        newthread.start()

main()
