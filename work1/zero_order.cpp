#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
 
int imagep[512][512]; 
int af_imagep[2048][2048]; //max *4
int sum_imagep[2048][2048];

int  diff_zero(int i,int j,float _Af){ 
	float avg_X= _Af/2 +j;
	float avg_Y= _Af/2 +i;
	float pow_X= (avg_X-j)*(avg_X-j);
	float pow_Y= (avg_Y-i)*(avg_Y-i);
	float pow_X_1= (avg_X-j+_Af)*(avg_X-j+_Af);
	float pow_Y_1= (avg_Y-i+_Af)*(avg_Y-i+_Af);
	if(		 (pow_X+pow_Y <pow_X+pow_Y_1) && (pow_X+pow_Y <pow_X_1+pow_Y	)&&(pow_X+pow_Y <pow_X_1+pow_Y_1))  	return imagep[i][j];	
	else if ((pow_X+pow_Y_1 <pow_X+pow_Y) && (pow_X+pow_Y_1 <pow_X_1+pow_Y	)&&(pow_X+pow_Y_1 <pow_X_1+pow_Y_1))	return imagep[i][j+1];
	else if ((pow_X_1+pow_Y <pow_X+pow_Y) && (pow_X_1+pow_Y <pow_X+pow_Y_1	)&&(pow_X_1+pow_Y <pow_X_1+pow_Y_1))	return imagep[i+1][j];
	else return imagep[i+1][j+1];
	

}


int main()
{
    int i,j;
    int i_,j_;
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


//put into file
	int Af_Xsize = Xsize*_Af;
    int Af_Ysize = Ysize*_Af;
	for(i_=0; i_<Af_Ysize; i_++)
	{ 
		for(j_=0; j_<Af_Xsize; j_++)
		{	
		int ii= i_/_Af;
		int jj= j_/_Af;
			//af_imagep[i_][j_]=imagep[ii][jj];
			af_imagep[i_][j_]=diff_zero(ii,jj,_Af);
			fputc(af_imagep[i_][j_],out);
		}
	}
	fclose(image);
	fclose(out);

	return 0;
}



	/*end of design*/
