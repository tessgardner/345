# Which version to compile with?

### x86-64:
signalTools_x86.lib

### Apple Silicon (m-chip):
signalTools_amac.lib

### Other ARM (works with m-chip Mac's booting an ARM VM):
signalTools_arm.lib

## Compile command should look like:

gcc sigHandler.c -o sigHandler ./signalTools_x86.lib

gcc sigHandler.c -o sigHandler ./signalTools_amac.lib

gcc sigHandler.c -o sigHandler ./signalTools_arm.lib


## FOR YOU TESS:
gcc sigHandler.c -o sigHandler -L. -lsignalTools_x86
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
./sigHandler