#CXX =	g++
CXXFLAGS = -g -Wall -O3
CPPFLAGS = -I /usr/local/BerkeleyDB.4.8/include -I ../COMMON/ -I ../PosVal

OBJS = AttributeManager.o TableManager.o EnvDB.o InMemDB.o BDBOpe.o \
	SecondDB.o IndexExtract.o Timer.o

TARGET = libCOMMON.a

$(TARGET): $(OBJS)
	ar rv $@ $(OBJS)
	ranlib $@

clean:
	rm -f $(OBJS)

distclean:
	rm -f $(OBJS) $(TARGET)

#testAttributeManager: testAttributeManager.o
#	$(CC)  $(FLAGS) $(COMMON_OPTION) $(DB_OPTION) testAttributeManager.o Att#ributeManager.o BDBOpe.o $(DB_LINK)
#testAttributeManager.o: testAttributeManager.cpp
#	$(CC) $(FLAGS) $(COMMON_OPTION) $(DB_OPTION) -c testAttributeManager.cpp# $(DB_LINK)

AttributeManager.cpp: AttributeManager.h
TableManager.cpp: TableManager.h
EnvDB.cpp: EnvDB.h
InMemDB.cpp: InMemDB.h
SecondDB.cpp: SecondDB.h
#SecondDB.cpp: BDBOpe.o SecondDB.h SecondDB.cpp
BDBOpe.cpp: BDBOpe.h
#BDBOpe.o: BDBOpe.h BDBOpe.cpp IndexExtract.o
IndexExtract.cpp: IndexExtract.h
Timer.cpp : Timer.h
