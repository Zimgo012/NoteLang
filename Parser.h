/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2024
* Author: John Rycca Belcina
* Professors: Paulo Sousa, Sarah Khan
************************************************************
# "=---------------------------------------="
# "|  COMPILERS - ALGONQUIN COLLEGE (F24)  |"
# "=---------------------------------------="
# "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ”
# "    @@                             @@    ”
# "    @@           %&@@@@@@@@@@@     @@    ”
# "    @@       @%% (@@@@@@@@@  @     @@    ”
# "    @@      @& @   @ @       @     @@    ”
# "    @@     @ @ %  / /   @@@@@@     @@    ”
# "    @@      & @ @  @@              @@    ”
# "    @@       @/ @*@ @ @   @        @@    ”
# "    @@           @@@@  @@ @ @      @@    ”
# "    @@            /@@    @@@ @     @@    ”
# "    @@     @      / /     @@ @     @@    ”
# "    @@     @ @@   /@/   @@@ @      @@    ”
# "    @@     @@@@@@@@@@@@@@@         @@    ”
# "    @@                             @@    ”
# "    @@         N O T E L A N G     @@    ”
# "    @@                             @@    ”
# "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ”
# "                                         "
# "[PARSER HEADER ........................]"
# "                                         "
*/

/*
************************************************************
* File name: Parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: 303
* Assignment: A32.
* Date: April 08, 2025
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
************************************************************
*/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferPointer stringLiteralTable;
extern nl_int line;
extern Token tokenizer(nl_void);
extern nl_string keywordTable[KWT_SIZE];
static nl_int syntaxErrorNumber = 0;

/* Constants */
#define STR_LANGNAME "NoteLang"

/* Keywords for NoteLang aligned with Scanner.h */
enum KEYWORDS {
    NO_ATTR = -1,     /* Special attribute for non-keywords */
    KW_df,            /*  0: Variable declaration */
    KW_section,       /*  1: Section definition */
    KW_Print,         /*  2: Print statement */
    KW_END,           /*  3: End of program */
    KW_repeat,        /*  4: Repeat loop */
    KW_repeatif,      /*  5: Conditional repeat */
    KW_break,         /*  6: Break statement */
    KW_mf,            /*  7: Mezzo-forte */
    KW_f,             /*  8: Forte */
    KW_ff,            /*  9: Fortissimo */
    KW_fff,           /* 10: Fortississimo */
    KW_ffff,          /* 11: Quadruple forte */
    KW_Tempo,         /* 12: Tempo setting */
    KW_Grave,         /* 13: 40 BPM */
    KW_Largo,         /* 14: 45 BPM */
    KW_Adagio,        /* 15: 65 BPM */
    KW_Adagietto,     /* 16: 69 BPM */
    KW_Andante,       /* 17: 77 BPM */
    KW_Moderato,      /* 18: 77 BPM */
    KW_Allegretto,    /* 19: 109 BPM */
    KW_Allegro,       /* 20: 132 BPM */
    KW_Vivace,        /* 21: 140 BPM */
    KW_Presto,        /* 22: 177 BPM */
    KW_Prestissimo    /* 23: 180 BPM */
};

/* Number of BNF rules for NoteLang */
#define NUM_BNF_RULES 18

/* Parser */
typedef struct parserData {
    nl_int parsHistogram[NUM_BNF_RULES]; /* Number of BNF Statements */
} ParserData, * pParsData;

/* Number of errors */
nl_int numParserErrors;

/* Scanner data */
ParserData psData;

/* Function definitions */
nl_void startParser();
nl_void matchToken(nl_int, nl_int);
nl_void syncErrorHandler(nl_int);
nl_void printError();
nl_void printBNFData(ParserData psData);

/* List of BNF statements */
enum BNF_RULES {
    BNF_program,              /* 0 */
    BNF_configurationSession, /* 1 */
    BNF_configStatement,      /* 2 */
    BNF_dataSession,          /* 3 */
    BNF_varListDeclarations,  /* 4 */
    BNF_varDeclaration,       /* 5 */
    BNF_codeSession,          /* 6 */
    BNF_section,              /* 7 */
    BNF_noteStatements,       /* 8 */
    BNF_noteStatement,        /* 9 */
    BNF_iterationStatement,   /* 10 */
    BNF_arithmeticExpression, /* 11 */
    BNF_stringExpression,     /* 12 */
    BNF_conditionalExpression,/* 13 */
    BNF_relationalExpression, /* 14 */
    BNF_comment,              /* 15 */
    BNF_outputStatement,      /* 16 */
    BNF_endOfFile             /* 17 */
};

/* BNF string table */
static nl_string BNFStrTable[NUM_BNF_RULES] = {
    "BNF_program",
    "BNF_configurationSession",
    "BNF_configStatement",
    "BNF_dataSession",
    "BNF_varListDeclarations",
    "BNF_varDeclaration",
    "BNF_codeSession",
    "BNF_section",
    "BNF_noteStatements",
    "BNF_noteStatement",
    "BNF_iterationStatement",
    "BNF_arithmeticExpression",
    "BNF_stringExpression",
    "BNF_conditionalExpression",
    "BNF_relationalExpression",
    "BNF_comment",
    "BNF_outputStatement",
    "BNF_endOfFile"
};

/* Non-terminal function declarations */
nl_void program();
nl_void configurationSession();
nl_void configStatement();
nl_void dataSession();
nl_void varListDeclarations();
nl_void varDeclaration();
nl_void codeSession();
nl_void section();
nl_void noteStatements();
nl_void noteStatement();
nl_void iterationStatement();
nl_void arithmeticExpression();
nl_void stringExpression();
nl_void conditionalExpression();
nl_void relationalExpression();
nl_void comment();
nl_void outputStatement();
nl_void endOfFile();

#endif