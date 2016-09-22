#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define pi 3.14159265
#define X_size 256
#define Y_size 256
int  imagep[Y_size][X_size];
int  af_imagep[Y_size][X_size] = { 0 }; //max *4
int error = 0;
int error_H=0;

void  process(int pass)
{
	
	int Y=Y_size;
	int X=X_size;
	for(int num = 0; num< pass; num++)
	{
		//change
		for (int i = 0; i < Y; i++)
		{
			for (int j = 0; j < X; j++)
			{
				imagep[i][j]=af_imagep[i][j];
			}
		}	
		//row_L
		for (int i = 0; i < Y; i++)
		{
			for (int j = 0; j < X/2; j++)
			{
				af_imagep[i][j]=(imagep[i][j*2]+imagep[i][j*2+1])/2+.5f;
			}
		}
		//row_H
		for (int i = 0; i < Y; i++)
		{
			for (int j = 0; j < X/2; j++)
			{
				af_imagep[i][j+X/2]=(imagep[i][j*2]-imagep[i][j*2+1])/2+.5f+128;
			}
		}	
		//change
		for (int i = 0; i < Y; i++)
		{
			for (int j = 0; j < X; j++)
			{
				imagep[i][j]=af_imagep[i][j];
			}
		}	
		//col_L	
		for (int i = 0; i < Y/2; i++)
		{
			for (int j = 0; j < X; j++)
			{
				af_imagep[i][j]=(imagep[i*2][j]+imagep[i*2+1][j])/2+.5f;
			}
		}	
		//col_H
		for (int i = 0; i < Y/2; i++)
		{
			for (int j = 0; j < X; j++)
			{
				af_imagep[i+Y/2][j]=(imagep[i*2][j]-imagep[i*2+1][j])/2+.5f+128;
			}
		}	
		Y=Y/2;
		X=X/2;

	}

}


int main()
{
	int i, j;
	int x, y;
	int pass=0;
	char output[20];
	FILE *image, *out;
	int Xsize = X_size;
	int Ysize = Y_size;
	if ((image = fopen("BOYGIRL.raw", "rb")) == NULL)
	{
		printf("\n Can't open the image  !! \n");
		exit(0);
	}
	printf(" Enter need wavelet num: ");
	scanf("%d", &pass);
	while(pass>7){
		printf(" Please re-Enter need wavelet num: (num<=4)");
		scanf("%d", &pass);
	}
	printf(" Enter output image filename: ");
	scanf("%s", output);
	out = fopen(output, "wb");
	for (i = 0; i<Ysize; i++) // read all pixel
	{
		for (j = 0; j<Xsize; j++)
		{
			imagep[i][j]=fgetc(image);
			af_imagep[i][j]=imagep[i][j];
		}
	}

	process(pass);
	for (i = 0; i<Ysize; i++)
	{
		for (j = 0; j<Xsize; j++)
		{
	
			fputc(af_imagep[i][j], out);
		}
	}
	//printf("pixel error has :%d,%d\n", error,error_H);
	fclose(image);
	fclose(out);

	return 0;
}



/*end of design*/


