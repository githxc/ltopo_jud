#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cha_ext.h"
#include "math.h"

long int bubble_sort_mid(long int a[8])
{
    int i,j,temp;   
    for (j=0;j<8-1;j++)   
    {                           
        for (i=0;i<8-1-j;i++)
        {
            if(a[i]>a[i+1])  
            {
                temp=a[i];  
                a[i]=a[i+1];  
                a[i+1]=temp;
            }
        }
    }
	return (a[3]+a[4])/2;
}


float cha_dval(long int *s,long int*f)
{
	int i;
	long int s_max=0,s_min=0,f_max,f_min;
	long int s_dval,f_dval;
	
	s_max = s[0];
	s_min = s[0];
	f_max = f[0];
	f_min = f[0];
	for(i=0;i<8;i++)
	{
		if(s_min>s[i])
		{
			s_min = s[i];
		}
		else if(s_max<s[i])
		{
			s_max = s[i];
		}
	}
	
	for(i=0;i<8;i++)
	{
		if(f_min>f[i])
		{
			f_min = f[i];
		}
		else if(f_max<f[i])
		{
			f_max = f[i];
		}
	}
	
	s_dval = s_max - s_min;
	f_dval = f_max - f_min;
	
	if(s_dval==0)
		return f_dval;
	return (float)f_dval/s_dval;
}

float cha_uord(long int *s,long int*f)
{
	int i;
	long int sum_fs=0,sum_ls=0,sum_ff=0,sum_lf=0;
	long int s_uord,f_uord;
	//float fs_uord,ff_uord;
	for(i=0;i<4;i++)
	{
		sum_fs = sum_fs + s[i];
	}
	for(i=0;i<4;i++)
	{
		sum_ls = sum_ls + s[7-i];
	}
	for(i=0;i<4;i++)
	{
		sum_ff = sum_ff + s[i];
	}
	for(i=0;i<4;i++)
	{
		sum_lf = sum_lf + s[7-i];
	}
	
	s_uord = sum_ls-sum_fs;
	f_uord = sum_lf-sum_ff;
	//fs_uord = tanh((float)s_uord);
	//ff_uord = tanh((float)f_uord);
	
	if(s_uord*f_uord>0)
		return 0;
	else 
		return 1;
}


float cha_jumt(long int *s,long int*f)
{
	int sd[7];
	int fd[7];
	int sd_max=0,fd_max=0;
	int i,ns=0,nf=0;
	for(i=0;i<7;i++)
		sd[i] = abs(s[i+1]-s[i]);
	for(i=0;i<7;i++)
		fd[i] = abs(f[i+1]-f[i]);
	
	for(i=0;i<7;i++)
	{
		if(sd_max<sd[i])
		{
			sd_max = sd[i];
			ns= i;
		}
	}
	
	for(i=0;i<7;i++)
	{
		if(fd_max<fd[i])
		{
			fd_max = fd[i];
			nf = i;
		}
	}
	return (float)(abs(nf-ns)/4);
}


void cha_rel(long int *s, long int *f,FILE *fp)
{
	float r[14];
    float sxy;
	float sss,ssf,dsf;
    int    delay,i,j;
	
	for(i=0;i<8;i++)
	{
		s[i] = s[i] - bubble_sort_mid(s);
		f[i] = f[i] - bubble_sort_mid(f);
	}
	printf("%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld\n",s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7]);
	printf("%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld\n",f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7]);
	
    for(delay = -7; delay < 8; delay++)
    {
        //Calculate the numerator
        sxy = 0;
        for(i=0; i<8; i++)
        {
            j = i + delay;
            if((j < 0) || (j >= 8))  //The series are no wrapped,so the value is ignored
                continue;
            else
                sxy += (s[i] * f[j]);
        }

        //Calculate the correlation series at "delay"
        r[delay + 7] = sxy;
    }
	
	for(i=0;i<8;i++)
	{
		sss += s[i]*s[i];
		ssf += f[i]*f[i];
	}
	sss = sqrt(sss);
	ssf = sqrt(ssf);
	dsf = sss*ssf;

	for(i=0;i<15;i++)
		r[i] = r[i]/dsf;

	
	fprintf(fp,"%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f\n",r[0],r[1],r[2],r[3],r[4],r[5],r[6],r[7],r[8],r[9],r[10],r[11],r[12],r[13],r[14]);
}

float cha_lost(long int *s,long int*f,FILE *fp)
{	
	int s_p;
	int f_p = -1;
	int i;
	int s_max = 0;
	for(i=0;i<8;i++)
	{
		if(s_max < s[i])
		{
			s_max = s[i];
			s_p = i;
		}
	}
	
	for(i=0;i<8;i++)
	{
		if(f[i] == -1)
		{
			f_p = i;
			break;
		}			
	}
	
	fprintf(fp,"%d,%d\n",s_p,f_p);	
	if(f_p == -1)
		return 0;
	else
		return ((float)f_p-(float)s_p)/4;
}

void output(long int *s,long int *f,FILE *fp)
{
	float dval,uord,jumt,lost;
	dval = cha_dval(s,f);
	uord = cha_uord(s,f);
	jumt = cha_jumt(s,f);
	cha_rel(s,f,fp);
	lost = cha_lost(s,f,fp);

	fprintf(fp,"%0.2f,%0.2f,%0.2f,%0.2f\n",dval,uord,jumt,lost);
}

