#CXX =	g++
CXXFLAGS = -g -Wall -funwind-tables -O3
CPPFLAGS = -I/usr/local/BerkeleyDB.4.8/include -I../COMMON/ -I../PosVal \
		-I../NSM -I../DSM -I../Node -I../Aggregation \
		-I../Operation -I../Operation_C
LDFLAGS = -L/usr/local/BerkeleyDB.4.8/lib \
		-L../DSM -L../NSM \
		-L../Aggregation -L../Operation -L../Operation_C \
		-L../PosVal  -L../Node -L../COMMON \
		-lDSM -lNSM -lAggregation -lOperation -lOperation_C \
		-lPosVal -lNode -lCOMMON \
		-ldb_cxx -lpthread 

OBJS = ShowSys.o
TARGET = ShowSys

all: $(TARGET)

ShowSys: ShowSys.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJS)

distclean:
	rm -f $(OBJS) $(TARGET)
