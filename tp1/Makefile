INC := include
CFLAGS := -pg -Wall -c -I$(INC)
OBJS := obj/main.o obj/functions.o obj/Hand.o obj/erro.o obj/player.o
SRC := src
EXE := bin/main


all: bin
	$(EXE) entrada.txt saida.txt
	# gprof $(EXE) gmon.out > teste.txt

bin: $(EXE)

$(EXE): $(OBJS)
	g++ -pg -o $(EXE) $(OBJS)

obj/main.o: $(SRC)/main.cpp 
	g++ $(CFLAGS) -o $@ $(SRC)/main.cpp

obj/functions.o: $(SRC)/functions.cpp
	g++ $(CFLAGS) -o $@ $(SRC)/functions.cpp

obj/player.o: $(SRC)/player.cpp
	g++ $(CFLAGS) -o $@ $(SRC)/player.cpp

obj/Hand.o: $(SRC)/Hand.cpp
	g++ $(CFLAGS) -o $@ $(SRC)/Hand.cpp

obj/erro.o: $(SRC)/erro.cpp
	g++ $(CFLAGS) -o $@ $(SRC)/erro.cpp

.PHONY: clean
clean:
	rm -f $(OBJS) gmon.out $(EXE)

