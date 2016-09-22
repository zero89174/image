#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int imagep[512][512]; 

int af_imagep[2048][2048]={0}; //max *4

double cubicInterpolate (double p[4], double x) {
	return p[1] + 0.5 * x*(p[2] - p[0] + x*(2.0*p[0] - 5.0*p[1] + 4.0*p[2] - p[3] + x*(3.0*(p[1] - p[2]) + p[3] - p[0])));
}

double bicubicInterpolate (double p[4][4], double x, double y) {
	double arr[4];
	arr[0] = cubicInterpolate(p[0], y);
	arr[1] = cubicInterpolate(p[1], y);
	arr[2] = cubicInterpolate(p[2], y);
	arr[3] = cubicInterpolate(p[3], y);
	return cubicInterpolate(arr, x);
}


int main()
{
    int i,j;
    int x,y;
	//char source[20]="BOYGIRL.RAW";
	char output[20];
	FILE *image,*out;
	int Xsize=256;
	int Ysize=256;  
	float	_Af; // define bigger or smaller


  	if ((image=fopen("BOYGIRL.RAW" ,"rb")) == NULL)
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


//put into file _Af -> ©ñ¤j­¿²v
	int error=0;
	int Af_Xsize = Xsize*_Af;
    int Af_Ysize = Ysize*_Af;
	for(i=0; i<Af_Ysize; i++)
	{ 
		for(j=0; j<Af_Xsize; j++)
		{	
			int af_i=i/_Af;
			int af_j=j/_Af; 
			float alpha = (j-af_j*_Af)/_Af;
			float beta = (i-af_i*_Af)/_Af;
			if(af_i-1<=0) 	af_i=1;
			if(af_j-1<=0) 	af_j=1;
			if(af_i+2>=255)	af_i=253;
			if(af_j+2>=255)	af_j=253;
			double p[4][4]={	{imagep[af_i-1][af_j-1],imagep[af_i-1][af_j],imagep[af_i-1][af_j+1],imagep[af_i-1][af_j+2]},
								{imagep[af_i  ][af_j-1],imagep[af_i  ][af_j],imagep[af_i  ][af_j+1],imagep[af_i  ][af_j+2]},
								{imagep[af_i+1][af_j-1],imagep[af_i+1][af_j],imagep[af_i+1][af_j+1],imagep[af_i+1][af_j+2]},
								{imagep[af_i+2][af_j-1],imagep[af_i+2][af_j],imagep[af_i+2][af_j+1],imagep[af_i+2][af_j+2]}	};
			af_imagep[i][j]=(int)bicubicInterpolate(p,beta,alpha);
			if(af_imagep[i][j]>255)	 {error++;	af_imagep[i][j]=255;}
			if(af_imagep[i][j]<0)	 {error++;	af_imagep[i][j]=255;	}
			fputc(af_imagep[i][j],out);
		}
	}
	printf("error has :%d\n",error );
	fclose(image);
	fclose(out);

	return 0;
}



	/*end of design*/
