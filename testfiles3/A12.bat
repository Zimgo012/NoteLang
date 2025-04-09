:: ---------------------------------------------------------------------
:: COMPILERS COURSE - SCRIPT                                           -
:: SCRIPT A22 - CST8152 - Fall 2024                                    -
:: ---------------------------------------------------------------------

CLS
SET COMPILER=Notelang.exe

SET FILE1=INPUT1_Blank
SET FILE2=INPUT2_WithoutConfig
SET FILE3=INPUT3_WithoutEnd
SET FILE4=INPUT4_WithoutMain
SET FILE5=INPUT5_WithoutVarSess
SET FILE6=INPUT6_ShortWorkingCode
SET FILE7=INPUT7_ShortNonWorkingCode
SET FILE8=INPUT8_MultipleSection
SET FILE9=INPUT9_FinalLongCode


SET ASSIGNMENT=A12
SET EXTENSION=note
SET OUTPUT=out
SET ERROR=err

SET PARAM=1

:: ---------------------------------------------------------------------
:: Begin of Tests (A12 - F24) ------------------------------------------
:: ---------------------------------------------------------------------

@echo off

ECHO "=---------------------------------------="
ECHO "|  COMPILERS - ALGONQUIN COLLEGE (F24)  |"
ECHO "=---------------------------------------="
ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ”
ECHO "    @@                             @@    ”
ECHO "    @@    __    __  __             @@    ”
ECHO "    @@    |  `  |  `|  `           @@    ”
ECHO "    @@    | $$` | $$| $$           @@    ”
ECHO "    @@    | $$$`| $$| $$           @@    ”
ECHO "    @@    | $$$$` $$| $$           @@    ”
ECHO "    @@    | $$`$$ $$| $$           @@    ”
ECHO "    @@    | $$ `$$$$| $$           @@    ”
ECHO "    @@    | $$ `$$$$| $$_______    @@    ”
ECHO "    @@    | $$  `$$$| $$_______`   @@    ”
ECHO "    @@     `$$   `$$ `$$$$$$$$$$`  @@     ”
ECHO "    @@                             @@    ”
ECHO "    @@       N O T E L A N G       @@     ”
ECHO "    @@                             @@    ”
ECHO "    @@                             @@    ”
ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ”
ECHO "                                         "
ECHO "[READER SCRIPT .........................]"
ECHO "                                         "

ren *.exe %COMPILER%

::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A12 - F24) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% %PARAM% %FILE1%.%EXTENSION%	> %FILE1%-%ASSIGNMENT%.%OUTPUT%	2> %FILE1%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE2%.%EXTENSION%	> %FILE2%-%ASSIGNMENT%.%OUTPUT%	2> %FILE2%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE3%.%EXTENSION%	> %FILE3%-%ASSIGNMENT%.%OUTPUT%	2> %FILE3%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE4%.%EXTENSION%	> %FILE4%-%ASSIGNMENT%.%OUTPUT%	2> %FILE4%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE5%.%EXTENSION%	> %FILE5%-%ASSIGNMENT%.%OUTPUT%	2> %FILE5%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE6%.%EXTENSION%	> %FILE6%-%ASSIGNMENT%.%OUTPUT%	2> %FILE6%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE6%.%EXTENSION%	> %FILE7%-%ASSIGNMENT%.%OUTPUT%	2> %FILE6%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE6%.%EXTENSION%	> %FILE8%-%ASSIGNMENT%.%OUTPUT%	2> %FILE6%-%ASSIGNMENT%.%ERROR%

::
:: ADVANCED TESTS  -------------------------------------------------------
::
:: Advanced Tests (A12 - F24) - - - - - - - - -- - - - - - - - - - - -

%COMPILER% %PARAM% %FILE7%.%EXTENSION%	f 100 10	> %FILE9%-%ASSIGNMENT%-f-500-10.%OUTPUT%	2> %FILE9%-%ASSIGNMENT%-f-500-10.%ERROR%
%COMPILER% %PARAM% %FILE7%.%EXTENSION%	a 100 10	> %FILE9%-%ASSIGNMENT%-a-500-10.%OUTPUT%	2> %FILE9%-%ASSIGNMENT%-a-500-10.%ERROR%
%COMPILER% %PARAM% %FILE7%.%EXTENSION%	m 100 10	> %FILE9%-%ASSIGNMENT%-m-500-10.%OUTPUT%	2> %FILE9%-%ASSIGNMENT%-m-500-10.%ERROR%

:: SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -
DIR *.OUT
DIR *.ERR

:: ---------------------------------------------------------------------
:: End of Tests (A12 - F24) --------------------------------------------
:: ---------------------------------------------------------------------
