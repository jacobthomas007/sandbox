#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#define MAX_ITEM 5
typedef struct circularque_s
{
	int head;
	int tail;
	int validItems; // will tell the total elements in the buffer
	int data[MAX_ITEM];
	pthread_mutex_t lock;
}cmdque;

/*functions to be implemented
	1. initialization of structure data
	2. isEMPTY
	3. isFULL
	4. push
	5. pop
	6. display 
*/

cmdque cmd_buff;
void cmd_init(cmdque *cmd_buff)
{
	int i;
	cmd_buff->head=0;
	cmd_buff->tail=0;
	cmd_buff->validItems=0;
	for(i=0;i<MAX_ITEM;i++)
	cmd_buff->data[i]=0;
	if(pthread_mutex_init(&cmd_buff->lock,NULL)!=0)
	{
		printf("Mutex failed\n");
		exit(1);
	}
	printf("Initialization completed..\n");
}
int isEMPTY(cmdque *cmd_buff)
{
	if(cmd_buff->validItems==0)
	{
		printf("CmdQue is empty\n");
		return 1;
	}
	else
	return 0;
}
int isFULL(cmdque *cmd_buff)
{
	if(cmd_buff->validItems>=MAX_ITEM)
	{
		printf("CmdQue is full\n");
		return 1;
	}
	else
	return 0;
}
void cmd_push(cmdque *cmd_buff,int data )
{
	if(isFULL(cmd_buff))
	{
		printf("You cannot add items..\n");
	}
	else
	{
		cmd_buff->validItems++;
		cmd_buff->data[cmd_buff->tail] = data;
		cmd_buff->tail=(cmd_buff->tail + 1)%MAX_ITEM;
	}
}
void cmd_pop(cmdque *cmd_buff,int *data)
{
	if(isEMPTY(cmd_buff))
	{	
		printf("No elements to remove\n");
		*data = -1;
	}
	else
	{
		*data=cmd_buff->data[cmd_buff->head];
		cmd_buff->head=(cmd_buff->head + 1)%MAX_ITEM;
		cmd_buff->validItems--;
	}
}
void display_cmdque(cmdque *cmd_buff)
{	
	int front,rear,items,i=0;
	front = cmd_buff->head;
	rear = cmd_buff->tail;
	items = cmd_buff->validItems;
//	for(i=cmd_buff->head;i<=cmd_buff->validItems;i++)
	while(items>0)
	{
		
		printf("head =%d,tail =%d,data=%d front=%d items=%d\n",cmd_buff->head,cmd_buff->tail,cmd_buff->data[front],front,cmd_buff->validItems);
		front++;
		front=front%MAX_ITEM;
		items--;
	}
}
void *tid_push(void *arg)
{
	cmdque *tmp;
	tmp=(cmdque *)arg;
	printf("Inside the tid_push\n");
//	int i=MAX_ITEM;
	int i=0;
	//	printf("tmp-lock =%p\n",&tmp->lock);
	//while(i!=0)
	while(1)
	{
		pthread_mutex_lock(&tmp->lock);
		cmd_push((cmdque *)arg,i);
		pthread_mutex_unlock(&tmp->lock);
	printf("pushed value = %d \n",i);
		i++;
	sleep(10);
	}
//	display_cmdque((cmdque *)arg);
}
void *tid_pop(void *arg)
{
	int i=3;
	int rem_value=0;
	cmdque *tmp;
	tmp=(cmdque *)arg;
	printf("Inside the tid_pop\n");
	//while(i!=0){
	while(1){
	pthread_mutex_lock(&tmp->lock);
	cmd_pop((cmdque *)arg,&rem_value);
	pthread_mutex_unlock(&tmp->lock);
	sleep(1);
	if(rem_value==-1)
	{
	}
	else
	printf("poped value = %d \n",rem_value);
	//i--;
	}
}
int main()
{
	int rem_value;
	pthread_t ntid[3];
	int tid1,tid2;
	//cmd_buff=(cmd_buff *)malloc(sizeof(cmdque));	
	cmd_init(&cmd_buff);
	printf("cmd_buff->lock =%p\n",&cmd_buff.lock);
	tid1=pthread_create(&(ntid[0]),NULL,tid_push,&cmd_buff);
	if(tid1!=0)
	{
		printf("Cant create thread\n");
		return 0;
	}
	tid2=pthread_create(&(ntid[1]),NULL,tid_pop,&cmd_buff);
	if(tid2!=0)
	{
		printf("Cant create thread\n");
		return 0;
	}
//	cmd_push(&cmd_buff,2);
/*	cmd_push(&cmd_buff,1);
	cmd_push(&cmd_buff,2);
	cmd_push(&cmd_buff,3);
//	cmd_push(&cmd_buff,4);
//	cmd_push(&cmd_buff,5);
	cmd_push(&cmd_buff,6);
	cmd_pop(&cmd_buff,&rem_value);
	printf("poped value %d\n", rem_value);
	cmd_push(&cmd_buff,7);
	printf("total element in the buffer %d\n",cmd_buff.validItems);*/
	//display_cmdque(&cmd_buff);
	pthread_join(ntid[1],NULL);
	pthread_join(ntid[0],NULL);
	display_cmdque(&cmd_buff);
	//pthread_exit(NULL);
return 0;
}
