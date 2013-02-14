#CXX =	g++
CXXFLAGS = -g -Wall -funwind-tables -O2
CPPFLAGS = -I /usr/local/BerkeleyDB.4.8/include -I ../COMMON/ -I ../PosVal \
		-I ../NSM -I ../DSM -I ../Node

OBJS =	Encode.o BareEncode.o RLEEncode.o IndexEncode.o MakeDSM.o SortColumn.o
TARGET = libDSM.a

$(TARGET): $(OBJS)
	ar rv $@ $(OBJS)
	ranlib $@
clean:
	rm -f $(OBJS)

distclean:
	rm -f $(OBJS) $(TARGET)

SortColumn.cpp: SortColumn.h
MakeDSM.cpp: MakeDSM.h
IndexEncode.cpp: IndexEncode.h
RLEEncode.cpp: RLEEncode.h
BareEncode.cpp: BareEncode.h
Encode.cpp: Encode.h

# testMakeDSM: MakeDSM.o testMakeDSM.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o BareEncode.o RLEEncode.o testMakeDSM.o MakeDSM.o SortColumn.o $(PV_PATH)RLEElement.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testMakeDSM.o: testMakeDSM.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testMakeDSM.cpp

# testRLEEncode6: RLEEncode.o testRLEEncode6.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o RLEEncode.o testRLEEncode6.o $(PV_PATH)RLEElement.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testRLEEncode6.o: testRLEEncode6.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testRLEEncode6.cpp

# testRLEEncode5: RLEEncode.o testRLEEncode5.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o RLEEncode.o testRLEEncode5.o $(PV_PATH)RLEElement.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testRLEEncode5.o: testRLEEncode5.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testRLEEncode5.cpp

# testRLEEncode4: RLEEncode.o testRLEEncode4.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o RLEEncode.o testRLEEncode4.o $(PV_PATH)RLEElement.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testRLEEncode4.o: testRLEEncode4.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testRLEEncode4.cpp

# testRLEEncode3: RLEEncode.o testRLEEncode3.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o RLEEncode.o testRLEEncode3.o $(PV_PATH)RLEElement.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testRLEEncode3.o: testRLEEncode3.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testRLEEncode3.cpp

# testRLEEncode2: RLEEncode.o testRLEEncode2.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o RLEEncode.o testRLEEncode2.o $(PV_PATH)RLEElement.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testRLEEncode2.o: testRLEEncode2.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testRLEEncode2.cpp

# testRLEEncode1: RLEEncode.o testRLEEncode1.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o RLEEncode.o testRLEEncode1.o $(PV_PATH)RLEElement.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testRLEEncode1.o: testRLEEncode1.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testRLEEncode1.cpp




# testSortColumn: SortColumn.o testSortColumn.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o BareEncode.o SortColumn.o testSortColumn.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testSortColumn.o: testSortColumn.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testSortColumn.cpp 




# testBareEncode7: BareEncode.o testBareEncode7.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o BareEncode.o testBareEncode7.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testBareEncode7.o: testBareEncode7.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testBareEncode7.cpp

# testBareEncode6: BareEncode.o testBareEncode6.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o BareEncode.o testBareEncode6.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testBareEncode6.o: testBareEncode6.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testBareEncode6.cpp

# testBareEncode5: BareEncode.o testBareEncode5.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o BareEncode.o testBareEncode5.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testBareEncode5.o: testBareEncode5.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testBareEncode5.cpp

# testBareEncode4: BareEncode.o testBareEncode4.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o BareEncode.o testBareEncode4.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testBareEncode4.o: testBareEncode4.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testBareEncode4.cpp

# testBareEncode3: BareEncode.o testBareEncode3.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o BareEncode.o testBareEncode3.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testBareEncode3.o: testBareEncode3.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testBareEncode3.cpp

# testBareEncode2: BareEncode.o testBareEncode2.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o BareEncode.o testBareEncode2.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testBareEncode2.o: testBareEncode2.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testBareEncode2.cpp

# testBareEncode1: BareEncode.o testBareEncode1.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ Encode.o BareEncode.o testBareEncode1.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)

# testBareEncode1.o: testBareEncode1.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -c testBareEncode1.cpp

#MakeBareDSM: MakeBareDSM.o BareEncode.o
#	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(PV_FLAGS) -o $@ MakeBareDSM.o BareEncode.o $(PV_OBJE) $(DB_OBJE) $(DB_LIB)
