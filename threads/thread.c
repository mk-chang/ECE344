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
	READY=0,
	RUNNING=1,
	EXIT=2,	
}

enum{
	ASSIGNED =1,
	AVAILABLE = 0,
}

struct thread {
	Tid threadID;
	int state;
	ucontext_t context;
};
typedef thread thread;

struct queueNode{
	struct thread *threadData;
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
//
//Find thread with Tid = TID in the given queue
int find(int q,Tid TID)
{
	//if q=READY,find in readyQueue
	//if q=EXIT, find in exitQueue
	  
	return 1;

	//if unsuccesfull
	return 0;
}

//Find thread with Tid = TID and extract the data from the node
int extract(Tid TID,thread *extraction)
{

}

//Extracting the first node in the queue
int extractFirst(int q, thread *extraction)
{

}

void appendQueue(int q, thread* append)
{

}

void clearQueue(int q){
	
}

//Cooperative Threads API
void
thread_init(void)
{
	/* your optional code here */
	readyQueue = (threadQueue *)malloc(sizeof(threadQueue));
	exitQueue = (threadQueue *)malloc(sizeof(threadQueue));
	for(int i=0;i<THREAD_MAX_THREADS;i++)
		tidArray[i]=AVAILABLE;
	
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
	//Checking if want_tid refers to a valid thread
	if(want_tid < -2 || want_tid > THREAD_MAX_THREADS)
		return THREAD_INVALID;
	else{
		if(want_tid == THREAD_ANY && readyQueue->head == NULL)
			return THREAD_NONE;
		if(want_tid >= 0 && tidArray[want_tid] = AVAILABLE)
			return THREAD_INVALID;
	}	

	//Check's passed, try and replace
	thread replacementThread; //might need to be pointer

	//If TID value is THREAD_ANY(-1), yield to first thread in readyQueue
	if(want_tid == THREAD_ANY){
		
		//store u_context of current thread
		getcontext(&runningThread->context);
		//add replaced thread to end of queue
		appendQueue(runningThread);
		//extract and update runningThread, setcontext of runningThread to new context
		extractFirst(READY, runningThread);
		setcontext(&runningThread->context);
		return runningThread->threadID;
	}

	else if(want_tid == THREAD_SELF){
		return runningThread->threadID;
	}

	else if(want_tid >= 0){
	//Find wanted_tid in readyQueue 
		if(find(READY,wanted_tid) == 1){
			getcontext(&runningThread->context);
			appendQueue(READY,runningThread);
			extract(Tid, &replacementThread);
			setcontext(&runningThread->context);
			
			return replacementThread->threadID;	
		}
	}
	//If wanted_tid not in readyQueue
	else
		return THREAD_INVALID;

	//clear exitqueue
	clearQueue(EXIT);
}

Tid
thread_exit()
{
	//Check if last thread
	if (readyQueue->head == NULL)
		return THREAD_NONE;
	else{
		//move current thread to exitQueue
		appendQueue(EXIT, runningThread);
		//yield to any thread
		thread_yield(THREAD_ANY);
	}
}

Tid
thread_kill(Tid tid)
{
	//Checking if want_tid refers to a valid thread
	if(want_tid < -2 || want_tid > THREAD_MAX_THREADS)
		return THREAD_INVALID;
	else{
		if(want_tid > 0 && tidArray[want_tid] = AVAILABLE)
			return THREAD_INVALID;
	}
	
	//Check passed
	if(find(READY,wanted_tid) == 1){
		thread replacementThread; //might need to be pointer

		appendQueue(runningThread);
		extract(Tid, &replacementThread);
		return repacementThread->threadID
	}	
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
