/*************************************************"
"**	Description				**"
"**	version      		0.1		**"
"**	czDotThengShift+2gmailDotcom		**"
"**	lastest update 2013.12.25		**"
"*************************************************/

#include "md5.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

#define BUF_SIZE 1024

static md5_ctx_t md5_ctx;
static md5_ctx_t *md5_ctx_ptr = NULL;

md5_ctx_t *md5_new(void)
{
	if (!md5_ctx_ptr){
		md5_ctx_ptr = &md5_ctx;
	}	
	md5_init(&md5_ctx_ptr->md5_obj);	
	memset(md5_ctx_ptr->digest,'\0',16);
	memset(md5_ctx_ptr->hexdigest,'\0',32);
	return md5_ctx_ptr;
}

int md5_update(md5_ctx_t *md5_ctx,const unsigned char *buf,int length)
{
	//TODO: add length check here and log it 
	md5_append(&md5_ctx->md5_obj,buf,length);
return 0;
}

unsigned char * md5_digest(md5_ctx_t *md5_ctx)
{
	md5_state_t tmp;
	tmp = md5_ctx->md5_obj;
	md5_finish(&tmp,md5_ctx->digest);
	return md5_ctx->digest;
}

unsigned char * md5_hexdigest(md5_ctx_t *md5_ctx)
{
	md5_state_t tmp;
	tmp = md5_ctx->md5_obj;
	md5_finish(&tmp,md5_ctx->digest);
	int i ,j; 
        for(i=j=0; i<16; i++) {
                char c;
                c = (md5_ctx->digest[i] >> 4) & 0xf;
                c = (c>9) ? c+'a'-10 : c + '0';
                md5_ctx->hexdigest[j++] = c;
                c = (md5_ctx->digest[i] & 0xf);
                c = (c>9) ? c+'a'-10 : c + '0';
                md5_ctx->hexdigest[j++] = c;
        }   
	return md5_ctx->hexdigest;
}

unsigned char * md5_buf_digest(const unsigned char *buf,int length)
{
	if (!md5_ctx_ptr)
		md5_new();
	md5_update(md5_ctx_ptr,buf,length);
	return md5_digest(md5_ctx_ptr);
}

unsigned char * md5_buf_hexdigest(const unsigned char *buf,int length)
{
	if (!md5_ctx_ptr)
		md5_new();
	md5_update(md5_ctx_ptr,buf,length);
	return md5_hexdigest(md5_ctx_ptr);
}


unsigned char * md5_file_hexdigest(const char *filepath)
{
	char 	buf[BUF_SIZE];
	int  	len = BUF_SIZE;
	int  	fd;
	size_t 	rst;

	if (!md5_ctx_ptr)
		md5_new();
		
	fd = open(filepath,'r');
	if (fd<0){
		return NULL;	
	}

	while((rst=read(fd,buf,len))!=0){
		if (rst == -1){
			if (errno == EINTR){
				continue;	
			}else{
				return NULL;	
			}	
		}	
		
		md5_update(md5_ctx_ptr,buf,rst);	
	}


	return  md5_hexdigest(md5_ctx_ptr);
}


