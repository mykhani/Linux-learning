Mutex vs Semaphore (binary)
===========================
The main difference between mutex and a binary semaphore (with count 1) is that
in case of mutex, only a thread that acquires lock can unlock the mutex. If any other
thread tries to release that lock, it results in error. For verification,
see the attached test example. Note that mutex attribute should be set to
PTHREAD_MUTEX_ERRORCHECK to enable error checking in case a different thread tries
to unlock mutex.

* In case of binary semaphore, any thread can increment the semaphore count and result
in opening of the lock. 

* In normal (non binary semaphore), it allows a certain number of threads to access a
shared resource depending on semaphore count.

* Both semaphore and mutexes are atomic variables.
