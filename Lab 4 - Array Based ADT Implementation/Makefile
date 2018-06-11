#------------------------------------------------------------------------------
# Makefile for any ADT and its test client
#------------------------------------------------------------------------------

ADT_NAME  = Block
SOURCES   = $(ADT_NAME).c $(ADT_NAME)chain.c $(ADT_NAME)chainClient.c
OBJECTS   = $(ADT_NAME).o $(ADT_NAME)chain.o $(ADT_NAME)chainClient.o
HEADERS   = $(ADT_NAME).h $(ADT_NAME)chain.h
EXEBIN    = $(ADT_NAME)chainClient
FLAGS     = -Wall

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

check:
	valgrind --leak-check=full ./$(EXEBIN) 
