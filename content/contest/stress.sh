# ./stress.sh sol brute gen [iters]   (gen.cpp reads seed argv[1]:
#   mt19937 rng(atoi(argv[1])); print a small random test)
for i in $(seq 1 ${4:-500}); do
	./$3 $i > in; ./$1 < in > o1; ./$2 < in > o2
	cmp -s o1 o2 || { echo "diff on seed $i"; cat in; break; }
done
