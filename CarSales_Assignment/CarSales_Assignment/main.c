//To allow Visual Studio to work with scanf()
#define _CRT_SECURE_NO_WARNINGS 

//Required to use printf() an scanf()
#include <stdio.h>
#include <string.h>

void main() {

	//CONSTANTS
#define DISCOUNT_1 .20f // 20%
#define DISCOUNT_2 .10f // 10%
#define OPTION_BUY_CAR 'a'
#define OPTION_SALES_STATS 'b'
#define OPTION_EXIT 'x'
#define TRUE 1
#define FALSE 0
#define MAX_SALES 20

	//VARIABLES
	//No negative values needed.
	unsigned short carsAvailable = 20, carsNeeded = 0, giveDiscount = FALSE, carsSold = 0, correctInput = FALSE, carType;
	float totalPrice = 0;
	//To hold the user's choice.
	char userChoice, discountCoupon;


	//To track how many sales took place 
	//Used as index position of each sale within the arrays ticketAmountPerSale, typeOfTicketPerSale, customerNames and discountGivenPerSale.
	unsigned short numberOfSales = 0;
	//ARRAYS
	//Will hold the number of cars sold in each sale.
	unsigned short carAmountPerSale[MAX_SALES];
	//Will hold the type of car sold in each sale.
	unsigned short typeOfCarPerSale[MAX_SALES];
	//Discount information for each sale.
	unsigned short discountGivenPerSale[MAX_SALES];

	char customerName[MAX_SALES][201];


	//Information about each car type along with the price
	float carPrices[] = { 20000.5f, 25000.5f, 30000.5f };

	char carTypes[][10] = { "SPORT", "SUV", "OFF ROAD" };



	do {

		//KEEP SCREEN CLEAR
		system("cls");

		//GREETING
		printf("Welcome to the car sales office!\n\n");

		//MENU
		printf("MENU\n");
		printf("a. Buy Car\n");
		printf("b. View Sales Stats\n");
		printf("x. Exit\n\n");

		correctInput = FALSE;

		do {
			//USER CHOICE
			printf("Please choose an option: ");
			scanf("\n%c", &userChoice);
			if (userChoice == OPTION_BUY_CAR || userChoice == OPTION_SALES_STATS || userChoice == OPTION_EXIT) {
				correctInput = TRUE;
			}
			else {
				printf("\nSorry, incorrect input. Please try again.\n");
			}

		} while (correctInput != TRUE);

		system("cls");

		//DECISION BASED ON USER CHOICE
		switch (userChoice) {

			//If user chooses 'a'
		case OPTION_BUY_CAR:

			//CHECK IF ATLEAST 1 CAR IS AVAILABLE
			if (carsAvailable > 0) {
				printf("There are %hd cars available.\n\n", carsAvailable);
			}
			else {
				printf("Sorry, there are no more cars available.");
				//Stops the case early
				break;
			}

			printf("What is your name? Name: ");
			scanf("\n%[^\n]s", &customerName[numberOfSales]);

			correctInput = FALSE;

			do {

				printf("\nHow many cars do you need? Amount: ");
				int captured = scanf("%hd", &carsNeeded);

				if (captured != 1) {
					printf("Sorry, incorrect input. Please try again\n");

				}
				else {
					correctInput = TRUE;

				}
				while (getchar() != '\n');
			} while (correctInput == FALSE);

			//CHECK IF WE HAVE ENOUGH CARS AVAIALBLE
			if (carsAvailable < carsNeeded) {
				printf("Sorry, there are fewer cars remaining than you require.");

				break;
			}

			//Record the number of cars needed in carAmountPerSale
			carAmountPerSale[numberOfSales] = carsNeeded;

			//Price will be based on the type of car the user wants
			int numberOfCars = sizeof(carPrices) / sizeof(float);

			printf("\nCar Types:\n");
			for (int i = 0; i < numberOfCars; i++) {
				printf("%d - %s\n", i, carTypes[i]);
			}

			correctInput = FALSE;

			do {
				printf("\nWhat type of car do you need? Choose from the above: ");
				int captured = scanf("\n%hd", &carType);

				if (captured != 1) {
					printf("Sorry, incorrect input. Please try again\n");

				}
				else {
					correctInput = TRUE;

				}
				while (getchar() != '\n');
			} while (correctInput == FALSE);

			//Record type of car in typeOfCarPerSale
			typeOfCarPerSale[numberOfSales] = carType;

			//Calculate total price for the sale based on the car type needed
			totalPrice = carsNeeded * carPrices[carType];

			//Update number of cars available
			carsAvailable -= carsNeeded;

			giveDiscount = FALSE;

			//DISCOUNT_1 based on number of cars purchased
			if (carsNeeded >= 5) {
				giveDiscount = TRUE;

				totalPrice *= (1 - DISCOUNT_1);

			}
			else {
				// Data validation
				correctInput = FALSE;

				do {
					printf("\nDo you have a discount coupon? Answer 'y' or 'n': ");
					scanf("\n%c", &discountCoupon);

					if (discountCoupon == 'y' || discountCoupon == 'n') {
						correctInput = TRUE;
					}
					else {
						printf("Sorry, incorrect input. Please try again.\n");
					}
				} while (correctInput != TRUE);

				//DISCOUNT_2 given based on discount coupon response
				if (discountCoupon == 'y') {
					//Value of giveDiscount changes to show that a discount should be given
					giveDiscount = TRUE;

					totalPrice *= (1 - DISCOUNT_2);

				}
			}

			//Record the outcome in discountGivenPerSale array
			discountGivenPerSale[numberOfSales] = giveDiscount;

			//Inform user about the discount result
			switch (giveDiscount) {

			case TRUE:
				printf("\n\nCongratulation on your purchase. You get a discount!");

				break;

			case FALSE:
				printf("\nNo discount given.");

				break;

			}

			//Present the outcome
			printf("\n\nThank you.\n");
			printf("You have bought %hd cars.\n", carsNeeded);
			printf("Total cost is %.2f GBP.\n", totalPrice);
			printf("\nThere are %hd cars remaining.", carsAvailable);

			//Add 1 to the numberOfSales counter
			numberOfSales++;

			break;

			//If user chooses 'b'
		case OPTION_SALES_STATS:

			printf("ALL SALES DATA\n\n");

			//Contains the sum total sales price
			float totalSalesValue = 0;
			//Contains the total number of cars sold for all sales
			unsigned int carsSold = 0;

			for (int i = 0; i < numberOfSales; i++) {


				int typeOfCar = typeOfCarPerSale[i];
				//Calculate the current sale's price
				float price = carAmountPerSale[i] * carPrices[typeOfCar];

				char discountGivenText[4];

				//If a discount was given...
				if (discountGivenPerSale[i] == TRUE) {
					//Set text to YES
					strcpy(discountGivenText, "Yes");
					//Modify price
					price *= (1 - DISCOUNT_1);
					price *= (1 - DISCOUNT_2);
				}
				else {
					//Set text to NO
					strcpy(discountGivenText, "No");
				}

				printf("Sale Index: %d | Sale Amount: %.2f | Type of Car: %s | \
                        Car Price: %.2f | Number of Cars: %hd | \
                        Discount Given: %s | Customer Name: %s\n",
					i, price, carTypes[typeOfCar], carPrices[typeOfCar], carAmountPerSale[i],
					discountGivenText, customerName[i]);

				//Add up total sales value
				totalSalesValue += price;
				//Add up total number of cars sold
				carsSold += carAmountPerSale[i];

			}

			printf("\n\n%hd cars have been sold with a total value of %f GBP. There are %hd cars unsold.\n", carsSold, totalSalesValue, carsAvailable);

			break;
			//If user chooses 'x'
		case OPTION_EXIT:

			printf("\n\nThank you for using the Car Sales program. Goodbye!");

			break;
		}

		if (userChoice == OPTION_EXIT) {
			printf("\n\nPress the Enter key to Exit...");
		}
		else {
			printf("\n\nPress Enter to return to the Menu...");
		}

		//Wait for Enter key press
		//2 to handl newline character from previous Enter key press
		getchar();

		getchar();

	} while (userChoice != OPTION_EXIT);

	system("cls");

	printf("\n\nHave a good day!");

}