#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define MAX_LEN 5
#define MAX_SIZE 4
#define INIT 0
typedef struct
{
	unsigned char buffer[MAX_SIZE];
	int head;
	int tail;
	int maxlen;
}ring_buff;

void cmd_buff_init(ring_buff *cmd_init);
int isFULL(ring_buff *cmd_buffer);
void cmd_buff_push(ring_buff *cmd_push,unsigned data);
void display(ring_buff *cmd_buffer);
void cmd_buff_pop(ring_buff *cmd_pop);

	static int stopper=1; 
int main(int argc,char *argv)
{	
	ring_buff *cmd_buff;
	cmd_buff = (ring_buff *)malloc(sizeof(ring_buff));
	cmd_buff_init(cmd_buff);
	cmd_buff_push(cmd_buff,1);	
	cmd_buff_push(cmd_buff,2);	
	cmd_buff_push(cmd_buff,3);	
	cmd_buff_push(cmd_buff,4);
//	cmd_buff_push(cmd_buff,5);
//	cmd_buff_push(cmd_buff,5);
	cmd_buff_pop(cmd_buff);
	cmd_buff_push(cmd_buff,7);
	printf("HEAD=%d\n",cmd_buff->head);
/*	cmd_buff_pop(cmd_buff);
	cmd_buff_push(cmd_buff,7);
	cmd_buff_pop(cmd_buff);
	cmd_buff_push(cmd_buff,8);*/
//	cmd_buff_pop(cmd_buff);
//	cmd_buff_push(cmd_buff,8);
//	printf("head=%d,tail=%d\n",cmd_buff->head,cmd_buff->tail);	
	display(cmd_buff);
	return 0;
}
void cmd_buff_init(ring_buff *cmd_init)
{
	cmd_init->maxlen = MAX_LEN;
	cmd_init->head=INIT;
	cmd_init->tail=INIT;
}
void cmd_buff_push(ring_buff *cmd_push,unsigned data)
{
	//check if the circullar buffer is full
	if(isFULL(cmd_push)){
//		printf("head=%d,tail=%d\n",cmd_push->head,cmd_push->tail);	
		printf("cmd_buff is full\n");
		printf("inside isFULL head=%d,tail=%d,cmd_push->buffer=%d\n",cmd_push->head,cmd_push->tail,cmd_push->buffer[cmd_push->tail]);	
		if(stopper == 1){ //have to find a different logic its a temop fix
		cmd_push->buffer[cmd_push->tail]=data;
// if changed would effect the if full effect		cmd_push->tail=((cmd_push->tail)+1)%MAX_LEN;
		stopper++;
		}
		}
	else{
		cmd_push->buffer[cmd_push->tail]=data;
		printf("head=%d,tail=%d,cmd_push->buffer=%d\n",cmd_push->head,cmd_push->tail,cmd_push->buffer[cmd_push->tail]);	
		cmd_push->tail=((cmd_push->tail)+1)%MAX_LEN;
//		stopper=1;
	}	
	// if full then do .>>>
	// if not full then insert tio the buffer
	
	//printf("%d\n",cmd_push->buffer[cmd_push->head -1]);
}
void cmd_buff_pop(ring_buff *cmd_pop)
{
	int temp1,temp2;
	if(isEMPTY(cmd_pop)){
	printf("Buffer is empty \n");
	}
	else{
	temp1=cmd_pop->tail +1;
	if(temp1>MAX_LEN)	
	temp2=(cmd_pop->tail +1)%MAX_LEN;
	else
	temp2=cmd_pop->tail;
	printf("temp1=%d,temp2=%d\n",temp1,temp2);
	
	if(temp2 == (cmd_pop->head)){ //if the buffer is full
	printf("inside pop cmp_pop->tail+1=%d,cmd_pop->head=%d \n",(cmd_pop->tail+1)%MAX_LEN,cmd_pop->head);
	cmd_pop->tail=((cmd_pop->tail)+1)%MAX_LEN;// doubtttttttttt  
	}
	printf("inside pop head before pop increment= %d\n",cmd_pop->head);
	cmd_pop->head=(cmd_pop->head +1)%MAX_LEN;
	printf("inside pop head get incre= %d\n",cmd_pop->head);
	stopper=1;
	}
	
}
int isFULL(ring_buff *cmd_buffer)
{
	int temp;
	temp=(cmd_buffer->tail +1)%MAX_LEN;
	printf("temp=%d,cmd_buffer->head=%d\n",temp,cmd_buffer->head);
	if(temp==cmd_buffer->head)
	return 1;
	else
	return 0;
}
int isEMPTY(ring_buff *cmd_buffer)
{
	int temp;
	if(cmd_buffer->head == cmd_buffer->tail){
		return 1;
	}
	else
	return 0;
}
void display(ring_buff *cmd_buffer)
{
	int temp=cmd_buffer->head;
	int i,j;
	//for(i=cmd_buffer->head;i!=(cmd_buffer->tail);i++){
	for(i=0;i<= MAX_SIZE;i++){
	printf("head=%d, tail=%d , i=%d,%d\n",cmd_buffer->head,cmd_buffer->tail,i,cmd_buffer->buffer[i]);
	i=i%MAX_LEN;
	}
}
