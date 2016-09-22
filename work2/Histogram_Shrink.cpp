#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define X_size 512
#define Y_size 512
int  imagep[512][512];

float  af_imagep[512][512] = { 0 }; //max *4



int main()
{
	int i, j;
	int x, y;
	//char source[20]="BOYGIRL.RAW";
	char output[20];
	FILE *image, *out;
	int Xsize = X_size;
	int Ysize = Y_size;
	int af_big_pixel;
	int af_small_pixel;
	int af_bigtemp=1;
	int af_smalltemp=255;
	int bigtemp = 1;
	int smalltemp = 255;

	if ((image = fopen("BIRD.RAW", "rb")) == NULL)
	{
		printf("\n Can't open the image  !! \n");
		exit(0);
	}
	/* start design*/

	printf("\n Enter image need biggest pixel: ");
	scanf("%d", &af_big_pixel);
	printf("\n Enter image need smallest pixel: ");
	scanf("%d", &af_small_pixel);


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

	int error = 0;

	for (i = 0; i<Ysize; i++)
	{
		for (j = 0; j<Xsize; j++)
		{
			float	ans = (float)(af_big_pixel - af_small_pixel) / (bigtemp - smalltemp);
			af_imagep[i][j] = (ans)*(imagep[i][j] - smalltemp)+af_small_pixel;
			//	printf("ans : %f  ,af_imagep[i][j] \n",ans,af_imagep[i][j]);
			if (af_imagep[i][j] >= af_bigtemp)		af_bigtemp = af_imagep[i][j];
			if (af_imagep[i][j] <= af_smalltemp)		af_smalltemp = af_imagep[i][j];

			if (af_imagep[i][j]>255)	 { error++;	af_imagep[i][j] = 255; }
			if (af_imagep[i][j]<0)	 { error++;	af_imagep[i][j] = 0; }
			//af_imagep[i][j] = 0;
			fputc(af_imagep[i][j], out);
		}
	}

	//printf("%d , %d \n",bigtemp,smalltemp); 
	//printf("%d , %d\n",af_bigtemp,af_smalltemp); 
	printf("error has :%d\n", error);
	fclose(image);
	fclose(out);

	return 0;
}



/*end of design*/
