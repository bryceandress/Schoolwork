///////////////////////////////////////////////////////////////////////////
// 										Bryce Andress 								                     //
// 								CSC 343 Operating Systems					                     //
// 											Assignmnet 3                                     //
// 										Compiler: gcc                                      //
// 								September 14th  2017 							 										 //
///////////////////////////////////////////////////////////////////////////
#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define MIN_PID 0
#define MAX_PID 40

/*************************************************************************/
/* Function name: disp_map                    							             */
/* Description: Displays all the PIDs that have been allocated           */
/* Return Value: none                                                    */
/*************************************************************************/
void disp_map(int *pid_list)
{
	int i = 0;
	printf("List: ");
	while(i <= MAX_PID)
	{
		if(pid_list[i] == 1)
		{
			//Print out all the PID values
			printf("%d ", i+100);
		}
		i++;
	}
}

/*************************************************************************/
/* Function name: scan_map                    							             */
/* Description: Searches map for a pid that can be allocated             */
/* Return Value: Returns a PID that can be used. -1 if none available    */
/*************************************************************************/
int scan_map(int *pid_list)
{
	printf("Scanning map...");
	int counter = 0;
	while(counter < MAX_PID)
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
/* Function name: allocate_pid                  							           */
/* Description: Allocates PID                                            */
/* Return Value: Allocated PID number or -1 if none available            */
/*************************************************************************/
int allocate_pid(int *pid_list, int pid_counter, int *pids_size)
{
	printf("\n");
	int counter = pid_counter;
	int allocated = 1;
	while(allocated)
	{
		// Make sure the PID is range and make sure the PID already isn't in use
		if (counter <= MAX_PID && counter >= 0 && pid_list[counter] != 1)
		{
			pid_list[counter] = 1;
			printf("Allocated PID=%d and total PID=%d ",counter+100, *pids_size);
			disp_map(pid_list);
			*pids_size = *pids_size + 1;
			return ++counter;
		}
		// If one of the previous conditions is not met see if there are any PIDs left
		else
		{
			counter = scan_map(pid_list);
			if (counter == -1)
			{
				printf("No PIDs to allocate");
				return counter;
			}
		}
	}
}

/*************************************************************************/
/* Function name: release_pid                    							           */
/* Description: Release a given PID                                      */
/* Return Value: Returns 0 if PID releases successfully -1 if it does not*/
/*************************************************************************/
int release_pid(int *pid_list, int release_pid, int *pids_size)
{
	printf("\n");
	if(release_pid >= 0 && release_pid <= MAX_PID)
	{
		pid_list[release_pid] = 0;
		*pids_size = *pids_size - 1;
		printf("Released  PID=%d and total PID=%d ", release_pid + 100, *pids_size-1);
		disp_map(pid_list);
	}
}

/*************************************************************************/
/* Function name: main                    							                 */
/* Description: Start the program to start allocating PIDs               */
/* Return Value: none                                                    */
/*************************************************************************/
int main()
{
	// Init random number
	srand(time(NULL));
	// Init PID array to 0
	int pid_list[MAX_PID+1] = {0};
	int current_pid = 0;
	int pids_in_use = 1;
	printf("**************************************************************\n");
	printf("Map initialized for PID numbers 100-140");
	int iterations = 0;
	current_pid = allocate_pid(pid_list, current_pid, &pids_in_use);
	int random = rand();
	while(iterations < 150)
	{
		//Generate random number
		random = rand();
		//If 0 allocate a pid if 1 release a pid
		if(random % 2 == 1)
		{
			current_pid = allocate_pid(pid_list, current_pid, &pids_in_use);
		}
		else
		{
			// Make sure there is something to release
			if (pids_in_use > 0)
			{
				// Generate random number based on PIDs used and kill that pid
				// When release == 0 a pid has successfully been released
				int released = 0;
				random = rand() % pids_in_use;
				while(pid_list[random] == 1 && released == 0)
				{
					release_pid(pid_list, random, &pids_in_use);
					released = 1;
				}
			}
  	}
		random = rand() % 3;
		sleep(random); // Change this to random amount of sleep time
		iterations++;
	}
}
