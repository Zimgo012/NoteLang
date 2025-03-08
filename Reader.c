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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2024
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#include <ctype.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

 /*
 ***********************************************************
 * Function name: readerCreate
 * Purpose: Creates the buffer reader according to capacity, increment
	 factor and operational mode ('f', 'a', 'm')
 * Author: Svillen Ranev / Paulo Sousa
 * History/Versions: S22
 * Called functions: calloc(), malloc()
 * Parameters:
 *   size = initial capacity
 *   increment = increment factor
 *   mode = operational mode
 * Return value: bPointer (pointer to reader)
 * Algorithm: Allocation of memory according to inicial (default) values.
 * TODO ......................................................
 *	- Adjust datatypes for your LANGUAGE.
 *   - Use defensive programming
 *	- Check boundary conditions
 *	- Check flags.
 *************************************************************
 */

BufferPointer readerCreate(nl_int size, nl_int increment, nl_char mode) {
	BufferPointer readerPointer;
	nl_int count = 0;
	/* TO_DO: Defensive programming */
	if (size < 0)
		size = READER_DEFAULT_SIZE;
	if (!size)
		size = READER_DEFAULT_SIZE;
		//increment = READER_DEFAULT_INCREMENT;

	if (increment < 0)
		mode  = MODE_FIXED;
	if (!increment)
		increment = READER_DEFAULT_INCREMENT;
	if (!mode)
		return NL_ERROR;
	readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));
	if (!readerPointer)
		return NL_ERROR;
	readerPointer->content = (nl_string)malloc(size);

	/* TO_DO: Defensive programming */
	if (!readerPointer->content)
		return NL_ERROR;
	/* TO_DO: Initialize the histogram */
	for (int i = 0; i < NCHAR; i++)
		readerPointer->histogram[i] = 0;
	/* TO_DO: Initialize errors */
	readerPointer->numReaderErrors = 0;
	readerPointer->mode = mode;
	readerPointer->size = size;
	readerPointer->increment = increment;

	/* TO_DO: Initialize flags */
	readerPointer->flags.isEmpty = NL_TRUE;
	readerPointer->flags.isFull =  NL_FALSE;
	readerPointer->flags.isEmpty = NL_FALSE;
	readerPointer->flags.isEmpty = NL_FALSE;

	/* TO_DO: Default checksum */
	readerPointer->checksum = 0; // check this again
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

BufferPointer readerAddChar(BufferPointer readerPointer, nl_char ch) {
	nl_string tempReader = NL_INVALID;
	nl_int newSize = 0;
	nl_char tempChar = ' ';
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_INVALID;
	/* TO_DO: Reset Realocation */
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->positions.wrte * (nl_int)sizeof(nl_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
		readerPointer->flags.isFull = NL_FALSE;

	}
	else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags.isFull = NL_TRUE;
		switch (readerPointer->mode) {
		case MODE_FIXED:
			/* TO_DO: Update the last position with Terminator */
			return NL_INVALID;
			break;
		case MODE_ADDIT:
			/* TO_DO: Update size for Additive mode */
			newSize = readerPointer->size + readerPointer->increment;
			/* TO_DO: Defensive programming */
			if(newSize > readerPointer->size)
			break;
		case MODE_MULTI:
			/* TO_DO: Update size for Additive mode */
			newSize = readerPointer->size * readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize > readerPointer->size)
				return NL_INVALID;
			break;
		default:
			return NL_INVALID;
		}
		/* TO_DO: Reallocate */
		tempReader = realloc(readerPointer->content, newSize);
		/* TO_DO: Defensive programming */
		if (!tempReader)
			return NL_INVALID;

		readerPointer->content = tempReader;
		readerPointer->size = readerPointer->content;
		readerPointer->flags.isFull = NL_FALSE;
		return readerPointer;
	}
	/* TO_DO: Update the flags */
	readerPointer->content[readerPointer->positions.wrte++] = ch;
	/* TO_DO: Updates histogram */
	readerPointer->histogram[ch] += 1;
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_boln readerClear(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_INVALID;
	/* TO_DO: Adjust the write, mark and read to zero */
	readerPointer->positions.wrte = 0;
	readerPointer->positions.read = 0;
	readerPointer->positions.mark = 0;
	/* TO_DO: Adjust flags */
	readerPointer->flags.isEmpty =	NL_TRUE;
	readerPointer->flags.isFull =	NL_FALSE;
	readerPointer->flags.isMoved =	NL_FALSE;
	readerPointer->flags.isRead =	NL_FALSE; 
	return NL_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_boln readerFree(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Free pointers */
	free(readerPointer);

	return NL_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_boln readerIsFull(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Check flag if buffer is FUL */
	if (readerPointer->flags.isFull)
		return NL_TRUE;
	else
		return NL_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_boln readerIsEmpty(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Check flag if buffer is EMP */
	if (readerPointer->flags.isEmpty)
		return NL_TRUE;
	else
		return NL_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_boln readerSetMark(BufferPointer const readerPointer, nl_int mark) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	if (mark < 0 || mark > readerPointer->positions.wrte)
		return NL_ERROR;
	/* TO_DO: Adjust mark */
	readerPointer->positions.mark = mark;
	return NL_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_int readerPrint(BufferPointer const readerPointer) {
	nl_int cont = 0;
	nl_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	c = readerGetChar(readerPointer);
	while (cont < readerPointer->positions.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_int readerLoad(BufferPointer readerPointer, FILE* const fileDescriptor) {
	nl_int size = 0;
	nl_char c;
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	if (!fileDescriptor)
		return NL_ERROR;
	// I need to put here certain situation in the future..
	if (!readerPointer)
		return NL_ERROR;
	while (!feof(fileDescriptor)) {
		c = (nl_char)fgetc(fileDescriptor);
		readerPointer = readerAddChar(readerPointer, c);
		size++;
	}
	/* TO_DO: Defensive programming */
	return size;
}

/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_boln readerRecover(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Recover positions: read and mark must be zero */
	readerPointer->positions.read = 0;
	readerPointer->positions.mark = 0;
	/* TO_DO: Update flags */
	return NL_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_boln readerRetract(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return NL_ERROR; // Null pointer
	}
	if (readerPointer->positions.read <= 0) {
		return NL_ERROR; // Can't retract past start
	}

	/* Retract: move read position back one character */
	readerPointer->positions.read--;
	return NL_TRUE; // Success
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_boln readerRestore(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Restore positions (read to mark) */
	readerPointer->positions.read = readerPointer->positions.mark;
	return NL_TRUE;
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_char readerGetChar(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Check condition to read/wrte */

	return readerPointer->content[readerPointer->positions.read++];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_string readerGetContent(BufferPointer const readerPointer, nl_int pos) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	if (pos < 0)
		return NL_ERROR;
	return readerPointer->content + pos;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_int readerGetPosRead(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Return read */
	return readerPointer->positions.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_int readerGetPosWrte(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Return wrte */
	return readerPointer->positions.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_int readerGetPosMark(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Return mark */
	return readerPointer->positions.mark;
	return 0;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_int readerGetSize(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Return size */
	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_int readerGetInc(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Return increment */
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_char readerGetMode(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Return mode */
	return readerPointer->mode;
}

/*
***********************************************************
* Function name: readerShowStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_void readerPrintStat(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Updates the histogram */ 
	for (int i = 0; i < NCHAR; i++) {
		if (i == ' ') 
			continue;
		
		if (!isprint(i))
			continue;

		if (readerPointer->histogram[i] != 0)
			printf("[%c]= %d ", i, readerPointer->histogram[i]);
	}
	printf("\n");
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nl_int readerGetNumErrors(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Returns the number of errors */
	return readerPointer->numReaderErrors;
}

/*
***********************************************************
* Function name: readerCalcChecksum
* Purpose: Calculates the checksum of the reader (8 bits).
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	[None]
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

nl_void readerCalcChecksum(BufferPointer readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Calculate checksum */
}

/*
***********************************************************
* Function name: readerPrintFlags
* Purpose: Sets the checksum of the reader (4 bits).
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	[None]
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

nl_boln readerPrintFlags(BufferPointer readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NL_ERROR;
	/* TO_DO: Shows flags */
	printf("| EMPTY Flag = %x|\n", readerPointer->flags.isEmpty);
	printf("| FULL Flag =  %x|\n", readerPointer->flags.isFull);
	printf("| READ Flag =  %x|\n", readerPointer->flags.isRead);
	printf("| MOVED Flag = %x|\n", readerPointer->flags.isMoved);
	
	return NL_TRUE;
}

