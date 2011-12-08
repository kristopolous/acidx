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
 * (c) Copyright 2004-2008, 2011 Christopher J. McKenzie under
 *     the terms of the GNU Public License, incorporated
 *     herein by reference.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char
  *lightColors = "6789ABCDEF",
  *darkColors = "0121";

char *xprog = "xterm";

extern char **environ;

int main(int argc, char*argv[]) {  
  srand(time(0) * getpid());

  int 
    dark_red = rand() % 4,
    dark_green = rand() % (4 - dark_red / 2),
    dark_blue = rand() % (4 - (dark_red + dark_green) / 3),
    light_red = dark_red + rand() % (10 - dark_red),
    light_green = dark_green + rand() % (10 - dark_green),
    light_blue = dark_blue + rand() % (10 - dark_blue);

  short 
    count_ix = 5, 
    count = argc + count_ix;

  char **myargs = (char**)malloc(sizeof(char*) * count);

  myargs[count - 1] = 0;
  
  if(!strcmp(argv[0] + strlen(argv[0]) - 5, "right")) {
    myargs[1] = "-fg";
    myargs[3] = "-bg";
  } else {
    myargs[1] = "-bg";
    myargs[3] = "-fg";
  }

  if(argc > 1) { 
    xprog = argv[1];
    argc--;
    argv++;
    count--;
  } 

  myargs[0] = xprog;

  myargs[2] = (char*)malloc(10 * sizeof(char));
  sprintf(myargs[2], "rgb:%c/%c/%c", 
    darkColors[dark_red],
    darkColors[dark_green],
    darkColors[dark_blue]);

  myargs[4] = (char*)malloc(10 * sizeof(char));
  sprintf(myargs[4], "rgb:%c/%c/%c", 
    lightColors[light_red],
    lightColors[light_green],
    lightColors[light_blue]);

  for(;count_ix <= count; count_ix++) {  
    argv++;
    myargs[count_ix] = *argv;
  }

  execvp(xprog, myargs);
}
