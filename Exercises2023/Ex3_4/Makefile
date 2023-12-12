CC=g++ #Name of compiler
FLAGS=-std=c++20 -w #Compiler flags (the s makes it silent)
TARGET=functionTest #Executable name
OBJECTS=functionTest.o FiniteFunctions.o NormalFunction.o CLFunction.o NegCrystalBallFunction.o sampling.o #Object files to link
LIBS=-I ../../GNUplot/ -lboost_iostreams

#First target in Makefile is default
${TARGET}:${OBJECTS} #Make target from objects
	@echo "Linking..."
	${CC} ${FLAGS} ${OBJECTS} ${LIBS} -o ${TARGET}
	@make clean

sampling.o : sampling.cpp sampling.h
	${CC} ${FLAGS} ${LIBS} -c sampling.cpp

functionTest.o : functionTest.cpp FiniteFunctions.h
	${CC} ${FLAGS} ${LIBS} -c functionTest.cpp

FiniteFunctions.o : FiniteFunctions.cxx FiniteFunctions.h
	${CC} ${FLAGS} ${LIBS} -c FiniteFunctions.cxx

normalFunction.o : NormalFunction.cpp NormalFunction.h
	${CC} ${FLAGS} ${LIBS} -c NormalFunction.cpp

CLFunction.o : CLFunction.cpp CLFunction.h
	${CC} ${FLAGS} ${LIBS} -c CLFunction.cpp

NegCrystalBall.o : NegCrystalBallFunction.cpp NegCrystalBallFunction.h
	${CC} ${FLAGS} ${LIBS} -c NegCrystalBallFunction.cpp




clean: #No targets just run shell command to rm object files and emacs backups
	@rm -f *.o *~

cleantarget: #Delete the exectuable
	@rm -f ${TARGET}
