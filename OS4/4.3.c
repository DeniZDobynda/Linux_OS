#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
int main()
{
int *array;
int shmid;
int new = 1;
char pathname[]="4.1a.c";
key_t key;
if((key=ftok(pathname,0)) < 0){
printf("Can\'t generate key\n");
exit(-1);
}
if((shmid=shmget(key,3*sizeof(int),0666|IPC_CREAT|IPC_EXCL))<0){
if(errno!=EEXIST){
printf("Can\'t create shared memory\n");
exit(-1);
}else{
if((shmid=shmget(key,3*sizeof(int),0))<0){
printf("Can\'t find shared memory\n");
exit(-1);
}
new = 0;
}
}
if((array=(int*)shmat(shmid,NULL,0))==(int*)(-1)){
printf("Can't attach shared memory\n");
exit(-1);
}
if(new){
array[0]=0;array[1]=1;array[2]=2;
printf("Shared memory created successfully\n");
}else{
printf(" %d %d %d\n", array[0], array[1], array[2]);
if(shmctl(shmid, IPC_RMID, NULL)==0){
printf("Shared memory removed successfully\n");
}
}

if(shmdt(array)<0){
printf("Can't detach shared memory\n");
exit(-1);
}
return 0;
}
