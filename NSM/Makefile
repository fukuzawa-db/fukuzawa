#CXX =	g++
CXXFLAGS = -g -Wall -O2 #-funwind-tables 
CPPFLAGS = -I/usr/local/BerkeleyDB.4.8/include -I../COMMON/ -I../PosVal

OBJS = MakeNSM.o
TARGET = libNSM.a

$(TARGET): $(OBJS)
	ar rv $@ $(OBJS)
	ranlib $@

clean:
	rm -f $(OBJS)

distclean:
	rm -f $(OBJS) $(TARGET)


MakeNSM.cpp: MakeNSM.h


# .PHONY: allTest
# allTest: testMakeNSM1 testMakeNSM2 testMakeNSM3 testMakeNSM4
# #testRLEEncode1 testRLEEncode2 testRLEEncode3 testRLEEncode4 testRLEEncode5 testRLEEncode6 testSortColumn testBareEncode1 testBareEncode2 testBareEncode3 testBareEncode4 testBareEncode5 testBareEncode6 testBareEncode7

# testMakeNSM4: testMakeNSM4.o MakeNSM.o 
# 	$(CC) $(FLAGS) $(DB_FLAGS) $(COMMON_FLAGS) -o $@ $(DB_OBJE) testMakeNSM4.o MakeNSM.o -ldb_cxx -lpthread

# testMakeNSM4.o: testMakeNSM4.cpp
# 	$(CC) $(FLAGS) $(DB_FLAGS) $(COMMON_FLAGS) -c testMakeNSM4.cpp

# testMakeNSM3: testMakeNSM3.o MakeNSM.o 
# 	$(CC) $(FLAGS) $(DB_FLAGS) $(COMMON_FLAGS) -o $@ $(DB_OBJE) testMakeNSM3.o MakeNSM.o -ldb_cxx -lpthread

# testMakeNSM3.o: testMakeNSM3.cpp
# 	$(CC) $(FLAGS) $(DB_FLAGS) $(COMMON_FLAGS) -c testMakeNSM3.cpp

# testMakeNSM2: testMakeNSM2.o MakeNSM.o 
# 	$(CC) $(FLAGS) $(DB_FLAGS) $(COMMON_FLAGS) -o $@ $(DB_OBJE) testMakeNSM2.o MakeNSM.o -ldb_cxx -lpthread

# testMakeNSM2.o: testMakeNSM2.cpp
# 	$(CC) $(FLAGS) $(DB_FLAGS) $(COMMON_FLAGS) -c testMakeNSM2.cpp

# testMakeNSM1: testMakeNSM1.o MakeNSM.o 
# 	$(CC) $(FLAGS) $(DB_FLAGS) $(COMMON_FLAGS) -o $@ $(DB_OBJE) testMakeNSM1.o MakeNSM.o -ldb_cxx -lpthread

# testMakeNSM1.o: testMakeNSM1.cpp
# 	$(CC) $(FLAGS) $(DB_FLAGS) $(COMMON_FLAGS) -c testMakeNSM1.cpp

