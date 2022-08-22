#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    printf("please enter the card holder name:");
    char name[30];
    fgets(name, 30, stdin);
    name[strcspn(name, "\n")] = 0;
    if (strlen(name) < 20 || strlen(name) > 24) // or null
    {
        return WRONG_NAME;
    }
    else
    {
        strncpy(cardData->cardHolderName, name, 25);
        return CARD_OK;
    }
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    printf("Please enter your PAN: ");
    char pan[30];
    fgets(pan, 30, stdin);
    int i;
    for (i = 0; i < 30; i++)
    {
        if (pan[i] == '\0')
        {
            break;
        }
        if (pan[i] == '\n')
        {
            pan[i] = 0;
            break;
        }
        if (pan[i] < '0' || pan[i] > '9')
        {
            return WRONG_PAN;
        }
    }
    if (i < 16 || i > 19)
    {
        return WRONG_PAN;
    }
    strncpy(cardData->primaryAccountNumber, pan, 20);
    return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{

    char cardDate_UserEntered[7];
    printf("Enter the card Expiration date\n\n");
    printf("Enter the month number then press enter \n");
    scanf("%c", &cardDate_UserEntered[0]);
    scanf("%c", &cardDate_UserEntered[1]);

    cardDate_UserEntered[2] = '/';

    printf("Enter the year number then press enter\n");
    scanf("%c", &cardDate_UserEntered[3]);
    scanf("%c", &cardDate_UserEntered[4]);
    scanf("%c", &cardDate_UserEntered[5]);
    scanf("%c", &cardDate_UserEntered[6]);

    if (cardDate_UserEntered[6] >= '0' && cardDate_UserEntered[6] <= '9')
    {
        printf("\nmore than five characters is entered\n");
        return WRONG_EXP_DATE;
    }

    if ('\n' == cardDate_UserEntered[0] || '\n' == cardDate_UserEntered[1] || '\n' == cardDate_UserEntered[4] || '\n' == cardDate_UserEntered[5])
    {
        printf("\nWrong date format\n");
        return WRONG_EXP_DATE;
    }

    if (!(cardDate_UserEntered[0] >= '0' && cardDate_UserEntered[0] <= '9') || !(cardDate_UserEntered[1] >= '0' && cardDate_UserEntered[1] <= '9') || !(cardDate_UserEntered[4] >= '0' && cardDate_UserEntered[4] <= '9') || !(cardDate_UserEntered[5] >= '0' && cardDate_UserEntered[5] <= '9'))
    {
        printf("\nCharacters are not allowed\n");
        return WRONG_EXP_DATE;
    }

    if ('1' == cardDate_UserEntered[0])
    {

        if (cardDate_UserEntered[1] > '2')
        {
            printf("\nWrong month number\n");
            return WRONG_EXP_DATE;
        }
    }

    if (cardDate_UserEntered[0] > '1')
    {
        printf("\nWrong month number\n");
        return WRONG_EXP_DATE;
    }

    if ('0' == cardDate_UserEntered[0])
    {

        if ('0' == cardDate_UserEntered[1])
        {
            printf("\nWrong month number\nmonth number is zero \n");
            return WRONG_EXP_DATE;
        }
    }

    cardData->cardExpirationDate[0] = cardDate_UserEntered[0];
    cardData->cardExpirationDate[1] = cardDate_UserEntered[1];
    cardData->cardExpirationDate[2] = '/';
    cardData->cardExpirationDate[3] = cardDate_UserEntered[4];
    cardData->cardExpirationDate[4] = cardDate_UserEntered[5];
    cardData->cardExpirationDate[5] = 0;

    return CARD_OK;
}
