/*
 * Acidx
 *
 *     Acidx is a simple wrapper for X applications that accept the -fg and -bg parameters. 
 *     Specifically designed to have a low memory footprint, it will wrap X programs such as 
 *     xterm and randomly determine the background and foreground colors for the program, 
 *     while keeping the color scheme legible.
 *
 *     https://github.com/kristopolous/acidx
 *
 * (c) Copyright 2004-2008, 2011, 2013 Christopher J. McKenzie under
 *     the terms of the GNU Public License, incorporated
 *     herein by reference.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_OF_2(a, b)       (a) > (b) ? (a) : (b)
#define MAX_OF_3(a, b, c)    MAX_OF_2(MAX_OF_2(a, b), c)

#define MIN_OF_2(a, b)       (a) < (b) ? (a) : (b)
#define MIN_OF_3(a, b, c)    MIN_OF_2(MIN_OF_2(a, b), c)

char *xprog = 0;

extern char **environ;

typedef struct { unsigned char h, s, l; } hsl;
typedef struct { unsigned char r, g, b; } rgb;

float hue2rgb(float p, float q, float t){
  if(t < 0) t += 1.0;
  if(t > 1) t -= 1.0;
  if(t < 1.0 / 6.0) return p + (q - p) * 6.0 * t;
  if(t < 1.0 / 2.0) return q;
  if(t < 2.0 / 3.0) return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
  return p;
}

void hsl2rgb(hsl in, rgb*out) {
    float 
      r, 
      g, 
      b,

      h = in.h / 256.0,
      s = in.s / 256.0,
      l = in.l / 256.0;

    if(s == 0.0){
      r = g = b = l; // achromatic
    } else {
      float 
        q = l < 0.5 ? l * (1 + s) : l + s - l * s,
        p = 2.0 * l - q;

      r = hue2rgb(p, q, h + 1.0 / 3.0);
      g = hue2rgb(p, q, h);
      b = hue2rgb(p, q, h - 1.0 / 3.0);
    }

    out->r = r * 255.0;
    out->g = g * 255.0;
    out->b = b * 255.0;
}

int main(int argc, char*argv[]) {  
  srand(time(0) * getpid());

  hsl 
    h_bg = {
      .h = 190 + rand() % 10,
      .s = rand() % 32 + 90,
      .l = rand() % 12 + 2 
    },
    h_fg = {
      .h = (((h_bg.h - 10) + rand() % 20) + (rand() % 2) * 32) % 256,
      .s = MIN_OF_2(255, 50 + rand() % 64 + h_bg.s / 2.0),
      .l = MIN_OF_2(255, 222 + h_bg.l)
    };
  
  rgb bg, fg;

  hsl2rgb(h_bg, &bg); 
  hsl2rgb(h_fg, &fg); 

  short 
    count_ix = 5, 
    count = argc + count_ix;

  char **myargs = (char**)malloc(sizeof(char*) * count);

  myargs[count - 1] = 0;
  
  myargs[1] = "-bg";
  myargs[3] = "-fg";

  myargs[2] = (char*)malloc(13 * sizeof(char));
  sprintf(
    myargs[2], 
    "#%02x%02x%02x", 
    bg.r, bg.g, bg.b
  );

  myargs[4] = (char*)malloc(13 * sizeof(char));
  sprintf(
    myargs[4], 
    "#%02x%02x%02x", 
    fg.r, fg.g, fg.b
  );

  if(argc > 1) { 
    xprog = argv[1];
    argc--;
    argv++;
    count--;
  } else { 
    for(count_ix = 1; myargs[count_ix]; count_ix++) {
      printf("%s ", myargs[count_ix]);
    }
    exit(0);
  }

  myargs[0] = xprog;
  for(;count_ix <= count; count_ix++) {  
    argv++;
    myargs[count_ix] = *argv;
  }

  execvp(xprog, myargs);
}
