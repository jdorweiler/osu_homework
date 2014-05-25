
CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
LDFLAGS = -lboost_date_time

OBJS = constructors.o

SRCS = constructors.cpp

HEADERS =

#target: dependencies
#	rule to build
#

constructor: ${OBJS} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS} -o constructor

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)
