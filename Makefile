all:
	$(MAKE) MrProper
	$(MAKE) wfiSeq
	$(MAKE) wfiPar
	$(MAKE) clean

wfiSeq:
	gcc ./wfiSequential/main.c -o buildMakeFile/main.o -c -std=c17 -Wall -O2
	gcc ./wfiSequential/wfiSequential.c -o buildMakeFile/wfiSequential.o -c -std=c17 -Wall -O2
	gcc ./common/commonFunctions.c -o buildMakeFile/commonFunctions.o -c -std=c17 -Wall -O2
	gcc -o buildMakeFile/wfiSequential buildMakeFile/main.o buildMakeFile/wfiSequential.o  buildMakeFile/commonFunctions.o -std=c17 -Wall -O2

wfiPar:
	gcc -o buildMakeFile/wfiOpenCl wfiOpenCl/main.c -lOpenCL -std=c17 -Wall -O2  #-Wextra -Werror -pedantic

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
