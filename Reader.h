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
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    �
# ECHO "    @@                             @@    �
# ECHO "    @@           %&@@@@@@@@@@@     @@    �
# ECHO "    @@       @%% (@@@@@@@@@  @     @@    �
# ECHO "    @@      @& @   @ @       @     @@    �
# ECHO "    @@     @ @ %  / /   @@@@@@     @@    �
# ECHO "    @@      & @ @  @@              @@    �
# ECHO "    @@       @/ @*@ @ @   @        @@    �
# ECHO "    @@           @@@@  @@ @ @      @@    �
# ECHO "    @@            /@@    @@@ @     @@    �
# ECHO "    @@     @      / /     @@ @     @@    �
# ECHO "    @@     @ @@   /@/   @@@ @      @@    �
# ECHO "    @@     @@@@@@@@@@@@@@@         @@    �
# ECHO "    @@                             @@    �
# ECHO "    @@         S O F I A           @@    �
# ECHO "    @@                             @@    �
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    �
# ECHO "                                         "
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2024
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct flag {
	nl_boln isEmpty;			/* indicates if the buffer is empty */
	nl_boln isFull;			/* indicates if the buffer is full */
	nl_boln isRead;			/* indicates if the buffer was completely read */
	nl_boln isMoved;			/* indicates if the buffer memory was changed */
} Flag;

/* Offset declaration */
typedef struct position {
	nl_int wrte;			/* the offset to the add chars (in chars) */
	nl_int read;			/* the offset to the get a char position (in chars) */
	nl_int mark;			/* the offset to the mark position (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	nl_string	content;			/* pointer to the beginning of character array (character buffer) */
	nl_int		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	nl_int		increment;			/* character array increment factor */
	nl_char		mode;				/* operational mode indicator */
	Flag			flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		positions;			/* Offset / position field */
	nl_int		histogram[NCHAR];	/* Statistics of chars */
	nl_int		numReaderErrors;	/* Number of errors from Reader */
	nl_byte		checksum;			
} Buffer, * BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer	readerCreate		(nl_int, nl_int, nl_char);
BufferPointer	readerAddChar		(BufferPointer const, nl_char);
nl_boln		readerClear		    (BufferPointer const);
nl_boln		readerFree		    (BufferPointer const);
nl_boln		readerIsFull		(BufferPointer const);
nl_boln		readerIsEmpty		(BufferPointer const);
nl_boln		readerSetMark		(BufferPointer const, nl_int);
nl_int		readerPrint		    (BufferPointer const);
nl_int		readerLoad			(BufferPointer const, FILE* const);
nl_boln		readerRecover		(BufferPointer const);
nl_boln		readerRetract		(BufferPointer const);
nl_boln		readerRestore		(BufferPointer const);
nl_void		readerCalcChecksum	(BufferPointer const);
nl_boln		readerPrintFlags	(BufferPointer const);
nl_void		readerPrintStat     (BufferPointer const);
/* Getters */
nl_char		readerGetChar		(BufferPointer const);
nl_string	readerGetContent	(BufferPointer const, nl_int);
nl_int		readerGetPosRead	(BufferPointer const);
nl_int		readerGetPosWrte	(BufferPointer const);
nl_int		readerGetPosMark	(BufferPointer const);
nl_int		readerGetSize		(BufferPointer const);
nl_int		readerGetInc		(BufferPointer const);
nl_char		readerGetMode		(BufferPointer const);
nl_int		readerGetNumErrors	(BufferPointer const);

#endif
