/*--------------------------------------------------- 
	Modelling Flow control for File transfer
  ---------------------------------------------------
*/
#include<stdio.h>
/*#include<conio.h>*/
#include<time.h>
#include<string.h>
#include<stdlib.h>
int main()
{
   //Initialization of parameters
   int size,filerecv = 0;	
   int bufA,bufB, bufcap;	
   int trans, seqno = 10000;	
   int ackBA, r , win = 1, flag =0;	//Flag bit used to distinguish 1 byte control data from file data byte; r-random number
   printf("Enter the file size-\n");	//Input file size
   scanf("%d",&size);
   if(size <= 0)			//Check for error condition
   {
	printf("\nError - File size should be a positive value\n");
	printf("Enter the file size-\n");
        scanf("%d",&size);
   }
   int original_size = size;		//store original file size
   /*getchar();*/	
   printf("\nEnter the buffer capacity of the send & receive buffers\n");	//Input send & receive buffer capacity
   scanf("%d",&bufcap);
   if(bufcap <= 0)			//check for error condition
   {
	printf("\nError - Buffer capacity should be a positive value\n");
	printf("\nEnter the buffer capacity of the send & receive buffers\n");
	scanf("%d",&bufcap);
   }
   //Initial conditions
   bufA = bufB =0;
   printf("\nInitial conditions : \nFile size = %d \tSend buffer A = 0 \t Bytes in channel = 0", size);
   printf("\nFile received = %d \tReceive Buffer B = 0 \n", filerecv);
   getchar();
   //Initiating File transfer -  
   printf("\nInitiating file transfer from A to B\n");	
   while(size > 0)
   {
      if(size == 0)	//Break from loop once file is transferred
      {
	break;
      }
      printf("\nLoading bytes from file to send buffer A...");
      if(size >= bufcap)	//Loading bytes into send buffer
	 bufA = bufcap;
      else
	 bufA = size;
      sleep(2);			//suspend operations for finite time for output visibility
      printf("\nTransmitting bytes from A to B...");
      if (win == 0)		//Transmit bytes into channel depending on receive window size feedback
      {
	 trans = 1;
	 flag = 1;
      }
      else   
      {
	 flag = 0;
	 trans = bufA;
	 bufA = 0;
	 size = size - trans;	//Decrement size of file that has been transmitted
      }
      if(size < 0)
	 size = 0;
      printf("\nFile size remaining = %d \tSend buffer A = %d \t Bytes in channel = %d, \tSequence no =%d", size, bufA, trans, seqno);
      if(flag != 1)		//Accept into receive buffer if data is a file data byte
      	 bufB = trans;
      r = rand() % 20;		//restrict random number range
      /*printf("\nMax random number = %d\n",RAND_MAX);*/
      ackBA = seqno;		//acknowledge received byte
      trans = 0;
      if(r < 5)			//random acceptance of data bytes from the receive buffer onto memory of B
      {
         filerecv = filerecv + bufB;
         bufB = 0;
      }
      if (bufB == 0)		//check for receive buffer status and set window size
      {
         win = 1;
         seqno = seqno +2;
      }
      else
	 win = 0;		
      printf("\nFile size received = %d \tReceive buffer B = %d \t Acknowledgement = %d", filerecv, bufB, ackBA);
      printf("\n Receive window = %d\n", win);
   }
   printf("\n Received file size - %d\n", (filerecv+bufB));		//Display the final received file size
   return 0;
}
