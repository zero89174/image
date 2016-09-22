#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define  PI 3.1415926

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define X_size 512
#define Y_size 512
int  imagep[512][512]; 
float pix_num[256]={0};
float  af_imagep[512][512]={0}; //max *4
int error=0;

float rand_gauss(int count){
	float f_count=(float)count;
	float Gauss_value=(sqrt(12)*f_count)/sqrt(10);
	float ran;
	float total=0.00;
	float Noise;
	for (int i = 0; i < 10; i++)
	{
		ran=((float)rand()/(RAND_MAX+1));
		total+=(float)(ran-0.5f);
	}
	Noise=(float)(Gauss_value*total);

    //printf("%f\n", ran);

	return Noise;

}

int main()
{
    int i,j;
    int x,y;
    srand(time(NULL));
	//char source[20]="BOYGIRL.RAW";
	char output[20];
	FILE *image,*out;
	int Xsize=X_size;
	int Ysize=Y_size;  
	float Gauss;

  	if ((image=fopen("BIRD.RAW" ,"rb")) == NULL)
	{
		printf("\n Can't open the image  !! \n");
		exit(0);
	}
	/* start design*/

    printf("\n set you want see Gauss_value: ");
	scanf("%f",&Gauss);   
 

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

	for(i=0; i<Ysize; i++)
	{ 
		for(j=0; j<Xsize; j++)
		{	
			af_imagep[i][j]=(float)imagep[i][j]+(float)rand_gauss(Gauss);
			if(af_imagep[i][j]>255)	 {error++;	af_imagep[i][j]=255;}
			if(af_imagep[i][j]<0)	 {error++;	af_imagep[i][j]=0;	}
			fputc(af_imagep[i][j],out);
		}
	}
	printf("pixel error has :%d\n",error );
	fclose(image);
	fclose(out);

	return 0;
}



	/*end of design*/
