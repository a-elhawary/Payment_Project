#pragma once
#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "terminal.h"
#include "lstd.h"
#include "../Card/card.h"

#define transactionDate_Size 11

typedef enum
{
	INVALID_PAN,
	AIRLINE_CREDIT_DCARD,
	AMERICAN_EXPRESS,
	VISA,
	MASTER_CARD,
	DISCOVER_CARD,
	PETROLUM_COMPANY_CARDS,
	TELECOMUNICATION_HEALTHCARE
} PANcategory;

typedef struct
{
	float transAmount;
	float maxTransAmount;
	u8_t transactionDate[transactionDate_Size];
	PANcategory category;
} ST_terminalData_t;

typedef enum
{
	TERMINAL_OK,
	WRONG_DATE,
	EXPIRED_CARD,
	INVALID_CARD,
	INVALID_AMOUNT,
	EXCEED_MAX_AMOUNT,
	BELOW_MIN_AMOUNT,
	INVALID_MAX_AMOUNT
} EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t terminalData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *terminalData);
EN_terminalError_t checkPANvalidity(ST_terminalData_t *terminalData, ST_cardData_t cardData);
PANcategory checkPANcategory(ST_cardData_t cardData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *terminalData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *terminalData);
void PrintArray(u8_t *Array, int Size);

#endif /* TERMINAL_H_ */