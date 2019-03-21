--------/* resched.c  -  resched */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include<scheduling.h>
#include<math.h>
unsigned long currSP;	/* REAL sp of current process */
extern int ctxsw(int, int, int, int);
/*-----------------------------------------------------------------------
 * resched  --  reschedule processor to highest priority ready process
 *
 * Notes:	Upon entry, currpid gives current process id.
 *		Proctab[currpid].pstate gives correct NEXT state for
 *			current process if other than PRREADY.
 *------------------------------------------------------------------------
 */
int resched()
{
	register struct	pentry	*optr;	/* pointer to old process entry */
	register struct	pentry	*nptr;	/* pointer to new process entry */

	/* no switch needed if current process priority higher than next*/

        if(scheduler == EXPDISTSCHED)
        {
        
           int r=(int)expdev(0.1);

          optr= &proctab[currpid];
                if(optr->pstate == PRCURR){
            //    kprintf("running1 \n");

          optr->pstate = PRREADY;
          insert(currpid, rdyhead, optr->pprio);
          }

          int process,process1,priority_Process_schedule;

          process=q[rdytail].qprev;
          process1=process;

          if(q[process].qkey==0)
          priority_Process_schedule = EMPTY;

          else
          { 
          int flag=0;

          while(r<q[process].qkey && flag==0)
          {

          if(q[process1].qkey==q[process].qkey)
          {
          process=q[process].qprev;
          }
		  
         else if(q[process1].qkey!=q[process].qkey)
         {
         process1=process;
         process=q[process].qprev;
         } 


        if(process>=NPROC)
         {
         flag=1;
         priority_Process_schedule = EMPTY;
         }
         } 


         if(flag==0)
         priority_Process_schedule= process1;

         }       
             
            if(priority_Process_schedule==EMPTY)
            currpid=NULLPROC;
             
             else
{              
             int a;
             a= dequeue(priority_Process_schedule);         
             currpid=a;
}
             nptr = &proctab[currpid];
             nptr->pstate=PRCURR;

             #ifdef  RTCLOCK
        preempt = QUANTUM;              /* reset preemption counter     */
#endif
        ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp, (int)nptr->pirmask);
        /* The OLD process returns here when resumed. */
        return OK;             
		}                                        
else if(scheduler == LINUXSCHED)
{
    register struct pentry *optr; 
	register struct pentry *nptr; 
	
   //   int flagde=0, count=0;



	  optr = &proctab[currpid];
	

	
	optr->good= optr->good - optr->timeleft + preempt;
	

	if (optr->timeleft == 0 || currpid == NULLPROC || preempt==0) {
		optr->timeleft = 0; 
	    optr->good=0;
	}

        else
        optr->timeleft = preempt;
	
       int flag=0;
       int cc;
       cc=q[rdyhead].qnext;
      int prt2=0;
      for (prt2 = cc; prt2 != rdytail; prt2 = q[prt2].qnext) {
                if (proctab[prt2].good >0) {
                        flag=1;
                        break;
                }
        }
        
         int best_Place;
        int bb;
        bb=q[rdyhead].qnext;
        int best = q[bb].qkey;
        int prt1 = 0; 
        for (prt1 = bb; prt1 != rdytail; prt1 = q[prt1].qnext) {
                if (proctab[prt1].good > best) {
                        best_Place = prt1;
                        best = proctab[prt1].good;
                }
        }                       
                      
       if(flag==1)
     {
      if ( optr->timeleft == 0 || optr->good < best || optr->pstate != PRCURR ){

                if (optr->pstate == PRCURR) {
                        optr->pstate = PRREADY;
                        insert(currpid, rdyhead, optr->pprio);
                }

                nptr = &proctab[best_Place];
                nptr->pstate = PRCURR;
                currpid=dequeue(best_Place);
                preempt = nptr->timeleft;
                ctxsw((int) &optr->pesp, (int) optr->pirmask, (int) &nptr->pesp, (int) nptr->pirmask);
                return OK;
        }

               if (optr->good >= best  && optr->pstate == PRCURR) {
                return OK;
                }
}

        else  if(flag == 0 )        
        {
        if (optr->pstate != PRCURR || optr->timeleft == 0){
		calculation_Function();]
		preempt = optr->timeleft;           
		if (currpid == NULLPROC) {
				return OK;
			} 
         else {
				
				if (optr->pstate == PRCURR) { 
					optr->pstate = PRREADY;
					insert(currpid, rdyhead, optr->pprio);
				}
				nptr = &proctab[NULLPROC];
				nptr->pstate = PRCURR;
		              	currpid =dequeue(NULLPROC);
			
#ifdef	RTCLOCK
				preempt = QUANTUM;
#endif
				ctxsw((int) &optr->pesp, (int) optr->pirmask, (int) &nptr->pesp, (int) nptr->pirmask);
				return OK;
			}
		
	} 
		}

	
  
else
		return OK;
}


                                              
                             
                                               
                                                 
                      
	
	




                                
                                                
                               
else
{


register struct	pentry	*optr;	/* pointer to old process entry */
	register struct	pentry	*nptr;	/* pointer to new process entry */

	/* no switch needed if current process priority higher than next*/

	if ( ( (optr= &proctab[currpid])->pstate == PRCURR) &&
	   (lastkey(rdytail)<optr->pprio)) {
		return(OK);
	}
	
	/* force context switch */

	if (optr->pstate == PRCURR) {
		optr->pstate = PRREADY;
		insert(currpid,rdyhead,optr->pprio);
	}

	/* remove highest priority process at end of ready list */

	nptr = &proctab[ (currpid = getlast(rdytail)) ];
	nptr->pstate = PRCURR;		/* mark it currently running	*/
#ifdef	RTCLOCK
	preempt = QUANTUM;		/* reset preemption counter	*/
#endif
	
	ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp, (int)nptr->pirmask);
	
	/* The OLD process returns here when resumed. */
	return OK;

}
                                                           
                                                                                                           
}




                                         

