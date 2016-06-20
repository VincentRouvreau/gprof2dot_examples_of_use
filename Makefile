naive_time:
	g++ -std=c++11 NaiveFibonacci.cpp -o naive

naive_perf:
	g++ -std=c++11 -g NaiveFibonacci.cpp -o naive
	perf record -g -- ./naive 42
	perf script | c++filt | ./gprof2dot.py -f perf | dot -Tpng -o images/output_naive_perf.png

naive_perf_bis:
	g++ -O2 -std=c++11 -fno-omit-frame-pointer -g NaiveFibonacci.cpp -o naive
	sudo perf record --call-graph fp ./naive 42
	sudo perf report -g -G

naive_callgrind:
	g++ -std=c++11 -g NaiveFibonacci.cpp -o naive
	valgrind --tool=callgrind --callgrind-out-file="callgrind.out" ./naive 38
	./gprof2dot.py --format=callgrind callgrind.out | dot -Tpng -o images/output_naive_callgrind.png

naive_gprof:
	g++ -std=c++11 -pg NaiveFibonacci.cpp -o naive
	./naive 42
	gprof ./naive | ./gprof2dot.py | dot -Tpng -o images/output_naive_gprof.png

para_gprof:
	g++ ParallelFibonacci.cpp -I /usr/include/tbb -ltbb -pg -std=c++11 -o para
	time -p ./para 35
	gprof ./para | ./gprof2dot.py | dot -Tpng -o images/output_para_gprof.png

iter_gprof:
	g++ -std=c++11 -pg IterativeFibonacci.cpp -o iter
	time -p ./iter 42
	gprof ./iter | ./gprof2dot.py | dot -Tpng -o images/output_iter_gprof.png

meta_gprof:
	g++ -std=c++11 -pg MetaFibonacci.cpp -o meta
	time -p ./meta
	gprof ./meta | ./gprof2dot.py | dot -Tpng -o images/output_meta_gprof.png


clean:
	rm -f meta iter naive para gmon.out output.png callgrind.out perf.dat* images/*.png

