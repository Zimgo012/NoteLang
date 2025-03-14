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
	readerRecover(psc_buf);
	readerClear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
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
    Token currentToken = { 0 };
    nl_int c;
    nl_int state = 0;
    nl_int lexStart;
    nl_int lexEnd;
    nl_int lexLength;
    nl_int i;
    nl_string lexeme;

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
        case HASH_CHR:
            // ... (unchanged comment logic) ...
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
                //printf("Comment transition: State %d, Char %c\n", state, c); // for debug
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
            // printf("Comment state: %d, Lexeme: %s\n", state, lexeme); // for debug
            currentToken = (state == 38) ? funcCMT(lexeme) : funcErr(lexeme);
            readerFree(lexemeBuffer);
            free(lexeme);
            return currentToken;
        case QUOTE_CHR:
            // ... (unchanged string logic) ...
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
        case DASH_CHR:
            readerSetMark(sourceBuffer, readerGetPosRead(sourceBuffer) - 1);
            lexStart = readerGetPosRead(sourceBuffer) - 1;
            nl_char next = readerGetChar(sourceBuffer);
            if (next == GT_CHR) { // Check for ->
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
                currentToken = funcNOTE(lexeme); // Should return OP_NOTE_T for "->"
                readerFree(lexemeBuffer);
                free(lexeme);
                return currentToken;
            }
            readerRestore(sourceBuffer); // Reset to try default case or OP_SUB_T
            currentToken.code = OP_SUB_T;
            scData.scanHistogram[currentToken.code]++;
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
                        currentToken = funcKEY("END"); // Pass "END" directly
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
            lexEnd = 0;
            state = nextState(0, c);

            // Handle numbers
            if (state == 20) {
                while (state == 20) {
                    c = readerGetChar(sourceBuffer);
                    if (c == EOS_CHR || c < 0 || c >= NCHAR) break;
                    if (c == NEWLINE_CHR) line++;
                    nl_int nextCol = nextClass(c);
                    if (nextCol != 19) { // Only digits continue
                        readerRetract(sourceBuffer);
                        break;
                    }
                    state = nextState(state, c);
                }
            }
            // Handle identifiers, keywords, and notes
            else if (state == 1 || state == 3) { // Start of identifiers/keywords (S1) or notes (S3)
                while (stateType[state] == NOFS || state == 5 || state == 56 || state == 30) { // S5, S56, S30
                    c = readerGetChar(sourceBuffer);
                    if (c == EOS_CHR || c < 0 || c >= NCHAR) break;
                    if (c == NEWLINE_CHR) line++;
                    nl_int nextCol = nextClass(c);
                    if (nextCol != 20 && nextCol != 19 && nextCol != 7 && nextCol != 16) {
                        nl_int tempPos = readerGetPosRead(sourceBuffer);
                        if (stateType[state] == FSWR) {
                            char nextChar = readerGetChar(sourceBuffer); // Peek
                            if (nextChar == '(') lexEnd = tempPos - 1; // Before '('
                            else lexEnd = tempPos - 1; // Before delimiter
                            readerRetract(sourceBuffer);
                        }
                        else if (state == 56) { // Note complete
                            readerRetract(sourceBuffer);
                            lexEnd = tempPos - 1; // Before space or -
                            break; // Process NOTE_T
                        }
                        else { // FSNR (S5, S30)
                            readerRetract(sourceBuffer);
                            lexEnd = tempPos; // Include last char
                        }
                        break;
                    }
                    state = nextState(state, c);
                }
                if (state == 1) { // Single-letter identifier
                    state = 5;
                    lexEnd = readerGetPosRead(sourceBuffer);
                }
            }

            // Build token
            if (stateType[state] == FSNR || stateType[state] == FSWR) {
                if (lexEnd == 0) lexEnd = readerGetPosRead(sourceBuffer);
                lexLength = lexEnd - lexStart;
                if (stateType[state] == FSNR && state != 56) lexLength++; // Include last char for FSNR except S56
               // printf("Debug: State=%d, lexLength=%ld, lexStart=%ld, lexEnd=%ld\n", state, lexLength, lexStart, lexEnd);
                if (lexLength <= 0) {
                    free(lexeme);
                    currentToken.code = ERR_T;
                    strcpy(currentToken.attribute.errLexeme, "Empty lexeme");
                    scData.scanHistogram[currentToken.code]++;
                    return currentToken;
                }
                lexemeBuffer = readerCreate((nl_int)lexLength + 2, 0, MODE_FIXED);
                if (!lexemeBuffer) {
                    free(lexeme);
                    currentToken.code = ERR_T;
                    strcpy(currentToken.attribute.errLexeme, "Buffer creation failed");
                    scData.scanHistogram[currentToken.code]++;
                    return currentToken;
                }
                readerRestore(sourceBuffer);
                for (i = 0; i < lexLength; i++) {
                    char ch = readerGetChar(sourceBuffer);
                    if (ch == EOS_CHR || ch < 0 || ch >= NCHAR) break;
                    readerAddChar(lexemeBuffer, ch);
                }
                readerAddChar(lexemeBuffer, READER_TERMINATOR);
                lexeme = readerGetContent(lexemeBuffer, 0);
                // printf("Debug: State=%d, Lexeme=%s, Length=%ld, lexStart=%ld, lexEnd=%ld\n", state, lexeme, lexLength, lexStart, lexEnd);
                currentToken = (finalStateTable[state] != NULL) ? (*finalStateTable[state])(lexeme) : funcErr(lexeme);
                readerFree(lexemeBuffer);
                free(lexeme);
                return currentToken;
            }
            else {
                lexEnd = readerGetPosRead(sourceBuffer);
                free(lexeme);
                currentToken.code = ERR_T;
                strcpy(currentToken.attribute.errLexeme, "Invalid token");
                scData.scanHistogram[currentToken.code]++;
                return currentToken;
            }
            break;
        }
    }
}


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
	// printf("nextState: State %d, Char %c, Col %d, Next %d\n", state, c, col, next);
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
    case EOS_CHR: col = 0; break;         /* CH00 - \0 */
    case EOF_CHR: col = 1; break;         /* CH01 - 0xFF */
    case SLASH_CHR: col = 2; break;       /* CH02 - / */
    case ASTERISK_CHR: col = 3; break;    /* CH03 - * */
    case LBRACE_CHR: col = 4; break;      /* CH04 - { */
    case RBRACE_CHR: col = 5; break;      /* CH05 - } */
    case ASSIGN_CHR: col = 6; break;      /* CH06 - = */
    case DASH_CHR: col = 7; break;        /* CH07 - - */
    case LBRACKET_CHR: col = 8; break;    /* CH08 - [ */
    case RBRACKET_CHR: col = 9; break;    /* CH09 - ] */
    case SEMICOLON_CHR: col = 10; break;  /* CH10 - ; */
    case EXCLAMATION_CHR: col = 11; break;/* CH11 - ! */
    case QUOTE_CHR: col = 12; break;      /* CH12 - " */
    case LPAREN_CHR: col = 13; break;     /* CH13 - ( */
    case RPAREN_CHR: col = 14; break;     /* CH14 - ) */
    case LT_CHR: col = 15; break;         /* CH15 - < */
    case GT_CHR: col = 16; break;         /* CH16 - > */
    case NEWLINE_CHR: col = 17; break;    /* CH17 - \n */
    case COMMA_CHR: col = 18; break;      /* CH18 - , */
    case SPC_CHR: col = 23; break;        /* CH23 - Space */
    case '\t': col = 24; break;           /* CH24 - Tab (fixed from '/t') */
    case HASH_CHR: col = 25; break;       /* CH25 - # */
    default:
        if (isdigit(c)) col = 19;           /* CH19 - [0-9] */
        else if (c >= 'A' && c <= 'G') col = 21; /* CH21 - [A-G] */
        else if (isalpha(c)) col = 20;      /* CH20 - [A-Za-z] excluding [A-G] */
        else col = 22;                      /* CH22 - Other */
        break;
    }
    // Handle unprintable characters in debug output
    /*
    if (c == NEWLINE_CHR) {
        printf("nextClass: Char \\n, Col %d\n", col);
    }
    else if (c == '\t') {
        printf("nextClass: Char \\t, Col %d\n", col);
    }
    else if (c == EOS_CHR) {
        printf("nextClass: Char \\0, Col %d\n", col);
    }
    else {
        printf("nextClass: Char %c, Col %d\n", c, col);
    }*/
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
    strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN); /* Store lexeme */
    currentToken.attribute.errLexeme[ERR_LEN - 1] = EOS_CHR;    /* Ensure null-terminated */
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
    nl_int kwindex = -1;
    for (nl_int j = 0; j < KWT_SIZE; j++) {
        if (strcmp(lexeme, keywordTable[j]) == 0) {
            kwindex = j;
            break;
        }
    }
    if (kwindex != -1) {
        currentToken.code = KW_T;
        currentToken.attribute.keywordIndex = kwindex;
    }
    else {
        currentToken.code = VID_T;
        strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
        currentToken.attribute.idLexeme[VID_LEN - 1] = EOS_CHR;
    }
    scData.scanHistogram[currentToken.code]++;
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
    readerAddChar(stringLiteralTable, EOS_CHR); /* Ensure null terminator */
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
    case VID_T:
        printf("VID_T\t\t%s\n", t.attribute.idLexeme[0] ? t.attribute.idLexeme : "[empty]");
        break;
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
    case CMT_T: printf("CMT_T\t\t%s\n", t.attribute.errLexeme); break;
    case SEOF_T: printf("SEOF_T\t\t%d\n", t.attribute.seofType); break;
    case NOTE_T: printf("NOTE_T\t\t%s\n", t.attribute.idLexeme); break;
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
    Token currentToken = { 0 };
    if (strcmp(lexeme, "->") == 0) {
        currentToken.code = OP_NOTE_T;
    }
    else {
        /* Check if it's a valid note: [A-G][0-8] */
        if (strlen(lexeme) == 2 &&
            (lexeme[0] >= 'A' && lexeme[0] <= 'G') &&
            (lexeme[1] >= '0' && lexeme[1] <= '8')) {
            currentToken.code = NOTE_T;
            strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
        }
        else {
            currentToken.code = ERR_T;
            strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN);
            strcpy(currentToken.attribute.errLexeme, "Invalid note");
        }
    }
    scData.scanHistogram[currentToken.code]++;
    return currentToken;
}