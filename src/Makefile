# --------make file------
SHELL = /bin/bash
# --------setting--------
CXX = g++
TARGET = FEM.exe
CXXFLAGS = -O2
SRCS = main.cpp matrix.cpp material.cpp util.cpp core.cpp variable.cpp solve.cpp
OBJS := $(SRCS:.cpp=.o) #SRCS .cpp -> .o

# --------compile--------
$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)

%.o:%.cpp
	$(CXX) $(SRCS) -c $<

# --------clean----------
clean:
	@echo 'clean-all : uninstall.'
	@echo 'clean-OBJ : delete object files.'
clean-all:
	rm -f $(TARGET) $(OBJS)
clean-OBJ:
	rm -f $(OBJS)
