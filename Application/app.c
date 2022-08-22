#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"

void appStart()
{
    // filling card data
    ST_cardData_t cardData;
    if (getCardHolderName(&cardData) != CARD_OK)
    {
        printf("Wrong Name");
        return;
    }
    if (getCardExpiryDate(&cardData) != CARD_OK)
    {
        printf("Incorrect Date");
        return;
    }
    if (getCardPAN(&cardData) != CARD_OK)
    {
        printf("Incorrect PAN");
        return;
    }
    printf("yaay\n");

    // terminal flow
    ST_terminalData_t terminalData;

    EN_terminalError_t terminalError1;
    EN_terminalError_t terminalError2;
    terminalError1 = getTransactionDate(&terminalData);

    if (terminalError1 == WRONG_DATE)
    {
        printf("Wrong date entered\n\n");
        return;
    }

    /********************Check if card expired or not********************/
    terminalError2 = isCardExpired(cardData, terminalData);

    if (terminalError2 == EXPIRED_CARD)
    {
        printf("card expired\n");
        return;
    }

    if (getTransactionAmount(&terminalData) != TERMINAL_OK)
    {
        printf("Invalid Amount");
        return;
    };

    terminalData.category = checkPANcategory(cardData);
    if (checkPANvalidity == INVALID_CARD)
    {
        printf("Invalid Card PAN Number");
        return;
    }

    if (setMaxAmount(&terminalData) != TERMINAL_OK)
    {
        printf("Invalid Card PAN Number");
    }

    switch (isBelowMaxAmount(&terminalData))
    {
    case EXCEED_MAX_AMOUNT:
        printf("exceed\n");
        break;
    case BELOW_MIN_AMOUNT:
        printf("below\n");
        break;
    case TERMINAL_OK:
        printf("ok\n");
        break;
    }

    ST_transaction_t transaction;
    transaction.cardHolderData = cardData;
    transaction.terminalData = terminalData;
    saveTransaction(&transaction);
}