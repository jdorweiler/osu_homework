
CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
#LDFLAGS = -lboost_date_time

OBJS = triangleWords.o

SRCS = triangleWords.cpp

HEADERS =

#target: dependencies
#	rule to build
#

trianglewords: ${OBJS} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS} -o triangleWords

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)
