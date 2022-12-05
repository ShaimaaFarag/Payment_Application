#pragma once
#ifndef CARD_H_
#define CARD_H_
/*typedefs and macros*/
typedef unsigned char uint8_t;
#define NULL 0
#define MAX_CARDHOLDER_NAME 24
#define MIN_CARDHOLDER_NAME 20

/*varibles for test functions*/
uint8_t cardHolderNameTest[25];
uint8_t cardExpirationDateTest[6];
uint8_t primaryAccountNumberTest[20];

/*structure for card data*/
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;
/*enumeration for card data error*/
typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

/*function prototypes */
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);
#endif // !CARD_H_
