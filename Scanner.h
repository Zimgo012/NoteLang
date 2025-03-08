/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2024
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
#
# ECHO "=---------------------------------------="
# ECHO "|  COMPILERS - ALGONQUIN COLLEGE (F24)  |"
# ECHO "=---------------------------------------="
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ”
# ECHO "    @@                             @@    ”
# ECHO "    @@           %&@@@@@@@@@@@     @@    ”
# ECHO "    @@       @%% (@@@@@@@@@  @     @@    ”
# ECHO "    @@      @& @   @ @       @     @@    ”
# ECHO "    @@     @ @ %  / /   @@@@@@     @@    ”
# ECHO "    @@      & @ @  @@              @@    ”
# ECHO "    @@       @/ @*@ @ @   @        @@    ”
# ECHO "    @@           @@@@  @@ @ @      @@    ”
# ECHO "    @@            /@@    @@@ @     @@    ”
# ECHO "    @@     @      / /     @@ @     @@    ”
# ECHO "    @@     @ @@   /@/   @@@ @      @@    ”
# ECHO "    @@     @@@@@@@@@@@@@@@         @@    ”
# ECHO "    @@                             @@    ”
# ECHO "    @@         S O F I A           @@    ”
# ECHO "    @@                             @@    ”
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ”
# ECHO "                                         "
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/

/*
************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2024
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 27

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,			/*  0: Error token */
	VID_T,			/*  1: Variable/method/note identifier (e.g., introPart, secondPart, C4) */
	INL_T,			/*  2: Integer literal token (e.g., 4) */
	STR_T,			/*  3: String literal token (e.g., "Water Melon") */
	LPR_T,			/*  4: Left parenthesis token ( ( ) */
	RPR_T,			/*  5: Right parenthesis token ( ) ) */
	LBR_T,			/*  6: Left brace token ( { ) */
	RBR_T,			/*  7: Right brace token ( } ) */
	KW_T,			/*  8: Keyword token (e.g., df, section, Print) */
	EOS_T,			/*  9: End of statement (semicolon ;) */
	ASSIGN_T,		/* 10: Assignment operator (=) */
	OP_NOTE_T,		/* 11: Note operator (->) */
	OP_ADD_T,		/* 12: Addition operator (+) */
	OP_SUB_T,		/* 13: Subtraction operator (-) */
	OP_MUL_T,		/* 14: Multiplication operator (*) */
	OP_DIV_T,		/* 15: Division operator (/) */
	OP_LBRACKET_T,	/* 16: Left bracket token ( [ ) */
	OP_RBRACKET_T,	/* 17: Right bracket token ( ] ) */
	OP_EQ_T,		/* 18: Equality operator (==) */
	OP_NE_T,		/* 19: Not equal operator (!=) */
	OP_LT_T,		/* 20: Less-than operator (<) */
	OP_GT_T,		/* 21: Greater-than operator (>) */
	OP_COMMA_T,		/* 22: Comma ( , ) */
	CMT_T,			/* 23: Comment token (/** ... **/ 
	SEOF_T,			/* 24: Source end-of-file token */
	RTE_T,			/* 25: Run-time error token */
	NOTE_T			/* 26: Note Token*/
};

/* TO_DO: Define the list of keywords */
static nl_string tokenStrTable[NUM_TOKENS] = {
	"ERR_T",         /*  0: Error token */
	"VID_T",         /*  1: Variable/method/note identifier (e.g., introPart, secondPart, C4) */
	"INL_T",         /*  2: Integer literal token (e.g., 4) */
	"STR_T",         /*  3: String literal token (e.g., "Water Melon") */
	"LPR_T",         /*  4: Left parenthesis token ( ( ) */
	"RPR_T",         /*  5: Right parenthesis token ( ) ) */
	"LBR_T",         /*  6: Left brace token ( { ) */
	"RBR_T",         /*  7: Right brace token ( } ) */
	"KW_T",          /*  8: Keyword token (e.g., df, section, Print) */
	"EOS_T",         /*  9: End of statement (semicolon ;) */
	"ASSIGN_T",      /* 10: Assignment operator (=) */
	"OP_NOTE_T",     /* 11: Note operator (->) */
	"OP_ADD_T",      /* 12: Addition operator (+) */
	"OP_SUB_T",      /* 13: Subtraction operator (-) */
	"OP_MUL_T",      /* 14: Multiplication operator (*) */
	"OP_DIV_T",      /* 15: Division operator (/) */
	"OP_LBRACKET_T", /* 16: Left bracket token ( [ ) */
	"OP_RBRACKET_T", /* 17: Right bracket token ( ] ) */
	"OP_EQ_T",       /* 18: Equality operator (==) */
	"OP_NE_T",       /* 19: Not equal operator (!=) */
	"OP_LT_T",       /* 20: Less-than operator (<) */
	"OP_GT_T",       /* 21: Greater-than operator (>) */
	"OP_COMMA_T",    /* 22: Comma ( , ) */
	"CMT_T",         /* 23: Comment token (/** ... / */
	"SEOF_T",         /* 24: Source end-of-file token */
	"RTE_T",		 /* 25: Run-time error token */
	"NOTE_T"
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators {
	OP_ADD,     /* + */
	OP_SUB,     /* - */
	OP_MUL,     /* * */
	OP_DIV      /* / */
} AriOperator;

typedef enum RelationalOperators {
	OP_EQ,      /* == */
	OP_NE,      /* != */
	OP_GT,      /* > */
	OP_LT,      /* < */
	OP_LE,      /* <= (added for Notelang conditionals) */
	OP_GE       /* >= (added for Notelang conditionals) */
} RelOperator;

/* Logical operators not used in Notelang but retained for potential extension */
typedef enum LogicalOperators {
	OP_AND,     /* && */
	OP_OR,      /* || */
	OP_NOT      /* ! */
} LogOperator;

typedef enum SourceEndOfFile {
	SEOF_0,     /* \0 */
	SEOF_255    /* 0xFF */
} EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	nl_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;    /* Arithmetic operator code (+, -, *, /) */
	RelOperator relationalOperator;    /* Relational operator code (==, !=, >, <, <=, >=) */
	EofOperator seofType;              /* Source end-of-file attribute code */
	nl_int intValue;                   /* Integer literal value (e.g., 4) */
	nl_int keywordIndex;               /* Keyword index in keywordTable (e.g., df -> 0) */
	nl_int contentString;              /* String literal offset in string buffer */
	nl_char idLexeme[VID_LEN + 1];     /* Identifier lexeme (e.g., introPart, C4) */
	nl_char errLexeme[ERR_LEN + 1];    /* Error token lexeme */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttributes {
	nl_byte flags;			/* Flags information */
	union {
		nl_int intValue;				/* Integer value */
		nl_float floatValue;			/* Float value */
		nl_string stringContent;		/* String value */
	} values;
} IdAttributes;

/* Token declaration */
typedef struct Token {
	nl_int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttributes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	nl_int scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////
		
/* TO_DO: Define lexeme FIXED classes */
/* EOF definitions */
#define EOS_CHR        '\0'   /* CH00 - End of string */
#define EOF_CHR        0xFF   /* CH01 - End of file */
#define SLASH_CHR      '/'    /* CH02 - Slash (Q) */
#define ASTERISK_CHR   '*'    /* CH03 - Asterisk (W) */
#define LBRACE_CHR     '{'    /* CH04 - Left brace (R) */
#define RBRACE_CHR     '}'    /* CH05 - Right brace (T) */
#define ASSIGN_CHR     '='    /* CH06 - Assignment (=, E) */
#define DASH_CHR       '-'    /* CH07 - Dash (-, Y) */
#define LBRACKET_CHR   '['    /* CH08 - Left bracket (A) */
#define RBRACKET_CHR   ']'    /* CH09 - Right bracket (B) */
#define SEMICOLON_CHR  ';'    /* CH10 - Semicolon (P) */
#define EXCLAMATION_CHR '!'   /* CH11 - Exclamation mark (X) */
#define QUOTE_CHR      '"'    /* CH12 - Double Quote (S) */
#define LPAREN_CHR     '('    /* CH13 - Left parenthesis (K) */
#define RPAREN_CHR     ')'    /* CH14 - Right parenthesis (M) */
#define LT_CHR         '<'    /* CH15 - Less-than (<, C) */
#define GT_CHR         '>'    /* CH16 - Greater-than (>, D) */
#define NEWLINE_CHR    '\n'   /* CH17 - Newline (I) */
#define COMMA_CHR      ','    /* CH18 - Comma (Z) */
#define DIGIT_CHR      '0'    /* CH19 - Digits [0-9] (N) */
#define LETTER_CHR     'L'    /* CH20 - Letters [A-Za-z] (L) */
#define NOTE_CHR       'N'    /* CH21 - Music notes [A-G] (RESERVED_NOTE) */
#define OTHER_CHR      '^'    /* CH22 - Other characters (O) */
#define SPC_CHR		   ' '	  /* CH23 - Space */		
#define TAB_CHR        '/t'	  /* CH24 - Tab*/	
#define HASH_CHR		'#'	  /* CH25 - Hash (#)*/
/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */


/* TO_DO: Error states and illegal state */
#define ER      100     /* Error state with retract (e.g., invalid start char) */
#define ENR     200     /* Error state with no retract (e.g., mid-token error) */
#define AS      300     /* Accepting state */
#define FS		-1		/* Illegal State */

 /* TO_DO: State transition table definition */
#define NUM_STATES		59
#define CHAR_CLASSES	26

/* TO_DO: Transition table - type of states defined in separate table */
static nl_int transitionTable[NUM_STATES][CHAR_CLASSES] = {
	/*   EOS, EOF,  /,   *,   {,   },   =,   -,   [,   ],   ;,   !,   ",   (,   ),   <,   >,  \n,  ,,   0,   L,   N,   ^,   Sp, Tab,  #  */

	/* S0: Start */
	{   AS,  AS,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  23,  ER,  ER,  ER,  ER,  ER,  ER,  20,   1,  20,  ER,  ER,  ER,  25 },

	/* S1: Recognizing keywords/variables */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,   5,  ER,  ER,  ER,  ER,  25 }, /* All L → S5 */

	/* S2: 'd' (Possible 'df') */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,   4,  ER,  ER,  ER,  ER,  ER },

	/* S3: Note start [A-G] */
	{   ER,  ER,  ER,  ER,  ER,  ER,  ER,  29,  ER,  ER,  AS,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ENR, ENR,  ER,  ER,  ER,  ER,  ER },

	/* S4: 'df' complete */
	{  ENR, ENR, ER,  ER,  ER,  ER,   6,  ER,  ER,  ER,  AS,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,   5,   5,   5,  ER,  ER,  ER,  ER },

	/* S5: Variable name or identifier */
	{  ENR, ENR, ER,  ER,  ER,  ER,   6,  ER,  ER,  ER,  AS,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,   5,   5,   5,  ER,  ER,  ER,  ER },

	/* S6: = */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  23,  ER,  ER,  ER,  ER,  ER,  ER,  10,  10,  10,  ER,  ER,  ER,  ER },

	/* S7: 's' (Possible 'section') */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,   8,  ER,  ER,  ER,  ER,  ER },

	/* S8: 'se' */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,   9,  ER,  ER,  ER,  ER,  ER },

	/* S9: 'sec' */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  12,  ER,  ER,  ER,  ER,  ER },

	/* S10: Value after = */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  11,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

	/* S11: Variable complete */
	{   AS, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  AS,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

	/* S12: 'sect' */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  14,  ER,  ER,  ER,  ER,  ER },

	/* S13: 'P' (Possible 'Print') */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  39,  ER,  ER,  ER,  ER,  ER },

	/* S14: 'secti' */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  16,  ER,  ER,  ER,  ER,  ER },

	/* S15: 'T' (Possible 'Tempo') */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  43,  ER,  ER,  ER,  ER,  ER },

	/* S16: 'sectio' */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  17,  ER,  ER,  ER,  ER,  ER },

	/* S17: 'section' complete */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  AS,  ER,  ER,  18,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

	/* S18: '(' */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  19,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

	/* S19: ')' */
	{  ENR, ENR, ER,  ER,  21,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

	/* S20: Number literal */
	{   AS, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  AS,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  20,  ER,  ER,  ER,  ER,  ER,  ER },

	/* S21: '{' */
	{  ENR, ENR, ER,  ER,  ER,  22,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

	/* S22: Inside function */
	{  ENR, ENR, ER,  ER,  21,  26,  ER,  ER,  ER,  ER,  ER,  ER,  23,  ER,  ER,  ER,  ER,  ER,  ER,  20,   1,   3,  ER,  ER,  ER,  25 },

	/* S23: String literal */
	{  ENR,  ER,  23,  23,  23,  23,  23,  23,  23,  23,  23,  23,  AS,  23,  23,  23,  23,  23,  23,  23,  23,  23,  23,  23,  23,  23 },

	/* S24: Function body content (simplified) */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

	/* S25: Comment start */
	{  ENR, ENR,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37 },

	/* S26: '}' */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  27,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

	/* S27: Section complete */
	{   AS, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  AS,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

	/* S28: 'r' (Possible 'repeatif') */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  47,  ER,  ER,  ER,  ER,  ER },

	/* S29: Note continuation */
	{   AS, ENR, ER,  ER,  30,  ER,  ER,  ER,  ER,  ER,  AS,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

	/* S30: '->' */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  31,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

	/* S31: Note -> complete */
	{  ENR, ENR, ER,  ER,  32,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

	/* S32: '{' for note */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  33,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

	/* S33: Note dynamics */
	{  ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  34,  ER,  ER,  ER,  ER,  ER },

		/* S34: ',' */
	{ ENR, ENR, ER,  ER,  ER,  35,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

		/* S35: Dynamics keyword */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  36,  ER,  ER,  ER,  ER,  ER },

		/* S36: '}' */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  AS,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

		/* S37: Comment body */
	{ ENR, ENR,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  38 },

		/* S38: Comment end */
	{ AS, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  AS,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

		/* S39: 'Pr' */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  40,  ER,  ER,  ER,  ER,  ER },

		/* S40: 'Pri' */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  41,  ER,  ER,  ER,  ER,  ER },

		/* S41: 'Prin' */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  42,  ER,  ER,  ER,  ER,  ER },

		/* S42: 'Print' complete */
	{ ENR, ENR, ER,  ER,  ER,  ER,   6,  ER,  ER,  ER,  AS,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

		/* S43: 'Te' */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  44,  ER,  ER,  ER,  ER,  ER },

		/* S44: 'Tem' */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  45,  ER,  ER,  ER,  ER,  ER },

		/* S45: 'Temp' */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  46,  ER,  ER,  ER,  ER,  ER },

		/* S46: 'Tempo' complete */
	{ ENR, ENR, ER,  ER,  ER,  ER,   6,  ER,  ER,  ER,  AS,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

		/* S47: 're' */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  48,  ER,  ER,  ER,  ER,  ER },

		/* S48: 'rep' */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  49,  ER,  ER,  ER,  ER,  ER },

		/* S49: 'repe' */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  50,  ER,  ER,  ER,  ER,  ER },

		/* S50: 'repea' */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  51,  ER,  ER,  ER,  ER,  ER },

		/* S51: 'repeat' */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  52,  ER,  ER,  ER,  ER,  ER },

		/* S52: 'repeati' */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  53,  ER,  ER,  ER,  ER,  ER },

		/* S53: 'repeatif' complete */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  54,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER },

		/* S54: '<' */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  55,  ER,  ER,  ER,  ER,  ER },

		/* S55: Condition content */
	{ ENR, ENR, ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  ER,  AS,  ER,  ER,  55,  55,  55,  ER,  ER,  ER,  ER }

};


/* Define accepting states types */
#define NOFS	0		/* Not an accepting state */
#define FSNR	1		/* Accepting state with no retract */
#define FSWR	2		/* Accepting state with retract */

/* TO_DO: Define list of acceptable states */
static nl_int stateType[NUM_STATES] = {
	NOFS, /* S0 */  NOFS, /* S1 */  NOFS, /* S2 */  NOFS, /* S3 */  FSWR, /* S4 */  // 'df'
	FSWR, /* S5 */  NOFS, /* S6 */  NOFS, /* S7 */  NOFS, /* S8 */  NOFS, /* S9 */  // Variable, P for Print
	NOFS, /* S10 */ FSNR, /* S11 */ NOFS, /* S12 */ NOFS, /* S13 */ NOFS, /* S14 */ // Variable complete
	NOFS, /* S15 */ NOFS, /* S16 */ FSWR, /* S17 */ NOFS, /* S18 */ NOFS, /* S19 */ // 'section'
	FSNR, /* S20 */ NOFS, /* S21 */ NOFS, /* S22 */ FSNR, /* S23 */ NOFS, /* S24 */ // Number, String
	NOFS, /* S25 */ NOFS, /* S26 */ FSNR, /* S27 */ NOFS, /* S28 */ FSNR, /* S29 */ // Section complete, Note
	NOFS, /* S30 */ NOFS, /* S31 */ NOFS, /* S32 */ NOFS, /* S33 */ NOFS, /* S34 */
	NOFS, /* S35 */ FSNR, /* S36 */ NOFS, /* S37 */ FSNR, /* S38 */ NOFS, /* S39 */ // Note complete, Comment
	NOFS, /* S40 */ NOFS, /* S41 */ FSWR, /* S42 */ NOFS, /* S43 */ NOFS, /* S44 */ // 'Print'
	NOFS, /* S45 */ FSWR, /* S46 */ NOFS, /* S47 */ NOFS, /* S48 */ NOFS, /* S49 */ // 'Tempo'
	NOFS, /* S50 */ NOFS, /* S51 */ NOFS, /* S52 */ FSWR, /* S53 */ NOFS, /* S54 */ // 'repeatif'
	FSNR  /* S55 */ // Condition complete
	/* Ensure NUM_STATES >= 56; add NOFS for S56-S58 if needed */
};


/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
nl_int				startScanner(BufferPointer psc_buf);
static nl_int		nextClass(nl_char c);						/* character class function */
static nl_int		nextState(nl_int, nl_char);					/* state machine function */
nl_void				printScannerData(ScannerData scData);
Token				tokenizer(nl_void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(nl_string lexeme);

/* Declare accepting states functions */
/* Declare accepting state functions for Notelang */
Token funcIL(nl_string lexeme);  /* Integer literal token (INL_T) */
Token funcSL(nl_string lexeme);  /* String literal token (STR_T) */
Token funcID(nl_string lexeme);  /* Identifier token (VID_T: variables, functions, notes) */
Token funcCMT(nl_string lexeme);  /* Comment token (CMT_T) */
Token funcKEY(nl_string lexeme);  /* Keyword token (KW_T) */
Token funcSEOF(nl_string lexeme);  /* Source end-of-file token (SEOF_T) */
Token funcErr(nl_string lexeme);  /* Error token (ERR_T) */
Token funcNOTE(nl_string lxeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,      /* S0 */  NULL,      /* S1 */  NULL,      /* S2 */  NULL,      /* S3 */ funcKEY,   /* S4 */  // 'df'
	funcID,    /* S5 */  NULL,      /* S6 */  NULL,      /* S7 */  NULL,      /* S8 */  NULL,      /* S9 */  // Variable or 'Print' start
	NULL,      /* S10 */ funcID,    /* S11 */ NULL,      /* S12 */ NULL,      /* S13 */ NULL,      /* S14 */ // Variable complete
	NULL,      /* S15 */ NULL,      /* S16 */ funcKEY,   /* S17 */ NULL,      /* S18 */ NULL,      /* S19 */ // 'section'
	funcIL,    /* S20 */ NULL,      /* S21 */ NULL,      /* S22 */ funcSL,    /* S23 */ NULL,      /* S24 */ // Number, String
	NULL,      /* S25 */ NULL,      /* S26 */ funcID,    /* S27 */ NULL,      /* S28 */ funcNOTE,  /* S29 */ // Section complete, Note
	NULL,      /* S30 */ NULL,      /* S31 */ NULL,      /* S32 */ NULL,      /* S33 */ NULL,      /* S34 */
	NULL,      /* S35 */ funcNOTE,  /* S36 */ NULL,      /* S37 */ funcCMT,   /* S38 */ NULL,      /* S39 */ // Note, Comment
	NULL,      /* S40 */ NULL,      /* S41 */ funcKEY,   /* S42 */ NULL,      /* S43 */ NULL,      /* S44 */ // 'Print'
	NULL,      /* S45 */ funcKEY,   /* S46 */ NULL,      /* S47 */ NULL,      /* S48 */ NULL,      /* S49 */ // 'Tempo'
	NULL,      /* S50 */ NULL,      /* S51 */ NULL,      /* S52 */ funcKEY,   /* S53 */ NULL,      /* S54 */ // 'repeatif'
	funcKEY    /* S55 */ // Condition complete (repeaetif)
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 24

/* TO_DO: Define the list of keywords */
static nl_string keywordTable[KWT_SIZE] = {
	/*General Keywords*/
	"df",					/* KW00 - Declare Variables */
	"section",				/* KW01 - Function definition */
	"Print",				/* KW02 - Output */
	"END",					/* KW03 - End of File */

	/*Loop and Control Flow*/
	"repeat",				/* KW04 - Loop */
	"repeatif",				/* KW05 - Conditional Loop */
	"break",				/* KW06 - Break Loop */

	/*Musical Notation*/
	"mf",					/* KW07 - Mezzo-forte */
	"f",					/* KW08 - Forte */
	"ff",					/* KW9  - Fortissimo */
	"fff",					/* KW10 - Triple Forte */
	"ffff",					/* KW11 - Quadruple Forte */ 

	/*Tempo Keywords*/
	"Tempo",				/* KW12 - Set tempo */
	"Grave",				/* KW13 - 40 BPM */
	"Largo",				/* KW14 - 45 BPM */
	"Adagio",				/* KW15 - 65 BPM */
	"Adagietto",			/* KW16 - 69 BPM */
	"Andante",				/* KW17 - 77 BPM */
	"Moderato",				/* KW18 - 77 BPM */
	"Allegretto",			/* KW19 - 109 BPM */
	"Allegro",				/* KW20 - 132 BPM */
	"Vivace",				/* KW21 - 140 BPM */
	"Presto",				/* KW22 - 177 BPM */
	"Prestissimo"			/* KW23 - 180 BPM */

};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT TAB_CHR  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	nl_char indentationCharType;
	nl_int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
nl_int numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif