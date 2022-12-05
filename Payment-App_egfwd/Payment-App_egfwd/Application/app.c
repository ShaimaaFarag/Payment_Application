#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NONSTDC_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>

#include "app.h"
//object to card data and its error
ST_cardData_t CardData;
EN_cardError_t CardError;

//object to terminal data and its errror
ST_terminalData_t TermData;
EN_terminalError_t TermError;

//object to transaction data 
ST_transaction_t TransData;

//refernce to the account
ST_accountsDB_t accountRef;
				
//enum object for the state of transaction
EN_transState_t transState;

//EN_testCase_t testCase;
///
extern uint32_t* ptr;

void appStart(void)
{
	/*uint8_t Test_case;
	printf("chose the test case:\n\
	for Transaction_approved_user_story (press 0 )\n \
	for Exceed_the_maximum_amount_user_story (press 1 )\n\
	for	Insufficient_fund_user_story (press 2 )\n \
	for    Expired_card_user_story(press 3 ) \n\
	for Stolen_card_user_story(press 4 )");
	(void)scanf("%c",&Test_case);
	switch (testCase)
	{
	case  Transaction_approved_user_story:
		printf("As a bank customer have an account and has a valid and not expired card,\
				I want to withdraw an amount of money less than the maximum allowed and less than or equal to the amount \
				in my balance, so that I am expecting that the transaction is approved and my account balance is reduced by\
				the withdrawn amount.\n");
		//printf("");
		break;
	case  Exceed_the_maximum_amount_user_story:
		printf("As a bank customer have an account, that has a valid and not expired card, \
		I want to withdraw an amount of money that exceeds the maximum allowed amount so that I am expecting \
		the transaction declined.\n");
		//printf("");
		break;
	case  Insufficient_fund_user_story:
		printf("As a bank customer have an account and has a valid and not expired card,\
		 I want to withdraw an amount of money less than the maximum allowed and larger than the amount \
		in my balance so that I am expecting that the transaction declined.\n");
		//printf("");
		break;
	case  Expired_card_user_story:
		printf("As a bank customer have an account and a valid but expired card, \
		I want to withdraw an amount of money so that I expect that the transaction declined.\n");
		//printf("");
		break;
	case  Stolen_card_user_story:
		printf("As a bank customer have an account and has a valid and not expired but stolen card, \
		I want to block anyone from using my card so that I am expecting that any transaction made by this card is declined.\n");
		//printf("");
		break;
	default:
		break;
	}*/
	/**********check card functions*********/
	//check for card holder name
	CardError = getCardHolderName(&CardData);
	while (WRONG_NAME == CardError)
	{
		printf("\t\t\tYou have entered a wrong name!\n\t\t\tplease try again:\n");
		CardError = getCardHolderName(&CardData);
	}
	//check for card pan
	CardError = getCardPAN(&CardData);
	while (WRONG_PAN == CardError)
	{
		printf("\t\t\tYou have entered a wrong pan!\n\t\t\tplease try again:\n");
		CardError = getCardPAN(&CardData);
	}
	//check for card expiry date
	CardError = getCardExpiryDate(&CardData);
	while (WRONG_EXP_DATE == CardError)
	{
		printf("\t\t\tYou have entered a wrong expiry date!\n\t\t\tplease try again:\n");
		CardError = getCardExpiryDate(&CardData);
	}


	/************check terminal functions******************/
	//check for transaction data
	TermError = getTransactionDate(&TermData);
	while (WRONG_DATE == TermError)
	{
		printf("\t\t\tYou have entered a wrong date!\n\t\t\tplease try again:\n");
		TermError = getTransactionDate(&TermData);
	}
	//check if card expired
	TermError = isCardExpired(&CardData, &TermData);
	if (EXPIRED_CARD == TermError)
	{
		printf("\t\t\tThis card is expired!\n");
		exit(0);
	}
	//set max amount
	TermError = setMaxAmount(&TermData);
	while (INVALID_MAX_AMOUNT == TermError)
	{
		printf("\t\t\tYou have entered an invalid max amount!\n\t\t\tplease try again:\n");
		TermError = setMaxAmount(&TermData);
	}
	//check for get trans amount
	TermError = getTransactionAmount(&TermData);
	while (INVALID_AMOUNT == TermError)
	{
		printf("\t\t\tYou have entered an invalid amount!\n\t\t\tplease try again:\n");
		TermError = getTransactionAmount(&TermData);
	}
	//check if below max amount
	TermError = isBelowMaxAmount(&TermData);
	if (EXCEED_MAX_AMOUNT == TermError)
	{
		printf("\t\t\tEXCEED_MAX_AMOUNT!\n");
		exit(0);
	}


	/***********check server functions***************/
	//check if the account is valid or not and if yes check if running or blocked
	//accountRef.balance = 10000.0;
	/*if (isValidAccount(&CardData, &accountRef) == ACCOUNT_NOT_FOUND)
	{
		printf("\t\t\taccount not found!\n");
		return;
	}
	else
	{
		if (isBlockedAccount(&accountRef) == BLOCKED_ACCOUNT)
		{
			printf("\t\t\taccount is blocked!\n");
			return;
		}
	}
	//check if the amount is available or not
	if (isAmountAvailable(&TermData, &accountRef) == LOW_BALANCE)
	{
		printf("\t\t\tit's a low balance!\n");
		return;
	}*/
	//save transaction
	//saveTransaction(&TransData);
	TransData.cardHolderData = CardData;
	TransData.terminalData = TermData;

	//check transaction state after recive transaction
	transState = recieveTransactionData(&TransData);
	if (transState == FRAUD_CARD)
	{
		printf("\t\t\tit's a FRAUD CARD !\n");

	}
	else if (transState == DECLINED_INSUFFECIENT_FUND)
	{
		printf("\t\t\tit's a DECLINED_INSUFFECIENT_FUND !\n");

	}
	else if (transState == DECLINED_STOLEN_CARD)
	{
		printf("\t\t\tit's a DECLINED_STOLEN_CARD !\n");

	}
	else if (transState == INTERNAL_SERVER_ERROR)
	{
		printf("\t\t\tit's a INTERNAL_SERVER_ERROR !\n");

	}
	else if (transState == APPROVED)
	{
		printf("\t\t\ttransaction approved !\n");

	}




/********test functions********/
/*void appStart(void)
{

	
	/*uint32_t counter;
	printf("Tester Name\t\t\t: shaima farag\n");
	printf("Function Name\t\t\t: getCardHolderName\n");
	for (counter = 1; counter < 5; ++counter)
	{
		switch(counter)
		{
		case 1:
			printf("Test Case 1\t\t\t:If the cardholder name is NULL\n");
			printf("Input Data\t\t\t:press Enteror \\0\n");
			printf("Expected Result\t\t\t:WRONG_NAME\n");
			printf("Actual Result\t\t\t:\n");
			getCardHolderNameTest();
			break;
		case 2:
			printf("Test Case 2\t\t\t:If the cardholder name is less than 20 characters\n");
			printf("Input Data\t\t\t:shaimaa farag\n");
			printf("Expected Result\t\t\t:WRONG_NAME\n");
			printf("Actual Result\t\t\t:\n");
			getCardHolderNameTest();
			break;
		case 3:
			printf("Test Case 3\t\t\t:If the cardholder name is more than 24 characters\n");
			printf("Input Data\t\t\t:shaimaaa farag okily hamed\n");
			printf("Expected Result\t\t\t:WRONG_NAME\n");
			printf("Actual Result\t\t\t:\n");
			getCardHolderNameTest();
			break;
		case 4:
			printf("Test Case 4\t\t\t:If the cardholder name is more than 20 and less than 25 characters\n");
			printf("Input Data\t\t\t:shaima farag okily hamed\n");
			printf("Expected Result\t\t\t:CARD_OK\n");
			printf("Actual Result\t\t\t:\n");
			getCardHolderNameTest();
			break;
		default:
			break;
		}

	}*/
	

	/*uint32_t counter;
	printf("Tester Name\t\t\t: shaima farag\n");
	printf("Function Name\t\t\t: getCardExpiryDateTest\n");
	for (counter = 1; counter <=5; ++counter)
	{
		switch (counter)
		{
		case 1:
			printf("Test Case 1\t\t\t:If the card expiry date is NULL\n");
			printf("Input Data\t\t\t:press Enter or \\0\n");
			printf("Expected Result\t\t\t:WRONG_EXP_DATE \n");
			printf("Actual Result\t\t\t:\n");
			getCardExpiryDateTest();
			break;
		case 2:
			printf("Test Case 2\t\t\t:the card expiry date is less  than 5 characters\n");
			printf("Input Data\t\t\t:5\/25\n");
			printf("Expected Result\t\t\t:WRONG_EXP_DATE \n");
			printf("Actual Result\t\t\t:\n");
			getCardExpiryDateTest();
			break;
		case 3:
			printf("Test Case 3\t\t\t:the card expiry date is more  than 5 characters\n");
			printf("Input Data\t\t\t:05\/2025\n");
			printf("Expected Result\t\t\t:WRONG_EXP_DATE \n");
			printf("Actual Result\t\t\t:\n");
			getCardExpiryDateTest();
			break;
		case 4:
			printf("Test Case 4\t\t\t:the card expiry date has the wrong format\n");
			printf("Input Data\t\t\t:05\:25\n");
			printf("Expected Result\t\t\t:WRONG_EXP_DATE \n");
			printf("Actual Result\t\t\t:\n");
			getCardExpiryDateTest();
			break;
		case 5:
			printf("Test Case 5\t\t\t:the format \"MM \/ YY\", e.g \"05 \/ 25\"\n");
			printf("Input Data\t\t\t:05\/25\n");
			printf("Expected Result\t\t\t:CARD_OK \n");
			printf("Actual Result\t\t\t:\n");
			getCardExpiryDateTest();
			break;
		default:
			break;
		}

	}*/

	/*uint32_t counter;
	printf("Tester Name\t\t\t: shaima farag\n");
	printf("Function Name\t\t\t: getCardPANTest \n");
	for (counter = 1; counter < 5; ++counter)
	{
		switch (counter)
		{
		case 1:
			printf("Test Case 1\t\t\t:If the PAN is NULL\n");
			printf("Input Data\t\t\t:press Enteror \\0\n");
			printf("Expected Result\t\t\t:WRONG_PAN\n");
			printf("Actual Result\t\t\t:\n");
			getCardPANTest();
			break;
		case 2:
			printf("Test Case 2\t\t\t:If the PAN less than 16 characters\n");
			printf("Input Data\t\t\t:297041749494321\n");
			printf("Expected Result\t\t\t:WRONG_PAN\n");
			printf("Actual Result\t\t\t:\n");
			getCardPANTest();
			break;
		case 3:
			printf("Test Case 3\t\t\t:If the PAN more than 19 characters\n");
			printf("Input Data\t\t\t:19843025340167832981\n");
			printf("Expected Result\t\t\t:WRONG_PAN\n");
			printf("Actual Result\t\t\t:\n");
			getCardPANTest();
			break;
		case 4:
			printf("Test Case 4\t\t\t:If the PAN more than 15 and less than 20 characters\n");
			printf("Input Data\t\t\t:8989374615436851\n");
			printf("Expected Result\t\t\t:CARD_OK\n");
			printf("Actual Result\t\t\t:\n");
			getCardPANTest();
			break;
		default:
			break;
		}

	}*/
	/*uint32_t counter;
	printf("Tester Name\t\t\t: shaima farag\n");
	printf("Function Name\t\t\t: getTransactionDateTest \n");
	for (counter = 1; counter < 5; ++counter)
	{
		switch (counter)
		{
		case 1:
			printf("Test Case 1\t\t\t:If the transaction date is NULL\n");
			printf("Input Data\t\t\t:press Enteror \\0\n");
			printf("Expected Result\t\t\t:WRONG_DATE \n");
			printf("Actual Result\t\t\t:\n");
			getTransactionDateTest();
			break;
		case 2:
			printf("Test Case 2\t\t\t:If the transaction date is less than 10 characters\n");
			printf("Input Data\t\t\t:17/11/22\n");
			printf("Expected Result\t\t\t:WRONG_DATE \n");
			printf("Actual Result\t\t\t:\n");
			getTransactionDateTest();
			break;
		case 3:
			printf("Test Case 3\t\t\t:If the transaction date is wrong format\n");
			printf("Input Data\t\t\t:17\:11\:2022\n");
			printf("Expected Result\t\t\t:WRONG_DATE \n");
			printf("Actual Result\t\t\t:\n");
			getTransactionDateTest();
			break;
		case 4:
			printf("Test Case 4\t\t\t:If the transaction date is in the format DD\/MM\/YYYY\n");
			printf("Input Data\t\t\t:17/11/2022\n");
			printf("Expected Result\t\t\t:TERMINAL_OK\n");
			printf("Actual Result\t\t\t:\n");
			getTransactionDateTest();
			break;
		default:
			break;
		}

	}*/
	/*uint32_t counter;
	printf("Tester Name\t\t\t: shaima farag\n");
	printf("Function Name\t\t\t: isCardExpriedTest \n");
	for (counter = 1; counter < 5; ++counter)
	{
		switch (counter)
		{
		case 1:
			printf("Test Case 1\t\t\t:if CardExpirationYear \> TransactionYear\n");
			printf("Input Data\t\t\t:05/25,17/11/2022\n");
			printf("Expected Result\t\t\t:TERMINAL_OK \n");
			printf("Actual Result\t\t\t:\n");
			isCardExpriedTest();
			break;
		case 2:
			printf("Test Case 2\t\t\tif CardExpirationYear \< TransactionYear\n");
			printf("Input Data\t\t\t:05/21,17/11/2022n");
			printf("Expected Result\t\t\t:EXPIRED_CARD \n");
			printf("Actual Result\t\t\t:\n");
			isCardExpriedTest();
			break;
		case 3:
			printf("Test Case 3\t\t\t:if CardExpirationYear = TransactionYear and TransactionMonth \< CardExpirationMonth\n");
			printf("Input Data\t\t\t:12/22,17/11/2022\n");
			printf("Expected Result\t\t\t:TERMINAL_OK \n");
			printf("Actual Result\t\t\t:\n");
			isCardExpriedTest();
			break;
		case 4:
			printf("Test Case 4\t\t\t:if CardExpirationYear = TransactionYear and TransactionMonth \>= CardExpirationMonth\n");
			printf("Input Data\t\t\t:10/22,17/11/2022\n");
			printf("Expected Result\t\t\t:EXPIRED_CARD\n");
			printf("Actual Result\t\t\t:\n");
			isCardExpriedTest();
			break;
		default:
			break;
		}
	}*/
	/*uint32_t counter;
	printf("Tester Name\t\t\t: shaima farag\n");
	printf("Function Name\t\t\t: getTransactionAmountTest \n");
	for (counter = 1; counter < 4; ++counter)
	{
		switch (counter)
		{
		case 1:
			printf("Test Case 1\t\t\t:If the transaction amount is less than 0\n");
			printf("Input Data\t\t\t:-20\n");
			printf("Expected Result\t\t\t:INVALID_AMOUNT \n");
			printf("Actual Result\t\t\t:\n");
			getTransactionAmountTest();
			break;
		case 2:
			printf("Test Case 2\t\t\tIf the transaction amount is equal to 0\n");
			printf("Input Data\t\t\t:0\n");
			printf("Expected Result\t\t\t:INVALID_AMOUNT \n");
			printf("Actual Result\t\t\t:\n");
			getTransactionAmountTest();
			break;
		case 3:
			printf("Test Case 3\t\t\t:If the transaction amount is  larger than 0\n");
			printf("Input Data\t\t\t:2000\n");
			printf("Expected Result\t\t\t:TERMINAL_OK \n");
			printf("Actual Result\t\t\t:\n");
			getTransactionAmountTest();
			break;
		default:
			break;
		}
	}*/
	/*uint32_t counter;
	printf("Tester Name\t\t\t: shaima farag\n");
	printf("Function Name\t\t\t: isBelowMaxAmountTest \n");
	for (counter = 1; counter < 3; ++counter)
	{
		switch (counter)
		{
		case 1:
			printf("Test Case 1\t\t\t:If the transaction amount is larger than the terminal max allowed amount\n");
			printf("Input Data\t\t\t:maxAmount=10000,transAmount=15000\n");
			printf("Expected Result\t\t\t:EXCEED_MAX_AMOUNT \n");
			printf("Actual Result\t\t\t:\n");
			isBelowMaxAmountTest();
			break;
		case 2:
			printf("Test Case 2\t\t\tIf the transaction amount is less than or equal the terminal max allowed amount\n");
			printf("Input Data\t\t\t:maxAmount=10000,transAmount=5000\n");
			printf("Expected Result\t\t\t:TERMINAL_OK \n");
			printf("Actual Result\t\t\t:\n");
			isBelowMaxAmountTest();
			break;

		default:
			break;
		}
	}*/
	
/*uint32_t counter;
printf("Tester Name\t\t\t: shaima farag\n");
printf("Function Name\t\t\t: setMaxAmountTest \n");
for (counter = 1; counter < 4; ++counter)
{
	switch (counter)
	{
	case 1:
		printf("Test Case 1\t\t\t:If the transaction max amount is less than 0\n");
		printf("Input Data\t\t\t:-20\n");
		printf("Expected Result\t\t\t:INVALID_MAX_AMOUNT \n");
		printf("Actual Result\t\t\t:\n");
		setMaxAmountTest();
		break;
	case 2:
		printf("Test Case 2\t\t\tIf the transaction max amount is equal to 0\n");
		printf("Input Data\t\t\t:0\n");
		printf("Expected Result\t\t\t:INVALID_MAX_AMOUNT \n");
		printf("Actual Result\t\t\t:\n");
		setMaxAmountTest();
		break;
	case 3:
		printf("Test Case 3\t\t\t:If the transaction max amount is  larger than 0\n");
		printf("Input Data\t\t\t:2000\n");
		printf("Expected Result\t\t\t:TERMINAL_OK \n");
		printf("Actual Result\t\t\t:\n");
		setMaxAmountTest();
		break;
	default:
		break;
	}
}*/
/*uint32_t counter;
printf("Tester Name\t\t\t: shaima farag\n");
printf("Function Name\t\t\t: isValidAccountTest \n");
for (counter = 1; counter < 3; ++counter)
{
	switch (counter)
	{
	case 1:
		printf("Test Case 1\t\t\t:If the PAN doesn't exist will return ACCOUNT_NOT_FOUND\n");
		printf("Input Data\t\t\t:9552843496832821\n");
		printf("Expected Result\t\t\t:ACCOUNT_NOT_FOUND \n");
		printf("Actual Result\t\t\t:\n");
		isValidAccountTest();
		break;
	case 2:
		printf("Test Case 2\t\t\t/if PAN exists return SERVER_OK\n");
		printf("Input Data\t\t\t:8989374615436851\n");
		printf("Expected Result\t\t\t:SERVER_OK \n");
		printf("Actual Result\t\t\t:\n");
		isValidAccountTest();
		break;
	default:
		break;
	}
}*/
/*uint32_t counter;
printf("Tester Name\t\t\t: shaima farag\n");
printf("Function Name\t\t\t: isBlockedAccountTest \n");
for (counter = 1; counter < 3; ++counter)
{
	switch (counter)
	{
	case 1:
		printf("Test Case 1\t\t\t:If the account is running it will return SERVER_OK\n");
		printf("Input Data\t\t\t:0\n");
		printf("Expected Result\t\t\t:SERVER_OK \n");
		printf("Actual Result\t\t\t:\n");
		isBlockedAccountTest();
		break;
	case 2:
		printf("Test Case 2\t\t\t/if the account is blocked it will return BLOCKED_ACCOUNT.\n");
		printf("Input Data\t\t\t:2\n");
		printf("Expected Result\t\t\t:BLOCKED_ACCOUNT \n");
		printf("Actual Result\t\t\t:\n");
		isBlockedAccountTest();
		break;
	default:
		break;
	}
}*/
/*uint32_t counter;
printf("Tester Name\t\t\t: shaima farag\n");
printf("Function Name\t\t\t: isAmountAvailableTest \n");
for (counter = 1; counter < 3; ++counter)
{
	switch (counter)
	{
	case 1:
		printf("Test Case 1\t\t\t:If the transaction amount is greater than the balance in the database\n");
		printf("Input Data\t\t\t:transaction amount=3000,AccountRefInDB=0\n");
		printf("Expected Result\t\t\t:LOW_BALANCE \n");
		printf("Actual Result\t\t\t:\n");
		isAmountAvailableTest();
		break;
	case 2:
		printf("Test Case 2\t\t\tIf the transaction amount is less than or equal the balance in the database\n");
		printf("Input Data\t\t\t:transaction amount=5000,AccountRefInDB=2\n");
		printf("Expected Result\t\t\t:SERVER_OK \n");
		printf("Actual Result\t\t\t:\n");
		isAmountAvailableTest();
		break;
	default:
		break;
	}
}*/
/*uint32_t counter;
printf("Tester Name\t\t\t: shaima farag\n");
printf("Function Name\t\t\t: saveTransactionTest \n");
for (counter = 1; counter < 2; ++counter)
{
	switch (counter)
	{
	case 1:
		printf("Test Case 1\t\t\t:\n");
		printf("Input Data\t\t\t:\n");
		printf("Expected Result\t\t\t:SERVER_OK \n");
		printf("Actual Result\t\t\t:\n");
		saveTransactionTest();
		break;
	default:
		break;
	}
//}

/*******test recieve function**********/
/*uint32_t counter;
printf("Tester Name\t\t\t: shaima farag\n");
printf("Function Name\t\t\t: recieveTransactionData\n");
for (counter = 1; counter < 6; ++counter)
{
	switch (counter)
	{
	case 1:
		printf("Test Case 1\t\t\t:If the account does not exist return FRAUD_CARD\n");
		printf("Input Data\t\t\t:PAN=3085769111844637\n");
		printf("Expected Result\t\t\t:FRAUD_CARD\n");
		printf("Actual Result\t\t\t:\n");
		//check for card holder name
		CardError = getCardHolderName(&CardData);
		while (WRONG_NAME == CardError)
		{
			printf("\t\t\tYou have entered a wrong name!\n\t\t\tplease try again:\n");
			CardError = getCardHolderName(&CardData);
		}
		//check for card pan
		CardError = getCardPAN(&CardData);
		while (WRONG_PAN == CardError)
		{
			printf("\t\t\tYou have entered a wrong pan!\n\t\t\tplease try again:\n");
			CardError = getCardPAN(&CardData);
		}
		//check for card expiry date
		CardError = getCardExpiryDate(&CardData);
		while (WRONG_EXP_DATE == CardError)
		{
			printf("\t\t\tYou have entered a wrong expiry date!\n\t\t\tplease try again:\n");
			CardError = getCardExpiryDate(&CardData);
		}
		//check for transaction data
		TermError = getTransactionDate(&TermData);
		while (WRONG_DATE == TermError)
		{
			printf("\t\t\tYou have entered a wrong date!\n\t\t\tplease try again:\n");
			TermError = getTransactionDate(&TermData);
		}
		//check if card expired
		TermError = isCardExpired(&CardData, &TermData);
		if (EXPIRED_CARD == TermError)
		{
			printf("\t\t\tThis card is expired!\n");
			exit(0);
		}
		//set max amount
		TermError = setMaxAmount(&TermData);
		while (INVALID_MAX_AMOUNT == TermError)
		{
			printf("\t\t\tYou have entered an invalid max amount!\n\t\t\tplease try again:\n");
			TermError = setMaxAmount(&TermData);
		}
		//check for get trans amount
		TermError = getTransactionAmount(&TermData);
		while (INVALID_AMOUNT == TermError)
		{
			printf("\t\t\tYou have entered an invalid amount!\n\t\t\tplease try again:\n");
			TermError = getTransactionAmount(&TermData);
		}
		//check if below max amount
		TermError = isBelowMaxAmount(&TermData);
		if (EXCEED_MAX_AMOUNT == TermError)
		{
			printf("\t\t\tEXCEED_MAX_AMOUNT!\n");
			exit(0);
		}
		TransData.cardHolderData = CardData;
		TransData.terminalData = TermData;
		transState = recieveTransactionData(&TransData);
		if (transState == FRAUD_CARD)
		{
			printf("\t\t\tit's a FRAUD CARD !\n");

		}
		else if (transState == DECLINED_INSUFFECIENT_FUND)
		{
			printf("\t\t\tit's a DECLINED_INSUFFECIENT_FUND !\n");

		}
		else if (transState == DECLINED_STOLEN_CARD)
		{
			printf("\t\t\tit's a DECLINED_STOLEN_CARD !\n");

		}
		else if (transState == INTERNAL_SERVER_ERROR)
		{
			printf("\t\t\tit's a INTERNAL_SERVER_ERROR !\n");

		}
		else if (transState == APPROVED)
		{
			printf("\t\t\ttransaction approved !\n");

		}
		printf("---------------------------------------------------\n");
		break;
	case 2:
		printf("Test Case 2\t\t\t:/if the amount is not available will return DECLINED_INSUFFECIENT_FUND\n");
		printf("Input Data\t\t\t:PAN=4237758758846158,MaxAmount=10000,TransAmount=9500\n");
		printf("Expected Result\t\t\t:DECLINED_INSUFFECIENT_FUND\n");
		printf("Actual Result\t\t\t:\n");

//check for card holder name
			CardError = getCardHolderName(&CardData);
			while (WRONG_NAME == CardError)
			{
				printf("\t\t\tYou have entered a wrong name!\n\t\t\tplease try again:\n");
				CardError = getCardHolderName(&CardData);
			}
			//check for card pan
			CardError = getCardPAN(&CardData);
			while (WRONG_PAN == CardError)
			{
				printf("\t\t\tYou have entered a wrong pan!\n\t\t\tplease try again:\n");
				CardError = getCardPAN(&CardData);
			}
			//check for card expiry date
			CardError = getCardExpiryDate(&CardData);
			while (WRONG_EXP_DATE == CardError)
			{
				printf("\t\t\tYou have entered a wrong expiry date!\n\t\t\tplease try again:\n");
				CardError = getCardExpiryDate(&CardData);
			}

	//check for transaction data
			TermError = getTransactionDate(&TermData);
			while (WRONG_DATE == TermError)
			{
				printf("\t\t\tYou have entered a wrong date!\n\t\t\tplease try again:\n");
				TermError = getTransactionDate(&TermData);
			}
			//check if card expired
			TermError = isCardExpired(&CardData, &TermData);
			if (EXPIRED_CARD == TermError)
			{
				printf("\t\t\tThis card is expired!\n");
				exit(0);
			}
			//set max amount
			TermError = setMaxAmount(&TermData);
			while (INVALID_MAX_AMOUNT == TermError)
			{
				printf("\t\t\tYou have entered an invalid max amount!\n\t\t\tplease try again:\n");
				TermError = setMaxAmount(&TermData);
			}
			//check for get trans amount
			TermError = getTransactionAmount(&TermData);
			while (INVALID_AMOUNT == TermError)
			{
				printf("\t\t\tYou have entered an invalid amount!\n\t\t\tplease try again:\n");
				TermError = getTransactionAmount(&TermData);
			}
			//check if below max amount
			TermError = isBelowMaxAmount(&TermData);
			if (EXCEED_MAX_AMOUNT == TermError)
			{
				printf("\t\t\tEXCEED_MAX_AMOUNT!\n");
				exit(0);
			}
			TransData.cardHolderData = CardData;
			TransData.terminalData = TermData;
			transState = recieveTransactionData(&TransData);
			if (transState == FRAUD_CARD)
			{
				printf("\t\t\tit's a FRAUD CARD !\n");

			}
			else if (transState == DECLINED_INSUFFECIENT_FUND)
			{
				printf("\t\t\tit's a DECLINED_INSUFFECIENT_FUND !\n");

			}
			else if (transState == DECLINED_STOLEN_CARD)
			{
				printf("\t\t\tit's a DECLINED_STOLEN_CARD !\n");

			}
			else if (transState == INTERNAL_SERVER_ERROR)
			{
				printf("\t\t\tit's a INTERNAL_SERVER_ERROR !\n");

			}
			else if (transState == APPROVED)
			{
				printf("\t\t\ttransaction approved !\n");

			}
			printf("---------------------------------------------------\n");
			break;
		case 3:
			printf("Test Case 3\t\t\t:if the account is blocked will return DECLINED_STOLEN_CARD\n");
			printf("Input Data\t\t\t:PAN=5807007076043875,MaxAmount=10000,TransAmount=5000\n");
			printf("Expected Result\t\t\t:DECLINED_STOLEN_CARD\n");
			printf("Actual Result\t\t\t:\n");

//check for card holder name
			CardError = getCardHolderName(&CardData);
			while (WRONG_NAME == CardError)
			{
				printf("\t\t\tYou have entered a wrong name!\n\t\t\tplease try again:\n");
				CardError = getCardHolderName(&CardData);
			}
			//check for card pan
			CardError = getCardPAN(&CardData);
			while (WRONG_PAN == CardError)
			{
				printf("\t\t\tYou have entered a wrong pan!\n\t\t\tplease try again:\n");
				CardError = getCardPAN(&CardData);
			}
			//check for card expiry date
			CardError = getCardExpiryDate(&CardData);
			while (WRONG_EXP_DATE == CardError)
			{
				printf("\t\t\tYou have entered a wrong expiry date!\n\t\t\tplease try again:\n");
				CardError = getCardExpiryDate(&CardData);
			}

	//check for transaction data
			TermError = getTransactionDate(&TermData);
			while (WRONG_DATE == TermError)
			{
				printf("\t\t\tYou have entered a wrong date!\n\t\t\tplease try again:\n");
				TermError = getTransactionDate(&TermData);
			}
			//check if card expired
			TermError = isCardExpired(&CardData, &TermData);
			if (EXPIRED_CARD == TermError)
			{
				printf("\t\t\tThis card is expired!\n");
				exit(0);
			}
			//set max amount
			TermError = setMaxAmount(&TermData);
			while (INVALID_MAX_AMOUNT == TermError)
			{
				printf("\t\t\tYou have entered an invalid max amount!\n\t\t\tplease try again:\n");
				TermError = setMaxAmount(&TermData);
			}
			//check for get trans amount
			TermError = getTransactionAmount(&TermData);
			while (INVALID_AMOUNT == TermError)
			{
				printf("\t\t\tYou have entered an invalid amount!\n\t\t\tplease try again:\n");
				TermError = getTransactionAmount(&TermData);
			}
			//check if below max amount
			TermError = isBelowMaxAmount(&TermData);
			if (EXCEED_MAX_AMOUNT == TermError)
			{
				printf("\t\t\tEXCEED_MAX_AMOUNT!\n");
				exit(0);
			}
			TransData.cardHolderData = CardData;
			TransData.terminalData = TermData;
			transState = recieveTransactionData(&TransData);
			if (transState == FRAUD_CARD)
			{
				printf("\t\t\tit's a FRAUD CARD !\n");

			}
			else if (transState == DECLINED_INSUFFECIENT_FUND)
			{
				printf("\t\t\tit's a DECLINED_INSUFFECIENT_FUND !\n");

			}
			else if (transState == DECLINED_STOLEN_CARD)
			{
				printf("\t\t\tit's a DECLINED_STOLEN_CARD !\n");

			}
			else if (transState == INTERNAL_SERVER_ERROR)
			{
				printf("\t\t\tit's a INTERNAL_SERVER_ERROR !\n");

			}
			else if (transState == APPROVED)
			{
				printf("\t\t\ttransaction approved !\n");

			}
			printf("---------------------------------------------------\n");
			break;
		case 4:
			printf("Test Case 4\t\t\t:if a transaction  saved will return  APPROVED.\n");
			printf("Input Data\t\t\t:PAN=8989374615436851,MaxAmount=10000,TransAmount=1000\n");
			printf("Expected Result\t\t\t:APPROVED\n");
			printf("Actual Result\t\t\t:\n");

//check for card holder name
			CardError = getCardHolderName(&CardData);
			while (WRONG_NAME == CardError)
			{
				printf("\t\t\tYou have entered a wrong name!\n\t\t\tplease try again:\n");
				CardError = getCardHolderName(&CardData);
			}
			//check for card pan
			CardError = getCardPAN(&CardData);
			while (WRONG_PAN == CardError)
			{
				printf("\t\t\tYou have entered a wrong pan!\n\t\t\tplease try again:\n");
				CardError = getCardPAN(&CardData);
			}
			//check for card expiry date
			CardError = getCardExpiryDate(&CardData);
			while (WRONG_EXP_DATE == CardError)
			{
				printf("\t\t\tYou have entered a wrong expiry date!\n\t\t\tplease try again:\n");
				CardError = getCardExpiryDate(&CardData);
			}

	//check for transaction data
			TermError = getTransactionDate(&TermData);
			while (WRONG_DATE == TermError)
			{
				printf("\t\t\tYou have entered a wrong date!\n\t\t\tplease try again:\n");
				TermError = getTransactionDate(&TermData);
			}
			//check if card expired
			TermError = isCardExpired(&CardData, &TermData);
			if (EXPIRED_CARD == TermError)
			{
				printf("\t\t\tThis card is expired!\n");
				exit(0);
			}
			//set max amount
			TermError = setMaxAmount(&TermData);
			while (INVALID_MAX_AMOUNT == TermError)
			{
				printf("\t\t\tYou have entered an invalid max amount!\n\t\t\tplease try again:\n");
				TermError = setMaxAmount(&TermData);
			}
			//check for get trans amount
			TermError = getTransactionAmount(&TermData);
			while (INVALID_AMOUNT == TermError)
			{
				printf("\t\t\tYou have entered an invalid amount!\n\t\t\tplease try again:\n");
				TermError = getTransactionAmount(&TermData);
			}
			//check if below max amount
			TermError = isBelowMaxAmount(&TermData);
			if (EXCEED_MAX_AMOUNT == TermError)
			{
				printf("\t\t\tEXCEED_MAX_AMOUNT!\n");
				exit(0);
			}
			TransData.cardHolderData = CardData;
			TransData.terminalData = TermData;
			transState = recieveTransactionData(&TransData);
			if (transState == FRAUD_CARD)
			{
				printf("\t\t\tit's a FRAUD CARD !\n");

			}
			else if (transState == DECLINED_INSUFFECIENT_FUND)
			{
				printf("\t\t\tit's a DECLINED_INSUFFECIENT_FUND !\n");

			}
			else if (transState == DECLINED_STOLEN_CARD)
			{
				printf("\t\t\tit's a DECLINED_STOLEN_CARD !\n");

			}
			else if (transState == INTERNAL_SERVER_ERROR)
			{
				printf("\t\t\tit's a INTERNAL_SERVER_ERROR !\n");

			}
			else if (transState == APPROVED)
			{
				printf("\t\t\ttransaction approved !\n");

			}
			printf("---------------------------------------------------\n");
			break;
		case 5:
			printf("Test Case 5\t\t\t:if a transaction can't be saved will return INTERNAL_SERVER_ERROR \n");
			printf("Input Data\t\t\t:\n");
			printf("Expected Result\t\t\t:INTERNAL_SERVER_ERROR\n");
			printf("Actual Result\t\t\t:\n");

//check for card holder name
			CardError = getCardHolderName(&CardData);
			while (WRONG_NAME == CardError)
			{
				printf("\t\t\tYou have entered a wrong name!\n\t\t\tplease try again:\n");
				CardError = getCardHolderName(&CardData);
			}
			//check for card pan
			CardError = getCardPAN(&CardData);
			while (WRONG_PAN == CardError)
			{
				printf("\t\t\tYou have entered a wrong pan!\n\t\t\tplease try again:\n");
				CardError = getCardPAN(&CardData);
			}
			//check for card expiry date
			CardError = getCardExpiryDate(&CardData);
			while (WRONG_EXP_DATE == CardError)
			{
				printf("\t\t\tYou have entered a wrong expiry date!\n\t\t\tplease try again:\n");
				CardError = getCardExpiryDate(&CardData);
			}

	//check for transaction data
			TermError = getTransactionDate(&TermData);
			while (WRONG_DATE == TermError)
			{
				printf("\t\t\tYou have entered a wrong date!\n\t\t\tplease try again:\n");
				TermError = getTransactionDate(&TermData);
			}
			//check if card expired
			TermError = isCardExpired(&CardData, &TermData);
			if (EXPIRED_CARD == TermError)
			{
				printf("\t\t\tThis card is expired!\n");
				exit(0);
			}
			//set max amount
			TermError = setMaxAmount(&TermData);
			while (INVALID_MAX_AMOUNT == TermError)
			{
				printf("\t\t\tYou have entered an invalid max amount!\n\t\t\tplease try again:\n");
				TermError = setMaxAmount(&TermData);
			}
			//check for get trans amount
			TermError = getTransactionAmount(&TermData);
			while (INVALID_AMOUNT == TermError)
			{
				printf("\t\t\tYou have entered an invalid amount!\n\t\t\tplease try again:\n");
				TermError = getTransactionAmount(&TermData);
			}
			//check if below max amount
			TermError = isBelowMaxAmount(&TermData);
			if (EXCEED_MAX_AMOUNT == TermError)
			{
				printf("\t\t\tEXCEED_MAX_AMOUNT!\n");
				exit(0);
			}
			TransData.cardHolderData = CardData;
			TransData.terminalData = TermData;
			*ptr=258;
			transState = recieveTransactionData(&TransData);
			if (transState == FRAUD_CARD)
			{
				printf("\t\t\tit's a FRAUD CARD !\n");

			}
			else if (transState == DECLINED_INSUFFECIENT_FUND)
			{
				printf("\t\t\tit's a DECLINED_INSUFFECIENT_FUND !\n");

			}
			else if (transState == DECLINED_STOLEN_CARD)
			{
				printf("\t\t\tit's a DECLINED_STOLEN_CARD !\n");

			}
			else if (transState == INTERNAL_SERVER_ERROR)
			{
				printf("\t\t\tit's a INTERNAL_SERVER_ERROR !\n");

			}
			else if (transState == APPROVED)
			{
				printf("\t\t\ttransaction approved !\n");

			}
			break;
		default:
			break;
		}

	//}

}*/
