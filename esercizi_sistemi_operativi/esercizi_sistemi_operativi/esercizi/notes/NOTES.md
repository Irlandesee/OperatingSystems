#CreateDestroy example
-> pthread_t thread_id: Integer used to identify the thread in the system.
-> pthread_create() return 0 on success, non-zero value on failure.
	with 4 arguments: 
	&thread_id -> It is a pointer to thread_id to supply the program with the thread's identifier.
	NULL -> Sets attributes for the new thread, supplying NULL tells the pthread_create() to use the default values.
	PrintHello -> it accepts a void * as an argument and also returns a void * as a return value. It is possible to use a void * to pass an arbitrary piece of data to the new thread, also the new thread can return an arbitrary piece of data when it finishes.
	(void* )t -> arbitrary argument. If the thread does not require any new data, the fourth argument is set to NULL.
-> after pthread_create() returns, the program will consist of 2 threads: The main and PrintHello(), 2 threads that execute in parallel.
-> pthread_create() causes the current thread to exit and free any thread-specific resources it is taking.