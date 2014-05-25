
CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
LDFLAGS = -lboost_date_time

OBJS = boostLect.o

SRCS = boostLect.cpp

HEADERS =

#target: dependencies
#	rule to build
#

boost: ${OBJS} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS} -o boost

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)
