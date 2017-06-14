#include <lib.h> //provides _syscall and message variables
#include <stdio.h>
#include <stdlib.h> //atoi
#include <unistd.h> // is this include needed?


int main(int argc, char **argv){

  if(argc < 2){
    printf(" No args for testing. Enter './executable arg' \n");
    printf("Enter: 0 for stop_plog \n" );
    printf("Enter: 1 for start_plog \n" );
    printf("Enter: 2 for reset_plog \n" );
    printf("Enter: 3 for get_plog_size \n" );
    printf("Enter: 4 for get_plog_byPID \n" );
    printf("Enter: 5 for get_plog_byindex \n" );
    exit(1);
  }

  int i = atoi(argv[1]); //can use this to choose which lib function

  long start, finish;//input for last two lib functions
  int index,PID;

  if(i == 1)//input signal to start
    start_plog();

  else if( i == 0)  //input signal to stop
    stop_plog(); //will turn it off after testing it on for a bit
  else if(i == 2)//reset log
    reset_plog();
  else if(i == 3)//return log size
    get_plog_size();//does  one more
  else if(i == 4){//get log elements with pid
    printf("Enter PID: ");
    scanf("%d", &PID); //finding pid, but time is off

    int retVal1 = get_plog_byPID(PID, &start, &finish);//fix param

    if(retVal1 == 0)
      printf("PID %d, started at %ld, finished at %ld\n", PID, start, finish);
    else
      printf("Error 2\n" );
  }
  else if(i == 5){
    printf("Enter index: ");
    scanf("%d", &index);
    int returnVal = get_plog_byindex(index, &start, &finish);

    if(returnVal == 0)
      printf("Entry %d started at %ld, finished at %ld\n", index, start, finish);
    else
      printf("Error 3\n");
  }


  return 0;


}
