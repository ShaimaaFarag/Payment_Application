#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NONSTDC_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <ctype.h> //for isdigit() function
#include "terminal.h"


uint8_t wrongFormat(ST_terminalData_t* termData)
{
	if (
		((termData->transactionDate[2]) != '/') || ((termData->transactionDate[5]) != '/')
		/*(isdigit(termData->transactionDate[0]) != 0) || (isdigit(termData->transactionDate[1]) != 0) ||
		(isdigit(termData->transactionDate[3]) != 0) || (isdigit(termData->transactionDate[4]) != 0) ||
		(isdigit(termData->transactionDate[6]) != 0) || (isdigit(termData->transactionDate[7]) != 0) ||
		(isdigit(termData->transactionDate[8]) != 0) || (isdigit(termData->transactionDate[9]) != 0) ||
		((termData->transactionDate[2]) != '/') || ((termData->transactionDate[5]) != '/')*/
		)
		return  Wrong_Format;
	else
		return NotWrong;

}
/*
1-This function will ask for the transaction date and store it in terminal data.
2-Transaction date is 10 characters string in the format DD/MM/YYYY, e.g 25/06/2022.
3-If the transaction date is NULL or is less than 10 characters or wrong format will return the WRONG_DATE error, else return TERMINAL_OK.
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	//ask for the transaction date and store it in terminal data.
	printf("please enter transaction date at this format DD/MM/YYYY, e.g 25/06/2022    : ");
	(void)scanf("%s", &(termData->transactionDate));
	//If the transaction date is NULL or is less than 10 characters or wrong format will return the WRONG_DATE error, else return TERMINAL_OK.
	if (
		(strlen(termData->transactionDate)==NULL)||
		(strlen(termData->transactionDate)<10)   ||
		(wrongFormat(termData))
		)
	{
		return WRONG_DATE;
	}
	else
	{
		return TERMINAL_OK;
	}
    
}
/*
This function compares the card expiry date with the transaction date.
If the card expiration date is before the transaction date will return EXPIRED_CARD, else return TERMINAL_OK.
*/
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{

	uint32_t CardExpirationYear = ((cardData->cardExpirationDate[3]-'0') * 10) + ((cardData->cardExpirationDate[4])-'0');
	uint32_t CardExpirationMonth = ((cardData->cardExpirationDate[0]-'0') * 10) + ((cardData->cardExpirationDate[1])-'0');

	uint32_t TransactionYear = ((termData->transactionDate[8]-'0') * 10) + ((termData->transactionDate[9])-'0');
	uint32_t TransactionMonth = ((termData->transactionDate[3]-'0') * 10) + ((termData->transactionDate[4])-'0');
	/*uint32_t CardExpirationYear = (atoi(cardData->cardExpirationDate[3]) * 10) + (atoi(cardData->cardExpirationDate[4]));
	uint32_t CardExpirationMonth =(atoi(cardData->cardExpirationDate[0]) * 10) + (atoi(cardData->cardExpirationDate[1]));

	uint32_t TransactionYear = (atoi(termData->transactionDate[8]) * 10) + (atoi(termData->transactionDate[9]));
	uint32_t TransactionMonth= (atoi(termData->transactionDate[3]) * 10) + (atoi(termData->transactionDate[4]));
	*/
	if (CardExpirationYear > TransactionYear)
	{
		return TERMINAL_OK;
	}
	else
	{
		if(CardExpirationYear<TransactionYear)
		{
			return EXPIRED_CARD;
		}
		else if (CardExpirationYear == TransactionYear)
		{
			if (TransactionMonth < CardExpirationMonth)
				return TERMINAL_OK;
			else
				return EXPIRED_CARD;
		}
	}
}
/*
1-This function asks for the transaction amount and saves it into terminal data.
2-If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return TERMINAL_OK.
*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	//ask for the transaction amount and save it into terminal data.
	printf("please enter transaction amount\t\t\t\t\t:");
	(void)scanf("%f", &(termData->transAmount));
	//2-If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return TERMINAL_OK.
	if(termData->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}
/*
1-This function compares the transaction amount with the terminal max allowed amount.
2-If the transaction amount is larger than the terminal max allowed amount will return EXCEED_MAX_AMOUNT, else return TERMINAL_OK.
*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	//If the transaction amount is larger than the terminal max allowed amount will return EXCEED_MAX_AMOUNT, else return TERMINAL_OK.
    if(termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}
/*
1-This function takes the maximum allowed amount and stores it into terminal data.
2-Transaction max amount is a float number.
3-If transaction max amount less than or equal to 0 will return the INVALID_MAX_AMOUNT error, else return TERMINAL_OK.
*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)//, float maxAmount)
{
	// take the maximum allowed amount and store it into terminal data.
	printf("please enter maximum allowed amount\t\t\t\t:");
	(void)scanf("%f", &(termData->maxTransAmount));
	//If transaction max amount less than or equal to 0 will return the INVALID_MAX_AMOUNT error, else return TERMINAL_OK.
	if((termData->maxTransAmount)<=0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}

}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData); // Optional

void getTransactionDateTest(void)
{
	
	printf("please enter transaction date at this format DD/MM/YYYY, e.g 25/06/2022    : ");
	(void)scanf("%s", &(transactionDateTest));
	//If the transaction date is NULL or is less than 10 characters or wrong format will return the WRONG_DATE error, else return TERMINAL_OK.
	if (
		(strlen(transactionDateTest) == NULL) ||
		(strlen(transactionDateTest) < 10) ||
		((transactionDateTest[2]) != '/') ||
		((transactionDateTest[5]) != '/')
		)
	{
		printf("\t\t\tWRONG_DATE\n");
		printf("---------------------------------------------------\n");
		//return WRONG_DATE;
	}
	else
	{
		printf("\t\t\tTERMINAL_OK\n");
		printf("---------------------------------------------------\n");
		//return TERMINAL_OK;
	}
}

void isCardExpriedTest(void)
{
	printf("please enter card expiry date as MM/YY\t\t\t\t: ");
	(void)scanf("%s",&cardExpirationDateTest);
	printf("please enter transaction date at this format DD/MM/YYYY, e.g 25/06/2022    : ");
	(void)scanf("%s", &(transactionDateTest));

	uint32_t CardExpirationYear = ((cardExpirationDateTest[3] - '0') * 10) + ((cardExpirationDateTest[4]) - '0');
	uint32_t CardExpirationMonth = ((cardExpirationDateTest[0] - '0') * 10) + ((cardExpirationDateTest[1]) - '0');

	uint32_t TransactionYear = ((transactionDateTest[8] - '0') * 10) + ((transactionDateTest[9]) - '0');
	uint32_t TransactionMonth = ((transactionDateTest[3] - '0') * 10) + ((transactionDateTest[4]) - '0');
	/*uint32_t CardExpirationYear = (atoi(cardData->cardExpirationDate[3]) * 10) + (atoi(cardData->cardExpirationDate[4]));
	uint32_t CardExpirationMonth =(atoi(cardData->cardExpirationDate[0]) * 10) + (atoi(cardData->cardExpirationDate[1]));

	uint32_t TransactionYear = (atoi(termData->transactionDate[8]) * 10) + (atoi(termData->transactionDate[9]));
	uint32_t TransactionMonth= (atoi(termData->transactionDate[3]) * 10) + (atoi(termData->transactionDate[4]));
	*/
	if (CardExpirationYear > TransactionYear)
	{
		printf("\t\t\tTERMINAL_OK\n");
		printf("---------------------------------------------------\n");
		//return TERMINAL_OK;
	}
	else
	{
		if (CardExpirationYear < TransactionYear)
		{
			printf("\t\t\tEXPIRED_CARD\n");
			printf("---------------------------------------------------\n");
			//return EXPIRED_CARD;
		}
		else if (CardExpirationYear == TransactionYear)
		{
			if (TransactionMonth < CardExpirationMonth)
			{
				printf("\t\t\tTERMINAL_OK\n");
				printf("---------------------------------------------------\n");
				//return TERMINAL_OK;
			}
			else
			{
				printf("\t\t\tEXPIRED_CARD\n");
				printf("---------------------------------------------------\n");
				//return EXPIRED_CARD;
			}
		}
	}
}

void getTransactionAmountTest(void)
{
	printf("please enter transaction amount\t\t\t\t\t:");
	(void)scanf("%f", &(transAmountTest));
	//2-If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return TERMINAL_OK.
	if (transAmountTest <= 0)
	{
		printf("\t\t\tINVALID_AMOUNT\n");
		printf("---------------------------------------------------\n");
		//return INVALID_AMOUNT;
	}
	else
	{
		printf("\t\t\tTERMINAL_OK\n");
		printf("---------------------------------------------------\n");
		//return TERMINAL_OK;
	}
}
void isBelowMaxAmountTest(void)
{
	printf("please enter maximum allowed amount\t\t\t\t:");
	(void)scanf("%f", &(maxTransAmountTest));
	printf("please enter transaction amount\t\t\t\t\t:");
	(void)scanf("%f", &(transAmountTest));

	if (transAmountTest > maxTransAmountTest)
	{
		printf("\t\t\tEXCEED_MAX_AMOUNT\n");
		printf("---------------------------------------------------\n");
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		printf("\t\t\tTERMINAL_OK\n");
		printf("---------------------------------------------------\n");
		return TERMINAL_OK;
	}
}
void setMaxAmountTest(void)
{
	printf("please enter maximum allowed amount\t\t\t\t:");
	(void)scanf("%f", &(maxTransAmountTest));
	//If transaction max amount less than or equal to 0 will return the INVALID_MAX_AMOUNT error, else return TERMINAL_OK.
	if ((maxTransAmountTest) <= 0)
	{
		printf("\t\t\tINVALID_MAX_AMOUNT\n");
		printf("---------------------------------------------------\n");
		//return INVALID_MAX_AMOUNT;
	}
	else
	{
		printf("\t\t\tTERMINAL_OK\n");
		printf("---------------------------------------------------\n");
		//return TERMINAL_OK;
	}
}