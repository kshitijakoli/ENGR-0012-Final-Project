/*
 * Matthew Renda, Kshitija Koli, & Amrutha Selvaraja
 * ENGR 0012 Project
 * Prof. Sanchez
 * 4/12/2022-4/19/2022
 * Team 172
 * 
 * Purpose of this code is to write a program that focuses on water sustainability for farmers, and to write a program to determine if water is potable.
 */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/*
 * reqs:
 * 5 functs (3)
 * 3 loops  (2)
 * one branching (2) DONE
 */
 
char whichCrop(); //functions for first program
void farmStatistics(double [],char);
void evaluation(double, double);

//functions for second program
void getSamples(double []);
int waterSafe(double []);

int main(void)
{
	int selection;
	do //do-while to errorcheck answer & get an input
	{
	printf("Welcome to our water sustainability program-enter 1 if you'd like to calculate water usage on your farm, or 2 if you'd like to calculate water quality index.");
	scanf("%d",&selection);
	}
	while(selection != 1 && selection != 2);
	
	if(selection == 1) //if statement for each seperate function
	{
		char cropChoice;
		cropChoice = whichCrop();
		
		double farmStats[1]; //sq footage, water usage
		farmStatistics(farmStats,cropChoice); //function to get user-inputted farm stats
		
		double waterUsage = farmStats[1]/farmStats[0]; //water per acre used
		double shouldUse; //variable to hold statistics independant for each crop, such as water that should be used
		
		switch (cropChoice)
		{
			case 'w': //trick question, wheat only needs abt 12-15 inches of rain since it is cool season crop
			shouldUse = 22650 * 15; //one inch of rainfall per arce * 15 inches
			break;
			
			case 'c': //case corn
			shouldUse = 600000;
			break;
			
			case 'o':
			shouldUse = 22650 * 15; //same as wheat
			break;
			
			default:
			shouldUse = 12.8*1.5*22650; //12.8 weeks to grow potatoes * 1.5 inches of water per week * 22650 inches of water to acres
			break;
		}
		
		evaluation(shouldUse,waterUsage); //prints out evaluation of your water sustainability farming skills
	}
	
	else //selection must be =2, second function, water potability
	{
		//calculate water quality index
		double waterInfo[2];
		int safe;
		
		getSamples(waterInfo); //get data samples from user
		
		safe = waterSafe(waterInfo);  //test to see if water is safe to drink or not
		
		if(safe ==1)
		{
			printf("\nYour drinking water is safe! Enjoy!");
		}
		
		while(safe != 1) //while drinking water is not acceptable quality
		{
			printf("\nThe drinking water is not safe! Enter '1' to confirm you've recieved this message.");
			scanf("%d",&safe);
		}
	}
	
	
	return 0;
}


//****************************************************************************************************************************************

//functions for first app-farming water usage
char whichCrop()
{
	//this function gets the crop the farmer is interested in finding water use statistics on.
	char crop;
	do //errorcheck crop input
	{
		printf("\nPlease enter the corresponding letter for your crop of interest: 'w' for wheat, 'c' for corn, 'p' for potatoes, or 'o' for oats. : ");
		scanf(" %c",&crop);
	}
	while(crop != 'w' && crop != 'c' && crop != 'o' && crop != 'p');
	return crop;
}

void farmStatistics(double a[], char c) //function that gets field statistics from grower, such as field size, and water usage
{
	printf("\nHow many acres is your field of %c?",c);
	scanf("%lf",&a[0]);
	
	printf("\nAnd for this field of %c, how many gallons of water do you use per season?",c);
	scanf("%lf",&a[1]);
}

void evaluation(double a, double b) //function evaluates your water usage compared to industry standards
{
	double ratio = b/a; //ratio of water used to water necessary b/a = ratio, a, b/ratio * a, 1/ratio = factor
	double factor = 1/ratio; //factor to change current water usage by to reach required amount
	double decreaseFactor = 1-factor; 
	if(ratio < .5)
	{
		printf("\nYou are not even using half of the water you need to. You should be using %.4lf times more water.",factor);
	}
	else if (ratio < .8)
	{
		printf("\nYou are using slightly less water than you need to. You should be using %.4lf times more water.",factor);
	}
	else if (ratio < 1.1)
	{
	printf("You are using an acceptable amount of water. Good job!");
	}
	else if (ratio < 1.4)
	{
		printf("\nYou are using slightly more water than you need to. You should be using %.4lf times less water, to not waste any.",decreaseFactor);
	}
	else
	{
		printf("\nYou are using 1.5 times the water you need to or more. You should be using %.4lf times less water.",decreaseFactor);
	}
}

//****************************************************************************************************************************************

//functions for second program-water safety

void getSamples(double a[])
{
	printf("\nPlease enter the measured concentration of lead in ppm : ");
	scanf("%lf",&a[0]);
	
	printf("\nPlease enter '1' if you detected any bacteria, parasites, viruses or fungi in the water. If none were detected, enter any other integer : ");
	scanf("%lf",&a[1]);
	
	printf("\nPlease enter the measured concentration of nitrates in your water sample : ");
	scanf("%lf",&a[2]);
}

int waterSafe(double a[])
{
	int safe; //variable to determine if water is safe to drink;
	if(a[1] == 1)
	{
		safe = -1;
	}
	else if(a[0] > .015)
	{
		safe = -1;
	}
	else if(a[2] > 10)
	{
		safe =  -1;
	}
	else
	{
		safe = 1;
	}
	return safe;
}
