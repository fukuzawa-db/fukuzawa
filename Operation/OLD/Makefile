CC=g++
FLAGS=-g -Wall -funwind-tables
DB_FLAGS=-L /usr/local/BerkeleyDB.4.2/lib -I /usr/local/BerkeleyDB.4.2/include
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

.PHONY: all
all: 

.PHONY: allObj
allObj:  BitManager.o Projection.o Select.o

.PHONY: allTest
allTest: testProjection testSelect


testSelect: testSelect.o Select.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ testSelect.o Select.o $(PV_OBJE) $(COMMON_OBJE) $(DB_LIB)

testSelect.o: testSelect.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testSelect.cpp

testProjection: testProjection.o Projection.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ testProjection.o Projection.o $(PV_OBJE) $(COMMON_OBJE) $(DB_LIB)

testProjection.o: testProjection.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testProjection.cpp


BitManager.o: BitManager.cpp BitManager.h
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(NSM_FLAGS) $(DSM_FLAGS) $(PV_FLAGS) -c BitManager.cpp

Projection.o: Projection.cpp Projection.h
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(NSM_FLAGS) $(DSM_FLAGS) $(PV_FLAGS) -c Projection.cpp

Select.o: Select.cpp Select.h
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(NSM_FLAGS) $(DSM_FLAGS) $(PV_FLAGS) -c Select.cpp


Scan.o: Scan.h Scan.cpp Operator.o
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(NSM_FLAGS) $(DSM_FLAGS) $(PV_FLAGS) -c Scan.cpp
	
Operator.o: Operator.h Operator.cpp
	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(NSM_FLAGS) $(DSM_FLAGS) $(PV_FLAGS) -c Operator.cpp
