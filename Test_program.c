#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>



int main(){
	FILE *faxi,*fs,*fb;
	int duty = 0, increment = 0, power,button;
	char sval[4] = {0,0,0,0}, bval[2] = {0,0};
	char *str,*str1;
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


	
	while(1){
		
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
		//Give copy values and check for on off change
		if(sval[0]==(str[2]-48))
			power = 0;
		else
			power = 1;
		
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
		
		
		if(sval[0]){
			if(sval[2]){
				if (sval[3])
					increment = 7;
				else
					increment = 6
			}
			else{
				if (sval[3])
					increment = 5;
				else
					increment = 4
			}
		}
		else
		{
			if(sval[2]){
				if (sval[3])
					increment = 3;
				else
					increment = 2
			}
			else{
				if (sval[3])
					increment = 1;
				else
					increment = 0
			}
		}
		
		/*
		*
		*Buttons and duty cycle calculation
		*
		*/
		
		fb = fopen("/dev/button","r");
		if(fb==NULL)
		{
			puts("Error while opening button file");
			return -1;
		}
		
		str1 = (char *)malloc(num_of_bytes+1);
		getline(&str1,&num_of_bytes,fb);
		
		if(fclose(fb)){
			puts("Error while closing button file");
			return -1;
		}
		
		if((bval[0]==(str[4]-48))&&(bval[1]==(str[5]-48)))
			button = 0;
		else
			button = 1;
		
		bval[0] = str[4] - 48;
		bval[1] = str[5] - 48;
		free(str1);
		
		if(bval[0]&&button){
			
			if((duty+increment)<100)
				duty+=increment;
			else{
				printf("Duty cycle is 100%%\n");
				duty = 100;
			}
		}
		else if(bval[1]&&button){
			
			if((duty-increment)<0)
				duty-=increment;
			else{
				printf("Duty cycle is 0%%\n");
				duty = 100;
		}
		else{}
			
			
		/*
		*
		* Pwm control
		*
		*/
		
		
			
		if(button && (bval[0] || bval[1]))
		{
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
		}


		if(power){
			faxi = fopen("/dev/pwm", "w");
			if(faxi == NULL){
				printf("Error while opening pwm file\n");
				return -1;
			}
		
			///Turn on off pwm
			if(sval[0])
				fputs("pwm on\n",faxi);
			else
				fputs("pwm off\n",faxi);

			if(fclose(faxi)){
				printf("Error while closing pwm file\n");
				return -1;
			}
		}
	}
	return 0;
}
