#include <stdio.h>
#include "dataimporter.h"
#include "construct_state_header.h"

int dataimport_test(void) {

    FILE *file = open_file("FILE_NAME", 'r');
    filesize f = ScanFile(file);
    char **dataStruct = Allocate2dCHARarray(f.lineCount, f.longestLine);
    ReadFileDataInto2dCHARarray(file, dataStruct, f.lineCount, f.longestLine, '\n');
    fclose(file);
    int **resultArray = ConvertToInt(dataStruct,f.lineCount,f.longestLine);
    Print2dArrayCHAR(dataStruct,f.lineCount,f.longestLine);
    Free2dArrayCHAR(dataStruct,f.lineCount);
    Free2dArrayINT(resultArray,f.lineCount);

    return 0;
}
