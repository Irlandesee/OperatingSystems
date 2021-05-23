#include <stdio.h>
#include <pthread.h>

void* PrintHello(void* data){
	int my_data = (int) data; //data received by thread

	pthread_detach(pthread_self());
	printf("Hello from new thread - got %d\n", my_data);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]){
	int rc; //return value
	pthread_t thread_id; //thread id ~ just an integer
	int t = 11; //data passed to the new thread

	rc = pthread_create(&thread_id, NULL, PrintHello, (void*)t);
	if(rc){
		printf("\nError: return code from pthread is %d\n", rc);
		return -1;
	}
	printf("\nMain Thread: %u\n", pthread_self());
	printf("\nCreated new Thread: %u\n", thread_id);
	pthread_exit(NULL);
	return 0;
}