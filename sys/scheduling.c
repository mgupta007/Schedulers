#include <kernel.h>
#include <math.h>
#include <scheduling.h>
#include<proc.h>
#include<q.h>
//#include<conf.h>

int scheduler;



void calculation_Function()
{
 int j=0;
                        struct pentry *p;
                        while (++ j < NPROC)
                        {
                            
                                p = &proctab[j];
                                
                                if(p->pstate != PRFREE)
                                {
                                 if (p->timeleft == 0)  { 
                                        p->counter = p->pprio;
                                } 
                                
                                else if( p->timeleft == p->counter)
                                p->counter = p->pprio;
                                
                                else {
                                        p->counter = (p->timeleft) / 2 + p->pprio;
                                }
                                p->timeleft = p->counter;
                                p->good = p->timeleft + p->pprio;
                        }
                        }


}

void setschedclass(int sched_class){
	scheduler = sched_class;
}

int getschedclass(){
	return scheduler;
}






