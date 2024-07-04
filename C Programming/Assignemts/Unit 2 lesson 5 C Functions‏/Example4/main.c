/*
 * main.c
 *
 *  Created on: 5 Jul 2024
 *      Author: Mostafa Mourad
 */


#include <stdio.h>
#include <stdlib.h>

int ClcPower(int IntNumber,int IntPower);

int main()
{
	int number=0,power=0;
	setbuf(stdout,NULL);
	printf("Enter Base Number: ");
	scanf("%d",&number);
	printf("Enter Power Number(Positive Integer): ");
	scanf("%d",&power);
	printf("%d^%d = %d",number,power,ClcPower(number,power));
	return 0;
}
int ClcPower(int IntNumber,int IntPower)
{
	if(IntNumber==0)
		return 0;
	else if (IntPower==0)
		return 1;
	else
		return (IntNumber*ClcPower(IntNumber,IntPower-1));
}


