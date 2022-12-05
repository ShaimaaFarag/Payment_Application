#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NONSTDC_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <ctype.h> //for isdigit() function
#include "server.h"

//global variable to return a reference to  account in the DB.
 uint32_t AccountRefInDB;
//global variable to give sequence number to a transaction, this number is incremented once a transaction is processed into the server
uint32_t SequenceNumber = 0;
uint32_t* ptr = &SequenceNumber;

/* global array of ST_accountsDB_t for the valid accounts database*/
ST_accountsDB_t accountsDB[255]=
{
	{2000.0 , RUNNING, "8989374615436851"},{100000.0, BLOCKED, "5807007076043875"},
	{10000.0, BLOCKED, "2472077658429553"},{12000.0 , RUNNING, "4514928712932808"},
	{1500.0 , BLOCKED, "5716735101470909"},{15000.0 , RUNNING, "0484360311241718"},
	{18000.0, RUNNING, "4111525335234849"},{20000.0 , RUNNING, "4587630861020318"},
	{3000.0 , BLOCKED, "4469042603760917"},{9000.0  , RUNNING, "4237758758846158"}

};
/* array of ST_transaction_t*/
uint32_t AccountRefInDBTest;
ST_transaction_t transaction[255] = { 0 };

/*************for test functions*************/
uint32_t AccountRefInDBTest;
static uint32_t SequenceNumberTest = 0;
ST_accountsDBTest_t accountsDBTest[255] =
{
	{2000.0 , RUNNING, "8989374615436851"},{100000.0, BLOCKED, "5807007076043875"},
	{10000.0, BLOCKED, "2472077658429553"},{12000.0 , RUNNING, "4514928712932808"},
	{1500.0 , BLOCKED, "5716735101470909"},{15000.0 , RUNNING, "0484360311241718"},
	{18000.0, RUNNING, "4111525335234849"},{20000.0 , RUNNING, "4587630861020318"},
	{3000.0 , BLOCKED, "4469042603760917"},{9000.0  , RUNNING, "4237758758846158"}

};
static ST_transactionTest_t transactionTest[255] = { 0 };
static ST_transactionTest_t transDataTest;
/*
1-This function will take all transaction data and validate its data, it contains all server logic.
2-It checks the account details and amount availability.
3-If the account does not exist return FRAUD_CARD, 
  if the amount is not available will return DECLINED_INSUFFECIENT_FUND, 
  if the account is blocked will return DECLINED_STOLEN_CARD, 
  if a transaction can't be saved will return INTERNAL_SERVER_ERROR , else returns APPROVED.
4-It will update the database with the new balance.
*/
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	uint8_t is_validAcc= isValidAccount(&(transData->cardHolderData), &accountsDB[AccountRefInDB]);
	uint8_t is_amountAvailable=isAmountAvailable(&(transData->terminalData),&accountsDB[AccountRefInDB]);
	uint8_t is_blocked = isBlockedAccount(&accountsDB[AccountRefInDB]);
	//If the account does not exist return FRAUD_CARD
	if (is_validAcc== ACCOUNT_NOT_FOUND)
	{
		transData->transState = FRAUD_CARD;
		saveTransaction(transData);
		printf("\t\t\taccount not found!\n");
		return FRAUD_CARD;
	}
	//if the amount is not available will return DECLINED_INSUFFECIENT_FUND
	if (is_amountAvailable == LOW_BALANCE)
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		saveTransaction(transData);
		printf("\t\t\tit's a low balance!\n");
		return DECLINED_INSUFFECIENT_FUND;
	}
	//if the account is blocked will return DECLINED_STOLEN_CARD
	if (is_blocked == BLOCKED_ACCOUNT)
	{
		transData->transState = DECLINED_STOLEN_CARD;
		saveTransaction(transData);
		printf("\t\t\taccount is blocked!\n");
		return DECLINED_STOLEN_CARD;
	}
	//if a transaction can't be saved will return INTERNAL_SERVER_ERROR , else returns APPROVED.
	if(saveTransaction(transData)==SAVING_FAILED)
	{
		return INTERNAL_SERVER_ERROR;
	}
	else
	{
		printf("\t\t\tNow ypur new balance=%f\n",((accountsDB[AccountRefInDB].balance) - (transData->terminalData.transAmount)));
		return APPROVED;
	}
}
/*
1-This function will take card data and validate if the account related to this card exists or not.
2-It checks if the PAN exists or not in the server's database (searches for the card PAN in the DB).
3-If the PAN doesn't exist will return ACCOUNT_NOT_FOUND and the account reference will be NULL, 
  else will return SERVER_OK and return a reference to this account in the DB.
*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	//take card data and validate if the account related to this card exists or not
	//if ((getCardPAN(cardData) == CARD_OK) && (getCardExpiryDate(cardData) == CARD_OK) && (getCardHolderName(cardData) == CARD_OK) )
	//EN_cardError_t PAN = getCardPAN(cardData);
	//EN_cardError_t ExpiryDate = getCardExpiryDate(cardData);
	//EN_cardError_t CardHolderName = getCardHolderName(cardData);
	//if ((PAN == CARD_OK) && (ExpiryDate == CARD_OK) && (CardHolderName == CARD_OK))
	{
		//check if the PAN exists or not in the server's database (searches for the card PAN in the DB).
		uint32_t counter ;
		for (counter = 0; counter < 255; counter++)
		{
			//if PAN exists return SERVER_OK and return a reference to this account in the DB.
			if (strcmp((cardData->primaryAccountNumber), (accountsDB[counter].primaryAccountNumber)) == 0)
			{
				AccountRefInDB = counter;
				//printf("counter=%d\n",counter);
				accountRefrence = &(accountsDB[counter]);
				printf("accountRefrenceBalance=%f\n",accountRefrence->balance);
				return SERVER_OK;
			}
			
		}
		//If the PAN doesn't exist will return ACCOUNT_NOT_FOUND and the account reference will be NULL
	//else
	{
		accountRefrence = NULL;
		AccountRefInDB = NULL;
		return ACCOUNT_NOT_FOUND;
	}
	}
}
/*
1-This function takes a reference to the account into the database and verifies if it is blocked or not.
2-If the account is running it will return SERVER_OK, else if the account is blocked it will return BLOCKED_ACCOUNT.
*/
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	//If the account is running it will return SERVER_OK
	accountRefrence = &accountsDB[AccountRefInDB];
	if((accountRefrence->state)==RUNNING)
	{
		return SERVER_OK;
	}
	//else if the account is blocked it will return BLOCKED_ACCOUNT.
	else 
	{
		return BLOCKED_ACCOUNT;
	}

}


/*
1-This function will take terminal data and a reference to the account in the database and check if the account has a sufficient amount to withdraw or not.
2-It checks if the transaction's amount is available or not.
3-If the transaction amount is greater than the balance in the database will return LOW_BALANCE, else will return SERVER_OK.
*/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	//check if the transaction's amount is available or not.
	if (getTransactionAmount(termData) == TERMINAL_OK)
	{
		accountRefrence = &accountsDB[AccountRefInDB];
		//printf("isamountav_aaccRef=%f\n", accountRefrence->balance);
		//If the transaction amount is greater than the balance in the database will return LOW_BALANCE
		if ((termData->transAmount) > accountRefrence->balance)
		{
			return LOW_BALANCE;
		}
		//else will return SERVER_OK.
		else
		{
			return SERVER_OK;
		}
	}
}

/*
1-This function will store all transaction data in the transactions database.
2-It gives a sequence number to a transaction, this number is incremented once a transaction is processed into
  the server,you must check the last sequence number in the server to give the new transaction a new sequence number.
3-It saves any type of transaction, APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD,
  INTERNAL_SERVER_ERROR.
4-It will list all saved transactions using the listSavedTransactions function.
5-Assuming that the connection between the terminal and server is always connected, then it will return SERVER_OK.
*/
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	if(SequenceNumber>=255)
	{
		printf("SequenceNumber=%d\n", SequenceNumber);
		return SAVING_FAILED;
	}
	else
	{
		
		//give a sequence number to a transaction
		transData->transactionSequenceNumber = SequenceNumber;
		// store all transaction data in the transactions database.
		strcpy(transaction[SequenceNumber].cardHolderData.cardExpirationDate , transData->cardHolderData.cardExpirationDate);
		strcpy(transaction[SequenceNumber].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
		strcpy(transaction[SequenceNumber].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);

		transaction[SequenceNumber].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
		strcpy(transaction[SequenceNumber].terminalData.transactionDate, transData->terminalData.transactionDate);
		transaction[SequenceNumber].terminalData.transAmount = transData->terminalData.transAmount;

		transaction[SequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber;
		transaction[SequenceNumber].transState = transData->transState;

		//number is incremented once a transaction is processed into the server
		SequenceNumber++;

		//list all saved transactions using the listSavedTransactions function.
		//listSavedTransactions(transData);
		
		//Assuming that the connection between the terminal and server is always connected, then it will return SERVER_OK.
		return SERVER_OK;
	}
	
	
}
/*
1-This function prints all transactions found in the transactions DB.
*/
void listSavedTransactions(ST_transaction_t* transData)
{
	printf("########################\n");
	

	printf("Cardholder Name	\t\t\t:%s\n", transData->cardHolderData.cardHolderName);
	printf("PAN\t\t\t\t\t:%s\n", transData->cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date\t\t\t:%s\n", transData->cardHolderData.cardExpirationDate);

	printf("Transaction Date\t\t\t:%s\n", transData->terminalData.transactionDate);
	printf("Terminal Max Amount\t\t\t:%f\n", transData->terminalData.maxTransAmount);
	printf("Transaction Amount\t\t\t:%f\n", transData->terminalData.transAmount);

	printf("Transaction Sequence Number\t\t:%d\n", transData->transactionSequenceNumber);
	printf("Transaction State\t\t\t:%d\n", transData->transState);

	printf("########################\n");
}
/**********************Test functions************************/
void isValidAccountTest(void)
{
	uint32_t counter;
	printf("please enter primaryAccountNumber\t\t\t\t:");
	(void)scanf("%s", &(primaryAccountNumberTest));
	for (counter = 0; counter < 255; counter++)
	{
		//printf("counter=%d,primaryAccountNumberTest=%s,primaryAccountNumberTest=%s\n", counter, primaryAccountNumberTest, accountsDBTest[counter].primaryAccountNumberTest);
		//if PAN exists return SERVER_OK and return a reference to this account in the DB.
		if (strcmp((primaryAccountNumberTest), (accountsDBTest[counter].primaryAccountNumberTest)) == 0)
		{
			AccountRefInDBTest = counter;
			//printf("counter=%d\n",counter);
			//accountRefrence = &(accountsDB[counter]);
			//printf("accountRefrenceBalance=%f\n", accountRefrence->balance);
			 printf("\t\t\tSERVER_OK\n");
			 printf("---------------------------------------------------\n");
			 return;
			//return SERVER_OK;
		}

	}
	//If the PAN doesn't exist will return ACCOUNT_NOT_FOUND and the account reference will be NULL
//else
		//accountRefrence = NULL;
		AccountRefInDBTest = NULL;
		printf("\t\t\tACCOUNT_NOT_FOUND\n");
		printf("---------------------------------------------------\n");
		//return ACCOUNT_NOT_FOUND;
}

void isBlockedAccountTest(void)
{

	printf("please enter AccountRefInDB chose from (0to254)\t\t\t\t:");
	(void)scanf("%d", &(AccountRefInDBTest));
	if ((accountsDBTest[AccountRefInDBTest].stateTest) == RUNNING)
	{
		printf("\t\t\tSERVER_OK\n");
		printf("---------------------------------------------------\n");
		//return SERVER_OK;
	}
	//else if the account is blocked it will return BLOCKED_ACCOUNT.
	else
	{
		printf("\t\t\tBLOCKED_ACCOUNT\n");
		printf("---------------------------------------------------\n");
		//return BLOCKED_ACCOUNT;
	}
}

void isAmountAvailableTest(void)
{
	printf("please enter transaction amount\t\t\t\t\t:");
	(void)scanf("%f", &(transAmountTest));
	printf("please enter AccountRefInDB chose from (0to254)\t\t\t\t:");
	(void)scanf("%d", &(AccountRefInDBTest));
	if (transAmountTest > (accountsDBTest[AccountRefInDBTest].balanceTest))
	{
		printf("\t\t\tLOW_BALANCE\n");
		printf("---------------------------------------------------\n");
		//return LOW_BALANCE;
	}
	//else will return SERVER_OK.
	else
	{
		printf("\t\t\tSERVER_OK\n");
		printf("---------------------------------------------------\n");
		//return SERVER_OK;
	}
}


void saveTransactionTest(void)
{
	//ST_transactionTest_t *transDataTest;
	if (SequenceNumberTest >= 255)
	{
		printf("\t\t\tSAVING_FAILED\n");
		printf("---------------------------------------------------\n");
		//return SAVING_FAILED;
	}
	else
	{

		//give a sequence number to a transaction
		transDataTest.transactionSequenceNumberTest = SequenceNumberTest;
		// store all transaction data in the transactions database.
		printf("please enter the cardholder's name\t\t\t\t: ");
		(void)scanf("%[^\n]%*c", &transDataTest.cardHolderDataTest.cardHolderName);
		strcpy(transactionTest[SequenceNumberTest].cardHolderDataTest.cardHolderName, transDataTest.cardHolderDataTest.cardHolderName);

		printf("please enter card expiry date as MM/YY\t\t\t\t: ");
		(void)scanf("%s", &(transDataTest.cardHolderDataTest.cardExpirationDate));
		strcpy(transactionTest[SequenceNumberTest].cardHolderDataTest.cardExpirationDate, transDataTest.cardHolderDataTest.cardExpirationDate);
		
		printf("please enter transaction date at this format DD/MM/YYYY, e.g 25/06/2022    : ");
		(void)scanf("%s", &(transDataTest.terminalDataTest.transactionDate));
		strcpy(transactionTest[SequenceNumberTest].terminalDataTest.transactionDate, transDataTest.terminalDataTest.transactionDate);

				
		printf("please enter  card's Primary Account Number\t\t\t:");
		(void)scanf("%s", & transDataTest.cardHolderDataTest.primaryAccountNumber);
		strcpy(transactionTest[SequenceNumberTest].cardHolderDataTest.primaryAccountNumber, transDataTest.cardHolderDataTest.primaryAccountNumber);

		printf("please enter maximum allowed amount\t\t\t\t:");
		(void)scanf("%f", &(transDataTest.terminalDataTest.maxTransAmount));
		transactionTest[SequenceNumberTest].terminalDataTest.maxTransAmount = transDataTest.terminalDataTest.maxTransAmount;
		
				
		printf("please enter transaction amount\t\t\t\t\t:");
		(void)scanf("%f", &(transDataTest.terminalDataTest.transAmount));
		transactionTest[SequenceNumberTest].terminalDataTest.transAmount = transDataTest.terminalDataTest.transAmount;


		transactionTest[SequenceNumberTest].transactionSequenceNumberTest = transDataTest.transactionSequenceNumberTest;
		
		printf("please enter transaction state 0 for running ,1 for blocked\t\t\t\t\t:");
		(void)scanf("%d", &(transDataTest.transStateTest));
		transactionTest[SequenceNumberTest].transStateTest = transDataTest.transStateTest;

		//number is incremented once a transaction is processed into the server
		SequenceNumberTest++;

		//list all saved transactions using the listSavedTransactions function.
		//listSavedTransactions(&transactionTest[SequenceNumberTest]);
		listSavedTransactionsTest();
		//Assuming that the connection between the terminal and server is always connected, then it will return SERVER_OK.
		printf("\t\t\tSERVER_OK\n");
		printf("---------------------------------------------------\n");
		//return SERVER_OK;
	}
}

void listSavedTransactionsTest(void)
{
	
	printf("########################\n");
	printf("Transaction Sequence Number\t\t:%d\n", transactionTest[SequenceNumberTest - 1].transactionSequenceNumberTest);
	printf("Transaction Date\t\t\t:%s\n", transactionTest[SequenceNumberTest - 1].terminalDataTest.transactionDate);
	printf("Transaction Amount\t\t\t:%f\n", transactionTest[SequenceNumberTest - 1].terminalDataTest.transAmount);
	printf("Transaction State\t\t\t:%d\n", transactionTest[SequenceNumberTest - 1].transStateTest);
	printf("Terminal Max Amount\t\t\t:%f\n", transactionTest[SequenceNumberTest - 1].terminalDataTest.maxTransAmount);

	printf("Cardholder Name	\t\t\t:%s\n", transactionTest[SequenceNumberTest-1].cardHolderDataTest.cardHolderName);
	printf("PAN\t\t\t\t\t:%s\n", transactionTest[SequenceNumberTest - 1].cardHolderDataTest.primaryAccountNumber);
	printf("Card Expiration Date\t\t\t:%s\n", transactionTest[SequenceNumberTest - 1].cardHolderDataTest.cardExpirationDate);

			
	
	//printf(" Sequence Number\t\t:%d\n", SequenceNumberTest);
		printf("########################\n");
}
