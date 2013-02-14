CC=g++
FLAGS=-g -Wall -funwind-tables -O2
DB_FLAGS=-L /usr/local/BerkeleyDB.4.8/lib/ -I /usr/local/BerkeleyDB.4.8/include/
DB_LIB=-ldb_cxx -lpthread


COMMON_FLAGS=-L ../COMMON/ -I ../COMMON/
COMMON_PATH=../COMMON/
COMMON_OBJE=$(COMMON_PATH)EnvDB.o $(COMMON_PATH)BDBOpe.o $(COMMON_PATH)SecondDB.o $(COMMON_PATH)InMemDB.o $(COMMON_PATH)TableManager.o $(COMMON_PATH)AttributeManager.o $(COMMON_PATH)Timer.o $(COMMON_PATH)IndexExtract.o


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
OPERATION_OBJE=$(OPERATION_PATH)Operator.o $(OPERATION_PATH)Scan.o $(OPERATION_PATH)IndexScan.o $(OPERATION_PATH)ScanHash.o $(OPERATION_PATH)ScanInMemHash.o $(OPERATION_PATH)OutPut.o $(OPERATION_PATH)Selection.o $(OPERATION_PATH)Projection.o $(OPERATION_PATH)Sort.o $(OPERATION_PATH)NestedJoin.o $(OPERATION_PATH)MargeJoin.o $(OPERATION_PATH)Hash.o  $(OPERATION_PATH)HashJoin.o $(OPERATION_PATH)HashJoin_old.o $(OPERATION_PATH)OneSideHashJoin.o $(OPERATION_PATH)OneSideHashJoin_old.o $(OPERATION_PATH)GroupBy.o $(OPERATION_PATH)Extract.o $(OPERATION_PATH)AggreOut.o

OPERATION_C_FLAG=-L ../Operation_C/ -I ../Operation_C/
OPERATION_C_PATH=../Operation_C/
OPERATION_C_OBJE=$(OPERATION_C_PATH)ScanDSM.o $(OPERATION_C_PATH)ScanRLE.o $(OPERATION_C_PATH)IndexScanDSM.o $(OPERATION_C_PATH)ScanJoinIndex.o $(OPERATION_C_PATH)SelectBitOut.o $(OPERATION_C_PATH)BitFilter.o $(OPERATION_C_PATH)JoinIndex_OneHash.o $(OPERATION_C_PATH)JoinFromJoinIndex.o $(OPERATION_C_PATH)ScanFromJI.o $(OPERATION_C_PATH)ScanFromPos.o $(OPERATION_C_PATH)ScanFromJI_OneHash.o $(OPERATION_C_PATH)BitSort.o $(OPERATION_C_PATH)ConnectJI.o $(OPERATION_C_PATH)JoinC.o


.PHONY: all

all: testSelection testIndex testJoinC testPosIndex clean


testSelection: testSelection.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testSelection.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testSelection.o:testSelection.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testSelection.cpp
	

testIndex: testIndex.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testIndex.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testIndex.o:testIndex.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testIndex.cpp


testJoinC: testJoinC.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testJoinC.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testJoinC.o:testJoinC.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testJoinC.cpp
	

testPosIndex: testPosIndex.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testPosIndex.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testPosIndex.o:testPosIndex.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testPosIndex.cpp


##===========================================================================---	
	
#ScanDSM_U.o: ScanDSM_U.cpp
#	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c ScanDSM_U.cpp
	
	
#SelectBitOut_U.o: SelectBitOut_U.cpp
#	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c SelectBitOut_U.cpp


clean:
	rm *.o
