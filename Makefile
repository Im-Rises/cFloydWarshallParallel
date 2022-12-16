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
	gcc ./wfiOpenCl/main.c -o buildMakeFile/main.o -c -std=c17 -Wall -O2
	gcc ./wfiOpenCl/wfiOpenCl.c -o buildMakeFile/wfiOpenCl.o -c -lOpenCL -std=c17 -Wall -O2
	gcc ./common/commonFunctions.c -o buildMakeFile/commonFunctions.o -c -std=c17 -Wall -O2
	gcc -o buildMakeFile/wfiOpenCl buildMakeFile/main.o buildMakeFile/wfiOpenCl.o  buildMakeFile/commonFunctions.o -lOpenCL -std=c17 -Wall -O2

wfiParOneFile:
	gcc -o buildMakeFile/wfiOpenClOneFile wfiOpenClOneFile/main.c -lOpenCL -std=c17 -Wall -O2  #-Wextra -Werror -pedantic

MrProper : clean
	rm -f buildMakeFile/primeNumberFinderSequential
	rm -f buildMakeFile/primeNumberFinderMPI
	rm -f buildMakeFile/twinPrimeNumberFinderMPI
	$(MAKE) clean

clean :
	rm -rf buildMakeFile/*.o
