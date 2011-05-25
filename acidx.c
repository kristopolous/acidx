/*
 * Acidx
 *
 *     Acidx is a simple wrapper for X applications that accept the -fg and -bg parameters. 
 *     Specifically designed to have a low memory footprint, it will wrap X programs such as 
 *     xterm and randomly determine the background and foreground colors for the program, 
 *     while keeping the color scheme legible.
 *
 *     http://qaa.ath.cx/
 *
 * (c) Copyright 2004-2008, Christopher J. McKenzie under
 *     the terms of the GNU Public License, incorporated
 *     herein by reference.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char
	*light = "09ABCDEF",
	*fallback= "xterm",
	*order= "bfb",
	*dark = "0123";

char	*cmd = 0,
	*xprog = 0;

extern char **environ;

int main(int argc, char*argv[])
{	
	int 	lr = 0,	dr = 0,
		lg = 0,	dg = 0,
		lb = 0,	db = 0;

	short count_ix = 0, count = argc + 4;

	char **myargs = (char**)malloc(sizeof(char*) * count);

	myargs[count - 1] = 0;

	srand(time(0) * getpid());
	
	if(!strcmp(argv[0] + strlen(argv[0]) - 5, "right"))
	{
		order ++;
	}

	dr = rand() % 4;
	dg = rand() % 4;
	db = rand() % 4;

	do
	{
		lr = rand() % 8;
		lg = rand() % 8;
		lb = rand() % 8;
	}while(!(lr + lg + lb));

	if(argc > 1)
	{ 
		xprog = argv[1];
		argc--;
		argv++;
		count--;
	}
	else
	{
		xprog = (char*)fallback;
	}

	/*
	 * From the execv manpage:
	 * "The initial argument for these functions is the pathname of a file which is to be executed."
	 */
	myargs[count_ix] = xprog;

	count_ix++;
	myargs[count_ix] = (char*)malloc(4 * sizeof(char));
	sprintf(myargs[count_ix], "-%cg", order[0]);

	count_ix++;
	myargs[count_ix] = (char*)malloc(10 * sizeof(char));
	sprintf(myargs[count_ix], "rgb:%c/%c/%c", 
		dark[dr],
		dark[dg],
		dark[db]);

	count_ix++;
	myargs[count_ix] = (char*)malloc(4 * sizeof(char));
	sprintf(myargs[count_ix], "-%cg", order[1]);

	count_ix++;
	myargs[count_ix] = (char*)malloc(10 * sizeof(char));
	sprintf(myargs[count_ix], "rgb:%c/%c/%c", 
		light[lr],
		light[lg],
		light[lb]);

	count_ix++;
	for(;count_ix <= count; count_ix++)
	{	
		argv++;
		myargs[count_ix] = *argv;
	}

	execvp(xprog, myargs);
}
