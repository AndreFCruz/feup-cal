CXX=g++
CPPFLAGS=-g -W -std=c++14

SRCS=main.cpp ViewerFunctions.cpp connection.cpp Coordinates.cpp Edge.cpp Graph.cpp Node.cpp Road.cpp Transport.cpp TransportStop.cpp graphviewer.cpp SubwayStop.cpp

FILENAME=executable

all: $(FILENAME)

$(FILENAME): $(SRCS)
	$(CXX) $(CPPFLAGS) $(SRCS) -o $(FILENAME)