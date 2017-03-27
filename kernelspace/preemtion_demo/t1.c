#include<stdio.h>
#include<unistd.h>
#include<pthread.h>


void *threadfn1(void *p)
{
	int r=0;
	puts("1");
	sleep(2);
	while(1){
		r++;
		printf("thread1 %d\n",r);
	}
	return NULL;
}

void *threadfn2(void *p)
{
	int r=0;
	puts("2");
	sleep(2);
	while(1){
		r++;
		printf("thread2 %d\n",r);
	}
	return NULL;
}


int main()
{
	pthread_t t1,t2,t3;
	
	pthread_attr_t attr1,attr2;
	
	struct sched_param param1,param2,param3;
	param1.sched_priority = 43;
//	pthread_setschedparam(pthread_self(),SCHED_FIFO,&param1);
  
	pthread_attr_init(&attr1);
	pthread_attr_setschedpolicy(&attr1, SCHED_RR);
	pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);	
	param2.sched_priority = 53;
	pthread_attr_setschedparam(&attr1, &param2);	
	pthread_create(&t1,&attr1,threadfn1,NULL);
	
	pthread_attr_init(&attr2);
	param3.sched_priority = 53;
	pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);	
	pthread_attr_setschedparam(&attr2, &param3);
	pthread_attr_setschedpolicy(&attr2, SCHED_RR);
	pthread_create(&t2,&attr2,threadfn2,NULL);
	

	puts("end main");
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}




