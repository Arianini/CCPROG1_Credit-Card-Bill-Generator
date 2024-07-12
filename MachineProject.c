/***************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts learned. 
I have constructed the functions and their respective algorithms and corresponding code by myself. The program was run, tested, and debugged by my own efforts. 
I further certify that I have not copied in part or whole or otherwise plagiarized the work of other students and/or persons.
<Ranada, Arianne M.> DLSU ID# <12208590>
***************************************************************************/

/*
Description: This program generates allows a user to input purchases, make payments, use points, view
			 balance, view points, and generate the credit card bill.
Programmed by: <Ranada, Arianne> <S11>
Last modified: <July 31, 2023>
Version: <4>
*/

#include <stdio.h>

//DEFINITION OF CONSTANTS
#define MINDUE_FEE 850 //Amount of default minimum amount due
#define MULTIPLIER 0.0357 //Number to be multiplied to get minimum due if amount due is >850

/* 
	This fucntion displays a line for design
*/
void 
displayDesign()
{
	int i;
	
	for (i=1; i<26; i++)
	{
		printf("*-");
	}
	printf("\n\n");
}

/* 
	This displays the opening message upon running the program
*/
void 
displayOpening()
{
	displayDesign();
	printf("\t WELCOME TO ANNA'S CREDIT CARD\n");
	printf("\t\tBILL GENERATOR!\n\n");
	displayDesign();
}

/* 
	This function display the options that the user get to choose from.
	A notice will be printed along the options if the  user did not pay any 
	amount for 3 consecutive cycles and that the credit card is about to be 
	cancelled on the next billing cycle
*/
void 
displayOptions(int nCancel)
{
	displayDesign();
	printf("Select your transaction:\n");
	printf("\n(1) Add purchase");
	printf("\n(2) View previous statement");
	printf("\n(3) Make payment");
	printf("\n(4) View rewards points");
	printf("\n(5) Use rewards points");
	printf("\n(6) End billing cycle");
	printf("\n(7) Exit\n\n");
	
	if (nCancel == 3)
	{
		printf("NOTICE: Your credit card is about to be cancelled."); 
		printf("\n\tPlease pay your dues.\n");
	}
	displayDesign();
}

/* 
	This function gets the amount of ourchase from the user
Precondition: Amount of purchase should be positive (greater than 0)
@param fCredit refers to the credit card limit of the user
@param fPurchase gets the amount of the purchase of the user
@param fTotalPurchase stores the amounts of purchases made during the billing cycle
@param nSumChecker checks if the the total purchase plus the new purchase will be greater 
		than or equal to twice of teh credit limit
*/
void 
addPurchase(float *fCredit, float *fPurchase, float *fTotalPurchase, int *nNowPoints, int *nNetPoints)
{
	int nSumChecker;
	
	do{	
		printf("Enter amount of purchase: ");
		scanf("%f", fPurchase);
		
		nSumChecker = *fPurchase + *fTotalPurchase; //total purchases during the billing cycle must not reach or exceed twice of the redit limit 
		
		if (nSumChecker >= *fCredit * 2)
		{
			printf("\nTransaction declined. Not enough credit limit\n"); 
			printf("Amount will reach/exceed twice of credit limit\n");
		}
		else if (*fPurchase >= 0 && *fPurchase < *fCredit * 2)
		{
			printf("\nPurchase successful!\n");
			*fTotalPurchase += *fPurchase;
			*nNowPoints += *fPurchase / 30;	//Updates the total points accumulated in the current billng cycle
			*nNetPoints += *fPurchase / 30;	//Updates the total points accumulated in the current billng cycle
		}
		else if(*fPurchase < 0)
		{
			printf("\nInvalid! Please enter a valid amount\n");
		}
	}while (*fPurchase < 0);
			 
	printf("Your Total Purchases is: Php %.2f\n\n", *fTotalPurchase);
	
}

/* This function displays the the previous balance and previous minimum amount due
@param fPrevious is the Previous balance amount
@param fMinDue is the previous minimum amunt due
*/
void 
viewPreviousStatement(float fPrevious, float fMinDue)
{
	printf("\nYour previous balance is \tPhp %12.2f\n", fPrevious);
	printf("Your previous minimum amount is Php %12.2f\n\n", fMinDue); 	
}

/* This function gets the amount of payment from the use
Precondition: Amount is a positive number
@param fPay is the amount entered by the user
@param fTotalPay saves the total amount of payments done by the user
*/
void 
getPayment(float *fPay, float *fTotalPay)
{
	do{
		printf("Enter the amount of your payment: ");
		scanf("%f", fPay);
		
		if (*fPay < 0)
			printf("\nPayment failed. Please enter a valid amount\n\n");
		else
		{
			printf("\nPayment successful!");
			*fTotalPay += *fPay;
		}
			
	}while (*fPay < 0); //repeats until user enter a positive amount
	
	printf("\nYour total payments is: Php %.2f\n\n", *fTotalPay);
}

/* This function computes the total credit points which is total of previous and current points minus used points
@param nPreviousPoints is the accumulated points minus the used points from the previous billing cycle
@param nNowPoints is the accumulated points in the current billing cycle
@param nUsedPoints is accumulated used points in the current biling cycle
@returns net total credit points
*/
int
getNetPoints(int nPreviousPoints, int nNowPoints, int nUsedPoints)
{
	return nPreviousPoints + nNowPoints - nUsedPoints;
}

/* This function display the previous, current, used, ane net total points of the user
@param nPreviousPoints is the netpoints accumulated from the previous billing cycle
@param nNowPoints is the points earned in the current cycle
@param nUsedPoints is the used points in the current billing cycle
@param nNetPoints is the netpoints in the previous and current billing cycle
*/
void 
viewRewardsPoints(int nPreviousPoints, int nNowPoints, int nUsedPoints, int nNetPoints)
{				
	printf("\nPrevious Cards Points Balance   =  %13d\n", nPreviousPoints);
	printf("   (+) Current Points Earned    =  %13d\n", nNowPoints);
	printf("   (-) Points Used\t\t=%15d\n", nUsedPoints);
	printf("Total Credit Points\t\t= %14d\n\n", nNetPoints);
}

/* This function gets which option chooses  by the user
Precondition: Accepted inputs are only 1, 2 and 3. Otherwise, user shall enter an input again
			  Total points must be >= 1000
@param nClaim gets which transaction was chosen by the user
@param nUsedPoints is the total used points in the current billing cycle
@param nNetPoints is the previous points plus current points minus used points
@param fTotalPay is the total amount paid by the user in the current billing cycle
*/
void 
useRewardPoints(int *nUsedPoints, int *nNetPoints, float *fTotalPay)
{
	int nClaim;
	
	do{	
		printf("\n[1] Php 100 eGift voucher for 1000 pts");
		printf("\n[2] Php 100 credits for 1000 pts");	
		printf("\n[3] Cancel transaction");
		
		printf("\n\nEnter your reward choice: ");
		scanf("%d", &nClaim);
		
		if (nClaim == 1 || nClaim == 2)
		{
			*nUsedPoints += 1000; //update total amount of used points during current billing cycle
			*nNetPoints -= 1000; //updates netpoints by subtracting amount of points used
						
			if (nClaim == 1)
			{
				printf("Your Php eGift voucher has been claimed.\n");
				printf("Voucher code sent to registered mobile number.\n\n");
			}
			else if (nClaim == 2)
			{
				printf("Your Php 100 credits has been claimed\n\n");
				*fTotalPay += 100; //an amount of 100 is credited to payments if user chooses this option
			}	
		}
		else if (nClaim == 3)
			printf("Transaction cancelled. Returning to main menu\n\n");
		else
			printf("Error. Please enter a valid choice\n");								
	}while (nClaim != 1 && nClaim != 2 && nClaim != 3);	
}

float getUnpaidBalance(float fPrevious, float fTotalPay)
{
	return fPrevious - fTotalPay;
}

/* This functions computes the outstanding balance of the user. It is the total of the previous balance
	and the purchases minus the payments both made during the current billing cycle
@param fPrevious os the total amount due in the previous billing cycle
@param fTotalPurchase is the total amount of purchases made by the user in the current billing cycle
@param fTotalPay is the total amount of payments made by the user in the current billing cycle
@return the outstanding balance for the current billing cycle
*/
float 
getOutstanding(float fPrevious, float fTotalPurchase, float fTotalPay)
{
	return fPrevious + fTotalPurchase - fTotalPay; 
}

/* This functions computes the finances charges of the user which is to be added to the total amount due
Precondition: This function return a value if either the outstanding balance is greater than the credit limit
			  or the total amount of payment paid is less that the total amount due of the previous billing cycle
@param fCredit refers to the credit limit of the user
@param fTotalPay is the total payments made by the user in the current billing cycle
@param fOutstanding is the total balance and purchases minus payments both during current billing cycle
@param fPrevious int the total amount due of the previous billing cycle
@return Total amount of finance charges
*/
float 
getFinanceCharges(float fCredit, float fOutstanding, float fTotalPay, float fPrevious, float fUnpaid)
{
	float fFinance = 0;
	
	if (fOutstanding > fCredit)
	{
		fFinance += 500;
	}
		
	if (fTotalPay < fPrevious )	
	{
		fFinance += fUnpaid * 0.03;
	}
	return fFinance;		
}

/* This function computes the late payment charges if any
@param fMinDue refers to the minimum amount due in the previous billing cycle
@param fPrevious refers to the previous total amount due in the previous billing cycle 
@param fTotalPay is the total amount paid by the user in the current billing cycleee
@param fLate is the amount of late payment charges
@return the amount of late payment charges
*/
float 
getLatePaymentCharges(float fMinDue, float fPrevious, float fTotalPay)
{
	float fLate;
	//to determine whichever is lower 
	if(fTotalPay < fMinDue)
	{
		if (MINDUE_FEE < fMinDue)
			fLate = MINDUE_FEE;
		else if (fMinDue < MINDUE_FEE)
			fLate = fMinDue - fTotalPay;
	}
	else
		fLate = 0;
	
	return fLate;
}

/* This functions computes for the payable minimum amount due
@param fTotalDue fPrevious is the total amount due in the previous billing cycle
@return the minimum amount due of the current billing cycle to be paid in the next billing cycle
*/
float 
getMinimumDue(float fTotalDue)
{
	float fMinDue;
	
	if (fTotalDue <= MINDUE_FEE)
		fMinDue = fTotalDue;
	else if (fTotalDue > MINDUE_FEE)
	{
		fMinDue = MULTIPLIER * fTotalDue;
		
		if (fMinDue < MINDUE_FEE)
		{
			fMinDue = MINDUE_FEE;
		}
	}	
	return fMinDue;
}

/*
	This function display the credit card bill
*/
void 
endBillingCycle(int nCycle, float fOutstanding, float fPrevious, float fTotalPay, float fTotalPurchase, float fFinance, float fLate, 
				float fTotalDue, float fMinDue, int nPreviousPoints, int nNowPoints, int nUsedPoints, int nNetPoints)
{
	int i,j;
	
	for (i=1; i<=4;i++)
	{
		if (i == 1 || i == 4)
		{
			printf("\n");
			for (j=1; j<=49; j++)
			{
				printf("=");
			}
		}
		
		else if (i==2)
		{
			printf("\n\t       PROG2CUTIE BANK INC.\n");
			printf("\t\t   Invoice # %d", nCycle);
		}
	}
	printf("\n\nOutstanding Balance: \t\tPhp %11.2f", fOutstanding);
	printf("\nPrevious Balance: \t\tPhp %11.2f", fPrevious);
	printf("\n   (-) Payments / Credits: \tPhp %11.2f", fTotalPay);
	printf("\n   (+) Purchases:\t\tPhp %11.2f", fTotalPurchase);
	printf("\n   (+) Finance Charges: \tPhp %11.2f", fFinance);
	printf("\n   (+) Late Payment Charges: \tPhp %11.2f", fLate);
	printf("\nTotal Amount Due: \t\tPhp %11.2f", fTotalDue);
	printf("\nMinimum Amount Due: \t\tPhp %11.2f", fMinDue);
	printf("\nETC Credit Card Bank -- Rewards Points");
	printf("\n   Previous Cards Points Balance: %13d", nPreviousPoints);
	printf("\n   (+) Current Points Earned:%18d", nNowPoints);
	printf("\n   (-) Points Used: %27d", nUsedPoints);
	printf("\n   Total Credit Points: %23d\n\n", nNetPoints);
}

/* This functions determines if the card will be cancelled on the next billing cycle and thus no transaction can be made
Precondition: Program to terminate if theres a min. amount due and the user does not pay any amount for 4 billing cycle
@param fMinDue is the min. amount due
@param nCancel increments by 1 if there was no payment made in a billing cycle
*/
void
isCancel(int *nCancel, float fTotalPay, float fMinDue)
{
	if (fMinDue > 0) //will start counting 
	{
		if (fTotalPay == 0)
			*nCancel += 1;
		
		else if(fTotalPay > 0)
			*nCancel = 0; //Resets value of nCancel if user pays an amount during the billing cycle
	}
}

/* This function computes the penalty fee charged to the user if no payment was made in 4 consecutive billing cycles while ahving a min. amount due
@param fTotalDue is the total amount due computed of the current billing cycle
@return the amount of penalty fee
*/
float getPenalty(float fTotalDue)
{
	return fTotalDue * 0.25;
}
/* 
	This function gets the credit limit of the user
@param fCredit stores the credit limit of the user
*/
void
getCreditLimit (float *fCredit)
{
	do{
		printf("Enter your credit card limit: ");
		scanf("%f", fCredit);
		
		if (*fCredit <= 0)
			printf("Error! Please enter a valid amount\n");
	
		printf("\n");
	}while (*fCredit <= 0);
}

/* 
	This function starts by asking the credit limit of user and then the user can choose what will be
	the next transaction. Credit limit must be positive for the program to proceed with the other transactions
*/
int 
main ()
{
	float fCredit;
	float fPurchase = 0;
	float fTotalPurchase = 0;
	float fPrevious = 0;
	float fMinDue = 0;
	float fLate = 0;
	float fTotalDue = 0;
	float fFinance = 0;
	float fPay = 0;
	float fTotalPay = 0;
	float fPenalty = 0;
	float fOutstanding = 0;
	float fUnpaid = 0;
	
	int nNowPoints = 0;
	int nPreviousPoints = 0;
	int nNetPoints = 0;
	int nUsedPoints = 0;
	int nChoice;
	int nCycle = 1;
	int nCancel = 0;
	
	displayOpening();
	getCreditLimit (&fCredit);
	do{
		displayOptions(nCancel);
		
		printf("Enter your choice: ");
		scanf("%d", &nChoice);
			switch(nChoice)
		{
			case 1:
				addPurchase(&fCredit, &fPurchase, &fTotalPurchase, &nNowPoints, &nNetPoints);
				break;
			case 2:
				viewPreviousStatement(fPrevious, fMinDue);	//view previous balance and min. amount due
				break;
			case 3:
				getPayment(&fPay, &fTotalPay); //gets amount payment of user
				break;
			case 4:
				viewRewardsPoints(nPreviousPoints, nNowPoints, nUsedPoints, nNetPoints); //view status of accumulated points
				break;
			case 5:
				if (nNetPoints >= 1000)
					useRewardPoints(&nUsedPoints, &nNetPoints, &fTotalPay);
				else
					printf("\nTransaction failed. Not enough points\n\n");
				break;
			case 6:
				isCancel(&nCancel, fTotalPay, fMinDue); //runs before fMinDue gets updated and then checks if there was a min due and no payment was made
				
				fUnpaid = getUnpaidBalance(fPrevious, fTotalPay);
				fOutstanding = getOutstanding(fPrevious, fTotalPurchase, fTotalPay);	 //asigns variable for the outstanding balance
				fFinance = getFinanceCharges(fCredit, fOutstanding, fTotalPay, fPrevious, fUnpaid); 	//assigns variable with the total computed finance charges
				fLate = getLatePaymentCharges(fMinDue, fPrevious, fTotalPay); //assigns variable with the late payment charges
				fTotalDue = fOutstanding + fFinance + fLate; 	//total amount due for the current billing cycle
				fMinDue = getMinimumDue(fTotalDue);	 //the minimum amount due payable in the next billing cycle
				nNetPoints = getNetPoints(nPreviousPoints, nNowPoints, nUsedPoints);
				endBillingCycle(nCycle, fOutstanding, fPrevious, fTotalPay, fTotalPurchase, fFinance, fLate, fTotalDue, 
								fMinDue, nPreviousPoints, nNowPoints, nUsedPoints, nNetPoints);
				
				//Reset and update values
				fPrevious = fTotalDue;
				nPreviousPoints = nNetPoints;
				nNowPoints = 0;
				nUsedPoints = 0;
				fTotalPurchase = 0;
				fTotalPay = 0;
				
				if(nCycle % 12 == 0)
					fTotalPurchase = 2000;
					
				nCycle++;
				break;
			case 7:
				printf("End of Transaction.\n\n");
				displayDesign();
				break;
			default:
				printf("\nInvalid! Please enter a valid choice number.\n\n");
		}
	}while (nChoice != 7 && nCancel != 4); //terminates if user choose option 7 or if user does not pay any amount for 4 consecutive billing cycle
	
	if (nCancel == 4) //will run if user does not pay any amount n 4 consecutive billing cycle with min. amount due
	{
		fPenalty = getPenalty(fTotalDue); //assigns variable for amount of penalty fees
		printf("Your credit card has been cancelled.");
		printf("\nPlease pay the penalty fee amounting Php %.2f\n\n", fPenalty);
		displayDesign();
	}
		
	return 0;
}
