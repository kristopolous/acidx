# Acidx

Acidx is a simple wrapper for X applications that accept the -fg and -bg parameters.  Specifically designed to have a low memory footprint, it will wrap X programs such as xterm and randomly determine the background and foreground colors for the program, while keeping the color scheme legible.

Screenshot:
<img src=http://i.imgur.com/JmWoi.png>

# Usage

acidx is a C program. If you run make and then just execute it, it will
give you arguments that you can put into any application.  For instance,

    acidx | xargs xterm
    acidx | xargs xlogo

