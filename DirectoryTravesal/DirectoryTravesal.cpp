/*
* Restart the deirectory traversal after a failure.
* This program uses telldir to get offset of directory.
* seekdir is used to set the directory stream from which next readdir call will start
*/
#include <iostream>
#include <stdio.h>
#include <dirent.h>

using namespace std;

//Refer: ://www.geeksforgeeks.org/c-program-list-files-sub-directories-directory/ for base source code
//
int main()
{
	struct dirent* de = NULL;  // Pointer for directory entry

	// opendir() returns a pointer of DIR type.
	DIR* dr = opendir("/testdir");
	
	if (dr == NULL)  // opendir returns NULL if couldn't open directory
	{
		cout << "Could not open current directory";
		return 0;
	}

	// Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
	// for readdir()
	while ((de = readdir(dr)) != NULL)
	{
		printf("%s\n", de->d_name);
		// telldir returns the current  location in directory stream.
	    // telldir: https://linux.die.net/man/3/telldir
		cout << "\n Tell Dir:" << telldir(dr) << "\n";
	}

	closedir(dr);

	// opendir() returns a pointer of DIR type
	dr = opendir("/testdir");

	if (dr == NULL)  // opendir returns NULL if couldn't open directory
	{
		cout << "Could not open current directory";
		return 0;
	}

	//seekdir sets the dirent dr to specific directory.
	//directory traversal will now start from this dierctory.
	//seekdir: https://linux.die.net/man/3/seekdir
	int dir_offset = 253;

	seekdir(dr, dir_offset);

	while ((de = readdir(dr)) != NULL)
	{
		printf("%s\n", de->d_name);
		cout << "\n Tell Dir:" << telldir(dr) << "\n";
	}

	closedir(dr);

	return 0;
