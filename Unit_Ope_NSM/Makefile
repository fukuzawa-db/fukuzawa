CC=g++
FLAGS=-g -Wall -funwind-tables
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
OPERATION_C_OBJE=$(OPERATION_C_PATH)ScanDSM.o $(OPERATION_C_PATH)ScanRLE.o $(OPERATION_C_PATH)IndexScanDSM.o $(OPERATION_C_PATH)ScanJoinIndex.o $(OPERATION_C_PATH)SelectBitOut.o $(OPERATION_C_PATH)BitFilter.o $(OPERATION_C_PATH)JoinIndex_OneHash.o $(OPERATION_C_PATH)JoinFromJoinIndex.o $(OPERATION_C_PATH)ScanFromJI.o $(OPERATION_C_PATH)ScanFromJI_OneHash.o $(OPERATION_C_PATH)BitSort.o $(OPERATION_C_PATH)ConnectJI.o


.PHONY: all
all: testScan testProjection testSelection testExtract testAggregation testGroupBy testSort testNestedJoin testMargeJoin testHashJoin testOneSideHashJoin clean




testScan: testScan.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testScan.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testScan.o: testScan.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testScan.cpp



#testScanDSM: testScanDSM.o
#	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testScanDSM.o $(OPERATION_OBJE) #$(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)

#testScanDSM.o:testScanDSM.cpp
#	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testScanDSM.cpp


testScan_U: testScan_U.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testScan_U.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testScan_U.o:testScan_U.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testScan_U.cpp


testProjection: testProjection.o Scan_U.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testProjection.o Scan_U.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testProjection.o: testProjection.cpp 
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testProjection.cpp
	

testSelection: testSelection.o Scan_U.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testSelection.o Scan_U.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testSelection.o: testSelection.cpp 
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testSelection.cpp
	
	
testExtract: testExtract.o Scan_U.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testExtract.o Scan_U.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testExtract.o: testExtract.cpp 
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testExtract.cpp


testAggregation: testAggregation.o Scan_U.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testAggregation.o Scan_U.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testAggregation.o: testAggregation.cpp 
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testAggregation.cpp


testGroupBy: testGroupBy.o Scan_U.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testGroupBy.o Scan_U.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testGroupBy.o: testGroupBy.cpp 
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testGroupBy.cpp


testSort: testSort.o Scan_U.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testSort.o Scan_U.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testSort.o: testSort.cpp 
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testSort.cpp


testNestedJoin: testNestedJoin.o Scan_U.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testNestedJoin.o Scan_U.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testNestedJoin.o: testNestedJoin.cpp 
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testNestedJoin.cpp


testMargeJoin: testMargeJoin.o Scan_U2.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testMargeJoin.o Scan_U2.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testMargeJoin.o: testMargeJoin.cpp 
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testMargeJoin.cpp


testHashJoin: testHashJoin.o Scan_U.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testHashJoin.o Scan_U.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testHashJoin.o: testHashJoin.cpp 
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testHashJoin.cpp


testOneSideHashJoin: testOneSideHashJoin.o Scan_U.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) -o $@ testOneSideHashJoin.o Scan_U.o $(OPERATION_OBJE) $(OPERATION_C_OBJE) $(PV_OBJE) $(COMMON_OBJE)  $(NODE_OBJE) $(DB_LIB) $(AGGRI_OBJE)
	
testOneSideHashJoin.o: testOneSideHashJoin.cpp 
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c testOneSideHashJoin.cpp
	
##===========================================================================---	
	
Scan_U.o: Scan_U.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c Scan_U.cpp

Scan_U2.o: Scan_U2.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c Scan_U2.cpp

ScanDSM_U.o: ScanDSM_U.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) $(NODE_FLAG) $(AGGRI_FLAG) $(OPERATION_FLAG) $(OPERATION_C_FLAG) -c ScanDSM_U.cpp -ldb_cxx


clean:
	rm *.o
