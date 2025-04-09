/*
************************************************************
* File name: MainParser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Parser (A32)
************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/* Global objects - variables */
static BufferPointer sourceBuffer;
BufferPointer stringLiteralTable;
nl_int errorNumber = 0;

/* External objects */
extern nl_int syntaxErrorNumber;
extern nl_int line;
extern ParserData psData;

/* Function declarations */
extern nl_void startParser(sofia_void);
extern nl_int startScanner(BufferPointer sc_buf);

static nl_void printParserError(nl_string fmt, ...);
static nl_void displayParser(BufferPointer ptrBuffer);
static nl_long getParserFileSize(nl_string fname);
static nl_void callGarbageCollector(sofia_void);
static nl_int isNumber(const nl_string ns);

/*
************************************************************
* Parser Main function
************************************************************
*/
nl_int mainParser(nl_int argc, nl_string* argv) {
    numParserErrors = 0;
    FILE* fi;
    nl_int loadsize = 0;
    nl_string program = argv[0];
    nl_string input = argv[2];
    nl_char mode = MODE_MULTI;  // Default mode
    nl_int bufferSize = READER_DEFAULT_SIZE;
    nl_int bufferIncrement = READER_DEFAULT_INCREMENT;
    nl_int wrongNumber = 0;

    /* Check for minimum arguments */
    if (argc <= 2) {
        printParserError("\nDate: %s  Time: %s", __DATE__, __TIME__);
        printParserError("\nRuntime error at line %d in file %s\n", __LINE__, __FILE__);
        printParserError("%s%s", program, ": Missing parameters.");
        printParserError("Usage: %s <Option=2> <SourceFile> [<Mode> <Size> <Increment>]", program);
        exit(EXIT_FAILURE);
    }

    /* Parse additional arguments */
    if (argc >= 4) {
        mode = *argv[3];
        switch (mode) {
        case MODE_FIXED:
        case MODE_ADDIT:
        case MODE_MULTI:
            break;
        default:
            printParserError("%s%s%c%s%c%s%c%s", program, ": Wrong mode - choose: ",
                MODE_FIXED, ", ", MODE_ADDIT, ", ", MODE_MULTI, ".");
            exit(EXIT_FAILURE);
        }
    }
    if (argc == 6) {
        mode = *argv[3];
        if (isNumber(argv[4])) {
            bufferSize = atoi(argv[4]);
            if (bufferSize <= 0) bufferSize = READER_DEFAULT_SIZE;
        }
        else {
            wrongNumber = 1;
        }
        if (isNumber(argv[5])) {
            bufferIncrement = atoi(argv[5]);
            if (bufferIncrement <= 0) bufferIncrement = READER_DEFAULT_INCREMENT;
        }
        else {
            wrongNumber = 1;
        }
        if (wrongNumber) {
            printParserError("\nDate: %s  Time: %s", __DATE__, __TIME__);
            printParserError("\nRuntime error at line %d in file %s\n", __LINE__, __FILE__);
            printParserError("%s%s", program, ": Missing or wrong number parameters.");
            printParserError("Usage: %s <Option=2> <SourceFile> [<Mode> <Size> <Increment>]", program);
            exit(EXIT_FAILURE);
        }
    }

    /* Create source buffer with custom settings */
    sourceBuffer = readerCreate(bufferSize, bufferIncrement, mode);
    if (sourceBuffer == NULL) {
        printParserError("%s%s%s", program, ": ", "Could not create source buffer");
        exit(EXIT_FAILURE);
    }

    /* Open source file */
    if ((fi = fopen(input, "r")) == NULL) {
        printParserError("%s%s%s%s", program, ": ", "Cannot open file: ", input);
        exit(EXIT_FAILURE);
    }

    /* Load source file */
    printf("Reading file %s ....Please wait\n", input);
    loadsize = readerLoad(sourceBuffer, fi);
    if (loadsize == -1) {
        printParserError("%s%s%s", program, ": ", "Error in loading buffer.");
    }
    fclose(fi);

    if (loadsize == -1) {
        printf("The input file %s %s\n", input, "is not completely loaded.");
        printf("Input file size: %ld\n", getParserFileSize(input));
    }

    if ((loadsize != -1) && (loadsize != 0)) {
        if (readerAddChar(sourceBuffer, READER_TERMINATOR)) {
            displayParser(sourceBuffer);
        }
    }

    /* Create string literal table */
    stringLiteralTable = readerCreate(bufferSize, bufferIncrement, MODE_ADDIT);
    if (stringLiteralTable == NULL) {
        printParserError("%s%s%s", program, ": ", "Could not create string literal buffer");
        exit(EXIT_FAILURE);
    }

    atexit(callGarbageCollector);
    startScanner(sourceBuffer);

    printf("\nParsing the source file...\n\n");
    startParser();

    printf("\nNumber of Parser errors: %d\n", numParserErrors);
    printBNFData(psData);

    return EXIT_SUCCESS;
}

/*
************************************************************
* Error printing function
************************************************************
*/
nl_void printParserError(nl_string fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    (nl_void)vfprintf(stderr, fmt, ap);
    va_end(ap);
    if (strchr(fmt, '\n') == NULL) fprintf(stderr, "\n");
}

/*
************************************************************
* Display buffer contents
************************************************************
*/
nl_void displayParser(BufferPointer ptrBuffer) {
    printf("\nPrinting input buffer parameters:\n\n");
    printf("The capacity of the buffer is:  %d\n", readerGetSize(ptrBuffer));
    printf("The current size of the buffer is:  %d\n", readerGetPosWrte(ptrBuffer));
    printf("\nPrinting input buffer contents:\n\n");
    readerRecover(ptrBuffer);
    readerPrint(ptrBuffer);
}

/*
************************************************************
* Get file size
************************************************************
*/
nl_long getParserFileSize(nl_string fname) {
    FILE* input;
    nl_long flength;
    input = fopen(fname, "r");
    if (input == NULL) {
        printParserError("%s%s", "Cannot open file: ", fname);
        return 0;
    }
    fseek(input, 0L, SEEK_END);
    flength = ftell(input);
    fclose(input);
    return flength;
}

/*
************************************************************
* Garbage collector
************************************************************
*/
nl_void callGarbageCollector(nl_void) {
    if (syntaxErrorNumber) printf("\nSyntax errors: %d\n", syntaxErrorNumber);
    printf("\nCollecting garbage...\n");
    readerFree(sourceBuffer);
    readerFree(stringLiteralTable);
}

/*
************************************************************
* Check if string is a number
************************************************************
*/
nl_int isNumber(const nl_string ns) {
    nl_char c;
    nl_int i = 0;
    if (ns == NULL) return 0;
    while ((c = ns[i++]) != 0) {  // Fixed from == 0 to != 0
        if (!isdigit(c)) return 0;
    }
    return 1;
}