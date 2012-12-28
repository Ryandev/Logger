 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2011  Ryan Powell                                       *
 * Proprietary & Confidential                                            *
 * This file & associated documentation may not be used                  *
 * without the consent of the authors permission.                        *
 * Undocumented use this material shall be an infringement of copyright. *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <stdio.h>
#include "test_logger_output.h"
#include "loggerFacade.h"


bool test_userVerifiedOutput ( void );
bool test_assertion_null ( void );
bool test_assertion_equals ( void );
bool test_assertion_less_greater_than ( void );
bool test_logger_output ( void );


#define LOGGER_MSG "!!! MSG: hello world :MSG !!!"

static LOGGER_OUTPUT_HANDLE _loggerHandle = LOGGER_OUTPUT_HANDLE_INVALID;


bool test_userVerifiedOutput ( void )
{
	bool didPass = false;
	char userInput = '\0';

	printf("\n\nDid that work? (y/n): ");

	userInput = fgetc(stdin);

	if (fgetc(stdin) != '\n')
	{
		printf("i need data in char\\n format\n");
	}
	else
	{
		switch (userInput)
		{
			case 'y':
			case 'Y':
			{
				didPass = true;
			}
            break;

			case 'n':
			case 'N':
			{
				didPass = false;
			}
            break;

			default:
			{
				printf("Unrecognised input (0x%x). Please try again\n",userInput);
				didPass = test_userVerifiedOutput();
			}
            break;
		}

		printf("\n");
	}

	return didPass;
}

bool test_assertion_null ( void )
{
	printf("\n\n*** NULL ASSERTION - MANUAL CHECK ***\n\n");
	
	printf("Testing assert NULL - assertion expected\n");	
	ASSERT_NULL((void *)1);
	printf("\n");
	
	printf("Testing assert NULL - assertion expected with msg\n");	
	ASSERT_NULL_MSG((void *)1, LOGGER_MSG);
	printf("\n");
	
	printf("Testing assert NULL - NO assertion expected\n");
	ASSERT_NULL(NULL);
	printf("\n");
	
	printf("Testing assert NOT_NULL - assertion expected\n");
	ASSERT_NOT_NULL(NULL);
	printf("\n");
	
	printf("Testing assert NOT_NULL - assertion expected with msg\n");
	ASSERT_NOT_NULL_MSG(NULL, LOGGER_MSG);
	printf("\n");
	
	printf("Testing assert NOT_NULL - NO assertion expected\n");
	ASSERT_NOT_NULL((void *)1);
	printf("\n");
	
	return test_userVerifiedOutput();
}

bool test_assertion_equals ( void )
{
	printf("\n\n*** ASSERTION EQUALS - MANUAL CHECK ***\n\n");
	
	printf("Testing assert equals - assertion expected\n");	
	ASSERT_EQUALS(0,1);
	printf("\n");
	
	printf("Testing assert equals - assertion expected with msg\n");	
	ASSERT_EQUALS_MSG(0,1, LOGGER_MSG);
	printf("\n");
	
	printf("Testing assert equals - NO assertion expected\n");	
	ASSERT_EQUALS(0,0);
	printf("\n");
	
	printf("Testing assert not equals - assertion expected\n");	
	ASSERT_NOT_EQUALS(0,0);
	printf("\n");
	
	printf("Testing assert not equals - assertion expected with msg\n");	
	ASSERT_NOT_EQUALS(0,0);
	printf("\n");
	
	printf("Testing assert not equals - NO assertion expected\n");	
	ASSERT_NOT_EQUALS(0,1);
	printf("\n");
	
	return test_userVerifiedOutput();
}

bool test_assertion_less_greater_than ( void )
{
	printf("\n\n*** ASSERTION < > - MANUAL CHECK ***\n\n");
	
	printf("Testing assert greater than - assertion expected\n");	
	ASSERT_GREATER_THAN(1,2);
	printf("\n");
	
	printf("Testing assert greater than - assertion expected with MSG\n");	
	ASSERT_GREATER_THAN_MSG(1,2, LOGGER_MSG);
	printf("\n");
	
	printf("Testing assert greater than-float - assertion expected with MSG\n");	
	ASSERT_GREATER_THAN_F_MSG(1.0f,2.0f, LOGGER_MSG);
	printf("\n");
	
	printf("Testing assert greater than - NO assertion expected\n");	
	ASSERT_GREATER_THAN(2,1);
	printf("\n");
	
	printf("Testing assert less than - assertion expected\n");	
	ASSERT_LESS_THAN(2,1);
	printf("\n");
	
	printf("Testing assert less than - assertion expected with MSG\n");	
	ASSERT_LESS_THAN_MSG(2,1, LOGGER_MSG);
	printf("\n");
	
	printf("Testing assert less than - NO assertion expected\n");	
	ASSERT_LESS_THAN(1,2);
	printf("\n");
	
	printf("Testing assert less than - NO assertion expected\n");	
	ASSERT_LESS_THAN_F(1.0,2.0);
	printf("\n");
	
	return test_userVerifiedOutput();
}

bool test_logger_output ( void )
{
	printf("\n\n*** LOGGER MANUAL CHECK ***\n\n");
	
	printf("testing LOGGER_EVENT\n");
	LOGGER_EVENT("LOGGER EVENT - hello world");
	printf("\n");
	
	printf("testing LOGGER_INFO\n");
	LOGGER_INFO("LOGGER INFO - hello world");
	printf("\n");
	
	printf("testing LOGGER_WARN\n");
	LOGGER_WARN("LOGGER WARN - hello world");
	printf("\n");
	
	printf("testing LOGGER_ERROR\n");
	LOGGER_ERROR("LOGGER ERROR - hello world");
	printf("\n");
	
	printf("testing LOGGER_FATAL\n");
	LOGGER_FATAL("LOGGER FATAL - hello world");
	printf("\n");
	
	printf("testing LOGGER_ENTRY\n");
	LOGGER_ENTRY;
	printf("\n");
	
	printf("testing LOGGER_EXIT\n");
	LOGGER_EXIT;
	printf("\n");
	
	return test_userVerifiedOutput();
}

bool test_logger_enableChange ( void )
{
    LOGGER_ENABLE_TYPE(LOGGER_LEVEL_EVENT);
	printf("LOGGER_EVENT expected\n");
	LOGGER_EVENT("EVENT msg");
	printf("\n");
    
    LOGGER_DISABLE_TYPE(LOGGER_LEVEL_EVENT);
	printf("LOGGER_EVENT disabled. NO output expected\n");
	LOGGER_EVENT("EVENT msg");
	printf("\n");
    
    return test_userVerifiedOutput();
}

bool test_logger ( void )
{
	bool testPass = false;
    
    loggerSetSeverityEnablements_Default ( LOGGER_LEVEL_ENTRY | LOGGER_LEVEL_EXIT | LOGGER_LEVEL_TRACE | LOGGER_LEVEL_INFO | LOGGER_LEVEL_WARN | LOGGER_LEVEL_ERROR | LOGGER_LEVEL_FATAL | LOGGER_LEVEL_EVENT | LOGGER_LEVEL_ASSERT );
    
    LOGGER_INIT;
    
	if (test_logger_output() == false)
	{
		printf("test_logger() failed\n");
	}
	else if (test_assertion_null() == false)
	{
		printf("test_assertion_null() failed\n");
	}
	else if (test_assertion_equals() == false)
	{
		printf("test_assertion_equals() failed\n");
	}
	else if (test_assertion_less_greater_than() == false)
	{
		printf("test_assertion_less_greater_than() failed\n");
	}
    else if (test_logger_enableChange() == false)
    {
		printf("test_logger_enableChange() failed\n");
    }
	else
	{
		printf("logger & assertion checks passed manual verification\n");
		testPass = true;
	}
    
    LOGGER_TERM;
	
	return testPass;
}
