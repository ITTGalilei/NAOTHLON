class MyClass(GeneratedClass):
    def __init__(self):
        GeneratedClass.__init__(self)

    def onLoad(self):
        #put initialization code here
        pass

    def onUnload(self):
        #put clean-up code here
        pass

    def onInput_onStart(self):
        #self.onStopped() #activate the output of the box
        import socket

        # get the hostname
        host = socket.gethostname()
        port = 7070  # initiate port no above 1024

        server_socket = socket.socket()  # get instance
        # look closely. The bind() function takes tuple as argument
        server_socket.bind(("127.0.0.1", 7070))  # bind host address and port together

        # configure how many client the server can listen simultaneously
        server_socket.listen(5)
        conn, address = server_socket.accept()  # accept new connection
        self.logger.info("Connection from: " + str(address))
        while True:
            # receive data stream. it won't accept data packet greater than 1024 bytes
            data = conn.recv(1024).decode()
            if not data:
                # if data is not received break
                break
            self.logger.info("****** RICEVUTO DATI  ********")
            self.logger.info("from connected user: " + str(data))
            tmp=data
            data= "Server: Ho ricevuto --> "
            data +=str(tmp)
            #self.tts=ALProxy("ALTextToSpeech")
            #self.tts.say("Hello, world!")
            conn.send(data.encode())  # send data to the client
        conn.close()  # close the connection
        server_socket.close()
        self.logger.info("connection close")
        self.onStopped()
        pass

    def onInput_onStop(self):
        self.onUnload() #it is recommended to reuse the clean-up as the box is stopped
        self.onStopped() #activate the output of the box