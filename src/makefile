FLAGS = -Wall

all: adds pbst opt

adds: adds.c read_adds.c read_adds.h
	gcc $(FLAGS) adds.c read_adds.c -o adds

pbst: pbst.c read_pbst.c read_pbst.h
	gcc $(FLAGS) pbst.c read_pbst.c -o pbst

opt: pbst_opt.c read_pbst.c read_pbst.h
	gcc $(FLAGS) pbst_opt.c read_pbst.c -o opt
