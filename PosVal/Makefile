#CXX =	g++
CXXFLAGS = -g -Wall -funwind-tables -O3
CPPFLAGS = -I/usr/local/BerkeleyDB.4.8/include -I../COMMON/ 

OBJS = PosVal.o IntPosVal.o LongPosVal.o FloatPosVal.o DoublePosVal.o \
	FixStrPosVal.o VarStrPosVal.o DatePosVal.o RLEElement.o
TARGET = libPosVal.a

$(TARGET): $(OBJS)
	ar rv $@ $(OBJS)
	ranlib $@

clean:
	rm -f $(OBJS)

distclean:
	rm -f $(OBJS) $(TARGET)

RLEElement.cpp: RLEElement.h
DatePosVal.cpp: DatePosVal.h
VarStrPosVal.cpp: VarStrPosVal.h
FixStrPosVal.cpp: FixStrPosVal.h
DoublePosVal.cpp: DoublePosVal.h
FloatPosVal.cpp: FloatPosVal.h
LongPosVal.cpp: LongPosVal.h
IntPosVal.cpp: IntPosVal.h
PosVal.cpp: PosVal.cpp

# .PHONY: allTest
# allTest: testIntPosVal testLongPosVal testFloatPosVal testDoublePosVal testFixStrPosVal testVarStrPosVal testDatePosVal testRLEElement

# testRLEElement: testRLEElement.o RLEElement.o IntPosVal.o PosVal.o 
# 	$(CC) $(FLAGS) -o $@ testRLEElement.o RLEElement.o IntPosVal.o PosVal.o $(DB_LINK)

# testRLEElement.o: testRLEElement.cpp
# 	$(CC) $(FLAGS) $(COMMON_OPTION) $(PosVal_OPTION) -c testRLEElement.cpp $(DB_LINK)

# testDatePosVal: testDatePosVal.o DatePosVal.o PosVal.o
# 	$(CC) $(FLAGS) -o $@ testDatePosVal.o DatePosVal.o PosVal.o

# testDatePosVal.o: testDatePosVal.cpp
# 	$(CC) $(FLAGS) $(COMMON_OPTION) $(PosVal_OPTION) -c testDatePosVal.cpp

# testVarStrPosVal: testVarStrPosVal.o VarStrPosVal.o PosVal.o
# 	$(CC) $(FLAGS) -o $@ testVarStrPosVal.o VarStrPosVal.o PosVal.o

# testVarStrPosVal.o: testVarStrPosVal.cpp
# 	$(CC) $(FLAGS) $(COMMON_OPTION) $(PosVal_OPTION) -c testVarStrPosVal.cpp

# testFixStrPosVal: testFixStrPosVal.o FixStrPosVal.o PosVal.o
# 	$(CC) $(FLAGS) -o $@ testFixStrPosVal.o FixStrPosVal.o PosVal.o

# testFixStrPosVal.o: testFixStrPosVal.cpp
# 	$(CC) $(FLAGS) $(COMMON_OPTION) $(PosVal_OPTION) -c testFixStrPosVal.cpp

# testDoublePosVal: testDoublePosVal.o DoublePosVal.o PosVal.o
# 	$(CC) $(FLAGS) -o $@ testDoublePosVal.o DoublePosVal.o PosVal.o

# testDoublePosVal.o: testDoublePosVal.cpp
# 	$(CC) $(FLAGS) $(COMMON_OPTION) $(PosVal_OPTION) -c testDoublePosVal.cpp

# testFloatPosVal: testFloatPosVal.o FloatPosVal.o PosVal.o
# 	$(CC) $(FLAGS) -o $@ testFloatPosVal.o FloatPosVal.o PosVal.o

# testFloatPosVal.o: testFloatPosVal.cpp
# 	$(CC) $(FLAGS) $(COMMON_OPTION) $(PosVal_OPTION) -c testFloatPosVal.cpp

# testLongPosVal: testLongPosVal.o LongPosVal.o PosVal.o
# 	$(CC) $(FLAGS) -o $@ testLongPosVal.o LongPosVal.o PosVal.o

# testLongPosVal.o: testLongPosVal.cpp
# 	$(CC) $(FLAGS) $(COMMON_OPTION) $(PosVal_OPTION) -c testLongPosVal.cpp

# testIntPosVal: testIntPosVal.o IntPosVal.o PosVal.o
# 	$(CC) $(FLAGS) -o $@ testIntPosVal.o IntPosVal.o PosVal.o

# testIntPosVal.o: testIntPosVal.cpp
# 	$(CC) $(FLAGS) $(COMMON_OPTION) $(PosVal_OPTION) -c testIntPosVal.cpp

