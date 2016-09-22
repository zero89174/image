#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define pi 3.14159265359
#define abs(a) (a>0 ? a : -a ) 
#define big_(a,b) (a>b ? a : b ) 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define X_size 868	
#define Y_size 600
#define N_size 3
#define sqrt_2 1.414 
int  imagep[Y_size][X_size];
float  af_imagep[Y_size][X_size] = { 0 }; //max *4
float  af_imagep2[Y_size][X_size] = { 0 };
int error = 0;

int sobel_operator(int i,int j,int threshold){

	int mid = N_size / 2;
	int temp[9]={0};
	int num=0;
	int sum=0;
	for (int i_ = i - mid; i_ <= i + mid; i_++){
		for (int j_ = j - mid; j_ <= j + mid; j_++){				
			temp[num++]= imagep[i_][j_];

		}
	}
	//for(int i_=0;i_<9;i_++)	printf("i=%d, j=%d ,img=%d\n",i,j,temp[i_]);
	int alpha=(temp[6]+2*temp[7]+temp[8])-(temp[0]+2*temp[1]+temp[2]) ;
	int beta=(temp[2]+2*temp[5]+temp[8])-(temp[0]+2*temp[3]+temp[6]);

	sum=abs(alpha)+abs(beta);

	if(sum<threshold) return 0;
	else {


		return 255; 
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
	int threshold;
	int line;
	if ((image = fopen("gray_Hough_test_868X600.raw", "rb")) == NULL)
	{
		printf("\n Can't open the image  !! \n");
		exit(0);
	}
	/* start design*/
	printf("\n Enter you need sobel threshold: ");
	scanf("%d", &threshold);
	//printf("\n Enter you need line number: ");
	//scanf("%d", &line);
	printf(" Enter output image filename: ");
	scanf("%s", output);
	out = fopen(output, "wb");


	for (i = 0; i<Ysize; i++) // read all pixel
	{
		for (j = 0; j<Xsize; j++)
		{
			imagep[i][j] = fgetc(image);
		}
	}
	//process


	//sobel
	for (i = 0; i<Ysize; i++)
	{
		for (j = 0; j<Xsize; j++)
		{
			if (i<N_size / 2 || i>Ysize - N_size / 2 || j<N_size / 2 || j>X_size - 1) af_imagep[i][j] = 0;
			else af_imagep[i][j]=sobel_operator(i,j,threshold);
			if (af_imagep[i][j]>255)	 { error++;	af_imagep[i][j] = 255; }
			if (af_imagep[i][j]<0)	 { error++;	af_imagep[i][j] = 0; }
		}
	}
	//hough
	int d=big_(X_size,Y_size);
	int p_arr=(int)(d*sqrt_2+0.5f);
	int step[p_arr][181]={0}; //-90 to 90
	for (i = 0; i<Ysize; i++)
	{
		for (j = 0; j<Xsize; j++)
		{
			if(af_imagep[i][j]==255){	
				for (int deg = -90; deg <= 90; deg++)
				{			
					int p=(int)j*cos(pi*deg/ 180)+i*sin(pi*deg/ 180); // long between (0,0) and line
					//if(p< sqrt_2*d && p>=0) {
						if(p<0) error++;
						step[p][(deg+90)]++;
						
					//}
				}
			}
		}
	}
	//sort and decide where to replace white
	int temp=0;
	int p_pix=0;
	int deg_pix=0;

	
	for (int p = 0; p <p_arr ; p++)
	{
		for (int deg = 0; deg < 181; deg++)
		{
			if(step[p][deg]>temp) {
				temp=step[p][deg];
				p_pix=p;
				deg_pix=deg;
			}
		}
	}
	//printf("%d,%d",p_pix,deg_pix);

	//paste line
	for (i = 0; i<Ysize; i++)
	{
		for (j = 0; j<Xsize; j++)
		{
			af_imagep2[i][j]=imagep[i][j];

			if(p_pix==(int)(j*cos((deg_pix-90)*pi/180)+i*sin((deg_pix-90)*pi/180)) ){ af_imagep2[i][j]==255;  error++;} //didn't set deg and p
			else af_imagep2[i][j]=0;
			fputc(af_imagep2[i][j], out);
		}
	}
	//printf("pix: %d, %d\n",cos(0*pi/180),sin((-90)*pi/180));
	printf("pixel error has :%d\n", error);
	fclose(image);
	fclose(out);

	return 0;
}



/*end of design*/

