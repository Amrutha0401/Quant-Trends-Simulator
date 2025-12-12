CXX = g++
CXXFLAGS = -std=c++17 -O2
SRCS = indicators.cpp strategies.cpp backtester.cpp main.cpp
OBJ = $(SRCS:.cpp=.o)
all: quant_sim
quant_sim: $(SRCS)
	$(CXX) $(CXXFLAGS) -o quant_sim $(SRCS)
clean:
	rm -f quant_sim *.o
