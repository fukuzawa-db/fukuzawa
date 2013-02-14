#CXX =	g++
CXXFLAGS = -g -Wall -funwind-tables -O2
CPPFLAGS = -I/usr/local/BerkeleyDB.4.8/include -I../COMMON/ -I../PosVal \
		-I../NSM -I../DSM #-I../Node
LDFLAGS = -L/usr/local/BerkeleyDB.4.8/lib \
		-L../COMMON -L../DSM -L../NSM -L../PosVal \
		-lDSM -lNSM -lPosVal -lCOMMON \
		-ldb_cxx -lpthread 

OBJS = main.o TableMaker.o
TARGET = main

all: main

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OBJS) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJS)

distclean:
	rm -f $(OBJS) $(TARGET)

TableMaker.cpp: TableMaker.h

