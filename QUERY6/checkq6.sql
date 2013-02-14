select l_orderkey, l_partkey, l_suppkey--sum(l_extendedprice*l_discount) as revenue
from lineitem
where	l_shipdate >= date '1994-01-01'
	and l_shipdate < date '1994-01-01' + interval'1'year
	and l_discount between 0.06 - 0.01 and 0.06 + 0.01
	and l_quantity < 24
order by
  	l_orderkey,  l_partkey, l_suppkey
;   
