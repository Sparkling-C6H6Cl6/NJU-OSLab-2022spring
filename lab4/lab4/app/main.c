#include "lib.h"
#include "types.h"
#define N 5





int uEntry(void) {

	// 测试scanf	
	int dec = 0;
	int hex = 0;
	char str[6];
	char cha = 0;
	int ret = 0;
	while(1) {
		printf("Input:\" Test %%c Test %%6s %%d %%x\"\n");
		ret = scanf(" Test %c Test %6s %d %x", &cha, str, &dec, &hex);
		printf("Ret: %d; %c, %s, %d, %x.\n", ret, cha, str, dec, hex);
		if (ret == 4) {
			break;
		}
	}
	
	// 测试信号量
	int i = 4;
	sem_t sem;
	printf("Father Process: Semaphore Initializing.\n");
	ret = sem_init(&sem, 0);
	if (ret == -1) {
		printf("Father Process: Semaphore Initializing Failed.\n");
		exit();
	}

	ret = fork();
	if (ret == 0) {
		while(i != 0) {
			i --;
			printf("Child Process: Semaphore Waiting.\n");
			sem_wait(&sem);
			printf("Child Process: In Critical Area.\n");
		}
		printf("Child Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}
	else if (ret != -1) {
		while(i != 0) {
			i--;
			printf("Father Process: Sleeping.\n");
			sleep(128);
			printf("Father Process: Semaphore Posting.\n");
			sem_post(&sem);
		}
		printf("Father Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}

	// For lab4.3
	// TODO: You need to design and test the philosopher problem.
	// Note that you can create your own functions.
	// Requirements are demonstrated in the guide.
	
	//哲学家
	int ret = 0;
	sem_t mutex, semFork[N];
	ret = sem_init(&mutex, N - 1);
	if(ret == -1) {
		return 0;
	}
	for (int i = 0;i < N; i++) {
		sem_init(semFork + i, 1);
	}
	int pid = 0;
	printf("Philosopher %d: Init\n", pid);
	for (int i = 1; i < N; i++) {
		ret = fork();
		if (ret == 0) {
			pid = i;
			printf("Philosopher %d: Init\n", pid);
			break;
		}
	}
	while(1) {
		printf("Philosopher %d: Thinking\n", pid);
		sleep(128);
		sem_wait(&mutex);
		sem_wait(&semFork[pid % N]);
		sem_wait(&semFork[(pid + 1) % N]);
		sem_post(&mutex);
		printf("Philosopher %d: Eating\n", pid);
		sleep(128);
		sem_post(&semFork[pid % N]);
		sem_post(&semFork[(pid + 1) % N]);
	}

	//生产者消费者问题
	int ret = 0;
	int isConsumer = 1;
	sem_t inBuffer, emptyBuffer, mutexIn;
	if (sem_init(&inBuffer, 0) == -1
		|| sem_init(&emptyBuffer,10) == -1
		|| sem_init(&mutexIn, 1) == -1) {
		return 0;
	}
	int pid = 0;
	for (int i = 1; i < N; i++) {
		ret = fork();
		if (ret == 0) {
			pid = i;
			isConsumer = 0;
			break;
		}
	}
	if (isConsumer) {
		while (1) {
			sem_wait(&inBuffer);
			printf("Consumer : Consumed\n");
			sem_post(&emptyBuffer);
			sleep(128);
		}
	}
	else {
		while (1) {
			sem_wait(&emptyBuffer);
			sem_wait(&mutexIn);
			printf("Producer %d: Produced\n", pid);
			sleep(128);
			sem_post(&mutexIn);
			sem_post(&inBuffer);
			sleep(128);
		}
	}

	//读者写者问题
	

	exit(0);
	return 0;
}
