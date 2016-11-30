CC= g++
FLAGS= -Wall -std=c++11
SFML_LIBS= -lsfml-window -lsfml-graphics -lsfml-system
EXEC_NAME= slideshooter

all:
	$(CC) main.cpp -o $(EXEC_NAME) $(FLAGS) $(SFML_LIBS)
