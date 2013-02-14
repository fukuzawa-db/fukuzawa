#CXX =	g++
CXXFLAGS = -g -Wall -funwind-tables -O3
CPPFLAGS = -I/usr/local/BerkeleyDB.4.8/include -I../COMMON/ -I../PosVal \
		-I../NSM -I../DSM -I../Node

OBJS = Aggregation.o Max.o Min.o Count.o Sum.o Avg.o
TARGET = libAggregation.a

$(TARGET): $(OBJS)
	ar rv $@ $(OBJS)
	ranlib $@

clean:
	rm -f $(OBJS)

distclean:
	rm -f $(OBJS) $(TARGET)


Avg.cpp: Avg.h
Sum.cpp: Sum.h
Count.cpp: Count.h
Min.cpp: Min.h
Max.cpp: Max.h
Aggregation.cpp: Aggregation.h
