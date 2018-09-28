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

#if 1   

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXSIZE 10

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