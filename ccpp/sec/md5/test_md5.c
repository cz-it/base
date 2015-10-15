/*************************************************"
"**	Description				**"
"**	version      		0.1		**"
"**	czDotThengShift+2gmailDotcom		**"
"**	lastest update 2013.12.25		**"
"*************************************************/

#include "md5.h"

#include <stdio.h>

void print_degest(unsigned char *degest)
{
	int i;
	for (i=0;i<16;i++) {
		printf("%c",degest[i]);	
	}
	puts("\n");
}


void print_hexdegest(unsigned char *hexdegest)
{
	int i;
	for (i=0;i<32;i++) {
		printf("%c",hexdegest[i]);	
	}
	puts("\n");
}


int main(int argc,char *argv[])
{
/*
	md5_ctx_t *md5_ctx;
	md5_ctx = md5_new();
	md5_update(md5_ctx,"nimeiai",7);
	unsigned char *degest = md5_degest(md5_ctx);
	unsigned char *hexdegest = md5_hexdegest(md5_ctx);
	unsigned char *nimei = "nimei";
	unsigned char *hexdigest = md5_buf_hexdigest(nimei,5);
*/
	char *filename = "nimei";
	unsigned char *hexdigest = md5_file_hexdigest(filename);
	print_hexdegest(hexdigest);
return 0;
}
