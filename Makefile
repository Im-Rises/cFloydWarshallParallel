CC=gcc
CFLAGS=-std=c17 -Wall -O2
LDFLAGS=
OPENCL_FLAGS=-lOpenCL
OUTPUT_DIR=buildMakeFile

all:
	$(MAKE) MrProper
	$(MAKE) wfiSeq
	$(MAKE) wfiPar
	$(MAKE) wfiParOneFile
	$(MAKE) clean

wfiSeq: commonFuncs
	$(CC) ./wfiSequential/main.c -o $(OUTPUT_DIR)/main.o -c $(CFLAGS) $(LDFLAGS)
	$(CC) ./wfiSequential/wfiSequential.c -o $(OUTPUT_DIR)/wfiSequential.o -c $(CFLAGS) $(LDFLAGS)
	$(CC) -o $(OUTPUT_DIR)/wfiSequential $(OUTPUT_DIR)/main.o $(OUTPUT_DIR)/wfiSequential.o  $(OUTPUT_DIR)/commonFunctions.o $(CFLAGS) $(LDFLAGS)

wfiPar: commonFuncs
	$(CC) ./wfiOpenCl/main.c -o $(OUTPUT_DIR)/main.o -c $(CFLAGS) $(LDFLAGS)
	$(CC) ./wfiOpenCl/wfiOpenCl.c -o $(OUTPUT_DIR)/wfiOpenCl.o -c $(CFLAGS) $(LDFLAGS) $(OPENCL_FLAGS)
	$(CC) ./common/commonFunctions.c -o $(OUTPUT_DIR)/commonFunctions.o -c $(CFLAGS) $(LDFLAGS)
	$(CC) -o $(OUTPUT_DIR)/wfiOpenCl $(OUTPUT_DIR)/main.o $(OUTPUT_DIR)/wfiOpenCl.o  $(OUTPUT_DIR)/commonFunctions.o $(CFLAGS) $(LDFLAGS) $(OPENCL_FLAGS)

wfiParOneFile: commonFuncs
	$(CC) -o $(OUTPUT_DIR)/wfiOpenClOneFile wfiOpenClOneFile/main.c $(CFLAGS) $(LDFLAGS) $(OPENCL_FLAGS)

commonFuncs:
	$(CC) common/commonFunctions.c -o $(OUTPUT_DIR)/commonFunctions.o -c $(CFLAGS) $(LDFLAGS)

MrProper : clean
	rm -f $(OUTPUT_DIR)/wfiSequential
	rm -f $(OUTPUT_DIR)/wfiOpenCl
	rm -f $(OUTPUT_DIR)/wfiOpenClOneFile
	$(MAKE) clean

clean :
	rm -rf $(OUTPUT_DIR)/*.o
