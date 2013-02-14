CC=g++
FLAGS=-g -Wall -funwind-tables
DB_FLAGS=-L /usr/local/BerkeleyDB.4.8/lib/ -I /usr/local/BerkeleyDB.4.8/include/
DB_LIB=-ldb_cxx -lpthread
COMMON_FLAGS=-L ../../COMMON/ -I ../../COMMON/
COMMON_PATH=../../COMMON/
COMMON_OBJE=$(COMMON_PATH)BDBOpe.o $(COMMON_PATH)TableManager.o $(COMMON_PATH)AttributeManager.o
PV_FLAGS=-L ../../PosVal/ -I ../../PosVal/
PV_PATH=../../PosVal/
PV_OBJE=$(PV_PATH)PosVal.o $(PV_PATH)IntPosVal.o $(PV_PATH)LongPosVal.o $(PV_PATH)FloatPosVal.o $(PV_PATH)DoublePosVal.o $(PV_PATH)FixStrPosVal.o $(PV_PATH)VarStrPosVal.o $(PV_PATH)DatePosVal.o $(PV_PATH)RLEElement.o
NSM_FLAGS=-L ../../NSM/ -I ../../NSM/
NSM_OBJE=../NSM/MakeNSM.o
DSM_PATH=../../DSM/
DSM_FLAGS=-L $(DSM_PATH) -I $(DSM_PATH)
DSM_OBJE=$(DSM_PATH)MakeDSM.o $(DSM_PATH)Encode.o $(DSM_PATH)BareEncode.o $(DSM_PATH)RLEEncode.o $(DSM_PATH)SortColumn.o

OPE_PATH=../
OPE_FLAGS=-L $(OPE_PATH) -I $(OPE_PATH)

NODE_FLAG=-L ../../Node/ -I ../../Node/
NODE_OBJE=../../Node/AxprNode.o ../../Node/ColumnRefNode.o ../../Node/ValueNode.o




.PHONY: all
all: 


.PHONY: allTest
allTest:test test2 test3 test4 test5 test6 test7

test9: test9.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS)  $(NODE_FLAG) $(OPE_FLAGS) -o $@ test9.o $(OPE_PATH)Operator.o $(OPE_PATH)Scan.o $(OPE_PATH)ScanHash.o $(OPE_PATH)OutPut.o $(OPE_PATH)Selection.o $(OPE_PATH)Projection.o $(OPE_PATH)Sort.o $(OPE_PATH)HashJoin.o $(OPE_PATH)OneSideHashJoin.o $(OPE_PATH)Hash.o $(OPE_PATH)NestedJoin.o $(OPE_PATH)MargeJoin.o $(PV_OBJE) $(COMMON_OBJE) $(NODE_OBJE) $(DB_LIB)

test9.o: test9.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(OPE_FLAGS) -c test9.cpp

test7: test7.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS)  $(NODE_FLAG) $(OPE_FLAGS) -o $@ -O3 test7.o $(OPE_PATH)Operator.o $(OPE_PATH)Scan.o $(OPE_PATH)OutPut.o $(OPE_PATH)Selection.o $(OPE_PATH)Projection.o $(OPE_PATH)Sort.o $(OPE_PATH)HashJoin.o $(OPE_PATH)Hash.o $(PV_OBJE) $(COMMON_OBJE) $(NODE_OBJE) $(DB_LIB)

test7.o: test7.cpp 
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(OPE_FLAGS) -c test7.cpp

test6: test6.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS)  $(NODE_FLAG) $(OPE_FLAGS) -o $@ test6.o $(OPE_PATH)Operator.o $(OPE_PATH)Scan.o $(OPE_PATH)OutPut.o $(OPE_PATH)Selection.o $(OPE_PATH)Projection.o $(OPE_PATH)Sort.o $(OPE_PATH)NestedJoin.o $(OPE_PATH)MargeJoin.o $(PV_OBJE) $(COMMON_OBJE) $(NODE_OBJE) $(DB_LIB)

test6.o: test6.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(OPE_FLAGS) -c test6.cpp

test5: test5.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS)  $(NODE_FLAG) $(OPE_FLAGS) -O3 -o $@ test5.o $(OPE_PATH)Operator.o $(OPE_PATH)Scan.o $(OPE_PATH)OutPut.o $(OPE_PATH)Selection.o $(OPE_PATH)Projection.o $(OPE_PATH)Sort.o $(OPE_PATH)NestedJoin.o $(PV_OBJE) $(COMMON_OBJE) $(NODE_OBJE) $(DB_LIB)

test5.o: test5.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(OPE_FLAGS) -c test5.cpp

test4: test4.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS)  $(NODE_FLAG) $(OPE_FLAGS) -o $@ test4.o $(OPE_PATH)Operator.o $(OPE_PATH)Scan.o $(OPE_PATH)OutPut.o $(OPE_PATH)Selection.o $(OPE_PATH)Projection.o $(OPE_PATH)Sort.o $(PV_OBJE) $(COMMON_OBJE) $(NODE_OBJE) $(DB_LIB)

test4.o: test4.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(OPE_FLAGS) -c test4.cpp

test3: test3.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS)  $(NODE_FLAG) $(OPE_FLAGS) -o $@ test3.o $(OPE_PATH)Operator.o $(OPE_PATH)Scan.o $(OPE_PATH)OutPut.o $(OPE_PATH)Selection.o $(OPE_PATH)Projection.o $(PV_OBJE) $(COMMON_OBJE) $(NODE_OBJE) $(DB_LIB)

test3.o: test3.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(OPE_FLAGS) -c test3.cpp

test2: test2.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS)  $(NODE_FLAG) $(OPE_FLAGS) -o $@ test2.o $(OPE_PATH)Operator.o $(OPE_PATH)Scan.o $(OPE_PATH)OutPut.o $(OPE_PATH)Selection.o $(PV_OBJE) $(COMMON_OBJE) $(NODE_OBJE) $(DB_LIB)

test2.o: test2.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(OPE_FLAGS) -c test2.cpp

test: test.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(OPE_FLAGS) -o $@ test.o $(OPE_PATH)Operator.o $(OPE_PATH)Scan.o $(OPE_PATH)OutPut.o $(PV_OBJE) $(COMMON_OBJE) $(DB_LIB)

test.o: test.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(OPE_FLAGS) -c test.cpp


