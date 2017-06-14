#include <stdio.h>
#include "pm.h"
#include "mproc.h"
#include <time.h>
#include "param.h"

typedef struct{

	long forTime;
	long exTime;
	int childID;

}buff;

buff procArr[1024];
int buffSize = 0; //amount of elements in buffer
int buffcounter = 0; //keeps track of last elements for circular buff
int buffToggle; //will toggle process log buffer
int mValue;//will tell proc_Log what to do according to message
////////////////////////////////////////
//have a main sys call function handling input, then helper functions
//have proc_Log deal with other wanted lib functions/helper sys functions
////////////////////////////////////////

int proc_Log(int child_id){ //PROC_LOG in callnr.h

	int searchPID;//will store pid we are looking for
	int searchIndex; //will store index we are looking for
	//handle messages for final 4 lib functions

	mValue = m_in.m1_i1;//passing in message value

	if(mValue == 1){//if message equals 1 change the toggle for add
	/* Time Calculation Part*/
	buffToggle = 1;

	}

	else if(mValue == 0){

		buffToggle = 0; //toggle off add to buffer
	}

	else if(mValue == 2){
		reset_proBuff();//all values = -1
	}//message 2 = reset
	else if(mValue == 3){
		return retuBuffSize(); //returns the size
	} //message 3 = size
	else if(mValue == 4){
		int searchPID = m_in.m1_i2;//storing specified pid value
		return retu_plogPID(searchPID); //should i return the funct
	} // message 4 = plog_byID
	else if(mValue == 5){
		int searchIndex = m_in.m1_i2;
		return retu_plogIndex(searchIndex); //should i return the funct

	} // message 5 = plog_by_indx
	//printf("buffcounter: %d\n", buffcounter);//delete, just printing buffsize +counter
	//printf("buffSize: %d\n", buffSize);

	return 0;
}

int pid_forkTime(int child_id){ //implement if(toggle), otherwise always running

	long PIDtime = mp->mp_reply.reply_time; //updated time value from do_time in fork
	//printf("Fork Time %ld\n", PIDtime);//erase this test print

	//printf("childPID is: %d\n", child_id);//erase and test buffer values

if(buffToggle == 1){
	procArr[buffcounter].childID = child_id;//addingPID to buffer
	procArr[buffcounter].forTime = PIDtime; //Fork process start time

	int printChildVal = procArr[buffcounter].childID;//mute these VV
	long printForkTime = procArr[buffcounter].forTime;

	printf("Buff ForkId %d\n", printChildVal); //mute these after testing start and stop_plog
	//printf("Buff ForkTime %ld\n", printForkTime);

	if(buffcounter == 1023)//proper order?
		buffcounter = 0;
	else
		buffcounter = buffcounter+1; //inc count

	if(buffSize < 1023)
		buffSize = buffSize+1; //keeps track of amount of elements in buffer
	}
}

int ex_time(){

if(buffToggle == 1){
	long exitingtime = mp->mp_reply.reply_time;//updated exit pid time
	procArr[buffcounter].exTime = exitingtime;

	//printf("Exit time: %ld\n", exitingtime);

	//long buffExitTime = procArr[buffcounter].exTime;
	//printf("buffer exit time: %ld\n", buffExitTime;
	}

}

void reset_proBuff(){ //clears buffer values, and resets counter/size
	buffSize = 0; //set buff size and counter equal to 0;
	buffcounter = 0;
	int i;//loop counter

	for(i = 0; i<1024; i = i+1){

			procArr[i].childID = -1;
			procArr[i].forTime = -1;
			procArr[i].exTime = -1;



	}

} //include proto.h, -in main sys-call, -libfunct, test

int retuBuffSize(){

		printf("Buffer Size is: %d\n", buffSize);
		return buffSize; //instructions say to return size, i printed it for simplicity

}

int retu_plogPID(int lookPID){

int inputPID = lookPID;//storing specified pid value
int j;//loop counter

	for(j = 0; j< buffSize; j=j+1){
		if(procArr[j].childID == inputPID){

			mp->mp_reply.m2_l1 = procArr[j].forTime; //retrieving Pid start
			mp->mp_reply.m2_l2 = procArr[j].exTime; // retrieving Pid end

			printf("PID values found");//can delete
			return 0;
		}
	}
	printf("Error 2: PID not found \n" );
	return 2;//see if this properly shows that not found
}

int retu_plogIndex(int lookIndex){

int inputIndex = lookIndex;//storing index value

 if( (inputIndex >= buffSize) || (inputIndex < 0) )//index out of range
 {
	 printf("Error 3: Index too large or negative \n" );
	 return 3;//error occured
 }
 else{

	 mp->mp_reply.m2_l1 = procArr[inputIndex].forTime;
	 mp->mp_reply.m2_l2 = procArr[inputIndex].exTime;

	 printf("Index values found  \n" );//can delete
	 return 0;//succesfully found value

 }


}
