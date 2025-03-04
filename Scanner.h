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
#define NUM_TOKENS 25

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,			/*  0: Error token */
	MNID_T,			/*  1: Method name identifier token (start: section) */
	VAR_T,			/*  2: Variable declaration (df) */
	INL_T,			/*  3: Integer literal token */
	STR_T,			/*  4: String literal token */
	LPR_T,			/*  5: Left parenthesis token ( ( ) */
	RPR_T,			/*  6: Right parenthesis token ( ) ) */
	LBR_T,			/*  7: Left brace token ( { ) */
	RBR_T,			/*  8: Right brace token ( } ) */
	KW_T,			/*  9: Keyword token */
	EOS_T,			/* 10: End of statement (semicolon ;) */
	ASSIGN_T,		/* 11: Assignment operator (=) */
	OP_NOTE_T,		/* 12: Note Operator (->) */
	OP_ADD_T,		/* 13: Addition Operator (+) */
	OP_SUB_T,		/* 14: Subtraction Operator (-) */
	OP_MUL_T,		/* 15: Multiplication Operator (*) */
	OP_DIV_T,		/* 16: Division Operator (/) */
	OP_LBRACKET_T,	/* 17: Left bracket token ( [ ) */
	OP_RBRACKET_T,	/* 18: Right bracket token ( ] ) */
	OP_NOT_T,		/* 19: Exclamation mark ( ! ) */
	OP_LT_T,		/* 20: Less-than operator (<) */
	OP_GT_T,		/* 21: Greater-than operator (>) */
	OP_COMMA_T,		/* 22: Comma ( , ) */
	CMT_T,			/* 23: Comment token (/* ... /) */ 
	SEOF_T			/* 24: Source end-of-file token */
};

/* TO_DO: Define the list of keywords */
static nl_string tokenStrTable[NUM_TOKENS] = {
	"ERR_T",         /*  0: Error token */
	"MNID_T",        /*  1: Method name identifier token (section) */
	"VAR_T",         /*  2: Variable declaration (df) */
	"INL_T",         /*  3: Integer literal token */
	"STR_T",         /*  4: String literal token */
	"LPR_T",         /*  5: Left parenthesis token ( ( ) */
	"RPR_T",         /*  6: Right parenthesis token ( ) ) */
	"LBR_T",         /*  7: Left brace token ( { ) */
	"RBR_T",         /*  8: Right brace token ( } ) */
	"KW_T",          /*  9: Keyword token */
	"EOS_T",         /* 10: End of statement (semicolon ;) */
	"ASSIGN_T",      /* 11: Assignment operator (=) */
	"OP_NOTE_T",     /* 12: Note Operator (->) */
	"OP_ADD_T",      /* 13: Addition Operator (+) */
	"OP_SUB_T",      /* 14: Subtraction Operator (-) */
	"OP_MUL_T",      /* 15: Multiplication Operator (*) */
	"OP_DIV_T",      /* 16: Division Operator (/) */
	"OP_LBRACKET_T", /* 17: Left bracket token ( [ ) */
	"OP_RBRACKET_T", /* 18: Right bracket token ( ] ) */
	"OP_NOT_T",      /* 19: Exclamation mark ( ! ) */
	"OP_LT_T",       /* 20: Less-than operator (<) */
	"OP_GT_T",       /* 21: Greater-than operator (>) */
	"OP_COMMA_T",    /* 22: Comma ( , ) */
	"CMT_T",         /* 23: Comment token (/* ... */
	"SEOF_T"         /* 24: Source end-of-file token */
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	nl_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	nl_int intValue;					/* integer literal attribute (value) */
	nl_int keywordIndex;				/* keyword index in the keyword table */
	nl_int contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	nl_float floatValue;				/* floating-point literal attribute (value) */
	nl_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	nl_char errLexeme[ERR_LEN + 1];		/* error token attribite */
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

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */


/* TO_DO: Error states and illegal state */
#define ESNR	8		/* Error state with no retract */
#define ESWR	9		/* Error state with retract */
#define FS		10		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		55
#define CHAR_CLASSES	18

/* TO_DO: Transition table - type of states defined in separate table */
static nl_int transitionTable[NUM_STATES][CHAR_CLASSES] = {

	/*	[A-G],	[-],	[>],	{,		 [0-9],		',',	[mf-f],		},		[df],	[L],	[K],	[M],	[R],	[T],	[P],	[Q],	[W],	other	*/
	{     1,	3,		ESNR,	ESNR,    ESNR,		ESNR,	ESWR,		ESWR,	21,		36,		38,		40,		42,		44,		46,		49,		ESNR,	ESNR	},	// S0: START
	{     FS,   2,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},	// S1: RECOGNIZING
	{	  FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},	// S2: ASNR (MVID)
	{     FS,   FS,		FS,		3,		 FS,		FS,		FS,			FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},	// S3: ASWR (KEY)
	{     FS,   FS,		FS,		FS,	     4,			FS,		FS,			FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},	// S4: NOAS
	{     FS,   FS,		FS,		FS,		 FS,		5,		6,			FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},	// S5: ASNR (SL)
	{     FS,   FS,     FS,		FS,		 FS,		FS,		6,			FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},	// S6: NOAS
	{     FS,   FS,     FS,     FS,		 FS,		FS,		FS,			7,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},	// S7: ASNR (COM)
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},	// S8: ASNR (ES)

	/* Variable df */
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			22,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},	// S9: ASWR (ER)
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		22,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		FS,		FS,		FS,		23,		FS,		FS,		FS,		FS,		FS,		},
	{     FS,   FS,		FS,		FS,		 24,		FS,		FS,			FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		FS,		FS,		FS,		FS,		30,		FS,		FS,		FS,		FS,		},

	/* Section, Function handling*/
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			37,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		38,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		40,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		FS,		42,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		FS,		FS,		44,		FS,		FS,		FS,		FS,		FS,		FS,		},
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		FS,		FS,		FS,		47,		FS,		FS,		FS,		FS,		FS,		},
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},

	/*	Comments */
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		FS,		FS,		FS,		FS,		FS,		50,		FS,		FS,		FS,		},
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		FS,		FS,		FS,		FS,		FS,		51,		FS,		FS,		FS,		},
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		FS,		FS,		FS,		FS,		FS,		52,		FS,		FS,		FS,		},
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		FS,		FS,		FS,		FS,		FS,		54,		FS,		FS,		FS,		},
	{     FS,   FS,		FS,		FS,		 FS,		FS,		FS,			FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		},
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static nl_int stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	FSWR, /* 03 (KEY) */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) */
	NOFS, /* 06 */
	FSNR, /* 07 (COM) */
	FSNR, /* 08 (Err1 - no retract) */
	FSWR  /* 09 (Err2 - retract) */
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
Token funcSL	(nl_string lexeme);
Token funcIL	(nl_string lexeme);
Token funcID	(nl_string lexeme);
Token funcCMT   (nl_string lexeme);
Token funcKEY	(nl_string lexeme);
Token funcErr	(nl_string lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	NULL,		/* -    [06] */
	funcCMT,	/* COM  [07] */
	funcErr,	/* ERR1 [06] */
	funcErr		/* ERR2 [07] */
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
