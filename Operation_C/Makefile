#CXX =	g++
CXXFLAGS = -g -Wall -funwind-tables -O3
CPPFLAGS = -I/usr/local/BerkeleyDB.4.8/include -I../COMMON/ -I../PosVal \
		-I../NSM -I../DSM -I../Node -I../Aggregation -I../Operation

OBJS = ScanFromJI_OneHash.o ConnectJI.o BitSort.o ScanFromJI_Com.o \
	 ScanFromJI.o ScanFromPos.o  ScanJoinIndex.o JoinIndex_OneHash.o \
	JoinC.o BitFilter.o SelectBitOut.o IndexScanDSM.o ScanRLE.o ScanDSM.o \
	JoinFromJoinIndex.o
TARGET = libOperation_C.a

$(TARGET): $(OBJS)
	ar rv $@ $(OBJS)
	ranlib $@

clean:
	rm -f $(OBJS)

distclean:
	rm -f $(OBJS) $(TARGET)

ConnectJI.cpp: ConnectJI.h
ScanFromJI_Com.cpp: ScanFromJI_Com.h
ScanFromJI_OneHash.cpp : ScanFromJI_OneHash.h
ScanFromJI.cpp: ScanFromJI.h
ScanFromPos.cpp: ScanFromPos.h
JoinC.cpp: JoinC.h
JoinFromJoinIndex.cpp: JoinFromJoinIndex.h
ScanJoinIndex.cpp: ScanJoinIndex.h
JoinIndex_OneHash.cpp: JoinIndex_OneHash.h
BitSort.cpp: BitSort.h
BitFilter.cpp: BitFilter.h
SelectBitOut.cpp: SelectBitOut.h
IndexScanDSM.cpp: IndexScanDSM.h
ScanRLE.cpp: ScanRLE.h
ScanDSM.cpp: ScanDSM.h

# .PHONY: allTest
# allTest: test1 test2 test3

# test3: test3.o ScanRLE.o JoinFromJoinIndex.o ScanJoinIndex.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ test3.o ScanDSM.o JoinFromJoinIndex.o ScanJoinIndex.o JoinIndex_OneHash.o $(OPERATION_OBJE) $(PV_OBJE) $(NODE_OBJE) $(AGGRI_OBJE) $(COMMON_OBJE) $(DB_LIB) $(DB_LIB)

# test3.o: test3.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(OPERATION_FLAG) -c test3.cpp

# test2: test2.o ScanRLE.o ScanDSM.o 
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(OPERATION_FLAG) -o $@ test2.o ScanRLE.o ScanDSM.o $(OPERATION_OBJE) $(PV_OBJE) $(NODE_OBJE) $(AGGRI_OBJE) $(COMMON_OBJE) $(DB_LIB)

# test2.o: test2.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(OPERATION_FLAG) -c test2.cpp

# test1: test1.o ScanDSM.o 
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(OPERATION_FLAG) -o $@ test1.o $(OPERATION_OBJE) ScanDSM.o  $(PV_OBJE) $(NODE_OBJE) $(AGGRI_OBJE) $(COMMON_OBJE) $(DB_LIB)

# test1.o: test1.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(OPERATION_FLAG) -c test1.cpp
