#include <lib.h>
#include <unistd.h>

void start_plog(){

  message m;
  m.m1_i1 = 1; //1 means go
  printf("Proc Log Start \n");
  return _syscall(PM_PROC_NR, PROC_LOG, &m);
}

void stop_plog(){

  message m;
  m.m1_i1 = 0;//0 means stop
  printf("Proc Log Stop \n");
  return _syscall(PM_PROC_NR, PROC_LOG, &m);
} // program only has this so far, not other 4 lib functs
/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//formatting of returns in project1.c, maybe access variable instead of sys call helpers and in sys call itself(pointer message update)
//chech returning the sys calls in lib functions
//POSSIBLE ISSUES- return values of lib and sys, maybe lib functions for plog_by_indx and plog_byID
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void reset_plog(){

  message m;
  m.m1_i1 = 2; //2 is reset mess
  printf("Reset proc log \n");
  return _syscall(PM_PROC_NR, PROC_LOG, &m);
}
//last 3 lib funct have print statements in sysCall

int get_plog_size(){

  message m;
  m.m1_i1 = 3; //3 is size mess
  return _syscall(PM_PROC_NR, PROC_LOG, &m);
}

int get_plog_byPID(int pid, long* c_time, long* t_time){

  message m;
  m.m1_i1 = 4; //4 is get byPid
  m.m1_i2 = pid;//sending pid we are searching for

  int response = _syscall(PM_PROC_NR, PROC_LOG, &m);//returns 2 if error or 0 if working

  *c_time = m.m2_l1; //storing 2 updated time variables, updated in sysCall
  *t_time = m.m2_l2;

  return response;
}

int get_plog_byindex(int index, long* c_time, long* t_time){

  message m;
  m.m1_i1 = 5; //5 is get byIndex
  m.m1_i2 = index;//sending index we are searching for

  int response = _syscall(PM_PROC_NR, PROC_LOG, &m);//returns 2 if error or 0 if working

  *c_time = m.m2_l1; //storing 2 updated time variables
  *t_time = m.m2_l2;

  return response;

}//returns 3 for error or 0 if fine
