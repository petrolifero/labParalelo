#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <mpi.h>

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
	
	MPI_Init_thread(&argc,&argv,MPI_THREAD_FUNNELED,&provided_thread_support);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size_of_world);
	number_of_lines=SIZE/size_of_world;
	for(i=number_of_lines*my_rank; i<=number_of_lines*(my_rank+1)-1; i++)
	{
		#pragma omp parallel 
		#pragma omp for private(k)
		for(j=0; j<SIZE; j++)
		{
			c[i][j]=0;
			for(k=0; k<SIZE; k++)
			{
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
	if(my_rank == 0)
	{
		MPI_Status status;
		int aux[SIZE];
		for(j=0; j<SIZE-number_of_lines; j++)
		{
			MPI_Recv((void*)aux, SIZE, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
			for(i=0; i<SIZE; i++)
			{
				c[status.MPI_TAG][i]=aux[i];
			}
		}
	}
	else
	{
		for(i=number_of_lines*my_rank; i<=number_of_lines*(my_rank+1)-1;i++)
		{
			MPI_Send(c[i],SIZE,MPI_INT,0,i,MPI_COMM_WORLD);
		}
	}
	MPI_Finalize();
	return 0;
}
