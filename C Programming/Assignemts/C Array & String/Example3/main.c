/*
 * main.c
 *
 *  Created on: 30 Jun 2024
 *      Author: Mostafa Mourad
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int  IntRows=0,IntColumn=0,IntRcounter=0,IntCcounter=0;
	float MatrixArr[10][10] ,TransArr[10][10];
	setbuf(stdout,NULL);
	printf("Enter The Number of Rows: ");
	scanf("%d",&IntRows);
	printf("Enter The Number of Column: ");
	scanf("%d",&IntColumn);
	printf("Enter The Elements of Matrix:\n");
	for(IntRcounter=0;IntRcounter<IntRows;IntRcounter++)
	{
		for(IntCcounter=0;IntCcounter<IntColumn;IntCcounter++)
		{
			printf("Enter Element[%d][%d]",IntRcounter+1,IntCcounter+1);
			scanf("%f",&MatrixArr[IntRcounter][IntCcounter]);
		}
	}
	printf("Entered Matrix:\n");
	for(IntRcounter=0;IntRcounter<IntRows;IntRcounter++)
	{
		for(IntCcounter=0;IntCcounter<IntColumn;IntCcounter++)
		{
			printf("%.2f\t",MatrixArr[IntRcounter][IntCcounter]);
		}
		printf("\n");
	}
	for(IntRcounter=0;IntRcounter<IntRows;IntRcounter++)
	{
		for(IntCcounter=0;IntCcounter<IntColumn;IntCcounter++)
		{
			TransArr[IntCcounter][IntRcounter]=MatrixArr[IntRcounter][IntCcounter];
		}
	}
	printf("Transpose of Matrix:\n");
	for(IntRcounter=0;IntRcounter<IntColumn;IntRcounter++)
	{
		for(IntCcounter=0;IntCcounter<IntRows;IntCcounter++)
		{
			printf("%.2f\t",TransArr[IntRcounter][IntCcounter]);
			if(IntColumn==1)
				break;
		}
		printf("\n");
	}
	return 0;
}





