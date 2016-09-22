#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define pi 3.14159265
#define X_size 256
#define Y_size 256
#define col_size 3
#define min_pix(a,b,c) (a<b ? (a<c?a:c):(b<c?b:c ) )
int  imagep[Y_size][X_size][col_size];
double H_temp[X_size*Y_size]={0};
double S_temp[X_size*Y_size]={0};
int	   I_temp[X_size*Y_size]={0};
double  af_imagep[Y_size][X_size][col_size] = { 0 }; //max *4
int error = 0;
int error_H=0;
double pix_num[256]={0};

void diff_pixel(int pixel){
	for (int i = 0; i < 256; i++)
	{
		if(i==pixel) pix_num[i]++;
	} 
}
void process(int max_graylevel){
	long int temp=0;
	for (int i = 0; i < 256; i++)
	{
		temp=pix_num[i]+temp;
		pix_num[i]=(double)temp/(X_size*Y_size)*max_graylevel;
	} 

}
double set_pixel(int pixel){
	double result_pix;
	for (int i = 0; i < 256; i++)
	{
		if(pixel==i) {	return pix_num[i];	break;	}
	}

	 
}

int main()
{
	int i, j;
	int x, y;
	char output[20];
	FILE *image, *out;
	int Xsize = X_size;
	int Ysize = Y_size;
	int tmp=0;
	int Max_I=1;
	if ((image = fopen("Lena2.raw", "rb")) == NULL)
	{
		printf("\n Can't open the image  !! \n");
		exit(0);
	}

	printf(" Enter output image filename: ");
	scanf("%s", output);
	out = fopen(output, "wb");
	for (i = 0; i<Ysize; i++) // read all pixel
	{
		for (j = 0; j<Xsize; j++)
		{
			for(int col=0;col<3;col++)
			{
				imagep[i][j][col]=fgetc(image);
				//tmp++;
			}
		}
	}
	for (i = 0; i<Ysize; i++) 
	{
		for (j = 0; j<Xsize; j++)
		{

			int r=imagep[i][j][0];
			int g=imagep[i][j][1];
			int b=imagep[i][j][2];
			int min_s=min_pix(r,g,b);
			double val=180.0/pi;
			double deno=sqrt((r-g)*(r-g) + (r-b)*(g-b)) ; //¤À¥À
			double w=((r-g)/2+(r-b)/2) / sqrt((r-g)*(r-g) + (r-b)*(g-b));
			if(w>1)w=1;
			
			I_temp[j+i*Xsize]=(int)(r+g+b)/col_size +.5f;
			if(g>=b) {//G>=B 
				if(deno==0){
					H_temp[j+i*Xsize]=0;
					S_temp[j+i*Xsize]=0;
				}	
				else 		{
					H_temp[j+i*Xsize]= (double)(acos(w) *val);
					S_temp[j+i*Xsize]=(double)(1.- (double)(3*min_s/ (double)(r+g+b)) );
				}
			}

			else{	// B>G
				if(deno==0)	{
					H_temp[j+i*Xsize]=0;
					S_temp[j+i*Xsize]=0;
				}
				else 	{
					H_temp[j+i*Xsize]= (double)(360.0f-acos(w)*val);
					S_temp[j+i*Xsize]=(double)(1.- (double)(3*min_s/ (double)(r+g+b)) );
				}
			}
			
			diff_pixel(I_temp[j+i*Xsize]);
			if(I_temp[j+i*Xsize]>Max_I) Max_I=I_temp[j+i*Xsize];

			//printf("%d  H=%f S=%f I=%d \n",j+i*Xsize,H_temp[j+i*Xsize],S_temp[j+i*Xsize],I_temp[j+i*Xsize] );
			//printf("%d RGB is %d , %d , %d \n", j+i*Xsize,r,g,b);
		}
	}
	process(Max_I);
	for ( i = 0; i < Xsize*Ysize ; i++)
	{
		I_temp[i]=set_pixel(I_temp[i]);
	}

	for (i = 0; i<Ysize; i++)
	{
		for (j = 0; j<Xsize; j++)
		{
			int Hn;
			double r=0;
			double g=0;
			double b=0;
			double s_af=S_temp[j+i*Xsize];
			int i_af=I_temp[j+i*Xsize];

			if(H_temp[j+i*Xsize]>=0 && H_temp[j+i*Xsize]<120){
				Hn=H_temp[j+i*Xsize];
				r=(double)i_af*(1+ s_af* cos(Hn*pi/180)/ cos((60-Hn)*pi/180 ) );
				b=(double)(i_af-i_af*s_af);
				g=(double)3*i_af -r-b;

			}
			else if(H_temp[j+i*Xsize]>=120 && H_temp[j+i*Xsize]<240){
				Hn=H_temp[j+i*Xsize]-120;
				g=(double)i_af*(1+ s_af* cos(Hn*pi/180)/ cos((60-Hn)*pi/180 ) );
				r=(double)(i_af-i_af*s_af);	
				b=(double)3*i_af -r-g;
			}
			else  if(H_temp[j+i*Xsize]>=240 && H_temp[j+i*Xsize]<360){
				Hn=H_temp[j+i*Xsize]-240;
				b=(double)i_af*(1+ s_af* cos(Hn*pi/180)/ cos((60-Hn)*pi/180 ) );
				g=(double)(i_af-i_af*s_af);
				r=(double)3*i_af -b-g;
			}
			else {
				
				error_H ++;
			}
			printf("%d RGB is %f , %f , %f ori is %d , %d , %d \n", j+i*Xsize,r,g,b ,imagep[i][j][0],imagep[i][j][1],imagep[i][j][2]);
			
			if(r>255) 		{r=255;	error++;}
			else if(r<0)	{r=0;	error++;}
			if(g>255) 		{g=255;	error++;}
			else if(g<0)	{g=0;	error++;}
			if(b>255) 		{b=255;	error++;}
			else if(b<0)	{b=0;	error++;}
			

			fputc(r, out);
			fputc(g, out);
			fputc(b, out);
		}
	}
	printf("pixel error has :%d,%d\n", error,error_H);
	fclose(image);
	fclose(out);

	return 0;
}



/*end of design*/

