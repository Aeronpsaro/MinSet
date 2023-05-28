CC		= gcc
CCFLAGS		= -O1
DEBUGFLAGS	= -O0 -g3 -Warray-bounds -Wformat-overflow -Wstringop-overflow -Wstringop-overread
CCFLAGS = $(DEBUGFLAGS)
BUILD		= build
BIN		= bin
SRC		= src

.PHONY:run clean

run: all clean
	./$(BIN)/MinConj

clean:
	rm $(BUILD)/*.o

all: $(BUILD)/ReadWords.o $(BUILD)/PrintUtils.o $(BUILD)/GetCore.o $(BUILD)/MinSet.o $(BUILD)/StringSet.o $(BUILD)/Expand.o
	$(CC) $(CCFLAGS) $(SRC)/Main.c deps/templated-hashmap/hashmap.o $(BUILD)/*.o -o $(BIN)/MinConj

$(BUILD)/Expand.o: $(SRC)/Expand.c $(BUILD)/Node.o $(BUILD)/StringSet.o
	$(CC) $(CCFLAGS) -c $(SRC)/Expand.c deps/templated-hashmap/hashmap.o $(BUILD)/Node.o $(BUILD)/StringSet.o -o $(BUILD)/Expand.o

$(BUILD)/PrintUtils.o: $(SRC)/PrintUtils.c
	$(CC) $(CCFLAGS) -c $(SRC)/PrintUtils.c -o $(BUILD)/PrintUtils.o

$(BUILD)/ReadWords.o: $(SRC)/ReadWords.c $(BUILD)/StringSet.o $(BUILD)/Node.o
	$(CC) $(CCFLAGS) -c $(SRC)/ReadWords.c deps/templated-hashmap/hashmap.o $(BUILD)/Node.o $(BUILD)/StringSet.o -o $(BUILD)/ReadWords.o

$(BUILD)/GetCore.o: $(SRC)/GetCore.c $(BUILD)/Node.o
	$(CC) $(CCFLAGS) -c $(SRC)/GetCore.c deps/templated-hashmap/hashmap.o $(BUILD)/Node.o -o $(BUILD)/GetCore.o

$(BUILD)/MinSet.o: $(SRC)/MinSet.c $(BUILD)/Node.o
	$(CC) $(CCFLAGS) -c $(SRC)/MinSet.c deps/templated-hashmap/hashmap.o $(BUILD)/Node.o -o $(BUILD)/MinSet.o

$(BUILD)/Node.o: $(SRC)/Node.c
	$(CC) $(CCFLAGS) -c $(SRC)/Node.c deps/templated-hashmap/hashmap.o -o $(BUILD)/Node.o

$(BUILD)/StringSet.o: $(SRC)/StringSet.c
	$(CC) $(CCFLAGS) -c $(SRC)/StringSet.c -o $(BUILD)/StringSet.o
