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
	float a[2][2],b[2][2],c[2][2];
	int x,y;
	setbuf(stdout,NULL);
	printf("Enter the element of 1st matrix\n");
	for(x=0;x<2;++x)
	{
		for(y=0;y<2;++y)
		{
			printf("Enter a%d%d ",x+1,y+1);
			scanf("%f", &a[x][y]);
		}
	}

	printf("Enter the element of 2st matrix\n");
	for(x=0;x<2;++x)
	{
		for(y=0;y<2;++y)
		{
			printf("Enter b%d%d ",x+1,y+1);
			scanf("%f",&b[x][y]);
		}
	}

	for(x=0;x<2;++x)
	{
		for(y=0;y<2;++y)
		{
			c[x][y]=a[x][y]+b[x][y];
		}
	}
	printf("Sum of the matrix\n");
	for(x=0;x<2;++x)
	{
		for(y=0;y<2;++y)
		{
			printf("%.1f\t",c[x][y]);
		}
		printf("\n");
	}

	return 0;
}
