INC=./includes
SRC=./src
OUT=./bin

$(OUT)/lab: $(OUT)/main.o $(OUT)/std.o $(OUT)/child.o $(OUT)/pipe.o $(OUT)/posix.o
	gcc -o $(OUT)/lab $(OUT)/main.o $(OUT)/std.o $(OUT)/child.o $(OUT)/pipe.o $(OUT)/posix.o

$(OUT)/main.o: $(SRC)/main.c $(INC)/lab1.h
	gcc -I$(INC) -o $(OUT)/main.o -c $(SRC)/main.c

$(OUT)/std.o: $(SRC)/std.c $(INC)/lab1.h
	gcc -I$(INC) -o $(OUT)/std.o -c $(SRC)/std.c

$(OUT)/child.o: $(SRC)/child.c $(INC)/lab1.h
	gcc -I$(INC) -o $(OUT)/child.o -c $(SRC)/child.c

$(OUT)/pipe.o: $(SRC)/pipe.c $(INC)/lab1.h
	gcc -I$(INC) -o $(OUT)/pipe.o -c $(SRC)/pipe.c

$(OUT)/posix.o: $(SRC)/posix.c $(INC)/lab1.h
	gcc -I$(INC) -o $(OUT)/posix.o -c $(SRC)/posix.c

clean:
	rm $(OUT)/*.o $(OUT)/lab
