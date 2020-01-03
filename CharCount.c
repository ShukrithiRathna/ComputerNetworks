/*
	01-09-18
	Shukrithi Rathna
*/
//Implementing character count in Data link  framing
#include<stdio.h>
#include<string.h>	

int main()
{
	int fsize,i,j=0,fcount=0;
	char data[100];
	printf("\nEnter the data (with frame character count) that is to be sent:");
	scanf("%s",data);
	int datasize=strlen(data);
	data[datasize]='\0';
	printf("\nData length: %d",datasize);
	printf("\n%s\n",data);
	//printf("d[i]:%d",data[i]-'0');
	Frame:
	{
		fsize=data[j]-'0';
		printf("\nFrame %d:",count);
		printf("\tFrame size: %d",fsize);
		printf("\tData:");
		for(i=j+1;i<j+fsize;i++)
		{	//printf("\nEntered for. i=%d fsize=%d\n",i,fsize);
			printf("%d",data[i]-'0');	
		}
		count++;
		j=j+fsize;
	}
	if(j>=datasize)
		return(0);
	else
		goto Frame;
	printf("\n");
	return(0);
}
