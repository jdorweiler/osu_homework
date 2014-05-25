
CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
LDFLAGS = -lboost_date_time

OBJS = ComplexNumber.o

SRCS = ComplexNumber.cpp

HEADERS =

#target: dependencies
#	rule to build
#

complexnumber: ${OBJS} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS} -o complexnumber

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)
