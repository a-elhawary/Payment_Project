/****************************************************************************/
/*                           INCLUDES                                       */
/****************************************************************************/
#include "terminal.h"
#include <stdio.h>
#include "lstd.h"
#include <string.h>
#include <stdlib.h>

/****************************************************************************/
/*                           INTERFACING FUNCTIONS                          */
/****************************************************************************/

/*Function NAME: getTransactionDate
 *
 *INPUT:         pointer points to ST_terminalData_t struct
 *Return Type:   EN_terminalError_t (enum)
 *
 *Description:   This function gets the transaction date from the user and checks
 *               the format of the date entered and checks on the month and day number is valid or not
 * */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{

	printf("Enter the current date\n");
	printf("Enter the date at that format DD/MM/YYYY \n");

	/****************************Getting date from user*****************************************/
	u8_t indexCounter = 0;

	for (; indexCounter < transactionDate_Size; indexCounter++)
	{

		scanf("%c", &termData->transactionDate[indexCounter]);

		if ('\n' == termData->transactionDate[indexCounter])
		{
			break;
		}
	}

	/*******************************Date entered***********************************/
	printf("\nDate Entered\n");
	PrintArray(&(termData->transactionDate[0]), transactionDate_Size);

	/**************************Checking null array**************************/
	if ('\n' == termData->transactionDate[0])
	{
		printf("no date is entered\n");
		return WRONG_DATE;
	}
	/**************************Checking null array**************************/

	/**************************Checking Date format**************************/

	if ((termData->transactionDate[0] < '0') || (termData->transactionDate[0] > '9'))
	{
		printf("Wrong Date Format\n");
		printf("First Character Must be a number \n");
		return WRONG_DATE;
	}

	if ((termData->transactionDate[1] < '/') || (termData->transactionDate[0] > '9'))
	{
		printf("Wrong Date Format\n");
		printf("Second Character Must be a number or (/) \n");
		return WRONG_DATE;
	}

	if ((termData->transactionDate[2] < '/') || (termData->transactionDate[2] > '9'))
	{
		printf("Wrong Date Format\n");
		printf("Third Character Must be a number or (/) \n");
		return WRONG_DATE;
	}

	if ((termData->transactionDate[3] < '/') || (termData->transactionDate[3] > '9'))
	{
		printf("Wrong Date Format\n");
		return WRONG_DATE;
	}

	if ((termData->transactionDate[4] < '/') || (termData->transactionDate[4] > '9'))
	{
		printf("Wrong Date Format\n");
		return WRONG_DATE;
	}

	if ((termData->transactionDate[5] < '/') || (termData->transactionDate[5] > '9'))
	{
		printf("Wrong Date Format\n");
		return WRONG_DATE;
	}

	if ((termData->transactionDate[6] < '0') || (termData->transactionDate[6] > '9'))
	{
		printf("Wrong Date Format\n");
		return WRONG_DATE;
	}

	if ((termData->transactionDate[7] < '0') || (termData->transactionDate[7] > '9'))
	{
		printf("Wrong Date Format\n");
		return WRONG_DATE;
	}

	if (((termData->transactionDate[1] == '/') && (termData->transactionDate[2] == '/')) || ((termData->transactionDate[2] == '/') && (termData->transactionDate[3] == '/')) || ((termData->transactionDate[3] == '/') && (termData->transactionDate[4] == '/')))
	{
		printf("Wrong Date Format\n");
		printf("No two consecutive (/) is allowed \n");
		return WRONG_DATE;
	}

	if (((termData->transactionDate[5] == '/') && (termData->transactionDate[4] == '/')) || ((termData->transactionDate[5] == '/') && (termData->transactionDate[6] == '/')))
	{
		printf("Wrong Date Format\n");
		printf("No two consecutive (/) is allowed \n");
		return WRONG_DATE;
	}
	/**************************Checking Date format**************************/

	/**************************Checking Day number**************************/
	if (termData->transactionDate[0] == '3')
	{
		if (termData->transactionDate[1] > '1')
		{
			printf("Wrong day number\n");
			return WRONG_DATE;
		}
	}

	if (termData->transactionDate[0] >= '4')
	{
		if (termData->transactionDate[1] >= '0')
		{
			printf("Wrong day number\n");
			return WRONG_DATE;
		}
	}
	/**************************Checking Day number**************************/

	/**************************Checking month number**************************/
	if (termData->transactionDate[1] == '/')
	{

		if (termData->transactionDate[2] == '1')
		{

			if (termData->transactionDate[3] > '2')
			{
				printf("Wrong month number\n");
				return WRONG_DATE;
			}
		}

		else if (termData->transactionDate[2] > '1')
		{

			if (termData->transactionDate[3] != '/')
			{
				printf("Wrong month number\n");
				return WRONG_DATE;
			}
		}

	} /**********End of IF condition**********/

	if (termData->transactionDate[2] == '/')
	{

		if (termData->transactionDate[3] == '1')
		{

			if (termData->transactionDate[4] > '2')
			{
				printf("Wrong month number\n");
				return WRONG_DATE;
			}
		}

		else if (termData->transactionDate[3] > '1')
		{

			if (termData->transactionDate[4] != '/')
			{
				printf("Wrong month number\n");
				return WRONG_DATE;
			}
		}
	}
	/**************************Checking month number**************************/

	return TERMINAL_OK;
}

/*Function NAME: isCardExpired
 *
 *INPUT:         pointer points to ST_terminalData_t struct
 *INPUT:         pointer points to ST_cardData_t struct
 *Return Type:   EN_terminalError_t (enum)
 *
 *Description:   This function compares the expiration date with the date entered by the user in getTransactionDate() function
 *               to see if the card expired or not
 * */
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t terminalData)
{

	if ('/' == terminalData.transactionDate[3])
	{

		/*******************Check on year *******************/
		if (terminalData.transactionDate[6] > cardData.cardExpirationDate[3])
		{
			return EXPIRED_CARD;
		}

		if (terminalData.transactionDate[7] > cardData.cardExpirationDate[4])
		{
			return EXPIRED_CARD;
		}

		/*******************Check on month *******************/
		if (cardData.cardExpirationDate[0] == '0')
		{
			if (terminalData.transactionDate[2] > cardData.cardExpirationDate[1])
			{
				return EXPIRED_CARD;
			}
		}
	}

	else if ('/' == terminalData.transactionDate[4])
	{

		/*******************Check on year *******************/
		if (terminalData.transactionDate[7] > cardData.cardExpirationDate[3])
		{
			return EXPIRED_CARD;
		}

		if (terminalData.transactionDate[8] > cardData.cardExpirationDate[4])
		{
			return EXPIRED_CARD;
		}

		/*******************Check on month *******************/
		if ('/' == terminalData.transactionDate[2])
		{
			if (cardData.cardExpirationDate[0] == '0')
			{
				if (terminalData.transactionDate[3] > cardData.cardExpirationDate[1])
				{
					return EXPIRED_CARD;
				}
			}
		}

		if ('/' == terminalData.transactionDate[1])
		{
			if (terminalData.transactionDate[2] > cardData.cardExpirationDate[0])
			{
				return EXPIRED_CARD;
			}

			if (cardData.cardExpirationDate[0] == '0' && terminalData.transactionDate[2] == '0')
			{
				if (terminalData.transactionDate[3] > cardData.cardExpirationDate[1])
				{
					return EXPIRED_CARD;
				}
			}
		}
	}

	else if ('/' == terminalData.transactionDate[5])
	{

		/*******************Check on year *******************/
		if (terminalData.transactionDate[8] > cardData.cardExpirationDate[3])
		{
			return EXPIRED_CARD;
		}

		if (terminalData.transactionDate[9] > cardData.cardExpirationDate[4])
		{
			return EXPIRED_CARD;
		}

		/*******************Check on month *******************/
		if (terminalData.transactionDate[3] != '0')
		{

			if (terminalData.transactionDate[3] > cardData.cardExpirationDate[0])
			{
				return EXPIRED_CARD;
			}
		}

		if ('0' == terminalData.transactionDate[3] && '0' == cardData.cardExpirationDate[0])
		{

			if (terminalData.transactionDate[4] > cardData.cardExpirationDate[1])
			{
				return EXPIRED_CARD;
			}
		}
	}

	return TERMINAL_OK;
}

/*Function NAME: getTransactionAmount
 *
 *INPUT:         pointer points to ST_terminalData_t struct
 *Return Type:   EN_terminalError_t (enum)
 *
 *Description:  This function gets the amount from the user that will be transacted
 *
 * */
EN_terminalError_t getTransactionAmount(ST_terminalData_t *terminalData)
{

	float TransAmount_UserEntered;
	printf("Enter the transaction amount\n");

	scanf("%f", &TransAmount_UserEntered);

	if (TransAmount_UserEntered == 0)
	{
		printf("No amount is entered\n");
		return INVALID_AMOUNT;
	}

	terminalData->transAmount = TransAmount_UserEntered;
	printf("Amount entered is %f \n", TransAmount_UserEntered);

	return TERMINAL_OK;
}

void PrintArray(u8_t *Array, int Size)
{
	int IndexCount = 0;
	for (; IndexCount < Size; IndexCount++)
	{

		printf("%c", Array[IndexCount]);

		if ('\n' == Array[IndexCount])
		{
			break;
		}
	}

	printf("\n\n");
}

int *stringToIntArr(char *pan, int *size)
{
	int n = strlen(pan);
	int *arr = malloc(n * sizeof(int));
	for (int i = 0; i < strlen(pan); i++)
	{
		arr[i] = pan[i] - 48;
	}
	*size = n;
	return arr;
}

PANcategory checkPANcategory(ST_cardData_t cardData)
{
	char i = cardData.primaryAccountNumber[0];
	if (i == '1' || i == '2')
	{
		return AIRLINE_CREDIT_DCARD;
	}
	if (i == '3')
	{
		return AMERICAN_EXPRESS;
	}
	else if (i == '4')
	{
		return VISA;
	}
	else if (i == '5')
	{
		return MASTER_CARD;
	}
	else if (i == '6')
	{

		return DISCOVER_CARD;
	}
	else if (i == '7')
	{
		return PETROLUM_COMPANY_CARDS;
	}
	else if (i == '8')
	{
		return TELECOMUNICATION_HEALTHCARE;
	}
	else
	{
		return INVALID_PAN;
	}
}

EN_terminalError_t checkPANvalidity(ST_terminalData_t *terminalData, ST_cardData_t cardData)
{
	int i;
	int panSize = 0;
	int *pan = stringToIntArr(cardData.primaryAccountNumber, &panSize);
	if (terminalData->category == 0)
	{
		return INVALID_CARD;
	}
	else if (terminalData->category == 1)
	{
		// expected from 13 to 16 n.o so we check the 17-> 20 if it contain any num then invalid
		if (panSize < 13 || panSize > 16)
		{
			return INVALID_CARD;
		}
	}
	else if (terminalData->category == 2)
	{
		// expected 15
		if (panSize != 15)
		{
			return INVALID_CARD;
		}
	}
	else if (terminalData->category == 3)
	{
		// excpected from 13 -> 16
		if (panSize < 13 || panSize > 16)
		{
			return INVALID_CARD;
		}
	}
	else if (terminalData->category == 4)
	{
		if (panSize != 16)
		{
			return INVALID_CARD;
		}
	}
	else if (terminalData->category == 5)
	{
		if (panSize != 19)
		{
			return INVALID_CARD;
		}
	}
	// assume discover card == 16
	else if (terminalData->category == 6)
	{
		if (panSize != 16)
		{
			return INVALID_CARD;
		}
	}
	// tele comunication cards could be 19 digit
	else if (terminalData->category == 7)
	{
		if (panSize < 12 || panSize > 19)
		{
			return INVALID_CARD;
		}
	}
	int sum = 0;
	for (int j = 0; j < panSize; j++)
	{
		if ((j % 2) == 0)
		{
			if ((pan[j]) * 2 > 9)
			{
				sum += ((pan[j]) * 2 - 10) + 1;
			}
			else
			{
				sum += (pan[j]) * 2;
			}
		}
		else
		{
			sum += pan[j];
		}
		printf("%d ", sum);
	}
	printf("\n%d\n", sum);
	if (sum % 10 != 0)
	{
		printf("invalid calc\n");
		return INVALID_CARD;
	}
	else
	{
		return TERMINAL_OK;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *terminalData)
{
	if (terminalData->category == 0)
	{
		return INVALID_CARD;
	}
	else if (terminalData->category == 1)
	{
		terminalData->maxTransAmount = 1000;
	}
	else if (terminalData->category == 1)
	{
		terminalData->maxTransAmount = 1000;
	}
	else if (terminalData->category == 2)
	{
		terminalData->maxTransAmount = 5000;
	}
	else if (terminalData->category == 3)
	{
		terminalData->maxTransAmount = 5000;
	}
	else if (terminalData->category == 4)
	{
		terminalData->maxTransAmount = 6000;
	}
	else if (terminalData->category == 5)
	{
		terminalData->maxTransAmount = 10000;
	}
	else if (terminalData->category == 6)
	{
		terminalData->maxTransAmount = 8000;
	}
	else if (terminalData->category == 7)
	{
		terminalData->maxTransAmount = 10000;
	}
	return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *terminalData)
{
	if (terminalData->transAmount > terminalData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else if (terminalData->transAmount <= 0)
	{
		return BELOW_MIN_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}
