/**Implement producer consumer across two processes using POSIX semaphores
and Mutexes.
Hints for communication across the processes.
Hint 1: Semaphore and Mutex must be in shared memory.
Hint 2: Mutex pshared attribute should be set to PTHREAD_PROCESS_SHARED.
Hint 3: Semaphore should be created with non-zero key (arg2 of sem_init()).
Hint 4: Use signal handlers to properly cleanup shared memory and
synchronization objects.**/


