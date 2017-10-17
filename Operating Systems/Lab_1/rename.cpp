///////////////////////////////////////////////////////
// 										Bryce Andress 								 //
// 								CSC 343 Operating Systems					 //
// 								September 7th  2017 							 //
///////////////////////////////////////////////////////
#include <stdio.h>
#include <ostream>
using namespace std;
/*************************************************************************/
/* Function name: main                          							           */
/* Description: Rename file given to specifed file name                  */
/* Parameters: int argc: The number of arguments - input                 */
/* char *argv[]: An array of pointers to the arguments                   */
/* Return Value: none                                                    */
/*************************************************************************/
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		write(1, "Usage: rename <old filename> <new filename>\n\00", 46);
		return -1;
	}
	int r = rename(argv[1], argv[2]);
	if (r == 0) {
		write(1, "Rename successful\n\00",19);
	}
	else {
		write(1, "Rename was not successful\n\00",28);
	}
}
