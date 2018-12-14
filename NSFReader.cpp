#include "NSFReader.h"

#define read_nsf(num,fp) fread(p,1,num,fp)
#define extra_link(s) strcat(nsf[pos].extra,s)

void string_filter(char s[],char d[])
{
	int i , L = strlen(s);
	for(i=0;i<L;i++)
	{
		if(s[i]>=FILTER_INF&&s[i]<=FILTER_SUP)
			d[i] = s[i];
		else break;
	}
	return;
}

int main()
{
	long file;
	_chdir(TEST_ADDRESS);
	int i , pos = 0;
	if((file = _findfirst("*.*", &find))==-1L)
	{
		printf("空白!\n");
		return -1;
	}
	while(_findnext(file, &find) == 0)
	{
		FILE *fp= fopen(find.name,"r");
		strcpy(nsf[pos].chs_name,find.name);
		if(!M_Load(fp,HEADER_TITLE))						//将文件指针移至Title处
		{
			//p =(char*)calloc(Max_Size,sizeof(char));
			read_nsf(NSF_NAME_LIMIT,fp);
			//strcpy(nsf[pos].org_name,p);
			string_filter(p,nsf[pos].org_name);
		}
		if(!M_Load(fp,HEADER_ARTIST))					//将文件指针移至Artist处
		{
			read_nsf(NSF_NAME_LIMIT,fp);
			string_filter(p,nsf[pos].artist);
		}
		if(!M_Load(fp,HEADER_COPYRIGHT))			//将文件指针移至Copyright处
		{
			read_nsf(NSF_NAME_LIMIT,fp);
			string_filter(p,nsf[pos].copyright);
		}
		if(!M_Load(fp,HEADER_CHIP))
		{
			read_nsf(1,fp);
			strcpy(nsf[pos].extra,"2A03");
			if((p[0] & APU_VRC6)!=0)
				extra_link("+VRC6");
			if((p[0] & APU_VRC7)!=0)
				extra_link("+VRC7");
			if((p[0] & APU_FDS)!=0)
				extra_link("+FDS");
			if((p[0] & APU_MMC5)!=0)
				extra_link("+MMC5");
			if((p[0] & APU_N163)!=0)
				extra_link("+N163");
			if((p[0] & APU_5B)!=0)
				extra_link("+SUN5B");
		}
		pos++;
		fclose(fp);
	}
	_findclose(file);
	FILE *wp = fopen(Save_File,"w+");
	for(i = 0;i < pos;i++)
		fprintf(wp,Output_Format,nsf[i].chs_name,nsf[i].org_name,nsf[i].artist,nsf[i].copyright,nsf[i].extra);
	//printf("%d",L);
	return 0;
}
