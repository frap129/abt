abt - An Android Build Tool
=======================================
What is abt?
------------
abt is a tool designed to simplify the process of building AOSP
and other Android-based platforms to a single command.
  
How do I install abt?
---------------------
It's simple! clone this repository anywhere, cd into it, and run make install!
  
How do I use abt?
-----------------
Usage: abt [OPTIONS]

OPTIONS: -bTARGET    Build target. ex. -botapackage. Defaults to bacon
         -c[TARGET]  Clean before build. Default target is clean, but can be set. ex. -cclobber 
         -dTARGET    Device to lunch. ex. full_bacon-eng. Set default in device.abt in the chroot
         -jJOBS      Number of threads to use. Auto calculates if not set
         -s          Sync sources before starting build. Defaults to false
         -p          Run commands specified in prebuild.abt before build
         -a          Run commands specified in postbuild.abt after build
         -h          Show this menu
