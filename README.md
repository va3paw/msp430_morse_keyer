MSP430 - CW Beacon Program
=========================
 
I wanted to build a compact CW beacon which I could use to call CQ in the fields when using a QRP transceiver or in a field day contest, or for a fox hunt. The TI MSP430 chip is very suitable for these applications due to its ultra-low power consumption and cheap price.

This is a first iteration of the beacon program and is my first program for MSP430. It only transmits one message in a loop. This is my first experience programming for microcontrollers in C/C++. Before, I only used ASM for all my code. I applied some good ideas from Don Bindner’s webpage and Peter Gabris’s code originally created for PIC chip.  The next iteration would be to add start/stop/cycle various messages by pressing button(s). I also plan to use watchdog interrupt (sleep mode) for a delay to lower down power consumption, and farther optimize the code to minimize the size of the resulting machine code.

To compile and load the program to the microcontroller run: 

        # msp430-gcc -mmcu=msp430g2452 -o morse.elf morse.c && mspdebug rf2500 'prog morse.elf'

For howto install msp430 utilities in Ubuntu - [check my blog] (http://va3paw.wordpress.com/2012/11/15/ti-msp430-launchpad-on-ubuntu-11-10/)


