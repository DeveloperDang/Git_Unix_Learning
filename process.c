#if 0
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

// ÓÃÓÚ´´½¨Ò»¸öÎ¨Ò»µÄkey
#define MSG_FILE "/etc/passwd"

// ÏûÏ¢½á¹¹
struct msg_form {
    long mtype;
    char mtext[256];
};

int main()
{
    int msqid;
    key_t key;
    struct msg_form msg;
    
    // »ñÈ¡keyÖµ
    if((key = ftok(MSG_FILE,'z')) < 0)
    {
        perror("ftok error");
        exit(1);
    }

    // ´òÓ¡keyÖµ
    printf("Message Queue - Server key is: %d.\n", key);

    // ´´½¨ÏûÏ¢¶ÓÁÐ
    if ((msqid = msgget(key, IPC_CREAT|0777)) == -1)
    {
        perror("msgget error");
        exit(1);
    }

    // ´òÓ¡ÏûÏ¢¶ÓÁÐID¼°½ø³ÌID
    printf("My msqid is: %d.\n", msqid);
    printf("My pid is: %d.\n", getpid());

    // Ñ­»·¶ÁÈ¡ÏûÏ¢
    for(;;) 
    {
        msgrcv(msqid, &msg, 256, 888, 0);// ·µ»ØÀàÐÍÎª888µÄµÚÒ»¸öÏûÏ¢
        printf("Server: receive msg.mtext is: %s.\n", msg.mtext);
        printf("Server: receive msg.mtype is: %d.\n", msg.mtype);

        msg.mtype = 999; // ¿Í»§¶Ë½ÓÊÕµÄÏûÏ¢ÀàÐÍ
        sprintf(msg.mtext, "hello, I'm server %d", getpid());
        msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
    }
    return 0;
}

#endif


#if 0
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

// ÓÃÓÚ´´½¨Ò»¸öÎ¨Ò»µÄkey
#define MSG_FILE "/etc/passwd"

// ÏûÏ¢½á¹¹
struct msg_form {
    long mtype;
    char mtext[256];
};

int main()
{
    int msqid;
    key_t key;
    struct msg_form msg;

    // »ñÈ¡keyÖµ
    if ((key = ftok(MSG_FILE, 'z')) < 0) 
    {
        perror("ftok error");
        exit(1);
    }

    // ´òÓ¡keyÖµ
    printf("Message Queue - Client key is: %d.\n", key);

    // ´ò¿ªÏûÏ¢¶ÓÁÐ
    if ((msqid = msgget(key, IPC_CREAT|0777)) == -1) 
    {
        perror("msgget error");
        exit(1);
    }

    // ´òÓ¡ÏûÏ¢¶ÓÁÐID¼°½ø³ÌID
    printf("My msqid is: %d.\n", msqid);
    printf("My pid is: %d.\n", getpid());

    // Ìí¼ÓÏûÏ¢£¬ÀàÐÍÎª888
    msg.mtype = 888;
    sprintf(msg.mtext, "hello, I'm client %d", getpid());
    msgsnd(msqid, &msg, sizeof(msg.mtext), 0);

    // ¶ÁÈ¡ÀàÐÍÎª777µÄÏûÏ¢
    msgrcv(msqid, &msg, 256, 999, 0);
    printf("Client: receive msg.mtext is: %s.\n", msg.mtext);
    printf("Client: receive msg.mtype is: %d.\n", msg.mtype);
    return 0;
}

#endif


#if 1

#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>

// ¿¿¿¿¿¿semctl¿¿¿
union semun
{
    int              val; /*for SETVAL*/
    struct semid_ds *buf;
    unsigned short  *array;
};

// ¿¿¿¿¿¿
int init_sem(int sem_id, int value)
{
    union semun tmp;
    tmp.val = value;
    if(semctl(sem_id, 0, SETVAL, tmp) == -1)
    {
        perror("Init Semaphore Error");
        return -1;
    }
    return 0;
}

// P¿¿:
//    ¿¿¿¿¿¿1¿¿¿¿¿¿¿¿¿¿¿-1 
//    ¿¿¿¿¿¿0¿¿¿¿¿¿¿
int sem_p(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0; /*¿¿*/
    sbuf.sem_op = -1; /*P¿¿*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)
    {
        perror("P operation Error");
        return -1;
    }
    return 0;
}

// V¿¿¿
//    ¿¿¿¿¿¿¿¿¿¿+1
//    ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
int sem_v(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0; /*¿¿*/
    sbuf.sem_op = 1;  /*V¿¿*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)
    {
        perror("V operation Error");
        return -1;
    }
    return 0;
}

// ¿¿¿¿¿¿
int del_sem(int sem_id)
{
    union semun tmp;
    if(semctl(sem_id, 0, IPC_RMID, tmp) == -1)
    {
        perror("Delete Semaphore Error");
        return -1;
    }
    return 0;
}


int main()
{
    int sem_id;  // ¿¿¿¿ID
    key_t key;  
    pid_t pid;

    // ¿¿key¿
    if((key = ftok(".", 'z')) < 0)
    {
        perror("ftok error");
        exit(1);
    }

    // ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
    if((sem_id = semget(key, 1, IPC_CREAT|0666)) == -1)
    {
        perror("semget error");
        exit(1);
    }

    // ¿¿¿¿¿¿¿¿0¿¿¿¿¿
    init_sem(sem_id, 0);

    if((pid = fork()) == -1)
        perror("Fork Error");
    else if(pid == 0) /*¿¿¿*/ 
    {
        sleep(2);
        printf("Process child: pid=%d\n", getpid());
        sem_v(sem_id);  /*¿¿¿¿*/
    }
    else  /*¿¿¿*/
    {
        sem_p(sem_id);   /*¿¿¿¿*/
        printf("Process father: pid=%d\n", getpid());
        sem_v(sem_id);   /*¿¿¿¿*/
        del_sem(sem_id); /*¿¿¿¿¿¿*/
    }
    return 0;
}

#endif
