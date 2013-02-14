CC=g++
FLAGS=-g -Wall -funwind-tables
DB_FLAGS=-L /usr/local/BerkeleyDB.4.8/lib/ -I /usr/local/BerkeleyDB.4.8/include/
DB_LIB=-ldb_cxx -lpthread
COMMON_FLAGS=-L ../COMMON/ -I ../COMMON/
COMMON_PATH=../COMMON/
COMMON_OBJE=$(COMMON_PATH)BDBOpe.o $(COMMON_PATH)TableManager.o $(COMMON_PATH)AttributeManager.o
PV_FLAGS=-L ../PosVal/ -I ../PosVal/
PV_PATH=../PosVal/
PV_OBJE=$(PV_PATH)PosVal.o $(PV_PATH)IntPosVal.o $(PV_PATH)LongPosVal.o $(PV_PATH)FloatPosVal.o $(PV_PATH)DoublePosVal.o $(PV_PATH)FixStrPosVal.o $(PV_PATH)VarStrPosVal.o $(PV_PATH)DatePosVal.o $(PV_PATH)RLEElement.o
NSM_FLAGS=-L ../NSM/ -I ../NSM/
NSM_OBJE=../NSM/MakeNSM.o
DSM_FLAGS=-L ../DSM/ -I ../DSM/
DSM_OBJE=../DSM/MakeDSM.o ../DSM/Encode.o ../DSM/BareEncode.o ../DSM/RLEEncode.o ../DSM/SortColumn.o

NODE_FLAG=-L ../Node/ -I ../Node/
NODE_OBJE=../Node/ArithmeticNode.o ../Node/AxprNode.o ../Node/ColumnRefNode.o ../Node/ValueNode.o

AGGRI_FLAG=-L ../Aggregation/ -I ../Aggregation/
AGGRI_OBJE=../Aggregation/Aggregation.o ../Aggregation/Max.o ../Aggregation/Min.o ../Aggregation/Count.o ../Aggregation/Sum.o ../Aggregation/Avg.o

OPERATION_FLAG=-L ../Operation/ -I ../Operation/
OPERATION_PATH=../Operation/
OPERATION_OBJE=$(OPERATION_PATH)Operator.o $(OPERATION_PATH)Scan.o $(OPERATION_PATH)ScanHash.o $(OPERATION_PATH)OutPut.o $(OPERATION_PATH)Selection.o $(OPERATION_PATH)Projection.o $(OPERATION_PATH)Sort.o $(OPERATION_PATH)NestedJoin.o $(OPERATION_PATH)MargeJoin.o $(OPERATION_PATH)Hash.o  $(OPERATION_PATH)HashJoin.o $(OPERATION_PATH)HashJoin_old.o $(OPERATION_PATH)OneSideHashJoin.o $(OPERATION_PATH)OneSideHashJoin_old.o $(OPERATION_PATH)GroupBy.o $(OPERATION_PATH)Extract.o

OPERATION_C_FLAG=-L ../Operation_C/ -I ../Operation_C/
OPERATION_C_PATH=../Operation_C/
OPERATION_C_OBJE=$(OPERATION_C_PATH)ScanDSM.o $(OPERATION_C_PATH)ScanRLE.o $(OPERATION_C_PATH)ScanJoinIndex.o $(OPERATION_C_PATH)SelectBitOut.o $(OPERATION_C_PATH)BitFilter.o $(OPERATION_C_PATH)JoinIndex_OneHash.o $(OPERATION_C_PATH)JoinFromJoinIndex.o $(OPERATION_C_PATH)ScanFromJI.o $(OPERATION_C_PATH)ScanFromJI_OneHash.o $(OPERATION_C_PATH)BitSort.o $(OPERATION_C_PATH)ConnectJI.o


.PHONY: all
all: Test1 Test2 Test3 Test4 Test5 Test6


Test6: Test6.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ Test6.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
Test6.o: Test6.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c Test6.cpp


Test5: Test5.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ Test5.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
Test5.o: Test5.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c Test5.cpp
	

Test4: Test4.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ Test4.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
Test4.o: Test4.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c Test4.cpp
	


Test3: Test3.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ Test3.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
	
Test3.o: Test3.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c Test3.cpp
	

Test2: Test2.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ Test2.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
	
Test2.o: Test2.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c Test2.cpp


Test1: Test1.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ Test1.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
	
Test1.o: Test1.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c Test1.cpp
