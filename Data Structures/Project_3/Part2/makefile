COMPILER  = g++

DEBUG  = -g -std=c++0x

EXE  = app

HDRS  = term.h\
	TermArrayList.h\
	TermList.h\
	TermDblLinkList.h\
	TermVectorList.h\

OBJS  = term.o\
	TermArrayList.o\
	TermDblLinkList.o\
	TermVectorList.o\
	app.o\

SRC  = 	term.cpp\
	TermArrayList.cpp\
	app.cpp\
	TermDblLinkList.cpp\
	TermVectorList.cpp\


##########################################################################
$(EXE): $(OBJS) $(HDRS) $(SRC)
	$(COMPILER) -o $(EXE) $(OBJS) $(DEBUG)

Term.o:  term.cpp term.h 
	$(COMPILER) -c term.cpp $(DEBUG)

TermArrayList.o:  term.h TermArrayList.cpp TermArrayList.h TermList.h 
	$(COMPILER) -c TermArrayList.cpp $(DEBUG)

TermDblLinkList.o:  term.h TermDblLinkList.cpp TermDblLinkList.h TermList.h 
	$(COMPILER) -c TermDblLinkList.cpp $(DEBUG)

TermVectorList.o:  term.h TermVectorList.cpp TermVectorList.h TermList.h 
	$(COMPILER) -c TermVectorList.cpp $(DEBUG)


app.o:  TermArrayList.h TermList.h app.cpp TermDblLinkList.h TermVectorList.h
	$(COMPILER) -c app.cpp $(DEBUG)


clean:
	del *.o $(EXE)

