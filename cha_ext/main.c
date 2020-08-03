#include <stdio.h>
#include <math.h>
#include "cha_ext.h"



int  main()
{
	float dval,uord,jumt,rel,lost;
	long int s_data[8] = {142,142,140,513,11005,1239,941,918};
	long int f_data[8] = {5505,5523,5541,5559,5577,-1,-1,4863};
	dval = cha_dval(s_data,f_data);
	uord = cha_uord(s_data,f_data);
	jumt = cha_jumt(s_data,f_data);
	rel = cha_rel(s_data,f_data);
	lost = cha_lost(s_data,f_data);
	printf("%f\n", dval);
	printf("%f\n", uord);
	printf("%f\n", jumt);	
	printf("%f\n", lost);

	return 0;
}





