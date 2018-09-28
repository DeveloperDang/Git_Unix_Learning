#if 0
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void print_message_function (void *ptr);

int main()
{
    int tmp1, tmp2;
    void *retval;
    pthread_t thread1, thread2;
    char *message1 = "thread1";
    char *message2 = "thread2";

    int ret_thrd1, ret_thrd2;

    ret_thrd1 = pthread_create(&thread1, NULL, (void *)&print_message_function, (void *) message1);
    ret_thrd2 = pthread_create(&thread2, NULL, (void *)&print_message_function, (void *) message2);

    // �̴߳����ɹ�������0,ʧ�ܷ���ʧ�ܺ�
    if (ret_thrd1 != 0) {
        printf("�߳�1����ʧ��\n");
    } else {
        printf("thread 1 success\n");
    }

    if (ret_thrd2 != 0) {
        printf("�߳�2����ʧ��\n");
    } else {
        printf("thread 2 success\n");
    }

    //ͬ����pthread_join�ķ���ֵ�ɹ�Ϊ0
    tmp1 = pthread_join(thread1, &retval);
    printf("thread1 return value(retval) is %d\n", (int)retval);
    printf("thread1 return value(tmp) is %d\n", tmp1);
    if (tmp1 != 0) {
        printf("cannot join with thread1\n");
    }
    printf("thread1 end\n");

    tmp2 = pthread_join(thread1, &retval);
    printf("thread2 return value(retval) is %d\n", (int)retval);
    printf("thread2 return value(tmp) is %d\n", tmp1);
    if (tmp2 != 0) {
        printf("cannot join with thread2\n");
    }
    printf("thread2 end\n");

}

void print_message_function( void *ptr ) {
    int i = 0;
    for (i; i<5; i++) {
        printf("%s:%d\n", (char *)ptr, i);
    }
}

#endif

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void print_message_function (void *ptr);

int main()
{
    int tmp1, tmp2;
    void *retval;
    pthread_t thread1, thread2;
    char *message1 = "thread1";
    char *message2 = "thread2";

    int ret_thrd1, ret_thrd2;

    ret_thrd1 = pthread_create(&thread1, NULL, (void *)&print_message_function, (void *) message1);
    ret_thrd2 = pthread_create(&thread2, NULL, (void *)&print_message_function, (void *) message2);

    // �̴߳����ɹ�������0,ʧ�ܷ���ʧ�ܺ�
    if (ret_thrd1 != 0) {
        printf("�߳�1����ʧ��\n");
    } else {
        printf("thread 1 success\n");
    }

    if (ret_thrd2 != 0) {
        printf("�߳�2����ʧ��\n");
    } else {
        printf("thread 2 success\n");
    }

    pthread_detach(thread1);
    printf("thread1 end\n");
    
		pthread_detach(thread2);
    printf("thread2 end\n");
	  return 0;
}

void print_message_function( void *ptr ) {
    int i = 0;
    for (i; i<5; i++) {
        printf("%s:%d\n", (char *)ptr, i);
    }
    sleep(3);
}

#endif

#if 0

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sharedi = 0;
void increse_num(void);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    int ret;
    pthread_t thrd1, thrd2, thrd3;

    ret = pthread_create(&thrd1, NULL, (void *)increse_num, NULL);
    ret = pthread_create(&thrd2, NULL, (void *)increse_num, NULL);
    ret = pthread_create(&thrd3, NULL, (void *)increse_num, NULL);

    pthread_join(thrd1, NULL);
    pthread_join(thrd2, NULL);
    pthread_join(thrd3, NULL);

    printf("sharedi = %d\n", sharedi);

    return 0;

}

void increse_num(void) {
    long i,tmp;
    for(i=0; i<=200000; i++) {
    	 pthread_mutex_lock(&mutex);
        tmp = sharedi;
        tmp = tmp + 1;
        sharedi = tmp;
        pthread_mutex_unlock(&mutex);
    }
}


#endif

#if 0

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXSIZE 1000000

int stack[MAXSIZE];
int size = 0;
sem_t sem;

// ������
void provide_data(void) {
    int i;
    for (i=0; i< MAXSIZE; i++) {
        stack[i] = i;
        sem_post(&sem); //Ϊ�ź�����1
        printf("post:%d\n",i);
    }
}

// ������
void handle_data(void) {
    int i = 0;
    printf("data\n");
    while(1){//((i = size++) < MAXSIZE) {
        sem_wait(&sem);
        printf("Multi: %d X %d = %d\n", stack[i], stack[i], stack[i]*stack[i]);
        sleep(1);
    }
}

int main(void) {

    pthread_t provider, handler;

    sem_init(&sem, 0,0); //�ź�����ʼ��
    pthread_create(&provider, NULL, (void *)handle_data, NULL);
    pthread_create(&handler, NULL, (void *)provide_data, NULL);
    pthread_join(provider, NULL);
    pthread_join(handler, NULL);
    sem_destroy(&sem); //�����ź���

    return 0;
}


#endif

#if 0
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 10

sem_t sem;

void funProducer()
{
	int i;
	//for (i = 0; i < SIZE; i++)
	for(;;)
	{
		sem_post(&sem);	        //��ʱ�ظ��ź�����1����������ź���Ϊ0������߳�ѭ�����ź���һֱ���ӵ�SIZE-1
	}	
}

void funConsumer()
{
	int i = 0; 
	while(i < SIZE)         //whileѭ���õ�Ŀ���ǵ�semΪ0�������߲�����ʱ�����ڽ���sem_wait����Ȼ�̻߳������������������̲����˳�
	{
		sem_wait(&sem);       // ���sem��0�Ļ�����ʱsem_wait��������״̬�����sem�Ǵ���0�Ļ�����ִ����������
		printf("%d * %d = %d\n", i, i, i * i);
		i++;	
		sleep(1);
	}
	while(1)               //����д���ᵼ��semΪ0���������߲�����֮�󣬵��������߳������������޷��˳�
	{
		sem_wait(&sem);       // ���sem��0�Ļ�����ʱsem_wait��������״̬�����sem�Ǵ���0�Ļ�����ִ����������
		printf("2%d * %d = %d\n", i, i, i * i);
		i++;	
		sleep(1);
		
	}
}

int main(void)
{
	pthread_t producer, consumer;    //�߳�id
	sem_init(&sem, 0, 0);  //���»��ź���
	pthread_create(&producer, NULL, (void *)&funProducer, NULL);   //�����߳�1	
	pthread_create(&consumer, NULL, (void *)&funConsumer, NULL);   //�����߳�2
	pthread_join(producer, NULL);                           //�ȴ��߳�1����������
	pthread_join(consumer, NULL);                           //�ȴ��߳�2����������
	sem_destroy(&sem);                                 //�����ź���
	return 0;
}

#endif


#if 1
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  
#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>

int index = 1;

pthread_mutex_t lock;
pthread_cond_t cond;

void* fun1(void* p)
{
    while (index < 50)
    {
        pthread_mutex_lock(&lock);    
        index++;
        printf("In fun1 : %d\n",index);
        pthread_cond_signal(&cond);//���б仯��ʹ��signal֪ͨwait����
        pthread_mutex_unlock(&lock);
        usleep(0.1);
    }
}

void* fun2(void* p)
{
    while (index < 50)
    {       
        pthread_mutex_lock(&lock);    
        index++;
        printf("In fun2 : %d\n",index);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
        usleep(0.1);
    }
}

void* fun3(void*p)
{
    int i=0;
    while (i < 70)
    {
         pthread_mutex_lock(&lock);
         while ( index % 3 != 0)
         {
             pthread_cond_wait(&cond, &lock);//�������˻��������������������ʵĻ���wait���ͷ�����������ִ�С����仯���������ʣ���ֱ�ӻ������
         }

         printf("%d\n",index/3);

         i++;
         pthread_mutex_unlock(&lock);
         usleep(0.1);
    }
}

int main(){

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t tid1,tid2,tid3;
    pthread_create(&tid1, NULL, fun1, NULL);
    pthread_create(&tid2, NULL, fun2, NULL);
    pthread_create(&tid3, NULL, fun3, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    return 0;
}



#endif