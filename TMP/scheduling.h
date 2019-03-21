
#ifndef _scheduling_h_
#define _scheduling_h_

	#define DEFAULTSCHED 0
	#define EXPDISTSCHED 1
	#define LINUXSCHED 2
        
        extern int scheduler;
        
	void setschedclass(int sched_class);
	int	getschedclass();
	int	exponent_process(int random);
        void calculation_Function();
	
        //int	linux_next_proc();
        //	//void 	getMaxProcess(int *next, int *max);
        //		//void 	updateGoodness();
 #endif
       
