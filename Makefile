all:
	$(MAKE) MrProper
	$(MAKE) wfiSeq
	$(MAKE) clean

wfiSeq:
	gcc -o buildMakeFile/wfiSequential wfiSequential/main.c

wfiParallel:
	gcc -o buildMakeFile/wfiParallel wfiParallel/main.c

MrProper : clean
	rm -f buildMakeFile/primeNumberFinderSequential
	rm -f buildMakeFile/primeNumberFinderMPI
	rm -f buildMakeFile/twinPrimeNumberFinderMPI
	$(MAKE) clean

clean :
	rm -rf buildMakeFile/*.o


# -----------------OTHER-----------------
#
#FinderSequential:
#	gcc finderSeq/main.c -o buildMakeFile/finderSequential -std=c90 -Wall -O2
#
#PrimeNumberFinderParallel:
#	mpicc primeNumberFinderMPI/main.c -o buildMakeFile/primeNumberFinderMPI -std=c90 -Wall -O2 -lm
#
#TwinPrimeNumberFinderParallelV1:
#	mpicc twinPrimeNumberFinderMpiV1/main.c -o buildMakeFile/twinPrimeNumberFinderMpiV1 -std=c90 -Wall -O2 -lm
#
#TwinPrimeNumberFinderParallelV2:
#	mpicc twinPrimeNumberFinderMpiV2/main.c -o buildMakeFile/twinPrimeNumberFinderMpiV2 -std=c90 -Wall -O2 -lm
#
