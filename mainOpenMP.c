#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000



void fill_matrix(int matrix[SIZE][SIZE])
{
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			matrix[i][j]=1;
		}
	}
}

void print_matrix(int matrix[SIZE][SIZE])
{
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE ;j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}



int main(int argc, char* argv[])
{
	int a[SIZE][SIZE],b[SIZE][SIZE],c[SIZE][SIZE];
	int i,j,k,N;
	int my_rank;
	int size_of_world;
	int number_of_lines;
	int provided_thread_support;
	N=SIZE;
	fill_matrix(a);
	fill_matrix(b);
	
	#pragma omp parallel
	#pragma omp for private(j,k)
	for(i=0; i<SIZE; i++)
	{
		for(j=0; j<SIZE; j++)
		{
			c[i][j]=0;
			for(k=0; k<SIZE; k++)
			{
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
	return 0;
}
