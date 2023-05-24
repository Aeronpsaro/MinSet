CC		= gcc
DEBUGFLAGS	= -O0 -g3 -Warray-bounds -Wformat-overflow -Wstringop-overflow -Wstringop-overread
CCFLAGS		= -O1
BUILD		= build
BIN		= bin
SRC		= src

.PHONY:run clean

run: all clean
	./$(BIN)/MinConj

clean:
	rm $(BUILD)/*.o

all: $(BUILD)/ReadWords.o $(BUILD)/PrintUtils.o $(BUILD)/GetCore.o $(BUILD)/MinSet.o $(BUILD)/StringSet.o
	$(CC) $(DEBUGFLAGS) $(SRC)/Main.c deps/templated-hashmap/hashmap.o $(BUILD)/*.o -o $(BIN)/MinConj

$(BUILD)/PrintUtils.o: $(SRC)/PrintUtils.c
	$(CC) $(DEBUGFLAGS) -c $(SRC)/PrintUtils.c -o $(BUILD)/PrintUtils.o

$(BUILD)/ReadWords.o: $(SRC)/ReadWords.c $(BUILD)/StringSet.o $(BUILD)/Node.o
	$(CC) $(DEBUGFLAGS) -c $(SRC)/ReadWords.c deps/templated-hashmap/hashmap.o $(BUILD)/Node.o $(BUILD)/StringSet.o -o $(BUILD)/ReadWords.o

$(BUILD)/GetCore.o: $(SRC)/GetCore.c $(BUILD)/Node.o
	$(CC) $(DEBUGFLAGS) -c $(SRC)/GetCore.c deps/templated-hashmap/hashmap.o $(BUILD)/Node.o -o $(BUILD)/GetCore.o

$(BUILD)/MinSet.o: $(SRC)/MinSet.c $(BUILD)/Node.o
	$(CC) $(DEBUGFLAGS) -c $(SRC)/MinSet.c deps/templated-hashmap/hashmap.o $(BUILD)/Node.o -o $(BUILD)/MinSet.o

$(BUILD)/Node.o: $(SRC)/Node.c
	$(CC) $(DEBUGFLAGS) -c $(SRC)/Node.c deps/templated-hashmap/hashmap.o -o $(BUILD)/Node.o

$(BUILD)/StringSet.o: $(SRC)/StringSet.c
	$(CC) $(DEBUGFLAGS) -c $(SRC)/StringSet.c -o $(BUILD)/StringSet.o
