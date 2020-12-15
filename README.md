# Acidx

Acidx is a simple wrapper for X applications that accept the -fg and -bg parameters.  Specifically designed to have a low memory footprint, it will wrap X programs such as xterm and randomly determine the background and foreground colors for the program, while keeping the color scheme legible.

Screenshot:
<img src=http://i.imgur.com/JmWoi.png>

# Usage

## Out-of band
acidx is a C program. If you run make and then just execute it, it will
give you arguments that you can put into any application.  For instance,

    acidx | xargs xterm
    acidx | xargs xlogo

## In-band
My primary use for the program however, is to provide the program as
the arguments to acidx.  In this method, it will execv the first argument
and then append the color arguments on it. So you can do something like:

    acidx xterm

You can also provide your own set of arguments for this purpose, for 
instance:

    acidx xeyes -center blue
