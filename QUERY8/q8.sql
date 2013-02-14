select o_year, sum(L_EXTENDEDPRICE * (1 - L_DISCOUNT))

from(
	SELECT extract(year from O_ORDERDATE) as o_year, n2.N_NAME, L_EXTENDEDPRICE, L_DISCOUNT
	FROM 	region, nation as n1, nation as n2, customer, orders, lineitem, part, supplier
	WHERE 		r_regionkey = n1.n_regionkey
		and 	c_nationkey = n1.n_nationkey
		and		o_custkey = c_custkey
		and		l_orderkey = o_orderkey
		and		l_partkey = p_partkey
		and		l_suppkey = s_suppkey
		and		s_nationkey = n2.n_nationkey	
		and		r_name = 'AMERICA'
		and		o_orderdate between date '1995-01-01' and date '1996-12-31'
		and		p_type = 'ECONOMY ANODIZED STEEL'
	ORDER BY  L_ORDERKEY, L_PARTKEY, L_SUPPKEY
) as all_nations

group by o_year
;
