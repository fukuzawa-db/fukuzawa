#CXX =	g++
CXXFLAGS = -g -Wall -funwind-tables -O3
CPPFLAGS = -I/usr/local/BerkeleyDB.4.8/include -I../COMMON/ -I../PosVal \
		-I../NSM -I../DSM -I../Node -I../Aggregation -I ../Operation

OBJS = Operator.o Scan.o KeyIndex.o IndexScan.o IndexRangScan.o Index.o \
	ScanHash.o ScanInMemHash.o OutPut.o Selection.o Projection.o Sort.o \
	NestedJoin.o NestedJoin_Index.o MargeJoin.o Hash.o HashJoin.o \
	HashJoin_old.o  OneSideHashJoin.o OneSideHashJoin_old.o GroupBy.o \
	Extract.o AggreOut.o
TARGET = libOperation.a

$(TARGET): $(OBJS)
	ar rv $@ $(OBJS)
	ranlib $@

ScanInMemHash.o: ScanInMemHash.h ScanInMemHash.cpp
	$(CXX) -g -Wall -funwind-tables $(CPPFLAGS) ScanInMemHash.cpp -c $(LDFLAGS)

clean:
	rm -f $(OBJS)

distclean:
	rm -f $(OBJS) $(TARGET)

AggreOut.cpp: AggreOut.h 
Extract.cpp: Extract.h
GroupBy.cpp: GroupBy.h 
OneSideHashJoin.cpp: OneSideHashJoin.h 
OneSideHashJoin_old.cpp: OneSideHashJoin_old.h 
HashJoin.cpp: HashJoin.h 
HashJoin_old.cpp: HashJoin_old.h 
Hash.cpp: Hash.h 
MargeJoin.cpp: MargeJoin.h
NestedJoin.cpp: NestedJoin.h
NestedJoin_Index.cpp: NestedJoin_Index.h
Sort.cpp: Sort.h
Projection.cpp: Projection.h
Selection.cpp: Selection.h
OutPut.cpp: OutPut.h
ScanHash.cpp: ScanHash.h
ScanInMemHash.cpp: ScanInMemHash.h
KeyIndex.cpp: KeyIndex.h
IndexScan.cpp: IndexScan.h
IndexRangScan.cpp: IndexRangScan.h
Index.cpp: Index.h
Scan.cpp: Scan.h
Operator.cpp: Operator.h

#.PHONY: allTest
#allTest: test test2 test3 test4 test5 test6 test7

# test8: test8.o Operator.o Scan.o OutPut.o GroupBy.o Projection.o Sort.o HashJoin.o Hash.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS)  $(NODE_FLAG)  $(AGGRI_FLAG) -o $@  test8.o Operator.o Scan.o OutPut.o GroupBy.o Hash.o $(PV_OBJE) $(COMMON_OBJE) $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)

# test8.o: test8.cpp 
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) -c test8.cpp

# test7: test7.o Operator.o Scan.o OutPut.o Selection.o Projection.o Sort.o HashJoin.o Hash.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS)  $(NODE_FLAG) -o $@ -O3 test7.o Operator.o Scan.o OutPut.o Selection.o Projection.o Sort.o HashJoin.o Hash.o $(PV_OBJE) $(COMMON_OBJE) $(NODE_OBJE) $(DB_LIB)

# test7.o: test7.cpp 
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) -c test7.cpp

# test6: test6.o Operator.o Scan.o OutPut.o Selection.o Projection.o Sort.o NestedJoin.o MargeJoin.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS)  $(NODE_FLAG) -o $@ test6.o Operator.o Scan.o OutPut.o Selection.o Projection.o Sort.o NestedJoin.o MargeJoin.o $(PV_OBJE) $(COMMON_OBJE) $(NODE_OBJE) $(DB_LIB)

# test6.o: test6.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) -c test6.cpp

# test5: test5.o Operator.o Scan.o OutPut.o Selection.o Projection.o Sort.o NestedJoin.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS)  $(NODE_FLAG) -o $@ test5.o Operator.o Scan.o OutPut.o Selection.o Projection.o Sort.o NestedJoin.o $(PV_OBJE) $(COMMON_OBJE) $(NODE_OBJE) $(DB_LIB)

# test5.o: test5.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) -c test5.cpp

# test4: test4.o Operator.o Scan.o OutPut.o Selection.o Projection.o Sort.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS)  $(NODE_FLAG) -o $@ test4.o Operator.o Scan.o OutPut.o Selection.o Projection.o Sort.o $(PV_OBJE) $(COMMON_OBJE) $(NODE_OBJE) $(DB_LIB)

# test4.o: test4.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) -c test4.cpp

# test3: test3.o Operator.o Scan.o OutPut.o Selection.o Projection.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS)  $(NODE_FLAG) -o $@ test3.o Operator.o Scan.o OutPut.o Selection.o Projection.o $(PV_OBJE) $(COMMON_OBJE) $(NODE_OBJE) $(DB_LIB)

# test3.o: test3.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) -c test3.cpp

# test2: test2.o Operator.o Scan.o OutPut.o Selection.o 
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS)  $(NODE_FLAG) -o $@ test2.o Operator.o Scan.o OutPut.o Selection.o $(PV_OBJE) $(COMMON_OBJE) $(NODE_OBJE) $(DB_LIB)

# test2.o: test2.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) -c test2.cpp

# test: test.o Operator.o Scan.o OutPut.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ test.o Operator.o OutPut.o Scan.o Projection.o $(PV_OBJE) $(COMMON_OBJE) $(DB_LIB)

# test.o: test.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c test.cpp
