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
* File name: Scanner.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2024
* Purpose: This file contains all functionalities from Scanner.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

 /* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */

/* #define NDEBUG to suppress assert() call */
#include <assert.h>  /* assert() prototype */

/* project header files */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/*
----------------------------------------------------------------
TO_DO: Global vars definitions
----------------------------------------------------------------
*/

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern BufferPointer stringLiteralTable;	/* String literal table */
nl_int line;								/* Current line number of the source code */
extern nl_int errorNumber;				/* Defined in platy_st.c - run-time error number */

extern nl_int stateType[NUM_STATES];
extern nl_string keywordTable[KWT_SIZE];

extern PTR_ACCFUN finalStateTable[NUM_STATES];
extern nl_int transitionTable[NUM_STATES][CHAR_CLASSES];

/* Local(file) global objects - variables */
static BufferPointer lexemeBuffer;			/* Pointer to temporary lexeme buffer */
static BufferPointer sourceBuffer;			/* Pointer to input source buffer */

/*
 ************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ***********************************************************
 */
 /* TO_DO: Follow the standard and adjust datatypes */

nl_int startScanner(BufferPointer psc_buf) {
	/* TO_DO: Start histogram */
	for (nl_int i=0; i<NUM_TOKENS;i++)
		scData.scanHistogram[i] = 0;
	/* Basic scanner initialization */
	/* in case the buffer has been read previously  */
	readerRecover(psc_buf);
	readerClear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
	printf("Transition check: S49[*] = %d, S52[*] = %d, S53[/] = %d\n",
		transitionTable[49][3], transitionTable[52][3], transitionTable[53][2]);
	return 0;
}

/*
 ************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states 
 *		in the Transition Diagram).
 ***********************************************************
 */

Token tokenizer(nl_void) {
    Token currentToken = { 0 }; /* Token to return */
    nl_int c;                   /* Input symbol */
    nl_int state = 0;           /* Initial state of the FSM */
    nl_int lexStart;            /* Start offset of lexeme */
    nl_int lexEnd;              /* End offset of lexeme */
    nl_int lexLength;           /* Token length */
    nl_int i;                   /* Counter */
    nl_string lexeme;           /* Lexeme buffer */

    /* Allocate lexeme buffer */
    lexeme = (nl_string)malloc(VID_LEN * sizeof(nl_char));
    if (!lexeme) {
        currentToken.code = ERR_T;
        strcpy(currentToken.attribute.errLexeme, "Memory allocation failed");
        scData.scanHistogram[currentToken.code]++;
        return currentToken;
    }
    lexeme[0] = EOS_CHR;

    while (1) {
        c = readerGetChar(sourceBuffer);
        if (c == EOS_CHR || c < 0 || c >= NCHAR) {
            free(lexeme);
            currentToken.code = SEOF_T;
            currentToken.attribute.seofType = SEOF_0;
            scData.scanHistogram[currentToken.code]++;
            return currentToken;
        }

        /* Check for # comments */
        if (c == HASH_CHR) {
            readerSetMark(sourceBuffer, readerGetPosRead(sourceBuffer) - 1);
            lexStart = readerGetPosRead(sourceBuffer) - 1;
            state = 25; /* S25 */
            while (stateType[state] == NOFS && state != ER && state != ENR) {
                c = readerGetChar(sourceBuffer);
                if (c == EOS_CHR || c < 0 || c >= NCHAR) {
                    free(lexeme);
                    currentToken.code = ERR_T;
                    strcpy(currentToken.attribute.errLexeme, "Unterminated comment");
                    scData.scanHistogram[currentToken.code]++;
                    return currentToken;
                }
                if (c == NEWLINE_CHR) line++;
                printf("Comment transition: State %d, Char %c\n", state, c);
                state = nextState(state, c);
                if (state == 38) break; /* S38 */
            }
            if (state == ER || state == ENR) {
                lexEnd = readerGetPosRead(sourceBuffer);
                lexLength = lexEnd - lexStart;
                lexemeBuffer = readerCreate((nl_int)lexLength + 2, 0, MODE_FIXED);
                readerRestore(sourceBuffer);
                for (i = 0; i < lexLength; i++)
                    readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
                readerAddChar(lexemeBuffer, READER_TERMINATOR);
                lexeme = readerGetContent(lexemeBuffer, 0);
                currentToken = funcErr(lexeme);
                readerFree(lexemeBuffer);
                free(lexeme);
                return currentToken;
            }
            lexEnd = readerGetPosRead(sourceBuffer);
            if (stateType[state] == FSWR) readerRetract(sourceBuffer);
            lexEnd = readerGetPosRead(sourceBuffer);
            lexLength = lexEnd - lexStart;
            lexemeBuffer = readerCreate((nl_int)lexLength + 2, 0, MODE_FIXED);
            if (!lexemeBuffer) {
                free(lexeme);
                currentToken.code = ERR_T;
                strcpy(currentToken.attribute.errLexeme, "Buffer creation failed");
                scData.scanHistogram[currentToken.code]++;
                return currentToken;
            }
            readerRestore(sourceBuffer);
            for (i = 0; i < lexLength; i++)
                readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
            readerAddChar(lexemeBuffer, READER_TERMINATOR);
            lexeme = readerGetContent(lexemeBuffer, 0);
            printf("Comment state: %d, Lexeme: %s\n", state, lexeme);
            currentToken = (state == 38) ? funcCMT(lexeme) : funcErr(lexeme);
            readerFree(lexemeBuffer);
            free(lexeme);
            return currentToken;
        }

        /* Single-char tokens */
        switch (c) {
        case SPC_CHR:
        case TAB_CHR:
            break;
        case NEWLINE_CHR:
            line++;
            break;
        case SEMICOLON_CHR:
            currentToken.code = EOS_T;
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            return currentToken;
        case LPAREN_CHR:
            currentToken.code = LPR_T;
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            return currentToken;
        case RPAREN_CHR:
            currentToken.code = RPR_T;
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            return currentToken;
        case LBRACE_CHR:
            currentToken.code = LBR_T;
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            return currentToken;
        case RBRACE_CHR:
            currentToken.code = RBR_T;
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            return currentToken;
        case ASSIGN_CHR:
            currentToken.code = ASSIGN_T;
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            return currentToken;
        case LBRACKET_CHR:
            currentToken.code = OP_LBRACKET_T;
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            return currentToken;
        case RBRACKET_CHR:
            currentToken.code = OP_RBRACKET_T;
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            return currentToken;
        case LT_CHR:
            currentToken.code = OP_LT_T;
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            return currentToken;
        case GT_CHR:
            currentToken.code = OP_GT_T;
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            return currentToken;
        case COMMA_CHR:
            currentToken.code = OP_COMMA_T;
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            return currentToken;
        case DASH_CHR:
            printf("DASH_CHR at Pos: %d\n", readerGetPosRead(sourceBuffer));
            readerSetMark(sourceBuffer, readerGetPosRead(sourceBuffer) - 1);
            nl_char next = readerGetChar(sourceBuffer);
            printf("Next: %c at Pos: %d\n", next, readerGetPosRead(sourceBuffer));
            if (next == GT_CHR) {
                state = 30; /* S30 */
                lexStart = readerGetPosRead(sourceBuffer) - 2;
                lexEnd = readerGetPosRead(sourceBuffer);
                lexLength = lexEnd - lexStart;
                lexemeBuffer = readerCreate((nl_int)lexLength + 2, 0, MODE_FIXED);
                readerRestore(sourceBuffer);
                for (i = 0; i < lexLength; i++)
                    readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
                readerAddChar(lexemeBuffer, READER_TERMINATOR);
                lexeme = readerGetContent(lexemeBuffer, 0);
                currentToken = funcNOTE(lexeme);
                readerFree(lexemeBuffer);
                free(lexeme);
                return currentToken;
            }
            readerRestore(sourceBuffer);
            currentToken.code = OP_SUB_T;
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            printf("Returning OP_SUB_T, Pos: %d\n", readerGetPosRead(sourceBuffer));
            return currentToken;
        case ASTERISK_CHR:
            currentToken.code = OP_MUL_T;
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            return currentToken;
        case SLASH_CHR:
            currentToken.code = OP_DIV_T;
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            return currentToken;
        case QUOTE_CHR:
            readerSetMark(sourceBuffer, readerGetPosRead(sourceBuffer) - 1);
            lexStart = readerGetPosRead(sourceBuffer) - 1;
            state = 23; /* S23 */
            c = readerGetChar(sourceBuffer);
            while (c != QUOTE_CHR && c != EOS_CHR && c >= 0 && c < NCHAR) {
                if (c == NEWLINE_CHR) line++;
                c = readerGetChar(sourceBuffer);
            }
            if (c == EOS_CHR || c < 0 || c >= NCHAR) {
                free(lexeme);
                currentToken.code = ERR_T;
                strcpy(currentToken.attribute.errLexeme, "Unterminated string");
                scData.scanHistogram[currentToken.code]++;
                return currentToken;
            }
            lexEnd = readerGetPosRead(sourceBuffer);
            lexLength = lexEnd - lexStart;
            lexemeBuffer = readerCreate((nl_int)lexLength + 2, 0, MODE_FIXED);
            if (!lexemeBuffer) {
                free(lexeme);
                currentToken.code = ERR_T;
                strcpy(currentToken.attribute.errLexeme, "Buffer creation failed");
                scData.scanHistogram[currentToken.code]++;
                return currentToken;
            }
            readerRestore(sourceBuffer);
            for (i = 0; i < lexLength; i++)
                readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
            readerAddChar(lexemeBuffer, READER_TERMINATOR);
            lexeme = readerGetContent(lexemeBuffer, 0);
            currentToken = funcSL(lexeme);
            readerFree(lexemeBuffer);
            free(lexeme);
            return currentToken;
        case EXCLAMATION_CHR:
            readerSetMark(sourceBuffer, readerGetPosRead(sourceBuffer) - 1);
            lexStart = readerGetPosRead(sourceBuffer) - 1;
            c = readerGetChar(sourceBuffer);
            if (c == 'E') {
                c = readerGetChar(sourceBuffer);
                if (c == 'N') {
                    c = readerGetChar(sourceBuffer);
                    if (c == 'D') {
                        lexEnd = readerGetPosRead(sourceBuffer);
                        lexLength = lexEnd - lexStart;
                        lexemeBuffer = readerCreate((nl_int)lexLength + 2, 0, MODE_FIXED);
                        readerRestore(sourceBuffer);
                        for (i = 0; i < lexLength; i++)
                            readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
                        readerAddChar(lexemeBuffer, READER_TERMINATOR);
                        lexeme = readerGetContent(lexemeBuffer, 0);
                        currentToken = funcKEY("END");
                        if (currentToken.code != KW_T) {
                            currentToken.code = KW_T;
                            currentToken.attribute.keywordIndex = 5; /* END at index 5 */
                            scData.scanHistogram[currentToken.code]++;
                        }
                        readerFree(lexemeBuffer);
                        free(lexeme);
                        return currentToken;
                    }
                }
            }
            readerRestore(sourceBuffer);
            currentToken.code = ERR_T;
            strcpy(currentToken.attribute.errLexeme, "!");
            scData.scanHistogram[currentToken.code]++;
            free(lexeme);
            return currentToken;
        default:
            readerSetMark(sourceBuffer, readerGetPosRead(sourceBuffer) - 1);
            lexStart = readerGetPosRead(sourceBuffer) - 1;
            state = nextState(0, c);

            /* Handle keyword branching at S1 */
            if (state == 1) {
                nl_int nextCol = nextClass(c);
                if (nextCol == 20) { /* Col 20 (L) */
                    switch (c) {
                        case 'P': state = 13; break; /* Print */
                        case 'd': state = 2;  break; /* df */
                        case 's': state = 7;  break; /* section */
                        case 'T': state = 15; break; /* Tempo */
                        case 'r': state = 28; break; /* repeatif */
                        default: state = 5;   break; /* Identifiers */
                    }
                }
            }

            /* Process states until final or error */
            while (stateType[state] == NOFS || state == ER || state == ENR) {
                c = readerGetChar(sourceBuffer);
                if (c == EOS_CHR || c < 0 || c >= NCHAR) break;
                if (c == NEWLINE_CHR) line++;
                nl_int nextCol = nextClass(c);
                /* Stop at delimiters for keywords/identifiers */
                if (nextCol == 23 || nextCol == 10 || nextCol == 6 || nextCol == 12) { /* Space, ;, =, " */
                    readerRetract(sourceBuffer);
                    break;
                }
                state = nextState(state, c);
                if (stateType[state] == FSNR || stateType[state] == FSWR) break;
            }

            lexEnd = readerGetPosRead(sourceBuffer);
            if (state == ER || state == ENR) {
                lexLength = lexEnd - lexStart;
                lexemeBuffer = readerCreate((nl_int)lexLength + 2, 0, MODE_FIXED);
                readerRestore(sourceBuffer);
                for (i = 0; i < lexLength; i++)
                    readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
                readerAddChar(lexemeBuffer, READER_TERMINATOR);
                lexeme = readerGetContent(lexemeBuffer, 0);
                currentToken = funcErr(lexeme);
                readerFree(lexemeBuffer);
                free(lexeme);
                return currentToken;
            }

            if (stateType[state] == FSNR || stateType[state] == FSWR) {
                if (stateType[state] == FSWR) {
                    readerRetract(sourceBuffer);
                    lexEnd = readerGetPosRead(sourceBuffer);
                }
                lexLength = lexEnd - lexStart;
                lexemeBuffer = readerCreate((nl_int)lexLength + 2, 0, MODE_FIXED);
                if (!lexemeBuffer) {
                    free(lexeme);
                    currentToken.code = ERR_T;
                    strcpy(currentToken.attribute.errLexeme, "Buffer creation failed");
                    scData.scanHistogram[currentToken.code]++;
                    return currentToken;
                }
                readerRestore(sourceBuffer);
                for (i = 0; i < lexLength; i++)
                    readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
                readerAddChar(lexemeBuffer, READER_TERMINATOR);
                lexeme = readerGetContent(lexemeBuffer, 0);
                currentToken = (finalStateTable[state] != NULL) ? (*finalStateTable[state])(lexeme) : funcErr(lexeme);
                readerFree(lexemeBuffer);
                free(lexeme);
                return currentToken;
            }
            break;
        } // switch
    } // while
} // tokenizer


/*
 ************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	(*) assert() is a macro that expands to an if statement;
	if test evaluates to false (zero) , assert aborts the program
	(by calling abort()) and sends the following message on stderr:
	(*) Assertion failed: test, file filename, line linenum.
	The filename and linenum listed in the message are the source file name
	and line number where the assert macro appears.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	If you place the #define NDEBUG directive ("no debugging")
	in the source code before the #include <assert.h> directive,
	the effect is to comment out the assert statement.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	The other way to include diagnostics in a program is to use
	conditional preprocessing as shown bellow. It allows the programmer
	to send more details describing the run-time problem.
	Once the program is tested thoroughly #define DEBUG is commented out
	or #undef DEBUG is used - see the top of the file.
 ***********************************************************
 */
 /* TO_DO: Just change the datatypes */
nl_int nextState(nl_int state, nl_char c) {
	nl_int col = nextClass(c);
	nl_int next = transitionTable[state][col];
	printf("nextState: State %d, Char %c, Col %d, Next %d\n", state, c, col, next);
	assert(next != FS);
	return next;

	/*
	nl_int col;
	nl_int next;
	col = nextClass(c);
	next = transitionTable[state][col];
	if (DEBUG)
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
	assert(next != FS);
	if (DEBUG)
		if (next == FS) {
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
			exit(1);
		}
	return next;
	*/
}

/*
 ************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
 ***********************************************************
 */
/* TO_DO: Use your column configuration */

/* Adjust the logic to return next column in TT */
/*    [A-z],[0-9],    _,    &,   \', SEOF,    #, other
	   L(0), D(1), U(2), M(3), Q(4), E(5), C(6),  O(7) */

nl_int nextClass(nl_char c) {
	nl_int col;
		switch (c) {
		case EOS_CHR: col = 0; break;
		case EOF_CHR: col = 1; break;
		case SLASH_CHR: col = 2; break;
		case ASTERISK_CHR: col = 3; break;
		case LBRACE_CHR: col = 4; break;
		case RBRACE_CHR: col = 5; break;
		case ASSIGN_CHR: col = 6; break;
		case DASH_CHR: col = 7; break;
		case LBRACKET_CHR: col = 8; break;
		case RBRACKET_CHR: col = 9; break;
		case SEMICOLON_CHR: col = 10; break;
		case EXCLAMATION_CHR: col = 11; break;
		case QUOTE_CHR: col = 12; break;
		case LPAREN_CHR: col = 13; break;
		case RPAREN_CHR: col = 14; break;
		case LT_CHR: col = 15; break;
		case GT_CHR: col = 16; break;
		case NEWLINE_CHR: col = 17; break;
		case COMMA_CHR: col = 18; break;
		case SPC_CHR: col = 23; break;
		case TAB_CHR: col = 24; break;
		case HASH_CHR: col = 25; break;
		default:
			if (isdigit(c)) col = 19;           /* [0-9] */
			else if (c >= 'A' && c <= 'G') col = 21; /* [A-G] */
			else if (isalpha(c)) col = 20;      /* [A-Za-z] */
			else col = 22;                      /* Other */
			break;
		}
		printf("nextClass: Char %c, Col %d\n", c, col);
		return col;
}

/*
 ************************************************************
 * Acceptance State Function COM
 *		Function responsible to identify COM (comments).
 ***********************************************************
 */
 /* TO_DO: Adjust the function for IL */

Token funcCMT(nl_string lexeme) {

	Token currentToken = { 0 };
	nl_int len = (nl_int)strlen(lexeme);
	if (len < 3 || lexeme[0] != HASH_CHR || lexeme[len - 1] != HASH_CHR) {
		printf("Comment rejected: %s\n", lexeme);
		return funcErr(lexeme);
	}
	for (nl_int i = 0; i < len; i++) {
		if (lexeme[i] == NEWLINE_CHR) line++;
	}
	currentToken.code = CMT_T;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


 /*
  ************************************************************
  * Acceptance State Function IL
  *		Function responsible to identify IL (integer literals).
  * - It is necessary respect the limit (ex: 2-byte integer in C).
  * - In the case of larger lexemes, error shoul be returned.
  * - Only first ERR_LEN characters are accepted and eventually,
  *   additional three dots (...) should be put in the output.
  ***********************************************************
  */
  /* TO_DO: Adjust the function for IL */

Token funcIL(nl_string lexeme) {
	Token currentToken = { 0 };
	nl_long tlong = atol(lexeme);
	if (strlen(lexeme) > NUM_LEN || tlong < 0 || tlong > SHRT_MAX) {
		return funcErr(lexeme);
	}
	currentToken.code = INL_T;
	currentToken.attribute.intValue = (nl_int)tlong;
	scData.scanHistogram[currentToken.code]++;
	printf("Number: %s, Value: %d\n", lexeme, currentToken.attribute.intValue); /* Debug */
	return currentToken;
}


/*
 ************************************************************
 * Acceptance State Function ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for ID */

Token funcID(nl_string lexeme) {
	Token currentToken = { 0 };
	currentToken = funcKEY(lexeme);
	if (currentToken.code == VID_T) {
		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = EOS_CHR;
	}
	return currentToken;
}



/*
************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table 
 *   (stringLiteralTable). You need to include the literals in 
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 ***********************************************************
 */
/* TO_DO: Adjust the function for SL */

Token funcSL(nl_string lexeme) {
	Token currentToken = { 0 };
	nl_int i, len = (nl_int)strlen(lexeme);
	if (len < 2 || lexeme[0] != QUOTE_CHR || lexeme[len - 1] != QUOTE_CHR) {
		printf("String rejected: %s\n", lexeme);
		return funcErr(lexeme);
	}
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == NEWLINE_CHR) line++;
		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RTE_T;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}
	readerAddChar(stringLiteralTable, EOS_CHR);
	currentToken.code = STR_T;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


/*
************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Keywords */

Token funcKEY(nl_string lexeme) {
	Token currentToken = { 0 };
	nl_int kwindex = -1;
	for (nl_int j = 0; j < KWT_SIZE; j++) {
		if (strcmp(lexeme, keywordTable[j]) == 0) {
			kwindex = j;
			break;
		}
	}
	printf("Checking keyword: %s, Index: %d\n", lexeme, kwindex);
	if (kwindex != -1) {
		currentToken.code = KW_T;
		currentToken.attribute.keywordIndex = kwindex;
		scData.scanHistogram[currentToken.code]++;
	}
	else {
		currentToken.code = VID_T;
		scData.scanHistogram[currentToken.code]++;
	}
	return currentToken;
}


/*
************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Errors */

Token funcErr(nl_string lexeme) {
	Token currentToken = { 0 };
	nl_int i = 0, len = (nl_int)strlen(lexeme);
	if (len > ERR_LEN) {
		strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
		currentToken.attribute.errLexeme[ERR_LEN - 3] = EOS_CHR;
		strcat(currentToken.attribute.errLexeme, "...");
	}
	else {
		strcpy(currentToken.attribute.errLexeme, lexeme);
	}
	for (i = 0; i < len; i++)
		if (lexeme[i] == NEWLINE_CHR)
			line++;
	currentToken.code = ERR_T;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


/*
 ************************************************************
 * The function prints the token returned by the scanner
 ***********************************************************
 */
 /*
  ************************************************************
  * Print Token
  * Prints the token’s code and relevant attributes for Notelang.
  * - Uses keywordTable for KW_T and stringLiteralTable for STR_T.
  * - Displays error messages for ERR_T, exits on severe errors.
  ************************************************************
  */
nl_void printToken(Token t) {
	extern nl_string keywordTable[]; /* Link to keyword table in Scanner.h */

	switch (t.code) {
	case ERR_T: printf("ERR_T\t\t%s\n", t.attribute.errLexeme); break;
	case VID_T: printf("VID_T\t\t%s\n", t.attribute.idLexeme); break;
	case INL_T: printf("INL_T\t\t%d\n", t.attribute.intValue); break;
	case STR_T: printf("STR_T\t\t%d\t%s\n", t.attribute.contentString,
		readerGetContent(stringLiteralTable, t.attribute.contentString)); break;
	case LPR_T: printf("LPR_T\t\t(\n"); break;
	case RPR_T: printf("RPR_T\t\t)\n"); break;
	case LBR_T: printf("LBR_T\t\t{\n"); break;
	case RBR_T: printf("RBR_T\t\t}\n"); break;
	case KW_T:  if (t.attribute.keywordIndex >= 0 && t.attribute.keywordIndex < KWT_SIZE)
		printf("KW_T\t\t%s\n", keywordTable[t.attribute.keywordIndex]);
			 else
		printf("KW_T\t\t[Invalid index: %d]\n", t.attribute.keywordIndex); break;
	case EOS_T: printf("EOS_T\t\t;\n"); break;
	case ASSIGN_T: printf("ASSIGN_T\t\t=\n"); break;
	case OP_NOTE_T: printf("OP_NOTE_T\t\t->\n"); break;
	case OP_ADD_T: printf("OP_ADD_T\t\t+\n"); break;
	case OP_SUB_T: printf("OP_SUB_T\t\t-\n"); break;
	case OP_MUL_T: printf("OP_MUL_T\t\t*\n"); break;
	case OP_DIV_T: printf("OP_DIV_T\t\t/\n"); break;
	case OP_LBRACKET_T: printf("OP_LBRACKET_T\t\t[\n"); break;
	case OP_RBRACKET_T: printf("OP_RBRACKET_T\t\t]\n"); break;
	case OP_EQ_T: printf("OP_EQ_T\t\t==\n"); break;
	case OP_NE_T: printf("OP_NE_T\t\t!=\n"); break;
	case OP_LT_T: printf("OP_LT_T\t\t<\n"); break;
	case OP_GT_T: printf("OP_GT_T\t\t>\n"); break;
	case OP_COMMA_T: printf("OP_COMMA_T\t\t,\n"); break;
	case CMT_T: printf("CMT_T\n"); break;
	case SEOF_T: printf("SEOF_T\t\t%d\n", t.attribute.seofType); break;
	default: printf("Scanner error: invalid token code: %d\n", t.code); break;
	}
}

/*
 ************************************************************
 * The function prints statistics of tokens
 * Param:
 *	- Scanner data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
nl_void printScannerData(ScannerData scData) {
	/* Print Scanner statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_TOKENS; cont++) {
		if (scData.scanHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", tokenStrTable[cont], "]=", scData.scanHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}

/*
TO_DO: (If necessary): HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
*/


/* Marks end of file */

Token funcSEOF(nl_string lexeme) {
	Token currentToken = { 0 };
	nl_int len = (nl_int)strlen(lexeme);
	if (len == 1 && (lexeme[0] == EOS_CHR || lexeme[0] == EOF_CHR)) {
		currentToken.code = SEOF_T;
		currentToken.attribute.seofType = (lexeme[0] == EOS_CHR) ? SEOF_0 : SEOF_255;
		scData.scanHistogram[currentToken.code]++;
		return currentToken;
	}
	currentToken.code = ERR_T;
	strncpy(currentToken.attribute.errLexeme, "Invalid SEOF: ", ERR_LEN - 4);
	strncat(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 14);
	currentToken.attribute.errLexeme[ERR_LEN - 1] = EOS_CHR;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}

Token funcNOTE(nl_string lexeme) {
	Token t = { 0 };
	if (strcmp(lexeme, "->") == 0) {
		t.code = OP_NOTE_T;
		scData.scanHistogram[t.code]++;
	}
	else {
		t = funcErr(lexeme);
	}
	return t;
}