CC = g++

FLAGS = 

TARGET = chatapp

TEST = ./testdir/test

FILES = Chatapp.cpp main.cpp StreamSocket.cpp

TESTFILES = StreamSocket.cpp  Chatapp.cpp ./testdir/test.cpp
 
$(TARGET) : $(FILES)
	$(CC) $(FLAGS) $(FILES) -o $(TARGET)

t: $(TEST)

$(TEST) : $(TESTFILES)
	$(CC) $(FLAGS) $(TESTFILES) -o $(TEST)

clean: 
	rm -f $(TARGET) $(TEST)
	$(MAKE)	cleanhist

cleanhist:
	: > ./history/.command_history
