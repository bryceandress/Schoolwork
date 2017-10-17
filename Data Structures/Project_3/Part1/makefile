COMPILER  = g++

DEBUG  = -g

EXE  = app

HDRS  = term.h\
	TermArrayList.h\
	TermList.h\

OBJS  = term.o\
	TermArrayList.o\
	app.o\

SRC  = 	term.cpp\
	TermArrayList.cpp\
	app.cpp\


##########################################################################
$(EXE): $(OBJS) $(HDRS) $(SRC)
	$(COMPILER) -o $(EXE) $(OBJS) $(DEBUG)

Term.o:  term.cpp term.h 
	$(COMPILER) -c term.cpp $(DEBUG)

TermArrayList.o:  term.h TermArrayList.cpp TermArrayList.h TermList.h 
	$(COMPILER) -c TermArrayList.cpp $(DEBUG)

app.o:  TermArrayList.h TermList.h app.cpp 
	$(COMPILER) -c app.cpp $(DEBUG)


clean:
	del *.o $(EXE)

