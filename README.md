# PIC-CDThread

This is a cooperative scheduler with messages and events capability that is compiled with PIC-C compiler (CCS).
I had created it to solve a simple problem, have a system that allow me to manage code as is available a kernel but in a system 
 with poor resource as a pic16 microcontroller with only 16KB rom and 256 bytes.
I also have created an empowered 32bit version of this scheduler for Analog devices BLACKFIN DSP that I use normally inside
 a single VDK microkernel thread to manage with semplicity complex works avoiding to make VDK heavy and slow in responce.

One of the key of this scheduler is that is statically configurable (no dynamic memory allocation) in the number of CDthreads
 CDEvents and CDmessages, so directly at compile time is possible evaluate the memory footprint. Also the scheduler is very simple 
 and could be recoded to solve different application constrain.
 
Told this ...good work
 
 
