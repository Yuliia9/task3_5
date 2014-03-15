/*
* @file			task3_5.cpp
* @brief		Program finds combination of characters in sentences and delete words with them.

* Copyright 2014 by Yuliia Lyubchik Inc.,
*
* This software is the confidential and proprietary information
* of Yuliia Lyubchik. ("Confidential Information").  You
* shall not disclose such Confidential Information and shall use
* it only with permission from Yuliia.
*
*/

#include "stdafx.h"
#include "task3_5.h"	/*defines prototypes of used in this file functions*/
#include <stdlib.h>
#include <string.h>

const unsigned char ERROR = 0;
const unsigned char SUCCESS = 1;
const unsigned int MAIN_SUCCESS = 0;

int main( )
{
	Interface();

	char* riadok = NULL;
	char* combination = NULL;
	unsigned char retCode;
	char* copy = NULL;


	retCode = Input(&riadok, &combination);

	if (retCode == ERROR)
	{
		printf("Error occurs while trying to input string.\n");
		return (int)ERROR;
	}

	if (riadok != NULL && strlen(riadok) != 0)
	{
		copy = (char*)malloc(strlen(riadok) * sizeof(char));
		if (copy != NULL)
		{
			strcpy(copy, riadok);
		}
		else
		{
			printf("Error occurs while trying to create string for results.\n");
			free(riadok);
			return (int)ERROR;
		}
	}

	retCode = Delete_words(&copy, combination );

	if (retCode == ERROR)
	{
		printf("Error occurs while trying to find combinations.\n");
		free(copy);
		free(riadok);
		return (int)ERROR;
	}

	printf("String after deleted words with defined combination: %s.\n", copy);

	free(riadok);
	system("pause");
	return MAIN_SUCCESS;
}

void Interface(void)
{
	printf("------------------------------------------------------------------\n");
	printf("Hi! Welcome to the genius characters finder.\n");
	printf("Enter sentences and combination of characters \n");
	printf("and program will delete for you words that include that combination. \n");
	printf("Program made by Yuliia Lyubchik.\n");
	printf("------------------------------------------------------------------\n\n");
}


unsigned char Input(char** riadok, char** combination)
{
	unsigned char retCode;
	do
	{
		char temp;
		int count = 0;
		printf("Please enter sentence: ");
		do
		{
			scanf("%c", &temp);
			++count;
			*riadok = (char*)realloc(*riadok, count * sizeof(char));

			if (*riadok != NULL) 
			{
				*(*riadok + count - 1) = temp;
			}
			else 
			{
				free(riadok);
				puts("Error (re)allocating memory. \n");
				return ERROR;
			}

		} 
		while (temp != '\n' && temp != EOF);

		fflush(stdin);
		*(*riadok + count - 1) = '\0';
	} 
	while (riadok == NULL || strlen(*riadok) == 0);

	int count = 0;
	retCode = ERROR;
	do
	{
		char temp;
		printf("Please enter combination of characters that you want to find: ");
		do
		{
			scanf("%c", &temp); 
			if (temp >= 'A' && temp <= 'Z')
			{
				retCode = SUCCESS;
			}
			else if (temp >= 'a' && temp <= 'z')
			{
				retCode = SUCCESS;
			}
			++count;
			*combination = (char*)realloc(*combination, count * sizeof(char));

			if (*combination != NULL) 
			{
				*(*combination + count - 1) = temp;
			}
			else 
			{
				free(combination);
				puts("Error (re)allocating memory. \n");
				return ERROR;
			}

		} 
		while (temp != '\n' && temp != EOF);
		fflush(stdin);
	} 
	while (retCode == ERROR || combination == NULL || strlen(*combination) == 0);
	*(*combination+ count - 1) = '\0';

	return SUCCESS;
}



unsigned char Delete_words(char** copy, const char* combination)
{
	if (*copy == NULL || combination == NULL)
	{
		printf("Error occurs while trying to get access to data.\n");
		return ERROR;
	}

	char* temp;
	char* token;
	char* pfinder;

	const char delimiters[] = { ' ', ',', '-', '.', ':', ';', '(', ')', '[', ']', '!', '?' };
	temp = (char*)calloc(strlen(*copy), sizeof(char));
	if (temp == NULL)
	{
		printf("Error occurs while trying to allocate memory for temporary values.\n");
		return ERROR;
	}
	token = strtok(*copy, delimiters);
	while (token != NULL)
	{
		pfinder = strstr(token, combination);
		if (pfinder == NULL)
		{
			strcat(temp, token);
			strcat(temp, " ");
		}
		token = strtok(NULL, delimiters);
	}

	strcpy(*copy, temp);
	return SUCCESS;
}


