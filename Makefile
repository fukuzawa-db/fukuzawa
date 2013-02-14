CXXFLAGS = -g -O3 -funwind-tables -Wall
subdirs = COMMON PosVal NSM DSM  Aggregation Node Operation Operation_C \
		InsertOperator \
		ex1_Q6 ex2-Q5 ex3-Q5 ex4-Q5 ex5-Q5 ex6-Q8 ex8-Q5-S20 \
		QUERY5 QUERY6 QUERY8 \
		ShowSys

.PHONY: all clean distclean

all:
	@for d in $(subdirs); \
	do \
		( cd $$d && $(MAKE) CXXFLAGS="$(CXXFLAGS)" ); \
	done

clean:
	for d in $(subdirs); \
	do \
		(cd $$d && $(MAKE) clean); \
	done

distclean:
	for d in $(subdirs); \
	do \
		(cd $$d && $(MAKE) distclean); \
	done

#$(subdirs):
#	$(MAKE) -C $@
