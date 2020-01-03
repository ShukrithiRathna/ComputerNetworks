/*
	02-09-18
	Shukrithi Rathna
*/
//Datalink layer framing-Byte stuffing
/*
	1.Takes as input the data to be
	and performs the required byte stuffing and displays final msg
	2.Removes the stuffed bit if any and regenerated data from msg
	Start of Frame ='STX'
	End of Frame ='ETX'
	Escape='E'
*/
#include<stdio.h>
#include<string.h>

int main()
{
	char data[100];
	char data2[100];
	char msg[100];
	char temp[100];
	int i,j,flag=0;
	printf("\nEnter data (characters) for frame:");
	scanf("%s",data);
	strcpy(data2,data);
	//printf("\nData:%s",data);
	i=0;
	int datalen=strlen(data);
	data[datalen]='\0';
	//printf("\nDL:%d",datalen);
	//printf("\nOriginal Data:%s",data2);		
	//printf("\nData:%s",data);

//Byte Stuffing
	while(i<datalen)//traverse through string
	{
		//check if string contains start char
		if(data[i]=='S'||data[i]=='E')
		{
			if(data[i+1]=='T')
			{
				if(data[i+2]=='X')
				{
					flag=1;		
				}	
				
			}
		}
		else
		{
			flag=0;
		}	
		if(data[i]=='E')//check if string contains escape character
			flag=1;
		if(flag==1)//if chars are present
		{
			//printf("\nEntered flag at %d",i);
			for(j=i;j<datalen;j++)
			{
				temp[j-i]=data[j];//copy remaining string into temp
			}
			data[i]='E';//stuffing byte(escape char)
			for(j=i+1;j<datalen+1;j++)
			{
				data[j]=temp[j-(i+1)];//copy remaining string back to data
			}
			datalen=datalen+1;
			data[datalen]='\0';
		}
		i=i+2;//increment i by 2 to avoid repeat recongnition of 'E'
	}	
	printf("\nOriginal Data:%s",data2);		
	printf("\nData:%s",data);
//	printf("\nDL:%d",datalen);
	data[datalen]='\0';

//Begin frame		
	msg[0]='S';
	msg[1]='T';
	msg[2]='X';
	for(i=3;i<strlen(data)+3;i++)
	{
		msg[i]=data[i-3];
	}
	
//End frame		
	j=strlen(data)+3;
	msg[j]='E';
	msg[j+1]='T';
	msg[j+2]='X';	
	
	int msglen=datalen+6;
	msg[msglen]='\0';
	printf("\nMsg:%s\n",msg);


	char data2[msglen];
	char temp2[100];
	
//Removing byte stuffing
	for(i=3;i<msglen-3;i++)
	{
		data2[i-3]=msg[i];
	}
	data2[msglen-6]='\0';
	printf("Data:%s\n",data2);
	int data2len=strlen(data2);
	//printf("DL:%d",datalen);
	i=0;
	while(i<data2len)
	{
		if(data2[i]=='E')
		{
			if(data2[i+1]=='E')
				{
					flag=1;
				}	
			else
				flag=0;
		
			for(j=i+1;j<data2len;j++)
			{
				temp2[j-(i+1)]=data2[j];
			}
			//printf("\nTemp:%s",temp);
			for(j=i;j<data2len+1;j++)
			{
				data2[j]=temp2[j-(i)];
			}
//			printf("D:%s",data);
			//i=i+4;
//			flag=1;
			data2len=data2len-1;//after removing stuffed byte
			data2[data2len]='\0';
		}
		i++;
	}
	printf("\nData after removing byte stuffing:%s",data2); 
	
//
	return(0);
}
