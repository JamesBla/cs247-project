EXEC = straights
CXX = g++
CXXFLAGS = -g -Wall -MMD
OBJECTS = src/Straights.o src/Model.o src/View.o src/Controller.o src/Player.o src/HumanPlayer.o src/ComputerPlayer.o src/Card.o src/Command.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean:
	rm -rf ${OBJECTS} ${EXEC} ${DEPENDS}

-include ${DEPENDS} 
