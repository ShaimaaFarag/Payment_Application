#pragma once
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "../Card/card.h"
#include "../Server/server.h"
#include "../Terminal/terminal.h"

/*typedef enum EN_testCase_t
{
    Transaction_approved_user_story, 
    Exceed_the_maximum_amount_user_story, 
    Insufficient_fund_user_story, 
    Expired_card_user_story,
    Stolen_card_user_story
}EN_testCase_t;*/

void appStart(void);

#endif // !APPLICATION_H_
