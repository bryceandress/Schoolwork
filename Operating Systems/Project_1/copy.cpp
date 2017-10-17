///////////////////////////////////////////////////////
// 										Bryce Andress 								 //
// 								CSC 343 Operating Systems					 //
// 								September 14th  2017 							 //
///////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

/*************************************************************************/
/* Function name: open                          							           */
/* Description: Open the file the user wants to copy                     */
/* Parameters: char *old_file - point to the file to copy's name         */
/* Return Value: int - File descriptor of the file to copy               */
/*************************************************************************/
int open(char *old_file)
{
	int old_file_descriptor = open(old_file, O_RDONLY, S_IRUSR | S_IWUSR);
	if (old_file_descriptor < 0)
	{
		write(1, "File does not exist\n\00", 21);
		exit(0);
	}
	return old_file_descriptor;
}

/*************************************************************************/
/* Function name: create                          						           */
/* Description: Create the file the user wants to copy to                */
/* Parameters: char *new_file: Name of the file the user wants to create */
/* Return Value: int - The new files file descriptor                     */
/*************************************************************************/
int create(char *new_file)
{
	// Create the file only if the file does not exist. Give the user read write access to it
	int new_file_descriptor = open(new_file, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	if (new_file_descriptor < 0)
	{
		write(1, "File already exists\n\00", 21);
		exit(0);
	}
	return new_file_descriptor;
}

/*************************************************************************/
/* Function name: copy                            						           */
/* Description: Copy contents of old file to new file                    */
/* Parameters: int old_file_descriptor: Descriptor of file to copy from  */
/*             int new_file_descriptor: Descriptor of file to copy to    */
/* Return Value: none                                                    */
/*************************************************************************/
void copy(int old_file_descriptor, int new_file_descriptor)
{
	int BUFF;
	char buffer[1024];
	while((BUFF = read(old_file_descriptor, buffer, 1024)) > 0)
	{
		write(new_file_descriptor, buffer, BUFF);
	}
}

/*************************************************************************/
/* Function name: main                          							           */
/* Description: Get file to copy and new file name from user             */
/* Parameters: int argc: The number of arguments - input                 */
/* char *argv[]: An array of pointers to the arguments                   */
/* Return Value: none                                                    */
/*************************************************************************/
int main(int argc, char *argv[])
{
	char old_file[256];
	char new_file[256];
	int old_file_name_length;
	int new_file_name_length;
	int new_file_descriptor;
	int old_file_descriptor;

	// Get file to copy name
	write(1, "File to copy: \00", 14);
	old_file_name_length = read(0, old_file, 256);

	// Change newline to \00
	old_file[old_file_name_length-1] = '\00';

	// Open file to copy from
	old_file_descriptor = open(old_file);

	// Get new file name to copy to
	write(1, "New file name: \00", 15);
	new_file_name_length = read(0, new_file, 256);

	// Change newline to \00
  new_file[new_file_name_length-1] = '\00';

	// Create new file
	new_file_descriptor = create(new_file);

  // Copy contents of the old file to the new one
	copy(old_file_descriptor, new_file_descriptor);

	// Close the files
	close(old_file_descriptor);
	close(new_file_descriptor);

  // Let user know the copy was successful
	write(1, "Copy successful\n\00", 16);
}
