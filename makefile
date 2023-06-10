CC		= gcc
OPTFLAGS	= -O3 -march=native -mtune=native -flto -ffast-math
DEBUGFLAGS	= -O0 -g3 -Warray-bounds -Wformat-overflow -Wstringop-overflow -Wstringop-overread
PROFFLAGS	= -pg
CCFLAGS		= $(DEBUGFLAGS)
# CCFLAGS		= $(OPTFLAGS) $(PROFFLAGS)
BUILD		= build
BIN		= bin
SRC		= src
DEPS		= deps

.PHONY:run clean

run: all clean
	./$(BIN)/MinConj

clean:
	rm $(BUILD)/*.o

all: $(BUILD)/ReadWords.o $(BUILD)/PrintUtils.o $(BUILD)/GetCore.o $(BUILD)/MinSet.o $(BUILD)/StringSet.o $(BUILD)/Expand.o $(BUILD)/hashmap.o $(BUILD)/heap.o
	$(CC) $(CCFLAGS) $(SRC)/Main.c $(BUILD)/*.o -o $(BIN)/MinConj

$(BUILD)/Expand.o: $(SRC)/Expand.c $(BUILD)/Node.o $(BUILD)/StringSet.o
	$(CC) $(CCFLAGS) -c $(SRC)/Expand.c -o $(BUILD)/Expand.o

$(BUILD)/PrintUtils.o: $(SRC)/PrintUtils.c
	$(CC) $(CCFLAGS) -c $(SRC)/PrintUtils.c -o $(BUILD)/PrintUtils.o

$(BUILD)/ReadWords.o: $(SRC)/ReadWords.c $(BUILD)/StringSet.o $(BUILD)/Node.o
	$(CC) $(CCFLAGS) -c $(SRC)/ReadWords.c -o $(BUILD)/ReadWords.o

$(BUILD)/GetCore.o: $(SRC)/GetCore.c $(BUILD)/Node.o
	$(CC) $(CCFLAGS) -c $(SRC)/GetCore.c -o $(BUILD)/GetCore.o

$(BUILD)/MinSet.o: $(SRC)/MinSet.c $(BUILD)/Node.o $(BUILD)/heap.o
	$(CC) $(CCFLAGS) -c $(SRC)/MinSet.c -o $(BUILD)/MinSet.o

$(BUILD)/Node.o: $(SRC)/Node.c
	$(CC) $(CCFLAGS) -c $(SRC)/Node.c -o $(BUILD)/Node.o

$(BUILD)/StringSet.o: $(SRC)/StringSet.c
	$(CC) $(CCFLAGS) -c $(SRC)/StringSet.c -o $(BUILD)/StringSet.o

$(BUILD)/hashmap.o: $(DEPS)/templated-hashmap/hashmap.c
	$(CC) $(CCFLAGS) -c $(DEPS)/templated-hashmap/hashmap.c -o $(BUILD)/hashmap.o

$(BUILD)/heap.o: local-deps/heap/heap.c
	$(CC) $(CCFLAGS) -c local-deps/heap/heap.c -o $(BUILD)/heap.o
