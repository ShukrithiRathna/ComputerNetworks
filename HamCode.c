/*
	02-09-18
	Shukrithi Rathna
*/
//Data link layer-Error Control-Hamming Code(7 bits)
/*
	Takes as input the 4 bit data and returns 
	the 7 bit message generated using hamming 
	code technique which includes parity 
	bits
*/
#include<stdio.h>
#include<string.h>

int errorhandling(char input[], int inputlen);
int errorhandling(char input[], int inputlen)
{
	int i,flag=0;
	for(i=0;i<inputlen;i++)
	{
		if(input[i]!='0'&&input[i]!='1')
		{
			flag=1;
			break;
		}	
			
	}
	if(flag==1)
		printf("\nError. Invalid input");
	return flag;
}

int main()
{
	char data[4];
	char msg[7];
	int H[3];
	int EH;
	char P[3];	
	char E[3];
	int i,flag=0,flag1=0,error;
	printf("\nEnter 4 bit data(0's and 1's):");
	scanf("%s",data);
	data[4]='\0';
	EH=errorhandling(data,strlen(data));
	if(EH==1)
	{
		printf("\nExiting program\n");
		return(0);
	}

//computing parity bits 
	H[0]=(data[0]-'0')+(data[1]-'0')+(data[3]-'0');//for computing P[0]
	H[1]=(data[0]-'0')+(data[2]-'0')+(data[3]-'0');//for computing P[1]	
	H[2]=(data[1]-'0')+(data[2]-'0')+(data[3]-'0');//for computing P[2]
	
	for(i=0;i<3;i++)
	{
		if(H[i]%2==0)//even parity
			P[i]='0';
		else
			P[i]='1'; 
	}

//placing parity bits aling with data bits in the right position
	msg[0]=P[0];
	msg[1]=P[1];
	msg[2]=data[0];
	msg[3]=P[2];
	msg[4]=data[1];
	msg[5]=data[2];
	msg[6]=data[3];		
	
	printf("\nMsg:%s",msg);
	
	printf("\nMsg(without error):%s",msg);
	
//computing error bits
	Error:
	{
		H[0]=(msg[2]-'0')+(msg[4]-'0')+(msg[6]-'0')+(msg[0]-'0');//for computing E[0]
		H[1]=(msg[2]-'0')+(msg[5]-'0')+(msg[6]-'0')+(msg[1]-'0');//for computing E[1]	
		H[2]=(msg[4]-'0')+(msg[5]-'0')+(msg[6]-'0')+(msg[3]-'0');//for computing E[2]
		
		for(i=0;i<3;i++)
		{
			//printf("\nH[%d]:%d",i,H[i]);
			if(H[i]%2==0)//even parity
				E[i]='0';
			else
				E[i]='1'; 
//			printf("E[%d]:%d",i,E[i]);
		}
	

		for(i=0;i<3;i++)
		{
			if(E[i]=='1')
				flag=1;
		}
		if(flag==0)
			printf("\nNo error");
		else
		{	
		//to check which bit has error
			error=(1*(E[0]-'0'))+(2*(E[1]-'0'))+(4*(E[2]-'0'));
			printf("\nError in bit %d",error);
					
		//correcting msg
			if(msg[error-1]=='0')
				msg[error-1]='1';
			else
				msg[error-1]='0';
			printf("\nCorrected message:%s",msg);
		}
	
	}	
	if(flag1==0)
	{ 
		flag1=1;
	//creating msg with error for simulation
		if(msg[2]=='0')
			msg[2]='1';
		else
			msg[2]='0';
		printf("\nMsg with error:%s",msg);
		goto Error;
		
	}	
	return(0);
}
			
	
	
