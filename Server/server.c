#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

ST_accountsDB_t accountsDB[255] = {
	{2000.0, RUNNING, "8989374615436851"},
	{100000.0, BLOCKED, "5807007076043875"},
	{5000.0, RUNNING, "8989734615436851"},
	{3000.0, RUNNING, "8989374615463851"},
	{2000.0, BLOCKED, "8989376415436851"},
};

ST_transaction_t transactionDB[255] = {{0, 0, 0, 0}};

uint32_t lastSequenceNumber = 0;

EN_transState_t reieveTranscationData(ST_transaction_t *transData)
{
	EN_serverError_t isValid;
	ST_accountsDB_t *accRefrence;
	EN_accountState_t isAmAvailable;
	isValid = isValidAccount(&(transData->cardHolderData), &accRefrence);
	if (isValid == ACCOUNT_NOT_FOUND)
	{
		// transData->transState=FRAUD_CARD;///shall it be modified or just return it????????
		return FRAUD_CARD;
	}
	else
	{
		isAmAvailable = isAmountAvailable(&(transData->terminalData), accRefrence);
		if (accRefrence->state == BLOCKED)
		{
			// transData->transState = DECLINED_STOLEN_CARD;//shall it be modified or just return it????????
			return DECLINED_STOLEN_CARD;
		}
		else if (isAmAvailable == LOW_BALANCE)
		{
			// transData->transState = DEClINED_INSUFFECIENT_FUND;//shall it be modified or just return it????????
			return DEClINED_INSUFFECIENT_FUND;
		}
		else if (lastSequenceNumber >= 255)
		{
			return INTERNAL_SERVER_ERROR;
		}
		else
		{
			accRefrence->balance -= transData->terminalData.transAmount;
			// transData->transState = APPROVED;//shall it be modified or just return it????????
			return APPROVED;
		}
	}
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t **accountRefrence)
{
	//////////// changed account refrence to be a pointer to a struct instead of a struct
	for (int i = 0; i < 255; i++)
	{
		if (accountsDB[i].primaryAccountNumber == 0)
			return ACCOUNT_NOT_FOUND;
		else if (!strcmp(accountsDB[i].primaryAccountNumber, cardData->primaryAccountNumber))
		{
			*accountRefrence = &accountsDB[i];
			return SERVER_OK;
		}
	}
	return ACCOUNT_NOT_FOUND;
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
	if (accountRefrence->state == BLOCKED)
		return BLOCKED_ACCOUNT;
	else
		return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
	if (termData->transAmount <= accountRefrence->balance)
		return SERVER_OK;
	else
		return LOW_BALANCE;
}
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
	ST_transaction_t trans;
	transData->transactionSequenceNumber = ++lastSequenceNumber;
	EN_transState_t resultState = reieveTranscationData(transData);
	transData->transState = resultState;
	if (resultState == INTERNAL_SERVER_ERROR)
	{
		lastSequenceNumber--;
		return SAVING_FAILED;
	}
	transactionDB[transData->transactionSequenceNumber - 1] = *transData;
	if (getTransacton(transData->transactionSequenceNumber - 1, &trans) == TRANSACTION_NOT_FOUND)
	{
		return SAVING_FAILED;
	}
	else
		return SERVER_OK;
}
EN_serverError_t getTransacton(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
	for (int i = 0; i < 255; i++)
	{
		if (transactionDB[i].transactionSequenceNumber == 0)
		{
			return TRANSACTION_NOT_FOUND;
		}
		if (transactionDB[i].transactionSequenceNumber == transactionSequenceNumber)
		{
			*transData = transactionDB[i];
			return SERVER_OK;
		}
	}
	return TRANSACTION_NOT_FOUND;
}