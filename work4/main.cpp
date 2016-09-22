#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define X_size 512
#define Y_size 512
#define N_size 3
int  imagep[Y_size][X_size];
float  af_imagep[Y_size][X_size] = { 0 }; //max *4
float  af_imagep2[Y_size][X_size]={0};
float  af_imagep3[Y_size][X_size]={0};
float  af_imagep4[Y_size][X_size]={0};
int error = 0;
int error2 = 0;
int error3 = 0;
int error4 = 0;

float lowpass_filter(int i, int j){
	double sum = 0;
	float avg;
	int mid = N_size / 2;
	for (int i_ = i - mid; i_ <= i + mid; i_++){
		for (int j_ = j - mid; j_ <= j + mid; j_++){
			sum += imagep[i_][j_];
		}
	}
	avg = (float)sum / (N_size*N_size);
	//printf("%f\n",avg );
	return avg;
}

int main()
{
	int i, j;
	int x, y;
	char output[20];
	FILE *image, *out;
	int Xsize = X_size;
	int Ysize = Y_size;
	int bigtemp = 1;
	int smalltemp = 255;
	int af_big_pixel;
	int af_small_pixel;
	if ((image = fopen("ALLEN.RAW", "rb")) == NULL)
	{
		printf("\n Can't open the image  !! \n");
		exit(0);
	}
	/* start design*/

	printf("\n default set 3*3 to lowpass: ");
	printf("\n Enter image need shrink max pixel: ");
	scanf("%d", &af_big_pixel);
	printf("\n Enter image need shrink min pixel: ");
	scanf("%d", &af_small_pixel);
	//printf("\n Enter image need Stretching max pixel: ");
	//scanf("%d", &af_big_pixel_str);
	//printf("\n Enter image need Stretching min pixel: ");
	//scanf("%d", &af_small_pixel_str);


	printf(" Enter output image filename: ");
	scanf("%s", output);
	out = fopen(output, "wb");


	for (i = 0; i<Ysize; i++) // read all pixel
	{
		for (j = 0; j<Xsize; j++)
		{
			imagep[i][j] = fgetc(image);
			if (imagep[i][j] >= bigtemp)		bigtemp = imagep[i][j];
			if (imagep[i][j] <= smalltemp)		smalltemp = imagep[i][j];
		}
	}
	//process



	for (i = 0; i<Ysize; i++)
	{
		for (j = 0; j<Xsize; j++)
		{
			if (i<N_size / 2 || i>Ysize - N_size / 2 || j<N_size / 2 || j>X_size - 1) af_imagep[i][j] = imagep[i][j];
			else {
				af_imagep[i][j] = lowpass_filter(i, j);
			}
			if (af_imagep[i][j]>255)	 { error++;	af_imagep[i][j] = 255; }
			if (af_imagep[i][j]<0)	 { error++;	af_imagep[i][j] = 0; }
			
			float	ans = (float)((af_big_pixel - af_small_pixel) / (bigtemp - smalltemp));
			af_imagep2[i][j] = (float)((ans)*(af_imagep[i][j] - smalltemp)+af_small_pixel);
			
			if (af_imagep2[i][j]>255)	 { error2++;	af_imagep2[i][j] = 255; }
			if (af_imagep2[i][j]<0)	 { error2++;	af_imagep2[i][j] = 0; }
			
			af_imagep3[i][j]=(float)(imagep[i][j]-af_imagep2[i][j] );
			//if (af_imagep3[i][j]>255)	 { error3++;	af_imagep3[i][j] = 255; }
			//if (af_imagep3[i][j]<0)	 { error3++;	af_imagep3[i][j] = 0; }

			//**********************//
			float ans1=(float)(af_imagep3[i][j]-smalltemp)/(bigtemp- smalltemp);
			af_imagep4[i][j]=(bigtemp-	smalltemp)*ans1 + smalltemp;
			if (af_imagep4[i][j]>255)	 { error4++;	af_imagep4[i][j] = 255; }
			if (af_imagep4[i][j]<0)	 { error4++;	af_imagep4[i][j] = 0; }
 

			fputc(af_imagep4[i][j], out);
		}
	}
	printf("pixel error has :%d\n", error);
	printf("pixel error has :%d\n", error2);
	printf("pixel error has :%d\n", error3);
	printf("pixel error has :%d\n", error4);
	fclose(image);
	fclose(out);

	return 0;
}



/*end of design*/
