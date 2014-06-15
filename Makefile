EXEC = straights
CXX = g++ 
CXXFLAGS = -g -Wall -MMD
OBJECTS = Straights.o Model.o View.o Controller.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean:
	rm -rf ${OBJECTS} ${EXEC} ${DEPENDS}

-include ${DEPENDS} 