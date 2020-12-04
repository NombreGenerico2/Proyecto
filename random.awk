#!/usr/bin/awk -f

BEGIN {
	srand();
	n = ARGC > 1 ? ARGV[ARGC-1] : 100;

	printf "%d %d 1 %d\n", n, rand()*n, rand()*n;

	for(i = 0; i < n; i++) {
		for(j = 0; j < 2; j++) {
			printf "%d %d %d\n", i, j, int(rand()*n);
		}
	}
}
