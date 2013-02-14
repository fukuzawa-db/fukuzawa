#CXX =	g++
CXXFLAGS = -g -Wall -funwind-tables -O3
CPPFLAGS = -I/usr/local/BerkeleyDB.4.8/include -I../COMMON/ -I../PosVal \
		-I../NSM -I../DSM
OBJS = AxprNode.o ColumnRefNode.o ValueNode.o ArithmeticNode.o
TARGET = libNode.a

$(TARGET): $(OBJS)
	ar rv $@ $(OBJS)
	ranlib $@

clean:
	rm -f $(OBJS)

distclean:
	rm -f $(OBJS) $(TARGET)

ArithmeticNode.cpp: ArithmeticNode.h Node.h
ValueNode.cpp: ValueNode.h Node.h
ColumnRefNode.cpp: ColumnRefNode.h Node.h
AxprNode.cpp: AxprNode.h Node.h

# .PHONY: allTest
# allTest:

# test2: test2.o Node.h ArithmeticNode.o ColumnRefNode.o ValueNode.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(NSM_FLAGS) $(DSM_FLAGS) $(PV_FLAGS) -o $@ test2.o ArithmeticNode.o ColumnRefNode.o ValueNode.o $(PV_OBJE)

# test2.o: test2.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(NSM_FLAGS) $(DSM_FLAGS) $(PV_FLAGS) -c test2.cpp


# test: test.o Node.h AxprNode.o ColumnRefNode.o ValueNode.o
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(NSM_FLAGS) $(DSM_FLAGS) $(PV_FLAGS) -o $@ test.o AxprNode.o ColumnRefNode.o ValueNode.o $(PV_OBJE)

# test.o: test.cpp
# 	$(CC) $(FLAGS) $(COMMON_FLAGS) $(DB_FLAGS) $(NSM_FLAGS) $(DSM_FLAGS) $(PV_FLAGS) -c test.cpp

