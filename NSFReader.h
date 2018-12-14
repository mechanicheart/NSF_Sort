#ifndef _NSFREADER
#define _NSFREADER

#include<io.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define Max_Size 2000
#define NAME_LIMIT 100
#define NSF_NAME_LIMIT 32
#define TEST_ADDRESS "d:\\FC BGM NSF\\123"
#define Save_File "NSFReader.txt"
#define Output_Format "%s\t\t%s\t\t%s\t\t%s\t\t%s\n"

#define APU_VRC6 0x01
#define APU_VRC7 0x02
#define APU_FDS 0x04
#define APU_MMC5 0x08
#define APU_N163 0x10
#define APU_5B 0x20

#define HEADER_TITLE 0x0E
#define HEADER_ARTIST 0x2E
#define HEADER_COPYRIGHT 0x4E
#define HEADER_CHIP 0x7B

#define FILTER_SUP 0x7A
#define FILTER_INF 0x20

#define M_Load(fp,address) fseek(fp,address,0)
struct nsf_file
{
	char chs_name[NAME_LIMIT];
	char org_name[NSF_NAME_LIMIT];
	char artist[NSF_NAME_LIMIT];
	char copyright[NSF_NAME_LIMIT];
	char extra[NSF_NAME_LIMIT];
}nsf[Max_Size];														//实际上不一定需要保存，可以实时输出

struct _finddata_t find;

char p[Max_Size];
extern void string_filter(char s[],char d[]);

#endif
