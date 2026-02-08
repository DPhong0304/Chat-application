CC = g++

FLAGS = 

TARGET = chatapp

FILES = Chatapp.cpp main.cpp StreamSocket.cpp

$(TARGET) : $(FILES)
	$(CC) $(FLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)