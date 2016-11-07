#include <stdio.h>
#include <pthread.h>
#include <assert.h>

pthread_mutex_t mutex;
pthread_mutexattr_t mutex_attrs; /* mutex attributes */

pthread_t thread_A, thread_B;

int global_var;

/* thread A routine */
void *thread_func_A(void *arg)
{
	char *message = arg;
	int ret;

	printf("%s \n", message);

	pthread_mutex_lock(&mutex);

	global_var = 5;

	/* release mutex lock */
	pthread_mutex_unlock(&mutex);

	return arg;	
}

/* thread B routine */
void *thread_func_B(void *arg)
{
	char *message = arg;
	int ret;

	printf("%s \n", message);

	ret = pthread_mutex_unlock(&mutex); /* trying to unlock mutex locked by thread A */
	if (ret != 0) {
		printf("Thread B failed to unlock mutex acquired by thread A \n");
	}

	pthread_mutex_lock(&mutex);
	global_var = 10;	
	
	pthread_mutex_unlock(&mutex);

	return arg;
}

int main(int argc, char *argv[])
{
	int ret;

	pthread_mutexattr_init(&mutex_attrs);
	pthread_mutexattr_settype(&mutex_attrs, PTHREAD_MUTEX_ERRORCHECK); /* enable error checking */
	pthread_mutex_init(&mutex, &mutex_attrs);

	/* create two threads */
	ret = pthread_create(&thread_A, NULL /* default attrs */, thread_func_A/*thread func */, "This is thread A");
	assert(ret == 0);

	ret = pthread_create(&thread_B, NULL /* default attrs */, thread_func_B/*thread func */, "This is thread B");
	assert(ret == 0);

	/* wait for threads to complete */
	ret = pthread_join(thread_A, NULL/* pointer to thread A return value */);
	assert(ret == 0);

	ret = pthread_join(thread_B, NULL); 
	assert(ret == 0);

	printf("Value of global variable: %d \n", global_var);

	pthread_mutexattr_destroy(&mutex_attrs);
	pthread_mutex_destroy(&mutex);
}
