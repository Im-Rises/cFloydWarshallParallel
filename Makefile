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
