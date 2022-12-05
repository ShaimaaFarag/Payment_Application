#pragma once
#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "../Card/card.h"

/*typedefs and macros*/
#define Wrong_Format 1
#define NotWrong     0
typedef unsigned char uint8_t;
typedef unsigned int  uint32_t;
/*variables for test functions*/
uint8_t transactionDateTest[11];
float transAmountTest;
float maxTransAmountTest;
/*structure for terminal data*/
typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;
/*enumeration for terminal data error*/
typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;
/*function prototypes */
uint8_t wrongFormat(ST_terminalData_t* termData);
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);//, float maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData); // Optional
/*test functions*/
void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
#endif // !TERMINAL_H_
