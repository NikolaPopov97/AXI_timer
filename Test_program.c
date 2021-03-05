#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>



int main(){
	FILE *faxi,*fs;
	int duty = 0, increment = 0;
	char sval[4] = {0,0,0,0};
	char *str;
	size_t num_of_bytes = 6;	
	 
	
	//Setting pwm period
	
	faxi = fopen("/dev/pwm", "w");
	if(faxi == NULL){
		printf("Error while opening pwm file\n");
		return -1;
	}

		
	fputs("period 100000\n", faxi);
	
	if(fclose(faxi)){
		printf("Error while closing pwm file\n");
		return -1;
	}


	
	//while(1){
		
		/*
		*
		*Checking switch conditions
		*
		*/
	
		fs = fopen("/dev/switch","r");
		if(fs==NULL){
			printf("Error opening switch\n");
			return -1;
		}		

		str = (char *)malloc(num_of_bytes+1);
		getline(&str,&num_of_bytes,fs);
		
		if(fclose(fs)){
			puts("Error while closing switch\n");
			return -1;
		}
		sval[0] = str[2] - 48;	
		sval[1] = str[3] - 48;		
		sval[2] = str[4] - 48;
		sval[3] = str[5] - 48;

		free(str);
		printf("Switch values %d %d %d %d",sval[0],sval[1],sval[2],sval[3]);

		/*
		*
		*Increment 
		*
		*/
					
		
		
		/*
		*
		* Pwm control
		*
		*/
		
		
		faxi = fopen("/dev/pwm", "w");
		if(faxi == NULL){
			printf("Error while opening pwm file\n");
			return -1;
		}
		
		//Pass the duty cycle value
		fprintf(faxi,"duty %d\n",duty);
				
		if(fclose(faxi)){
			printf("Error while closing pwm file\n");
			return -1;
		}
		



		faxi = fopen("/dev/pwm", "w");
		if(faxi == NULL){
			printf("Error while opening pwm file\n");
			return -1;
		}
		
		///Turn on off pwm
		if(sval[0])
			fputs("pwm on\n",faxi);
		else
			fpust("pwm off\n",faxi);

		if(fclose(faxi)){
			printf("Error while closing pwm file\n");
			return -1;
		}
		
	//}
	return 0;
}
