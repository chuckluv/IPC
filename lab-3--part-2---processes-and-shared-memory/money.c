#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>


void Parent(int [],int[]);
void Child(int [],int[]);
int  main(int  argc, char *argv[])
{
  int    ShmID;
  int    ShmID2;
   int    *BankAccount;
    int    *Turn;
  pid_t  pid;
  
  ShmID = shmget(IPC_PRIVATE, 4*sizeof(int), IPC_CREAT | 0666);
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
   ShmID2 = shmget(IPC_PRIVATE, 4*sizeof(int), IPC_CREAT | 0666);
     if (ShmID2 < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
   BankAccount = (int *) shmat(ShmID, NULL, 0);
     if (*BankAccount == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
   Turn = (int *) shmat(ShmID2, NULL, 0);
     if (*Turn == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
  
  
   BankAccount[0] = 0;
   Turn[0] = 0;
  
  pid = fork();
     if (pid > 0) {
       int i ;
       for(i = 0; i <25; i++){
          
         Parent(BankAccount,Turn);
       }
         
     }
     else if (pid == 0) {
       int x;
       for(x = 0; x<25; x++){
        
          Child(BankAccount,Turn);
       }
          
     }
  
}

void Parent(int BankAccount[], int Turn[]){
  
 
  sleep(random() % 5);
  while(Turn[0] != 0);
   
    if (BankAccount[0] <= 100){
      int deposit = random() % 100;
      if(deposit%2 ==0){
        BankAccount[0] += deposit;
        printf("Dear old Dad: Deposits $%d / Balance = $%d\n", deposit, BankAccount[0]);
         
      }
      else
      {
        printf("Dear old Dad: Doesn't have any money to give\n");
      }
    }
    else
    {
      printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", BankAccount[0]);
    
    Turn[0] = 1;
  }
   return;
}

void Child(int BankAccount[], int Turn[]){
  
 
  sleep(random() % 5);
  while(Turn[0] !=1);
    
  
    int Balneed = random()% 50;
    printf("Poor Student needs $%d\n", Balneed);
   
    if(Balneed <= BankAccount[0]){
     
      BankAccount[0] -= Balneed;
      printf("Poor Student: Withdraws $%d / Balance = $%d\n", Balneed, BankAccount[0]);
 
      }
    else{
       printf("Poor Student: Not Enough Cash ($%d)\n", BankAccount[0] );
    }
    Turn[0] = 0;
    return;
}

