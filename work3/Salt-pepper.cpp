#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define X_size 512
#define Y_size 512
int  imagep[512][512]; 
float pix_num[256]={0};
float  af_imagep[512][512]={0}; //max *4
int error=0;

int main()
{
    int i,j;
    int x,y;
    srand(time(NULL));
	//char source[20]="BOYGIRL.RAW";
	char output[20];
	FILE *image,*out;
	int Xsize=512;
	int Ysize=512;  
	float pepper_per_w;
	float pepper_per_b;
  	if ((image=fopen("BIRD.RAW" ,"rb")) == NULL)
	{
		printf("\n Can't open the image  !! \n");
		exit(0);
	}
	/* start design*/

    printf("\n set you want see white(percent): ");
	scanf("%f",&pepper_per_w);   
	printf("\n set you want see black(percent): ");
	scanf("%f",&pepper_per_b);   

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
    //  random percent

	for(i=0; i<Ysize; i++)
	{ 
		for(j=0; j<Xsize; j++)
		{	
			float set_rand_pixel_w=(rand()%(100));
			float set_rand_pixel_b=(rand()%(100));
			if(		(set_rand_pixel_w >= 0			 ) && (set_rand_pixel_w < pepper_per_w)) 				af_imagep[i][j]=255;	
			else if((set_rand_pixel_b >=pepper_per_w ) && (set_rand_pixel_b < pepper_per_b+pepper_per_w)) 	af_imagep[i][j]=0;	
			else af_imagep[i][j]=imagep[i][j];
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
