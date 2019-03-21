#include <stdio.h>



unsigned long int  RAND_MAX = 077777;


double pow(double base, double exponent)
{
int i;
double product=1.000;

for(i=1;i<=exponent;i++)
{
product=product*base;
}


return product;
}



double log(double b)
{
int i,x;
double a=1.00,c,sum=0;

b=1-b;
for(i=1;i<=20;i++)
{
a= (a*(b));
sum = sum + (a/i);
}

sum=sum * -1;

//kprintf("\nlog sum %d \n", sum);

return sum;

}








double expdev(double lambda){
	double dummy;
	do{
		dummy =(( (double)rand()) / RAND_MAX);
	}while(dummy == 0.0);
          

       // kprintf("\nvalue %d\n",-1*(log(dummy) / lambda));
	return -1 *(log(dummy) / lambda);
}





/*
 * int main()
 * {
 *
 * double a=0.9;
 *
 * calclog(a);
 *
 * }
 * */









                                                    














