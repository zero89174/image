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
int error = 0;

int lowpass_filter(int i, int j){
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
	float Gauss;

	if ((image = fopen("BIRD.RAW", "rb")) == NULL)
	{
		printf("\n Can't open the image  !! \n");
		exit(0);
	}
	/* start design*/

	printf("\n default set 3*3 to lowpass: ");
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
			fputc(af_imagep[i][j], out);
		}
	}
	printf("pixel error has :%d\n", error);
	fclose(image);
	fclose(out);

	return 0;
}



/*end of design*/
