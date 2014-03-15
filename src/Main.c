/*
 * Main.c
 *
 *  Created on: 11 mars 2014
 *      Author: selalaouit
 */
#define __STDC_FORMAT_MACROS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include<pthread.h>
#include<unistd.h>
#include "Main.h"

int main()
{
	
	//printf("%d",is_prime(23));
	//printf("\n");
	//print_prime_factors(92);
	 FILE * fichier =fopen ("numbers.txt", "r");
	uint64_t p;
	while(fscanf(fichier,"%llu",&p)!=EOF)
	{
		int c1, c2;
		pthread_t t1,t2;

		c1 =pthread_create(&t1,NULL,print_prime_factors,NULL);
		c2 =pthread_create(&t2,NULL,print_prime_factors,NULL);
		
		c1 =pthread_join(t1,NULL);
		c2 =pthread_join(t2,NULL);
		
		print_prime_factors(p);
		printf("\n");
		
	}
	
}

int is_prime(uint64_t p)

{
	uint64_t i;
	for(i=2; i<=sqrt(p);i++)
	{
		if(p%i==0)
		{
			return 0;
		}
	}

	return 1;

}

void print_prime_factors(uint64_t n)
{
	
	uint64_t i;
	printf("%"PRIu64,n);
	printf(":");
	for(i=2; i<=n ; i++)
	{
		
		if(is_prime(i) == 1 && (n%i ==0) )
		{
			while(n%i ==0)
			{	
			 	printf("%"PRIu64,i);
				printf(" ");
				n=n/i;
			}
			
		}
		
	}

}






