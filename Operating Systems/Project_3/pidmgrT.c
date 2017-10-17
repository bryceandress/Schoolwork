///////////////////////////////////////////////////////////////////////////
// 										Bryce Andress 								                     //
// 								CSC 343 Operating Systems					                     //
// 											Assignmnet 3                                     //
// 					Compiler: gcc -pthread pidmgrT.c -o pidmgrT -g               //
// 								September 14th  2017 							 										 //
// 	Log files were created by running ./pidmgrT > case.log               //
///////////////////////////////////////////////////////////////////////////
#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MIN_PID 0
#define MAX_PID 15
#define MAX_THREADS 10

struct allocate_pid_data {
	int *pid_list;
	int pid_counter;
	int pids_size;
	int pid_thread;
};

int thread_num = 0;

/*************************************************************************/
/* Function name: scan_map                    							             */
/* Description: Searches map for a pid that can be allocated             */
/* Return Value: Returns a PID that can be used. -1 if none available    */
/*************************************************************************/
int scan_map(struct allocate_pid_data *args)
{
	int counter = 0;
	int *pid_list = args->pid_list;
	while(counter <= MAX_PID)
	{
		// Check to see if there are any PIDs left
		if (pid_list[counter] == 0)
		{
			return counter;
		}
		counter++;
	}
	// If there are no PIDs left return -1
	return -1;
}

/*************************************************************************/
/* Function name: release_pid                    							           */
/* Description: Release a given PID                                      */
/* Return Value: Returns 0 if PID releases successfully -1 if it does not*/
/*************************************************************************/
void release_pid(struct allocate_pid_data *args, int release_pid, int thread)
{
	int local_thread = thread;
	if(release_pid >= 0 && release_pid <= MAX_PID)
	{
		printf("Thread %d: released %d\n", local_thread + 2200,release_pid+299);
		args->pid_list[release_pid] = 0;
		args->pids_size = args->pids_size - 1;
	}
}

/*************************************************************************/
/* Function name: allocate_pid                  							           */
/* Description: Allocates PID                                            */
/* Return Value: Allocated PID number or -1 if none available            */
/*************************************************************************/
void allocate_pid(struct allocate_pid_data *args, int thread)
{
	int local_thread = thread;
	int allocated = 1;
	int counter = args->pid_counter;
	while(allocated)
	{
		// Make sure the PID is range and make sure the PID already isn't in use
		if (counter <= MAX_PID && counter >= 0 && args->pid_list[counter] != 1)
		{
			args->pid_list[counter] = 1;
			args->pids_size = args->pids_size + 1;
			printf("Thread %d: Allocation Request ... allocated %d\n", local_thread+2200, counter+300);
			counter++;
			args->pid_counter = counter;
			allocated = 0;
		}
		// If one of the previous conditions is not met see if there are any PIDs left
		else
		{
			counter = scan_map(args);
			if (counter == -1)
			{
				printf("No PIDs to allocate\n");
				allocated = 0;
			}
		}
	}
}

/*************************************************************************/
/* Function name: allocator                							                 */
/* Description: start allocating and deallocating PIDs                   */
/* Return Value: none                                                    */
/*************************************************************************/
void *allocator(void *arg)
{
	int thread = thread_num;
	thread_num = thread_num + 1;
	struct allocate_pid_data *args = arg;
	int iterations = 0;
	int random = rand();
	int current;
	while(iterations < 5)
	{
		random = rand() % 5;
		sleep(random);
		allocate_pid(args, thread);
		current = args->pid_counter;
		random = rand() % 5;
		sleep(random); // Change this to random amount of sleep time
		release_pid(args, current, thread);
		iterations++;
	}
}
/*************************************************************************/
/* Function name: main                    							                 */
/* Description: Start the program to start allocating PIDs               */
/* Return Value: none                                                    */
/*************************************************************************/
int main()
{
	srand(time(NULL));
	// Init PID array to 0
	int pid_list[MAX_PID] = {0};
	struct allocate_pid_data apd;
	apd.pid_list = pid_list;
	apd.pid_counter = 0;
	apd.pids_size = 0;
	apd.pid_thread = 0;
	pthread_t threads[MAX_THREADS];
	printf("**************************************************************\n");
	printf("Map initialized for PID numbers 300-315\n");
	int iter = 0;
	while(iter < MAX_THREADS)
	{
		pthread_create(&threads[iter], NULL, allocator, (void *)&apd);
		iter = iter + 1;
	}
	iter = 0;
	// NOTE the way this program is designed the last outputs will be
	// all releases
	while (iter < MAX_THREADS)
	{
		pthread_join(threads[iter], NULL);
		iter++;
	}
	pthread_exit(NULL);
}
