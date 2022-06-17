#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void main()
{
	double a[10][10],b[10],x[10],xn[10],epsilon=0.00001,parcial;
	int i,j,n,flag;

	printf("\nInsira o numero de variaveis do sistema: ");
	scanf("%d",&n);
	printf("\nInsira os coeficientes do sistema em linha: ");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%lf",&a[i][j]);
		}
	}
	printf("\nInsira o vetor b: ");
	for(i=0;i<n;i++)
		scanf("%lf",&b[i]);
	for(i=0;i<n;i++)
		x[i]=0; //inicializa o vetor x com zeros

	for(i=0;i<n;i++)
		printf(" x[%d] ",i);
	printf("\n");

	do
	{
		for(i=0;i<n;i++)
		{
			parcial=b[i];
			for(j=0;j<n;j++){
				if(j!=i)
					parcial-=a[i][j]*x[j];
			}
			xn[i]=parcial/a[i][i];
		}
		for(i=0;i<n;i++)
			printf("%8.5f ",xn[i]);
		printf("\n");
		flag=1; 
		//verifica condicao de parada |x[i]-xn[i]|<epsilon para todo i
		for(i=0;i<n;i++){
			if(fabs(x[i]-xn[i])<epsilon){
				flag=0;
			}
		}

		if(flag==1){
			for(i=0;i<n;i++){
				x[i]=xn[i]; //atualiza x[i]	para a proxima iteracao
			}
		}
	}while(flag==1);

	printf("\nA solucao do SL eh: \n");
	for(i=0;i<n;i++)
		printf("%8.5f ",xn[i]);
}