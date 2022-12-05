#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h> //for isdigit() function

#include "card.h"

/*
1-This function will ask for the cardholder's name and store it into card data.
2-Cardholder name is 24 alphabetic characters string max and 20 min.
3-If the cardholder name is NULL, less than 20 characters or more than 24 will return a WRONG_NAME error, else return CARD_OK.
*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	//ask for the cardholder's name and store it into card data.
	printf("please enter the cardholder's name\t\t\t\t: ");
	(void)scanf("%[^\n]%*c", cardData->cardHolderName);

	//If the cardholder name is NULL, less than 20 characters or more than 24 will return a WRONG_NAME error, else return CARD_OK.
	if((strlen(cardData->cardHolderName)==NULL) ||
		(strlen(cardData->cardHolderName) < 20) ||
		(strlen(cardData->cardHolderName) > 24))
	{
		//printf("\t\t\tWRONG_NAME\n");
		return WRONG_NAME;
	}
	else
	{
		//printf("\t\t\CARD_OK\n");
		return CARD_OK;
		
	}
}
/*
1-This function will ask for the card expiry date and store it in card data.
2-Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25".
3-If the card expiry date is NULL, less or more than 5 characters, or has the wrong format will return the WRONG_EXP_DATE error, else return CARD_OK.
*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	//ask for the card expiry date and store it in card data
	printf("please enter card expiry date as MM/YY\t\t\t\t: ");
	(void)scanf("%s", cardData->cardExpirationDate);
	//If the card expiry date is NULL, less or more than 5 characters, or has the wrong format will return the WRONG_EXP_DATE error, else return CARD_OK.
	if((strlen(cardData->cardExpirationDate) == NULL) ||
	   (strlen(cardData->cardExpirationDate) < 5) ||
	   (strlen(cardData->cardExpirationDate) > 5) ||
		((cardData->cardExpirationDate[2]) != '/')
	  // ((isdigit(cardData->cardExpirationDate[0]) != 0)||(isdigit(cardData->cardExpirationDate[1]) != 0)||
		//((cardData->cardExpirationDate[2]) != '/')//||(isdigit(cardData->cardExpirationDate[3]) != 0)||
		//(isdigit(cardData->cardExpirationDate[4]) != 0))
		)
	{
		return WRONG_EXP_DATE;
	}
	else
	{
		return CARD_OK;
	}
}
/*
1-This function will ask for the card's Primary Account Number and store it in card data.
2-PAN is 20 numeric characters string, 19 character max, and 16 character min.
3-If the PAN is NULL, less than 16 or more than 19 characters, will return the WRONG_PAN error, else return CARD_OK.
*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	//ask for the card's Primary Account Number and store it in card data.
	printf("please enter  card's Primary Account Number\t\t\t:");
	(void)scanf("%s", cardData->primaryAccountNumber);
	//If the PAN is NULL, less than 16 or more than 19 characters, will return the WRONG_PAN error, else return CARD_OK.
	if (
		(strlen(cardData->primaryAccountNumber)==NULL) ||
		(strlen(cardData->primaryAccountNumber)<16)    ||
		(strlen(cardData->primaryAccountNumber)>19))
		
	{
		return WRONG_PAN;
	}
	else
	{
		return CARD_OK;
	}
	
}

/************************test functions*******************************/
void getCardHolderNameTest(void)
{
	
	printf("please enter the cardholder's name\t\t\t\t: ");
	(void)scanf("%[^\n]%*c", cardHolderNameTest);

	//If the cardholder name is NULL, less than 20 characters or more than 24 will return a WRONG_NAME error, else return CARD_OK.
	if ((strlen(cardHolderNameTest) == NULL) ||
		(strlen(cardHolderNameTest) < MIN_CARDHOLDER_NAME) ||
		(strlen(cardHolderNameTest) > MAX_CARDHOLDER_NAME))
	{
		printf("\t\t\tWRONG_NAME\n");
		printf("---------------------------------------------------\n");
		//return WRONG_NAME;
	}
	else
	{
		printf("\t\t\tCARD_OK\n");
		printf("---------------------------------------------------\n");
		//return CARD_OK;

	}
}

void getCardExpiryDateTest(void)
{
	
	printf("please enter card expiry date as MM/YY\t\t\t\t: ");
	(void)scanf("%s", cardExpirationDateTest);
	//If the card expiry date is NULL, less or more than 5 characters, or has the wrong format will return the WRONG_EXP_DATE error, else return CARD_OK.
	if ((strlen(cardExpirationDateTest) == NULL) ||
		(strlen(cardExpirationDateTest) < 5) ||
		(strlen(cardExpirationDateTest) > 5) ||
		((cardExpirationDateTest[2]) != '/')
		// ((isdigit(cardData->cardExpirationDate[0]) != 0)||(isdigit(cardData->cardExpirationDate[1]) != 0)||
		  //((cardData->cardExpirationDate[2]) != '/')//||(isdigit(cardData->cardExpirationDate[3]) != 0)||
		  //(isdigit(cardData->cardExpirationDate[4]) != 0))
		)
	{
		printf("\t\t\tWRONG_EXP_DATE\n");
		printf("---------------------------------------------------\n");
		//return WRONG_EXP_DATE;
	}
	else
	{
		printf("\t\t\tCARD_OK\n");
		printf("---------------------------------------------------\n");
		return CARD_OK;
	}
}

void getCardPANTest(void)
{
	
	printf("please enter  card's Primary Account Number\t\t\t:");
	(void)scanf("%s", primaryAccountNumberTest);
	//If the PAN is NULL, less than 16 or more than 19 characters, will return the WRONG_PAN error, else return CARD_OK.
	if (
		(strlen(primaryAccountNumberTest) == NULL) ||
		(strlen(primaryAccountNumberTest) < 16) ||
		(strlen(primaryAccountNumberTest) > 19))

	{
		printf("\t\t\tWRONG_PAN \n");
		printf("---------------------------------------------------\n");
		//return WRONG_PAN;
	}
	else
	{
		printf("\t\t\tCARD_OK\n");
		printf("---------------------------------------------------\n");
		//return CARD_OK;
	}

}