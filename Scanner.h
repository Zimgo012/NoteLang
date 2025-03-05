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
#define NUM_TOKENS 26

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
	"SEOF_T"         /* 24: Source end-of-file token */
	"RTE_T"			 /* 25: Run-time error token */
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
#define SPC_CHR		   ' '
#define TAB_CHR        '/t'

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */


/* TO_DO: Error states and illegal state */
#define ER      100     /* Error state with retract (e.g., invalid start char) */
#define ENR     200     /* Error state with no retract (e.g., mid-token error) */
#define AS      300     /* Accepting state */
#define FS		-1		/* Illegal State */

 /* TO_DO: State transition table definition */
#define NUM_STATES		102
#define CHAR_CLASSES	23

/* TO_DO: Transition table - type of states defined in separate table */
static nl_int transitionTable[NUM_STATES][CHAR_CLASSES] = {
	/*   EOS, EOF,  /,   *,   {,   },   =,   -,   [,   ],   ;,   !,   ",   (,   ),   <,   >,  \n,  ,,   0,   L,   N,   ^   */
	/* S0: Start */
	{    AS,  AS,  49,  ER,  ER,  ER,  ER,   7,  ER,  ER,  ER,  55,  80,  ER,  ER,  ER,  ER,  ER,  ER,  70,   1,   3,  ER },

	/* S1: Recognizing keywords/variables - All letters start here */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  20,  10,  20,  ER }, /* L → S20, N → S10 (notes) */

	/* S2: Unused */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR },

	/* S3: Note start [A-G] */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR,   7, ENR, ENR,  AS, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,   5, ENR, ENR,  ER },

	/* S4-S9: Note states */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,   9, ENR, ENR, ENR, ENR, ENR,  ER },
	{   ENR, ENR, ENR, ENR,  11, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  AS, ENR, ENR, ENR, ENR, ENR,   8, ENR, ER , ER , ER , ER ,  ER }, /* S7: -> */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  AS, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER }, /* S8: -> complete */
	{   ENR, ENR, ENR, ENR, ENR,  17, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },

	/* S10: Note or keyword continuation [A-G] or other letters */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  AS, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  20,  20,  20,  ER }, /* Continue identifier or keyword */

	/* S11-S19: Note states */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },
	{    AS, ENR, ENR, ENR, ENR, ENR,  23, ENR, ENR, ENR,  AS, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  22,  22,  ER },
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  80, ENR, ENR, ENR, ENR, ENR, ENR,  24,  24,  24,  ER },
	{    AS, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  30, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  17, ENR,  ER },
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  19, ENR,  ER },
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  AS, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },

	/* S20-S30: Identifier/Keyword states */
	{    AS, ENR, ENR, ENR, ENR, ENR,  23, ENR, ENR, ENR,  AS, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  22,  22,  22,  ER }, /* S20: Identifier start */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER }, /* S21: Unused */
	{    AS, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  AS, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  22,  22,  22,  ER }, /* S22: Continue identifier */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  80, ENR, ENR, ENR, ENR, ENR, ENR,  24,  24,  24,  ER }, /* S23: = */
	{    AS, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  30, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER }, /* S24: Value after = */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },
	{    AS, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  AS, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER }, /* S30: Variable complete */

	/* S31: 'section' start */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  32, ENR, ENR },

	/* S32-S36: 'section' continued */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  33, ENR, ENR },
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  34, ENR, ENR },
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  35, ENR, ENR },
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  36, ENR, ENR },
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  37, ENR, ENR },

	/* S37: 'section' complete */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  AS, ENR, ENR,  38, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },

	/* S38: '(' */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  39, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },

	/* S39: ')' */
	{   ENR, ENR, ENR, ENR,  40, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },

	/* S40: '{' */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },

	/* S41: Inside function */
	{   ENR, ENR,  49, ENR,  40,  43, ER ,   7, ER , ER ,  42,  55,  80, ER , ER , ER , ER , ER , ER ,  70,   1,   3,  ER },

	/* S42: Function end ; */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  44, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },

	/* S43: '}' */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  45, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },

	/* S44: Second ; */
	{   ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  AS, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR, ENR,  ER },

	/* S45-S49: Function end and comment start */
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER ,  50, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , 100 }, /* S49: Comment start */

	/* S50: Comment '*' */
	{   ENR, ENR, ER ,  51, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , 100 },

	/* S51: Comment '**' */
	{   ENR, ENR, ER ,  52, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },

	/* S52: Comment body */
	{   ENR, ENR, ER ,  53,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52 },

	/* S53: Comment ending '*' */
	{   ENR, ENR, ER ,  54,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52 },

	/* S54: Comment ending */
	{   ENR, ENR,  AS,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52 },

	/* S55-S59: !END states */
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  56, ENR,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  57, ENR,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  58, ENR,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , AS , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },

	/* S60: 'Print' start */
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  61, ENR,  ER },

	/* S61-S64: 'Print' continued */
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  62, ENR,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  63, ENR,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  64, ENR,  ER },
	{   ENR, ENR, ER , ER , ER , ER ,  23, ER , ER , ER , AS , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER }, /* S64: 'Print' complete */

	/* S65: 'ff' start */
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  66, ENR,  ER },

	/* S66-S69: 'ff' continued */
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , AS , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },

	/* S70: Number literal */
	{    AS, ENR, ER , ER , ER , ER , ER , ER , ER , ER , AS , ER , ER , ER , ER , ER , ER , ER , ER ,  70, ER ,  70,  AS },

	/* S71-S79: Unused */
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },

	/* S80: String literal */
	{   ENR,  ER,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  AS,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80 },

	/* S81-S89: Unused */
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  ER },

	/* S90: 'repeatif' start */
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  91, ENR,  ER },

	/* S91-S96: 'repeatif' continued */
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  92, ENR,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  93, ENR,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  94, ENR,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  95, ENR,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  96, ENR,  ER },
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  97, ENR,  ER },

	/* S97: 'repeatif' complete */
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER ,  98, ER , ER , ER , ER , ER , ER ,  ER },

	/* S98: '<' for repeatif */
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ENR,  99, ENR,  ER },

	/* S99: Condition content */
	{   ENR, ENR, ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , ER , AS , ER , ER , ENR,  99, ENR,  ER },
};


/* Define accepting states types */
#define NOFS	0		/* Not an accepting state */
#define FSNR	1		/* Accepting state with no retract */
#define FSWR	2		/* Accepting state with retract */

/* TO_DO: Define list of acceptable states */
static nl_int stateType[NUM_STATES] = {
	FSNR, /* S0  - Start (SEOF_T: EOS/EOF) */
	NOFS, /* S1  - Recognizing keywords/variables */
	NOFS, /* S2  - Unused */
	NOFS, /* S3  - Note start [A-G] */
	NOFS, /* S4  - Unused */
	NOFS, /* S5  - Note continuation */
	NOFS, /* S6  - Unused */
	NOFS, /* S7  - Note - or -> */
	FSNR, /* S8  - -> complete (OP_NOTE_T) */
	NOFS, /* S9  - Note { */
	NOFS, /* S10 - Note/keyword continuation */
	FSNR, /* S11 - Unused (was 'df' complete, now reserved) */
	NOFS, /* S12 - Variable name */
	NOFS, /* S13 - Assignment '=' */
	NOFS, /* S14 - String value */
	NOFS, /* S15 - Integer/keyword value */
	NOFS, /* S16 - Unused */
	NOFS, /* S17 - Note dynamics */
	NOFS, /* S18 - Unused */
	FSNR, /* S19 - Note complete (VID_T) */
	FSNR, /* S20 - Identifier/keyword start (VID_T/KW_T) */
	NOFS, /* S21 - Unused */
	FSNR, /* S22 - Identifier continue (VID_T/KW_T) */
	NOFS, /* S23 - = */
	FSNR, /* S24 - Value after = (INL_T/STR_T/VID_T) */
	NOFS, /* S25 - Unused */
	NOFS, /* S26 - Unused */
	NOFS, /* S27 - Unused */
	NOFS, /* S28 - Unused */
	NOFS, /* S29 - Unused */
	FSNR, /* S30 - Variable complete (EOS_T) */
	NOFS, /* S31 - 'section' start */
	NOFS, /* S32 - 'section' continued */
	NOFS, /* S33 - 'section' continued */
	NOFS, /* S34 - 'section' continued */
	NOFS, /* S35 - 'section' continued */
	NOFS, /* S36 - 'section' continued */
	FSNR, /* S37 - 'section' complete (KW_T) */
	NOFS, /* S38 - '(' */
	NOFS, /* S39 - ')' */
	NOFS, /* S40 - '{' */
	NOFS, /* S41 - Inside function */
	NOFS, /* S42 - Function end ; */
	NOFS, /* S43 - '}' */
	FSNR, /* S44 - Second ; (EOS_T) */
	FSNR, /* S45 - Function complete (VID_T) */
	NOFS, /* S46 - Unused */
	NOFS, /* S47 - Unused */
	NOFS, /* S48 - Unused */
	NOFS, /* S49 - Comment start / */
	NOFS, /* S50 - Comment * */
	NOFS, /* S51 - Comment ** */
	NOFS, /* S52 - Comment body */
	NOFS, /* S53 - Comment ending * */
	FSNR, /* S54 - Comment complete (CMT_T) */
	NOFS, /* S55 - '!' for !END */
	NOFS, /* S56 - 'E' in !END */
	NOFS, /* S57 - 'N' in !END */
	FSNR, /* S58 - !END complete (SEOF_T) */
	NOFS, /* S59 - Unused */
	NOFS, /* S60 - 'Print' start */
	NOFS, /* S61 - 'Print' continued */
	NOFS, /* S62 - 'Print' continued */
	NOFS, /* S63 - 'Print' continued */
	FSNR, /* S64 - 'Print' complete (KW_T) */
	NOFS, /* S65 - 'ff' start */
	FSNR, /* S66 - 'ff' complete (KW_T) */
	NOFS, /* S67 - Unused */
	NOFS, /* S68 - Unused */
	NOFS, /* S69 - Unused */
	FSWR, /* S70 - Number complete (INL_T) */
	NOFS, /* S71 - Unused */
	NOFS, /* S72 - Unused */
	NOFS, /* S73 - Unused */
	NOFS, /* S74 - Unused */
	NOFS, /* S75 - Unused */
	NOFS, /* S76 - Unused */
	NOFS, /* S77 - Unused */
	NOFS, /* S78 - Unused */
	NOFS, /* S79 - Unused */
	FSNR, /* S80 - String complete (STR_T) */
	NOFS, /* S81 - Unused */
	NOFS, /* S82 - Unused */
	NOFS, /* S83 - Unused */
	NOFS, /* S84 - Unused */
	NOFS, /* S85 - Unused */
	NOFS, /* S86 - Unused */
	NOFS, /* S87 - Unused */
	NOFS, /* S88 - Unused */
	NOFS, /* S89 - Unused */
	NOFS, /* S90 - 'repeatif' start */
	NOFS, /* S91 - 'repeatif' continued */
	NOFS, /* S92 - 'repeatif' continued */
	NOFS, /* S93 - 'repeatif' continued */
	NOFS, /* S94 - 'repeatif' continued */
	NOFS, /* S95 - 'repeatif' continued */
	NOFS, /* S96 - 'repeatif' continued */
	FSNR, /* S97 - 'repeatif' complete (KW_T) */
	NOFS, /* S98 - '<' for repeatif */
	FSNR, /* S99 - Repeatif condition complete (KW_T) */
	NOFS, /* S100 - Unused */
	NOFS  /* S101 - Unused */
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
	funcSEOF,  /* S0  - Start (SEOF_T) */
	NULL,      /* S1  - Recognizing keywords/variables */
	NULL,      /* S2  - Unused */
	NULL,      /* S3  - Note start [A-G] */
	NULL,      /* S4  - Unused */
	NULL,      /* S5  - Note continuation */
	NULL,      /* S6  - Unused */
	NULL,      /* S7  - Note - or -> */
	funcNOTE,  /* S8  - -> complete (OP_NOTE_T) - New function needed */
	NULL,      /* S9  - Note { */
	NULL,      /* S10 - Note/keyword continuation */
	funcID,    /* S11 - Unused (was 'df', now reserved) */
	NULL,      /* S12 - Variable name */
	NULL,      /* S13 - Assignment '=' */
	NULL,      /* S14 - String value */
	NULL,      /* S15 - Integer/keyword value */
	NULL,      /* S16 - Unused */
	NULL,      /* S17 - Note dynamics */
	NULL,      /* S18 - Unused */
	funcID,    /* S19 - Note complete (VID_T) */
	funcID,    /* S20 - Identifier/keyword start (VID_T/KW_T via funcID) */
	NULL,      /* S21 - Unused */
	funcID,    /* S22 - Identifier continue (VID_T/KW_T via funcID) */
	NULL,      /* S23 - = */
	funcID,    /* S24 - Value after = (INL_T/STR_T/VID_T via funcID) */
	NULL,      /* S25 - Unused */
	NULL,      /* S26 - Unused */
	NULL,      /* S27 - Unused */
	NULL,      /* S28 - Unused */
	NULL,      /* S29 - Unused */
	funcID,    /* S30 - Variable complete (EOS_T) */
	NULL,      /* S31 - 'section' start */
	NULL,      /* S32 - 'section' continued */
	NULL,      /* S33 - 'section' continued */
	NULL,      /* S34 - 'section' continued */
	NULL,      /* S35 - 'section' continued */
	NULL,      /* S36 - 'section' continued */
	funcKEY,   /* S37 - 'section' complete (KW_T) */
	NULL,      /* S38 - '(' */
	NULL,      /* S39 - ')' */
	NULL,      /* S40 - '{' */
	NULL,      /* S41 - Inside function */
	NULL,      /* S42 - Function end ; */
	NULL,      /* S43 - '}' */
	funcID,    /* S44 - Second ; (EOS_T) */
	funcID,    /* S45 - Function complete (VID_T) */
	NULL,      /* S46 - Unused */
	NULL,      /* S47 - Unused */
	NULL,      /* S48 - Unused */
	NULL,      /* S49 - Comment start / */
	NULL,      /* S50 - Comment * */
	NULL,      /* S51 - Comment ** */
	NULL,      /* S52 - Comment body */
	NULL,      /* S53 - Comment ending * */
	funcCMT,   /* S54 - Comment complete (CMT_T) */
	NULL,      /* S55 - '!' for !END */
	NULL,      /* S56 - 'E' in !END */
	NULL,      /* S57 - 'N' in !END */
	funcSEOF,  /* S58 - !END complete (SEOF_T) */
	NULL,      /* S59 - Unused */
	NULL,      /* S60 - 'Print' start */
	NULL,      /* S61 - 'Print' continued */
	NULL,      /* S62 - 'Print' continued */
	NULL,      /* S63 - 'Print' continued */
	funcKEY,   /* S64 - 'Print' complete (KW_T) */
	NULL,      /* S65 - 'ff' start */
	funcKEY,   /* S66 - 'ff' complete (KW_T) */
	NULL,      /* S67 - Unused */
	NULL,      /* S68 - Unused */
	NULL,      /* S69 - Unused */
	funcIL,    /* S70 - Number complete (INL_T) */
	NULL,      /* S71 - Unused */
	NULL,      /* S72 - Unused */
	NULL,      /* S73 - Unused */
	NULL,      /* S74 - Unused */
	NULL,      /* S75 - Unused */
	NULL,      /* S76 - Unused */
	NULL,      /* S77 - Unused */
	NULL,      /* S78 - Unused */
	NULL,      /* S79 - Unused */
	funcSL,    /* S80 - String complete (STR_T) */
	NULL,      /* S81 - Unused */
	NULL,      /* S82 - Unused */
	NULL,      /* S83 - Unused */
	NULL,      /* S84 - Unused */
	NULL,      /* S85 - Unused */
	NULL,      /* S86 - Unused */
	NULL,      /* S87 - Unused */
	NULL,      /* S88 - Unused */
	NULL,      /* S89 - Unused */
	NULL,      /* S90 - 'repeatif' start */
	NULL,      /* S91 - 'repeatif' continued */
	NULL,      /* S92 - 'repeatif' continued */
	NULL,      /* S93 - 'repeatif' continued */
	NULL,      /* S94 - 'repeatif' continued */
	NULL,      /* S95 - 'repeatif' continued */
	NULL,      /* S96 - 'repeatif' continued */
	funcKEY,   /* S97 - 'repeatif' complete (KW_T) */
	NULL,      /* S98 - '<' for repeatif */
	funcKEY,   /* S99 - Repeatif condition complete (KW_T) */
	NULL,      /* S100 - Unused */
	NULL       /* S101 - Unused */
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