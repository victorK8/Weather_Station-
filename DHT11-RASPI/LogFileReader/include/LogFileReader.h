/************ Library to parser log files  *******************
************* From Weather Station Project *******************
************* By Victor Malumbres Talles   ******************/

#ifndef LOGFILEREADER_H
#define LOGFILEREADER_H

// Include basic modules

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// ****** Functions ******
int GetNumberOfLinesOfFile(char *Filename);
int ConvertLineFromStringToStruct(char *line);
int WriteStatisticFile(char *Filename);

#endif
