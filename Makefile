EXEC = straights
CXX = g++
CXXFLAGS = -Wall -O -g `pkg-config gtkmm-2.4 --cflags`
LDFLAGS = -g `pkg-config gtkmm-2.4 --libs`
OBJECTS = src/Straights.o src/CardButtonView.o src/PlayerView.o src/DeckGUI.o src/Model.o src/View.o src/Controller.o src/Player.o src/HumanPlayer.o src/ComputerPlayer.o src/Card.o src/Command.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	$(CXX) ${OBJECTS} $(LDFLAGS) -o ${EXEC}

clean:
	rm -rf ${OBJECTS} ${EXEC} ${DEPENDS}

test:
	sh ./test.sh

zip:
	zip straights.zip src/*.h src/*.cpp Makefile

-include ${DEPENDS} 
