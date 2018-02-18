CXX = g++
CXXFLAGS = -Wall -g -std=c++11

OBJS = main.o settings.o room.o q_learn.o
HEADERS =


qBot : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJS) : settings.h

clean :
	@rm -f *o qBot
