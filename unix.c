#if 0

#include <unistd.h>
#include <stdio.h> 
int main () 
{ 
	pid_t fpid; //fpid表示fork函数返回的值
	int count=0;
	fpid=fork(); 
	if (fpid < 0) 
		printf("error in fork!\n"); 
	else if (fpid == 0) {
		printf("i am the child process, my process id is %d\n, parent process is %d\n",getpid(), getppid()); 
		printf("我是爹的儿子\n");//对某些人来说中文看着更直白。
		count++;
	}
	else {
		printf("i am the parent process, my process id is %d\n,parent process is %d\n",getpid(), getppid()); 
		printf("我是孩子他爹\n");
		count++;
                sleep(1);
	}
	printf("统计结果是: %d\n",count);
	return 0;
}


#endif

#if 0
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	pid_t pid;
	int i;
	printf("maid.hn process %d\n", getpid());
	for (i = 0; i < 2 ;i++)
	{
		pid = fork();
		if(pid > 0)
		{
		    printf("Parent, loop %d, pid = %d\n", i, getpid());	
		}	else if(pid == 0)
		{
		    printf("Son, loop %d, pid = %d\n", i, getpid());		    
		}	
		  			
  }
  
  while(1){}
  return 0;    	
}

#endif

#if 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int my_daemon()
{
    int fd, i;
		pid_t pid;
		char *buf = "this is a output\n";
		pid = fork();
		if(pid > 0)
		{
			exit(0);
		} 
		setsid();
		chdir("/");
		umask(0);
		for(i = 0; i < getdtablesize(); i++)
		{
			close(i);	
		}
		
    while(1) {// 死循环表征它将一直运行
// 以读写方式打开"/tmp/daemon.log"，返回的文件描述符赋给fd
        if ((fd=open("/tmp/daemon.log",O_CREAT|O_WRONLY|O_APPEND,0600))<0) {
            printf("Open file error!\n");
            exit(1);
        }
        // 将buf写到fd中
        write(fd,buf,strlen(buf)+1);
        close(fd);
        sleep(10);
        printf("Never output!\n");
    }

		 
		       		
}

int main(void)
{
	my_daemon();
	return 0;	
}



#endif