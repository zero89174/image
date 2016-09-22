#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define X_size 512
#define Y_size 512
int  imagep[512][512]; 
float pix_num[256]={0};
float  af_imagep[512][512]={0}; //max *4
int error=0;
void diff_pixel(int pixel){
	for (int i = 0; i < 256; i++)
	{
		if(i==pixel) pix_num[i]++;
	} 
}
void process(int max_graylevel){
	int temp=0;
	for (int i = 0; i < 256; i++)
	{
		temp=pix_num[i]+temp;
		pix_num[i]=(float)temp/(X_size*Y_size)*max_graylevel;
	} 

}
float set_pixel(int pixel){
	float result_pix;
	for (int i = 0; i < 256; i++)
	{
		if(pixel==i) {	return pix_num[i];	break;	}
	}

	 
}
int main()
{
    int i,j;
    int x,y;
	//char source[20]="BOYGIRL.RAW";
	char output[20];
	FILE *image,*out;
	int Xsize=X_size;
	int Ysize=Y_size;  
	int af_big_pixel;
	int af_small_pixel;

	int max_graylevel=1;
	int min_graylevel=255;

  	if ((image=fopen("BIRD_HistogramShrink_100to0.RAW" ,"rb")) == NULL)
	{
		printf("\n Can't open the image  !! \n");
		exit(0);
	}
	/* start design*/

    //printf("\n Enter image need biggest pixel: ");
	//scanf("%d",&af_big_pixel);   
    //printf("\n Enter image need smallest pixel: ");
	//scanf("%d",&af_small_pixel);    
	

    printf(" Enter output image filename: ");
	scanf("%s",output);	
    out=fopen(output,"wb");

    
	for(i=0; i<Ysize; i++) // read all pixel
	{ 
		for(j=0; j<Xsize; j++)
		{
			imagep[i][j]=fgetc(image);
			if(imagep[i][j]>=max_graylevel)		max_graylevel=imagep[i][j];
			if(imagep[i][j]<=min_graylevel)		min_graylevel=imagep[i][j];
			diff_pixel(imagep[i][j]);
		}
	}
	process(max_graylevel);
	for (int s = 0; s < 256; s++)
	{
		printf("%f ,\n",pix_num[s] );
	}
	

	for(i=0; i<Ysize; i++)
	{ 
		for(j=0; j<Xsize; j++)
		{	
			af_imagep[i][j]=set_pixel(imagep[i][j]);
			if(af_imagep[i][j]>255)	 {error++;	af_imagep[i][j]=255;}
			if(af_imagep[i][j]<0)	 {error++;	af_imagep[i][j]=0;	}
			fputc(af_imagep[i][j],out);
		}
	}
	printf("error has :%d\n",error );
	fclose(image);
	fclose(out);

	return 0;
}



	/*end of design*/
