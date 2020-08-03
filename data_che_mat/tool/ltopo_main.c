#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "ltopo_define.h"
#include "ltopo_xml.h"
#include "pul_data.h"
#incldue "cha_ext.h"

#define TOOL_TEST_INPUT_PATH "../test/tool"
#define TOOL_XML_FILE TOOL_TEST_INPUT_PATH "/tool.xml"

typedef struct struct_ltool_statis {
int s1_count;
} ltool_statis;
ltool_statis g_s;

LTOOL_XML_NODE * ltopo_find_xml_node(char * addr)
{
    LTOPO_LIST *p;
    LTOOL_XML_NODE  *pmeter;
    list_for_each(p, &g_xmlhead.list){
        pmeter=container_of(p, LTOOL_XML_NODE, list);
        if(!strcmp(pmeter->addr, addr)){
                return pmeter;
            }
        }
    return NULL;
}


int du(int t,FILE *proc);
int tiaoguo(FILE *proc);
int mfz_proc_file(char *filename, char * outfile);

int du(int t,FILE *proc)
{
	int i;
	for(i=0;i<t;i++)
		fgetc(proc);
	return 1; 
}

int tiaoguo(FILE *proc)
{
    while (!feof(proc) && fgetc(proc) != '\n');
    return 1;
}

int judge_fs(char *s,char *f,char num2[2],FILE *fp)
{
	LTOOL_XML_NODE * pmeter;
	pmeter=ltopo_find_xml_node(s);
	//fprintf(fp,"123");
	//fprintf(fp,"%s-%s ",pmeter->f_addr,pmeter->f_b_no);
	while(strcmp(pmeter->f_addr,"-1")!=0)
	{
		if((strcmp(f,pmeter->f_addr)==0)&&(strcmp(num2,pmeter->f_b_no)==0))
			return 1;
		pmeter= ltopo_find_xml_node(pmeter->f_addr);
	
	}
	
	return 0;
}

int mfz_proc_file(char *filename, char * outfile)
{
    FILE *fp = NULL;
	FILE *fpo = NULL;
    fp = fopen(filename,"r");
	fpo = fopen(outfile,"wb");

	int pulse,d_pulse;
	int pul_num,d_pul_num;

	if(!fp||!fpo)
    {
        printf("failed open!\n");
		return -1;
    }

	char biaozhi;
	char addr[12],d_addr[13];
	char num2[10]={0};
	
	long int s[8];
	int pan;
	
	while(biaozhi != EOF)
	{
		int i;
		for(i=0;i<8;i++)
			s[i]=0;
		
		biaozhi = fgetc(fp);
   		if(biaozhi == 'L')
    	{				
        	du(9,fp);
       		biaozhi = fgetc(fp);
	        if(biaozhi == 'm')
    	    {
        	   	du(2,fp);
			fgets(addr,13,fp);
			du(8,fp);
			fscanf(fp,"%ld",&(s[0]));
			du(1,fp);
			fscanf(fp,"%ld",&s[1]);
			du(3,fp);
			fscanf(fp,"%ld",&s[2]);
			du(1,fp);
			fscanf(fp,"%ld",&s[3]);
			du(1,fp);
			fscanf(fp,"%ld",&s[4]);
			du(1,fp);
			fscanf(fp,"%ld",&s[5]);
			du(3,fp);
			fscanf(fp,"%ld",&s[6]);
			du(1,fp);
			fscanf(fp,"%ld",&s[7]);
			tiaoguo(fp);
       		}
        	else if(biaozhi == 'b')
       		{
    			du(2,fp);
			fgets(d_addr,13,fp);
			du(1,fp);
			num2[0] = fgetc(fp);
			du(8,fp);
			fscanf(fp,"%ld",&(s[0]));
			du(1,fp);
			fscanf(fp,"%ld",&s[1]);
			du(3,fp);
			fscanf(fp,"%ld",&s[2]);
			du(1,fp);
			fscanf(fp,"%ld",&s[3]);
			du(1,fp);
			fscanf(fp,"%ld",&s[4]);
			du(1,fp);
			fscanf(fp,"%ld",&s[5]);
			du(3,fp);
			fscanf(fp,"%ld",&s[6]);
			du(1,fp);
			fscanf(fp,"%ld",&s[7]);
			tiaoguo(fp);
	        }
		else
			tiaoguo(fp);
    	}
		if(biaozhi == 'm')
		{
			pul_num = pul_detect(s);
			pulse = pul_judg(pul_num);
			
			pul_out_m(pulse,addr,s,fpo);
		}
		else if(biaozhi == 'b')
		{
			d_pul_num = pul_detect(s);
			d_pulse = pul_judg(d_pul_num);
			
			pan = judge_fs(addr,d_addr, num2,fpo);
			pul_out_d(pan,pulse,d_pulse,d_addr,num2,s,fpo);
		}
	}
	printf("end\n");
}

void ltool_init()
{
    memset(&g_s, 0x0, sizeof(g_s));
}


int main(int argc, char ** argv)
{
    char filename[128];

    if(argc!=2)
    {
        return -1;
    }

	ltool_init();
    g_xmlhead.list.next=NULL;
    ltopo_xml_load_file(TOOL_XML_FILE);
    ltopo_print_mlist(&g_xmlhead.list);
	
    strncpy(filename, argv[1], sizeof(filename)-1);
    mfz_proc_file(filename,"./o");
    return 0;
}

