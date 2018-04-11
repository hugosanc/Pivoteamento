#include<stdio.h>
#include<stdlib.h>
#include<math.h>

FILE *leitura;

double **ler( char *nome, int *dim)
{	
	int i, j;
    double **M, a;
     
	leitura = fopen(nome,"r");
	i = fscanf(leitura,"%d",dim);

	M = malloc( *dim *sizeof(double *));
	for( i = 0 ; i < *dim ; i++ )
		M[i] = malloc((*dim+1)*sizeof(double) );
	    
	i = j = 0;

	while ( fscanf(leitura,"%lf",&a) != EOF) 
	{
		M[i][j] = a;
		j++;
		if (j == *dim+1) 
		{	j = 0;
			i++;
		}
	}		
	return M;
}

void imprime( double **M, int dim)
{
	int i, j;
     
	for(i=0;i<dim;i++)
	{
		for(j=0;j<dim+1;j++)
			printf("%.3lf\t ",M[i][j]);
			  
		puts("");
	}	
}

double **pivoteamento( double **M, int dim)
{
     double l, pivo, maior, aux;
     int i,j,k,m,n;
        
     for(j=0;j<dim;j++)
     {	
		pivo = M[j][j];
		maior = pivo;

		for(k=j+1;k<dim;k++)
		{	if( fabs(maior) < fabs(M[k][j]))
			{	maior = M[k][j];
				m = k;
			}
		}

		if( maior != pivo)
		{	for( n=0;n<dim+1;n++)
			{	aux = M[m][n];
				M[m][n] = M[j][n];
				M[j][n] = aux;
			}
		}

		for(i=j+1;i<dim;i++)
		{
			l = M[i][j]/M[j][j];       
			for(k=0;k<dim+1;k++)
				M[i][k] -= l*M[j][k]; 
		}
	}       
	return M;
}

void subreversa( double **M, double *x, int dim)
{
	int i,k;
	double sum;

	for( i=dim-1; i>=0; i-- )
	{
		sum=0;
		for( k=i+1; k<dim; k++)
			sum += M[i][k]* x[k];

		x[i] = ( M[i][dim] - sum )/M[i][i];
	}
}	

void main(int argc, char **argv)
{
	double **L, *raiz;
	int dim,i;
	
	L = ler(argv[1],&dim);
	printf("\nMatriz\n");
	imprime(L,dim);

	printf("\nTriagulação\n");
	L = pivoteamento(L,dim);
	imprime(L,dim);
	
	raiz = malloc( dim* sizeof(double));
	subreversa(L,raiz,dim);
	printf("\nRaizes");
	for( i=0; i<dim; i++)
		printf("\nv[%d]: %.4lf",i,raiz[i]);
	puts(" ");   
}

