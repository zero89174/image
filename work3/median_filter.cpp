#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define X_size 512
#define Y_size 512
#define N_size 7
int  imagep[Y_size][X_size]; 
int  af_imagep[Y_size][X_size]={0}; 
int error=0;

int median_filter(int i,int j){
	int mid=N_size/2;
	int temp=0;
	int reg[N_size*N_size]={0};
	for(int i_=i-mid;i_<=i+mid;i_++){
		for(int j_=j-mid;j_<=j+mid;j_++){
			reg[temp++]=imagep[i_][j_];
		}
	}
	//for (int x = 0; x < N_size*N_size; x++) printf("%d\n",reg[x] );
	//printf("before\n");
	//bubble sort
	for(int x=N_size*N_size; x>=1; x--){
            for(int y=0; y<=x-1; y++){
                if(reg[y] > reg[y+1]){
                    temp = reg[y];
                    reg[y] = reg[y+1];
                    reg[y+1] = temp;
                }
            }
        }	
    //for (int x = 0; x < N_size*N_size; x++) printf("%d\n",reg[x] );
	//printf("done\n");
	return reg[(N_size*N_size)/2];
}

int main()
{
    int i,j;
    int x,y;
	char output[20];
	FILE *image,*out;
	int Xsize=X_size;
	int Ysize=Y_size;  
	int max_pix=0;
	int min_pix=256;
  	if ((image=fopen("111.RAW" ,"rb")) == NULL)
	{
		printf("\n Can't open the image  !! \n");
		exit(0);
	}
	/* start design*/

    printf("\n default set 3*3 to mediun: ");
    printf(" Enter output image filename: ");
	scanf("%s",output);	
    out=fopen(output,"wb");


	for(i=0; i<Ysize; i++) // read all pixel
	{ 
		for(j=0; j<Xsize; j++)
		{
			imagep[i][j]=fgetc(image);
			if(imagep[i][j]>max_pix) max_pix=imagep[i][j];
			if(imagep[i][j]<min_pix) min_pix=imagep[i][j];
		}
	}
	//process



	for(i=0; i<Ysize; i++)
	{ 
		for(j=0; j<Xsize; j++)
		{	
			if(imagep[i][j]==max_pix || imagep[i][j]==min_pix) af_imagep[i][j]=median_filter(i,j);
			else	af_imagep[i][j]=imagep[i][j];
			
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
