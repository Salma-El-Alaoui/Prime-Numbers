CC = g++
EDL= g++
EXE=THREAD
LIB_MATH=-lm
LIB_THREAD=-lpthread
CPPFLAGS=-c -Wall

OBJ_DIR= bin
SRC_DIR= src

THREAD_OBJ = $(OBJ_DIR)/Main.o
						

$(EXE): $(THREAD_OBJ)
	$(EDL) -o $(EXE) $(THREAD_OBJ) $(LIB_MATH) $(LIB_THREAD)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o THREAD core


