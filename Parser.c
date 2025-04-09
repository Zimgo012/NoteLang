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
# "[PARSER IMPLEMENTATION .................]"
# "                                         "
*/

/*
************************************************************
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: 303
* Assignment: A32.
* Date: April 08, 2025
* Purpose: This file contains all functionalities from Parser.
* Function list: startParser, matchToken, syncErrorHandler, printError, ...
************************************************************
*/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/* Parser data */
extern ParserData psData; /* BNF statistics */

/*
************************************************************
* Process Parser
************************************************************
*/
nl_void startParser() {
    nl_int i = 0;
    for (i = 0; i < NUM_BNF_RULES; i++) {
        psData.parsHistogram[i] = 0;
    }
    lookahead = tokenizer();
//    printf("DEBUG: Start lookahead.code = %d\n", lookahead.code);
    program();
    matchToken(SEOF_T, NO_ATTR);
 //   printf("DEBUG: After match SEOF_T, lookahead.code = %d\n", lookahead.code);
    printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}

/*
************************************************************
* Match Token
************************************************************
*/
nl_void matchToken(nl_int tokenCode, nl_int tokenAttribute) {
    nl_int matchFlag = 1;
//    printf("DEBUG: matchToken called with tokenCode = %d, tokenAttribute = %d, lookahead.code = %d, codeType = %d\n",
//        tokenCode, tokenAttribute, lookahead.code, lookahead.attribute.codeType);
    switch (lookahead.code) {
    case KW_T:
        if (lookahead.attribute.codeType != tokenAttribute)
            matchFlag = 0;
        break;
    default:
        if (lookahead.code != tokenCode)
            matchFlag = 0;
    }
    if (matchFlag && lookahead.code == SEOF_T)
        return;
    if (matchFlag) {
    //    printf("DEBUG: Match successful, advancing lookahead\n");
        lookahead = tokenizer();
    //    printf("DEBUG: New lookahead.code = %d\n", lookahead.code);
        if (lookahead.code == ERR_T) {
            printError();
            lookahead = tokenizer();
            syntaxErrorNumber++;
        }
    }
    else {
        syncErrorHandler(tokenCode);
    }
}

/*
************************************************************
* Synchronize Error Handler
************************************************************
*/
nl_void syncErrorHandler(nl_int production) {
    // Advance to next EOS_T, KW_section, KW_END, or SEOF_T
    while (lookahead.code != EOS_T && lookahead.code != SEOF_T &&
        !(lookahead.code == KW_T && (lookahead.attribute.codeType == KW_section ||
            lookahead.attribute.codeType == KW_END))) {
        lookahead = tokenizer();
    }
}

/*
************************************************************
* Print Error
************************************************************
*/
nl_void printError() {
    extern nl_int numParserErrors;
    Token t = lookahead;
    printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
    printf("*****  Token code:%3d Attribute: ", t.code);
    switch (t.code) {
    case ERR_T:
        printf("*ERROR*: %s\n", t.attribute.errLexeme);
        break;
    case SEOF_T:
        printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
        break;
    case STR_T:
        printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
        break;
    case KW_T:
        printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
        break;
    case NOTE_T:
        printf("NOTE_T: %s\n", t.attribute.idLexeme);
        break;
    case VID_T:
        printf("VID_T: %s\n", t.attribute.idLexeme);
        break;
    case INL_T:
        printf("INL_T: %d\n", t.attribute.intValue);
        break;
    case LPR_T: printf("LPR_T\n"); break;
    case RPR_T: printf("RPR_T\n"); break;
    case LBR_T: printf("LBR_T\n"); break;
    case RBR_T: printf("RBR_T\n"); break;
    case EOS_T: printf("EOS_T\n"); break;
    case OP_NOTE_T: printf("OP_NOTE_T\n"); break;
    case OP_COMMA_T: printf("OP_COMMA_T\n"); break;
    default:
        printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
    }
    numParserErrors++;
}

/*
************************************************************
* Program statement
* BNF: <program> -> <configuration_session> <data_session> <code_session> <end_of_file>
* FIRST(<program>) = { CMT_T, KW_T(Tempo), KW_T(Print) }
************************************************************
*/
nl_void program() {
    psData.parsHistogram[BNF_program]++;
    configurationSession();
    dataSession(); 
    codeSession();
    endOfFile();
    printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
************************************************************
* Configuration Session
* BNF: <configuration_session> -> { <config_statement> | <comment> }
* FIRST(<configuration_session>) = { CMT_T, KW_T(Tempo), KW_T(Print) }
************************************************************
*/
/*
************************************************************
* Configuration Session
* BNF: <configuration_session> -> <config_statement_Tempo> <config_statement_Print> { <comment> | <config_statement> }
* FIRST(<configuration_session>) = { CMT_T, KW_T(Tempo), KW_T(Print) }
* FOLLOW(<configuration_session>) = { KW_T(df) }
* Note: Both Tempo and Print config statements are now mandatory
************************************************************
*/
nl_void configurationSession() {
    psData.parsHistogram[BNF_configurationSession]++;
 //   printf("DEBUG: Entering configurationSession, lookahead.code = %d\n", lookahead.code);
    int hasTempo = 0;  // Track if Tempo config is present
    int hasPrint = 0;  // Track if Print config is present
    while (lookahead.code != SEOF_T) {
    //    printf("DEBUG: configurationSession loop, lookahead.code = %d\n", lookahead.code);
        switch (lookahead.code) {
        case CMT_T:
            comment();
            break;
        case KW_T:
            if (lookahead.attribute.codeType == KW_Tempo) {  // 12
                if (hasTempo) {
                    printf("%s%s\n", STR_LANGNAME, ": Error: Duplicate Tempo configuration");
                    printError();
                }
                configStatement();
                hasTempo = 1;
            }
            else if (lookahead.attribute.codeType == KW_Print) {  // 2
                if (hasPrint) {
                    printf("%s%s\n", STR_LANGNAME, ": Error: Duplicate Print configuration");
                    printError();
                }
                configStatement();
                hasPrint = 1;
            }
            else {
                goto exit_config; // Move to dataSession or error if missing configs
            }
            break;
        default:
            goto exit_config; // Non-config tokens (e.g., VID_T, NOTE_T)
        }
    }
exit_config:
    if (!hasTempo) {
        printf("%s%s\n", STR_LANGNAME, ": Error: Missing mandatory Tempo configuration");
        printError();
    }
    if (!hasPrint) {
        printf("%s%s\n", STR_LANGNAME, ": Error: Missing mandatory Print configuration");
        printError();
    }
//    printf("DEBUG: Leaving configurationSession, lookahead.code = %d\n", lookahead.code);
    printf("%s%s\n", STR_LANGNAME, ": Configuration session parsed");
}

/*
************************************************************
* Config Statement
* BNF: <config_statement> -> Tempo = INL_T ; | Print = INL_T ;
* FIRST(<config_statement>) = { KW_T(Tempo), KW_T(Print) }
************************************************************
*/
nl_void configStatement() {
    psData.parsHistogram[BNF_configStatement]++;
  //  printf("DEBUG: Entering configStatement, lookahead.code = %d\n", lookahead.code);
    switch (lookahead.code) {
    case KW_T:
        switch (lookahead.attribute.codeType) {
        case KW_Tempo:
            matchToken(KW_T, KW_Tempo);
            matchToken(ASSIGN_T, NO_ATTR);
            matchToken(INL_T, NO_ATTR);
            matchToken(EOS_T, NO_ATTR);
            break;
        case KW_Print:
            matchToken(KW_T, KW_Print);
            matchToken(ASSIGN_T, NO_ATTR);
            matchToken(INL_T, NO_ATTR);
            matchToken(EOS_T, NO_ATTR);
            break;
        default:
            printError();
        }
        break;
    default:
        printError();
    }
    printf("%s%s\n", STR_LANGNAME, ": Config statement parsed");
}

/*
************************************************************
* Data Session
* BNF: <data_session> -> { <var_declaration> | <comment> }
* FIRST(<data_session>) = { CMT_T, KW_T(df) }
************************************************************
*/
nl_void dataSession() {
    psData.parsHistogram[BNF_dataSession]++;
//    printf("DEBUG: Entering dataSession, lookahead.code = %d\n", lookahead.code);
    int hasDeclaration = 0; // Track if at least one declaration exists

    while (lookahead.code != SEOF_T) {
    //    printf("DEBUG: dataSession loop, lookahead.code = %d\n", lookahead.code);
        switch (lookahead.code) {
        case CMT_T:
            comment();
            break;
        case KW_T:
            if (lookahead.attribute.codeType == KW_df) {  // 0
                varDeclaration();
                hasDeclaration = 1;
            }
            else if (lookahead.attribute.codeType == KW_section ||
                lookahead.attribute.codeType == KW_END) {
                goto exit_data; // Move to codeSession or endOfFile
            }
            else {
                printf("%s%s%d\n", STR_LANGNAME, ": Error: Unexpected keyword in data session, codeType = ", lookahead.attribute.codeType);
                printError();
                syncErrorHandler(BNF_dataSession); // Recover and try to exit
                goto exit_data;
            }
            break;
        default:
            printf("%s%s%d\n", STR_LANGNAME, ": Error: Unexpected token in data session, code = ", lookahead.code);
            printError();
            syncErrorHandler(BNF_dataSession); // Recover and try to exit
            goto exit_data;
        }
    }

exit_data:
 //   printf("DEBUG: Leaving dataSession, lookahead.code = %d\n", lookahead.code);
    printf("%s%s\n", STR_LANGNAME, ": Data session parsed");
}

/*
************************************************************
* Variable Declaration
* BNF: <var_declaration> -> df VID_T = (INL_T | STR_T) ;
* FIRST(<var_declaration>) = { KW_T(df) }
************************************************************
*/
nl_void varDeclaration() {
    psData.parsHistogram[BNF_varDeclaration]++;
//    printf("DEBUG: Entering varDeclaration, lookahead.code = %d\n", lookahead.code);

    matchToken(KW_T, KW_df);      // Match "df" (code 8, attribute 0)
    matchToken(VID_T, NO_ATTR);   // Match variable identifier (code 1)
    matchToken(ASSIGN_T, NO_ATTR);// Match "=" (code 10)

    if (lookahead.code == STR_T) {
        matchToken(STR_T, NO_ATTR); // Match string (code 3)
    }
    else if (lookahead.code == INL_T) {
        matchToken(INL_T, NO_ATTR); // Match integer (code 2)
    }
    else {
        printf("%s%s\n", STR_LANGNAME, ": Error: Expected string or integer literal after assignment");
        printError();
        syncErrorHandler(BNF_varDeclaration);
        return;
    }

    if (lookahead.code != EOS_T) {
        printf("%s%s\n", STR_LANGNAME, ": Error: Expected ';' at end of variable declaration");
        printError();
        syncErrorHandler(BNF_varDeclaration);
        return;
    }
    matchToken(EOS_T, NO_ATTR);   // Match ";" (code 9)

    printf("%s%s\n", STR_LANGNAME, ": Variable declaration parsed");
}

/*
************************************************************
* Code Session
* BNF: <code_session> -> section main ( ) { <note_statements> } ;
* FIRST(<code_session>) = { KW_T(section) }
************************************************************
*/
nl_void codeSession() {
    psData.parsHistogram[BNF_codeSession]++;
   // printf("DEBUG: Entering codeSession, lookahead.code = %d\n", lookahead.code);

    // Loop until SEOF_T or KW_END is encountered
    while (lookahead.code != SEOF_T &&
        !(lookahead.code == KW_T && lookahead.attribute.codeType == KW_END)) {
     //   printf("DEBUG: codeSession loop, lookahead.code = %d\n", lookahead.code);
        matchToken(KW_T, KW_section); // Match "section" (code 8, attribute 1)
        matchToken(VID_T, NO_ATTR);   // Match section name (e.g., "main")
        matchToken(LPR_T, NO_ATTR);   // Match "("
        matchToken(RPR_T, NO_ATTR);   // Match ")"
        matchToken(LBR_T, NO_ATTR);   // Match "{"
        noteStatements();
        matchToken(RBR_T, NO_ATTR);   // Match "}"
        matchToken(EOS_T, NO_ATTR);   // Match ";"
        printf("%s%s\n", STR_LANGNAME, ": Section parsed");
    }

   // printf("DEBUG: Leaving codeSession, lookahead.code = %d\n", lookahead.code);
    printf("%s%s\n", STR_LANGNAME, ": Code session parsed");
}

/*
************************************************************
* Note Statements
* BNF: <note_statements> -> { <note_statement> | <comment> }
* FIRST(<note_statements>) = { CMT_T, NOTE_T }
************************************************************
*/
nl_void noteStatements() {
    psData.parsHistogram[BNF_noteStatements]++;
    //printf("DEBUG: Entering noteStatements, lookahead.code = %d\n", lookahead.code);

    while (lookahead.code != RBR_T && lookahead.code != SEOF_T) {
     //   printf("DEBUG: noteStatements loop, lookahead.code = %d\n", lookahead.code);
        switch (lookahead.code) {
        case NOTE_T:
            noteStatement();
            break;
        default:
            printf("%s%s%d\n", STR_LANGNAME, ": Error: Unexpected token in note statements, code = ", lookahead.code);
            printError();
            syncErrorHandler(BNF_noteStatements);
            return;
        }
    }

    //printf("DEBUG: Leaving noteStatements, lookahead.code = %d\n", lookahead.code);
    printf("%s%s\n", STR_LANGNAME, ": Note statements parsed");
}

/*
************************************************************
* Note Statement
* BNF: <note_statement> -> NOTE_T -> { INL_T , KW_T } ;
* FIRST(<note_statement>) = { NOTE_T }
************************************************************
*/
nl_void noteStatement() {
    psData.parsHistogram[BNF_noteStatement]++;
    //printf("DEBUG: Entering noteStatement, lookahead.code = %d\n", lookahead.code);

    matchToken(NOTE_T, NO_ATTR);      // Match note (e.g., C4) (code 26)
    matchToken(OP_NOTE_T, NO_ATTR);   // Match "->" (code 11)
    matchToken(LBR_T, NO_ATTR);       // Match "{" (code 6)
    matchToken(INL_T, NO_ATTR);       // Match duration (e.g., 1) (code 2)

    // Match dynamic marking (mf, f, ff, fff)
    if (lookahead.code == KW_T && (lookahead.attribute.codeType == KW_mf ||
        lookahead.attribute.codeType == KW_f ||
        lookahead.attribute.codeType == KW_ff ||
        lookahead.attribute.codeType == KW_fff)) {
        matchToken(KW_T, lookahead.attribute.codeType); // Match specific dynamic keyword
    }
    else {
        printf("%s%s\n", STR_LANGNAME, ": Error: Expected dynamic marking (mf, f, ff, fff)");
        printError();
        syncErrorHandler(BNF_noteStatement);
        return;
    }

    matchToken(RBR_T, NO_ATTR);       // Match "}" (code 7)
    matchToken(EOS_T, NO_ATTR);       // Match ";" (code 9)

    printf("%s%s\n", STR_LANGNAME, ": Note statement parsed");
}

/*
************************************************************
* Comment
* BNF: <comment> -> CMT_T
* FIRST(<comment>) = { CMT_T }
************************************************************
*/
nl_void comment() {
    psData.parsHistogram[BNF_comment]++;
    matchToken(CMT_T, NO_ATTR);
    printf("%s%s\n", STR_LANGNAME, ": Comment parsed");
}

/*
************************************************************
* End of File
* BNF: <end_of_file> -> !END
* FIRST(<end_of_file>) = { KW_T(END) }
************************************************************
*/
nl_void endOfFile() {
    psData.parsHistogram[BNF_endOfFile]++;
    //printf("DEBUG: Entering endOfFile, lookahead.code = %d\n", lookahead.code);
    while (lookahead.code == CMT_T) {
        comment();
    }
    if (lookahead.code == KW_T && lookahead.attribute.codeType == KW_END) {
        matchToken(KW_T, KW_END);
        lookahead = tokenizer();
     //   printf("DEBUG: After END, lookahead.code = %d\n", lookahead.code);
        if (lookahead.code != SEOF_T) {
            printError();
        }
        else {
            matchToken(SEOF_T, NO_ATTR);
        }
    }
    else {
        printError();
    }
   // printf("DEBUG: Leaving endOfFile, lookahead.code = %d\n", lookahead.code);
    printf("%s%s\n", STR_LANGNAME, ": End of file parsed");
}

/*
************************************************************
* Print BNF Data
************************************************************
*/
nl_void printBNFData(ParserData psData) {
    printf("Statistics:\n");
    printf("----------------------------------\n");
    int cont = 0;
    for (cont = 0; cont < NUM_BNF_RULES; cont++) {
        if (psData.parsHistogram[cont] > 0)
            printf("%s%s%s%d%s", "Token[", BNFStrTable[cont], "]=", psData.parsHistogram[cont], "\n");
    }
    printf("----------------------------------\n");
}