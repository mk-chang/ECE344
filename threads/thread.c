#include <assert.h>
#include <stdlib.h>
#include <ucontext.h>
#include "thread.h"
#include "interrupt.h"

/* This is the wait queue structure */
struct wait_queue {
	/* ... Fill this in Lab 3 ... */
};

/* This is the thread control block */
enum{
	READY=0; 
	RUNNING=1;
	EXIT=2;	
}

enum{
	ASSIGNED =1;
	AVAILABLE = 0;
}

struct thread {
	Tid threadID;
	int state;
	ucontext_t context;
};
typedef thread thread;

struct queueNode{
	struct thread *threadBlock;
	struct queueNode *next;
}
typedef queueNode queueNode;

struct threadQueue{
	queueNode *head;
}
typedef threadQueue threadQueue;

//Global Variables
int tidArray[THREAD_MAX_THREADS]; 
threadQueue *readyQueue;
threadQueue *exitQueue;
thread *runningThread;

//Helper Functions
int find(Tid TID,int q)
{
	//if q=READY,find in readyQueue
	//if q=EXIT, find in exitQueue
	  
	return 1;

	//if unsuccesfull
	return 0;
}

int find_and_extract(Tid TID,thread *extraction)
{

}


//Cooperative Threads API
void
thread_init(void)
{
	/* your optional code here */
	readyQueue = (threadQueue *)malloc(sizeof(threadQueue));
	exitQueue = (threadQueue *)malloc(sizeof(threadQueue));
	for(int i=0;i<THREAD_MAX_THREADS;i++)
		tidArray[i]=0;
	
	//set kernel thread
	thread *kernelThread = (thread*)malloc(sizeof(thread));
	kernelThread->threadID = 0;
	kernelThread->state = RUNNING;
       	tidArray[0] = ASSIGNED;	
	
	//initialize running thread
	runningThread = kernelThread;	
}

Tid
thread_id()
{
	return runningThread->threadID;
}

Tid
thread_create(void (*fn) (void *), void *parg)
{
	TBD();
	return THREAD_FAILED;
}

Tid
thread_yield(Tid want_tid)
{
	//Find wanted_tid in readyQueue 
	if(find(wanted_tid)=1){
		thread *
		thread *replacementThread = find_and_extract();
	{

	//If wanted_tid not in readyQueue
	else
		return THREAD_FAILED;
}

Tid
thread_exit()
{
	TBD();
	return THREAD_FAILED;
}

Tid
thread_kill(Tid tid)
{
	TBD();
	return THREAD_FAILED;
}

/*******************************************************************
 * Important: The rest of the code should be implemented in Lab 3. *
 *******************************************************************/

/* make sure to fill the wait_queue structure defined above */
struct wait_queue *
wait_queue_create()
{
	struct wait_queue *wq;

	wq = malloc(sizeof(struct wait_queue));
	assert(wq);

	TBD();

	return wq;
}

void
wait_queue_destroy(struct wait_queue *wq)
{
	TBD();
	free(wq);
}

Tid
thread_sleep(struct wait_queue *queue)
{
	TBD();
	return THREAD_FAILED;
}

/* when the 'all' parameter is 1, wakeup all threads waiting in the queue.
 * returns whether a thread was woken up on not. */
int
thread_wakeup(struct wait_queue *queue, int all)
{
	TBD();
	return 0;
}

/* suspend current thread until Thread tid exits */
Tid
thread_wait(Tid tid)
{
	TBD();
	return 0;
}

struct lock {
	/* ... Fill this in ... */
};

struct lock *
lock_create()
{
	struct lock *lock;

	lock = malloc(sizeof(struct lock));
	assert(lock);

	TBD();

	return lock;
}

void
lock_destroy(struct lock *lock)
{
	assert(lock != NULL);

	TBD();

	free(lock);
}

void
lock_acquire(struct lock *lock)
{
	assert(lock != NULL);

	TBD();
}

void
lock_release(struct lock *lock)
{
	assert(lock != NULL);

	TBD();
}

struct cv {
	/* ... Fill this in ... */
};

struct cv *
cv_create()
{
	struct cv *cv;

	cv = malloc(sizeof(struct cv));
	assert(cv);

	TBD();

	return cv;
}

void
cv_destroy(struct cv *cv)
{
	assert(cv != NULL);

	TBD();

	free(cv);
}

void
cv_wait(struct cv *cv, struct lock *lock)
{
	assert(cv != NULL);
	assert(lock != NULL);

	TBD();
}

void
cv_signal(struct cv *cv, struct lock *lock)
{
	assert(cv != NULL);
	assert(lock != NULL);

	TBD();
}

void
cv_broadcast(struct cv *cv, struct lock *lock)
{
	assert(cv != NULL);
	assert(lock != NULL);

	TBD();
}
