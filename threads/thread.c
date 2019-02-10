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
};

enum{
	ASSIGNED =1,
	AVAILABLE = 0,
};

struct thread {
	Tid threadID;
	int state;
	ucontext_t context;
	void *stackAddress;
};
typedef struct thread thread;

struct queueNode{
	struct thread *threadData;
	struct queueNode *next;
};
typedef struct queueNode queueNode;

struct threadQueue{
	queueNode *head;
};
typedef struct threadQueue threadQueue;

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
	
      	if(q = READY){
		queueNode *searchNode = readyQueue->head;
		while(searchNode != NULL){
			if(searchNode->threadData->threadID == TID)
				return 1;
			searchNode = searchNode->next;
		}
		//Unsuccessful, thread with given Tid not found in queue
		return 0;
	}
	else if(q = EXIT){
		queueNode *searchNode = exitQueue->head;
		while(searchNode != NULL){
			if(searchNode->threadData->threadID == TID)
				return 1;
			searchNode = searchNode->next;	
		}
		//Unsuccessful, thread with given Tid not found in queue
		return 0;
	}
}

//Find thread with Tid = TID and extract the data from the node
int extract(int q, Tid TID, thread *extraction)
{
	if(q = READY){
		queueNode *extractNode = readyQueue->head;
		while(extractNode != NULL){
			
		}
	}
	else if(q = EXIT){

	}
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

void thread_stub(void (*thread_main)(void *), void *arg)
{
	Tid ret;
	thread_main(arg);
	ret = thread_exit();
	//we should only get here if we are the last thread
	assert(ret == THREAD_NONE);
	//all threads are done, so process should exit
	exit(0);
}

Tid
thread_create(void (*fn) (void *), void *parg)
{
	return THREAD_FAILED;
	thread *temp = (thread *)malloc(sizeof(thread));
	if(temp == NULL){
		return THREAD_NOMEMORY;
	}

	//Have memory for thread, find available thread ID	
	for(int i=1;tidArray[i] == 1;i++){
		if(i==THREAD_MAX_THREADS)
			return THREAD_NOMORE;
	}
	temp->thread_id = i;
	tidArray[i]=1;

	//Initialize temp->context, then update temp context
	getcontext(&temp->context);
	
	temp->context.uc_mcontext.gregs[REG_RIP] = (unsigned long) &thread_stub;
	temp->context.uc_mcontext.gregs[REG_RDI} = (unsigned long) fn;
	temp->context.uc_mcontext.gregs[REG_RSI] = (unsigned long) parg;
	
	temp->state = READY;

	void *stackPointer;
	stackPointer = malloc(THREAD_MIN_STACK);
	if(stackPointer == NULL){
		free(temp);
		return THREAD_NOMEMORY;
	}
	
	temp->context.uc_stack.ss_sp = stackPointer;
	temp->context.uc_mcontext.gregs[REG_RSP] = (unsigned long)stackPointer + THREAD_MIN_STACK - 8;
	temp->context.uc_stack.ss_size = THREAD_MIN_STACK - 8;
	temp->stackAddress = stackPointer;
	
	queueNode *newThread = (queueNode *)malloc(sizeof(queueNode));
	queueNode->threadData = temp;
	appendQueue(READY, newThread);
	return temp->threadID;
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
			extract(READY, Tid, &replacementThread);
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
