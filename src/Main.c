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
#include <pthread.h>
#include <unistd.h>
#include "Main.h"

#define MAX_FACTORS 64
 // a affiner ?

static FILE * fichier =fopen ("numbers.txt", "r");
//pour éviter de réouvrir le fichier plusieurs fois.

static pthread_mutex_t mutexFichier;
//mutex lecture du fichier

static pthread_mutex_t mutexEcriture;
//mutex ecriture 

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

int get_prime_factors(uint64_t n, uint64_t * dest)
{
	uint64_t i;
	//uint64_t lim = floor(n/2);
	uint64_t factors=0;
	for(i=2; i<=n; i++)
	{
		if(is_prime(i) && (n%i ==0) )
		{
			while(n%i ==0)
			{	
			 	dest[factors]=i;
			 	factors++;
				n=n/i;
			}
			
		}
	}

	return factors;
}


/* version 1 
void print_prime_factors(uint64_t n)
{
	
	uint64_t i;
	printf("%"PRIu64,n);
	printf(": ");
	for(i=2; i<=n ; i++)
	{
		
		if(is_prime(i) == 1 && (n%i ==0) )
		{
			while(n%i ==0)
			{	
				pthread_mutex_lock(& mutexFichier);
			 	printf("%"PRIu64,i);
				printf(" ");
				pthread_mutex_unlock(& mutexFichier);
				n=n/i;
			}
			
		}
		
	}
	

}*/

void print_prime_factors(uint64_t n)
{
	uint64_t factors[MAX_FACTORS];
	int j, k;
	k=get_prime_factors(n,factors);
	printf("%llu: ",n);
	for(j=0;j<k;j++)
	{
		printf("%llu ",factors[j]);
	}
	printf("\n");

}




/* Question 4
static void * start_routine(void * arg)
{
	uint64_t n= (uint64_t)arg;
	print_prime_factors(n);
	printf("\n");
	pthread_exit(NULL);
}
*/
static void * start_routine(void * arg)
{
	uint64_t p;
	int lecture=0;
	while(lecture!=EOF)
	{

		pthread_mutex_lock(& mutexFichier);
		lecture=fscanf(fichier,"%llu",&p);
		pthread_mutex_unlock(& mutexFichier);
		print_prime_factors(p);
		
	}

	pthread_exit(NULL);
}


int main()
{
	//Question 6
	int crdu;
	pthread_t t1,t2;
	pthread_mutex_init(& mutexFichier,NULL);
	pthread_mutex_init(& mutexEcriture,NULL);


	crdu=pthread_create(&t1,NULL,start_routine,NULL);
	if(crdu !=0)
	{
		exit(-1);
	}
	crdu=pthread_create(&t2,NULL,start_routine,NULL);
	if(crdu !=0)
	{
		exit(-1);
	}

	//attente des threads
	crdu=pthread_join(t1,NULL);
	if(crdu !=0)
	{
		exit(-1);
	}
	crdu=pthread_join(t2,NULL);
	if(crdu !=0)
	{
		exit(-1);
	}
	
	//printf("%d",is_prime(23));
	//printf("\n");
	//print_prime_factors(92);

	/* Question 4
	uint64_t p;
	while(fscanf(fichier,"%llu",&p)!=EOF)
	{
		
	
		int crdu;
		pthread_t t1,t2;

		crdu=pthread_create(&t1,NULL,start_routine,(void *)p);
		if(crdu !=0)
		{
			exit(-1);
		}
		crdu=pthread_create(&t2,NULL,start_routine,(void *)p);
		if(crdu !=0)
		{
			exit(-1);
		}

		//attente des threads
		crdu=pthread_join(t1,NULL);
		if(crdu !=0)
		{
			exit(-1);
		}
		crdu=pthread_join(t2,NULL);
		if(crdu !=0)
		{
			exit(-1);
		}
		
		
	}
	*/
	

		
}
	
	




