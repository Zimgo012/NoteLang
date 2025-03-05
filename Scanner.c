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
	return EXIT_SUCCESS; /*0*/
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

	/* TO_DO: Follow the standard and adjust datatypes */

	Token currentToken = { 0 }; /* token to return after pattern recognition. Set all structure members to 0 */
	nl_int c;			/* input symbol */
	nl_int state = 0;	/* initial state of the FSM */
	nl_int lexStart;	/* start offset of a lexeme in the input char buffer (array) */
	nl_int lexEnd;		/* end offset of a lexeme in the input char buffer (array)*/

	nl_int lexLength;	/* token length */
	nl_int i;			/* counter */
	///sofia_char newc;		// new char

	/* Starting lexeme */
	nl_string lexeme;	/* lexeme (to check the function) */
	lexeme = (nl_string)malloc(VID_LEN * sizeof(nl_char));
	if (!lexeme)
		return currentToken;
	lexeme[0] = EOS_CHR;

	while (1) { /* endless loop broken by token returns it will generate a warning */
		c = readerGetChar(sourceBuffer);

		// TO_DO: Defensive programming
		if (c < 0 || c >= NCHAR)
			return currentToken;

		/* ------------------------------------------------------------------------
			Part 1: Implementation of token driven scanner.
			Every token is possessed by its own dedicated code
			-----------------------------------------------------------------------
		*/

		/* Part 1: Token-driven scanner for single-char tokens */
		switch (c) {
		case SPC_CHR:
		case TAB_CHR:
			break;
		case SEMICOLON_CHR:  // EOS_T
			currentToken.code = EOS_T;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case LPAREN_CHR:     // LPR_T
			currentToken.code = LPR_T;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case RPAREN_CHR:     // RPR_T
			currentToken.code = RPR_T;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case LBRACE_CHR:     // LBR_T
			currentToken.code = LBR_T;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case RBRACE_CHR:     // RBR_T
			currentToken.code = RBR_T;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case ASSIGN_CHR:     // ASSIGN_T
			currentToken.code = ASSIGN_T;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case LBRACKET_CHR:   // OP_LBRACKET_T
			currentToken.code = OP_LBRACKET_T;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case RBRACKET_CHR:   // OP_RBRACKET_T
			currentToken.code = OP_RBRACKET_T;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case LT_CHR:         // OP_LT_T
			currentToken.code = OP_LT_T;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case GT_CHR:         // OP_GT_T
			currentToken.code = OP_GT_T;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case COMMA_CHR:      // OP_COMMA_T
			currentToken.code = OP_COMMA_T;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case DASH_CHR:       // OP_SUB_T (single -)
			currentToken.code = OP_SUB_T;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case ASTERISK_CHR:   // OP_MUL_T
			currentToken.code = OP_MUL_T;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case SLASH_CHR:      // OP_DIV_T
			currentToken.code = OP_DIV_T;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case EOS_CHR:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_0;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;
		case EOF_CHR:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_255;
			scData.scanHistogram[currentToken.code]++;
			free(lexeme);
			return currentToken;

		/* ------------------------------------------------------------------------
			Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
			Note: Part 2 must follow Part 1 to catch the illegal symbols
			-----------------------------------------------------------------------
		*/

		/* TO_DO: Adjust / check the logic for your language */

		default:
			state = nextState(state, c);
			lexStart = readerGetPosRead(sourceBuffer) - 1;
			readerSetMark(sourceBuffer, lexStart);
			nl_int pos = 0;
			while (stateType[state] == NOFS) {
				c = readerGetChar(sourceBuffer);
				if (c == NEWLINE_CHR) line++;
				state = nextState(state, c);
				pos++;
			}
			if (stateType[state] == FSWR)
				readerRetract(sourceBuffer);
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
			if (!lexeme) {
				readerRestore(lexemeBuffer);
				free(lexeme);
				currentToken.code = ERR_T;
				strcpy(currentToken.attribute.errLexeme, "Lexeme retrieval failed");
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			}
			currentToken = (*finalStateTable[state])(lexeme);
			readerRestore(lexemeBuffer);
			free(lexeme);
			return currentToken;
		} // switch

	} //while

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
	nl_int val = -1;
	switch (c) {
	case EOS_CHR:        return 0;  /* CH00 - \0 */
	case EOF_CHR:        return 1;  /* CH01 - 0xFF */
	case SLASH_CHR:      return 2;  /* CH02 - / */
	case ASTERISK_CHR:   return 3;  /* CH03 - * */
	case LBRACE_CHR:     return 4;  /* CH04 - { */
	case RBRACE_CHR:     return 5;  /* CH05 - } */
	case ASSIGN_CHR:     return 6;  /* CH06 - = */
	case DASH_CHR:       return 7;  /* CH07 - - */
	case LBRACKET_CHR:   return 8;  /* CH08 - [ */
	case RBRACKET_CHR:   return 9;  /* CH09 - ] */
	case SEMICOLON_CHR:  return 10; /* CH10 - ; */
	case EXCLAMATION_CHR: return 11; /* CH11 - ! */
	case QUOTE_CHR:      return 12; /* CH12 - " */
	case LPAREN_CHR:     return 13; /* CH13 - ( */
	case RPAREN_CHR:     return 14; /* CH14 - ) */
	case LT_CHR:         return 15; /* CH15 - < */
	case GT_CHR:         return 16; /* CH16 - > */
	case NEWLINE_CHR:    return 17; /* CH17 - \n */
	case COMMA_CHR:      return 18; /* CH18 - , */
	default:
		if (isdigit(c))  return 19; /* CH19 - [0-9] */
		if (c >= 'A' && c <= 'G') return 21; /* CH21 - [A-G] (notes) */
		if (isalpha(c))  return 20; /* CH20 - [A-Za-z] (letters) */
		return 22;          /* CH22 - Other (^) */
	}
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
	nl_int i = 0, len = (nl_int)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == NEWLINE_CHR)
			line++;
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
	nl_long tlong;
	if (lexeme[0] != EOS_CHR && strlen(lexeme) > NUM_LEN) {
		currentToken = (*finalStateTable[ENR])(lexeme);
	}
	else {
		tlong = atol(lexeme);
		if (tlong >= 0 && tlong <= SHRT_MAX) {
			currentToken.code = INL_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.intValue = (nl_int)tlong;
		}
		else {
			currentToken = (*finalStateTable[ENR])(lexeme);
		}
	}
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
	nl_int length = (nl_int)strlen(lexeme);

	/* Check if lexeme is a keyword first */
	Token kwToken = funcKEY(lexeme);
	if (kwToken.code == KW_T) {
		return kwToken;  /* Return KW_T if it matches a keyword */
	}

	/* If not a keyword, treat as identifier (VID_T) */
	currentToken.code = VID_T;
	scData.scanHistogram[currentToken.code]++;

	/* Copy lexeme to idLexeme, respecting VID_LEN */
	strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
	currentToken.attribute.idLexeme[VID_LEN] = EOS_CHR;  /* Null-terminate */

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
	nl_int i = 0, len = (nl_int)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == NEWLINE_CHR)
			line++;
		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RTE_T;
			scData.scanHistogram[currentToken.code]++;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}
	if (!readerAddChar(stringLiteralTable, EOS_CHR)) {
		currentToken.code = RTE_T;
		scData.scanHistogram[currentToken.code]++;
		strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
		errorNumber = RTE_CODE;
		return currentToken;
	}
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
	nl_int kwindex = -1, j = 0;
	nl_int len = (nl_int)strlen(lexeme);
	///lexeme[len - 1] = EOS_CHR;
	for (j = 0; j < KWT_SIZE; j++)
		if (!strcmp(lexeme, &keywordTable[j][0]))
			kwindex = j;
	if (kwindex != -1) {
		currentToken.code = KW_T;
		scData.scanHistogram[currentToken.code]++;
		currentToken.attribute.codeType = kwindex;
	}
	else {
		currentToken = funcErr(lexeme);
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
	case ERR_T:  /* 0 */
		printf("ERR_T\t\t%s\n", t.attribute.errLexeme);
		break;
	case VID_T:  /* 1 */
		printf("VID_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case INL_T:  /* 2 */
		printf("INL_T\t\t%d\n", t.attribute.intValue);
		break;
	case STR_T:  /* 3 */
		printf("STR_T\t\t%d\t%s\n", t.attribute.contentString,
			readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case LPR_T:  /* 4 */
		printf("LPR_T\t\t(\n");
		break;
	case RPR_T:  /* 5 */
		printf("RPR_T\t\t)\n");
		break;
	case LBR_T:  /* 6 */
		printf("LBR_T\t\t{\n");
		break;
	case RBR_T:  /* 7 */
		printf("RBR_T\t\t}\n");
		break;
	case KW_T:   /* 8 */
		if (t.attribute.keywordIndex >= 0 && t.attribute.keywordIndex < KWT_SIZE)
			printf("KW_T\t\t%s\n", keywordTable[t.attribute.keywordIndex]);
		else
			printf("KW_T\t\t[Invalid index: %d]\n", t.attribute.keywordIndex);
		break;
	case EOS_T:  /* 9 */
		printf("EOS_T\t\t;\n");
		break;
	case ASSIGN_T:  /* 10 */
		printf("ASSIGN_T\t\t=\n");
		break;
	case OP_NOTE_T: /* 11 */
		printf("OP_NOTE_T\t\t->\n");
		break;
	case OP_ADD_T:  /* 12 */
		printf("OP_ADD_T\t\t+\n");
		break;
	case OP_SUB_T:  /* 13 */
		printf("OP_SUB_T\t\t-\n");
		break;
	case OP_MUL_T:  /* 14 */
		printf("OP_MUL_T\t\t*\n");
		break;
	case OP_DIV_T:  /* 15 */
		printf("OP_DIV_T\t\t/\n");
		break;
	case OP_LBRACKET_T: /* 16 */
		printf("OP_LBRACKET_T\t\t[\n");
		break;
	case OP_RBRACKET_T: /* 17 */
		printf("OP_RBRACKET_T\t\t]\n");
		break;
	case OP_EQ_T:  /* 18 */
		printf("OP_EQ_T\t\t==\n");
		break;
	case OP_NE_T:  /* 19 */
		printf("OP_NE_T\t\t!=\n");
		break;
	case OP_LT_T:  /* 20 */
		printf("OP_LT_T\t\t<\n");
		break;
	case OP_GT_T:  /* 21 */
		printf("OP_GT_T\t\t>\n");
		break;
	case OP_COMMA_T: /* 22 */
		printf("OP_COMMA_T\t\t,\n");
		break;
	case CMT_T:  /* 23 */
		printf("CMT_T\n");
		break;
	case SEOF_T: /* 24 */
		printf("SEOF_T\t\t%d\n", t.attribute.seofType);
		break;
	default:
		printf("Scanner error: invalid token code: %d\n", t.code);
		break;
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

	/* Validate lexeme */
	if (len == 1) {
		if (lexeme[0] == EOS_CHR) {  /* \0 */
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_0;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		}
		else if (lexeme[0] == EOF_CHR) {  /* 0xFF */
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_255;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		}
	}
	else if (len == 5 && strncmp(lexeme, "!END;", 5) == 0) {  /* !END; */
		currentToken.code = SEOF_T;
		currentToken.attribute.seofType = SEOF_255;  /* Treat as EOF equivalent */
		scData.scanHistogram[currentToken.code]++;
		return currentToken;
	}

	/* Invalid lexeme for SEOF_T */
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