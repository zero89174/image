#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int imagep[512][512]; 

int af_imagep[2048][2048]={0}; //max *4

int main()
{
    int i,j;
    int i_,j_;
    int x,y;
	//char source[20]="BOYGIRL.RAW";
	char output[20];
	FILE *image,*out;
	int Xsize=256;
	int Ysize=256;  
	float	_Af; // define bigger or smaller


  	if ((image=fopen("Girl.raw" ,"rb")) == NULL)
	{
		printf("\n Can't open the image  !! \n");
		exit(0);
	}
	/* start design*/

    printf("\n Enter image bigger X size: ");
	scanf("%f",&_Af);    printf("\n");

	

    printf(" Enter output image filename: ");
	scanf("%s",output);	
    out=fopen(output,"wb");


	for(i=0; i<Ysize; i++) // read all pixel
	{ 
		for(j=0; j<Xsize; j++)
		{
			imagep[i][j]=fgetc(image);

		}
	}


//put into file
	int error=0;
	int Af_Xsize = Xsize*_Af;
    int Af_Ysize = Ysize*_Af;
	for(i=0; i<Af_Ysize; i++)
	{ 
		for(j=0; j<Af_Xsize; j++)
		{	
		int  ii= i/_Af;
		int  jj= j/_Af;
		float  alpha=(j-jj*_Af)/_Af;
		float  beta   =(i-ii*_Af)/_Af;	
		int temp=(1-alpha)*(1-beta)*(imagep[ii][jj])+(alpha)*(1-beta)*(imagep[ii][jj+1])+(1-alpha)*(beta)*(imagep[ii+1][jj])+(alpha)*(beta)*(imagep[ii+1][jj+1]	);
		af_imagep[i][j]=temp;

		if(af_imagep[i][j]>255)	error++;// {	error++;	af_imagep[i][j]=255;}
		if(af_imagep[i][j]<0)	error++;//{error++;	af_imagep[i][j]=0;	}
		fputc(af_imagep[i][j],out);
		}
	}
	printf("%d\n",error );
	fclose(image);
	fclose(out);

	return 0;
}



	/*end of design*/
