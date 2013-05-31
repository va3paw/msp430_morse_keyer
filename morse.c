/*
// MSP430 - CW Beacon Program - ver. 0.01 2012-11-14
// by Paul Shiryaev, VA3PAW
// This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <msp430.h>
// transmitted message:
const unsigned char* message = "CQ CQ CQ CQ DE VA3PAW VA3PAW K ";
#define pin0mask (0x01 << 0)
#define pin6mask (0x01 << 6)
#define dot 1
#define dash 3
// Morse character codes: 5 first bits dits/dahs, 3 bits - length
const unsigned char m[] = { 
 0b11111101 //0
 ,0b01111101 //1
 ,0b00111101 //2
 ,0b00011101 //3
 ,0b00001101 //4
 ,0b00000101 //5
 ,0b10000001 //6
 ,0b11000001 //7
 ,0b11100001 //8
 ,0b11110001 //9
 ,0,0,0,0,0,0,0 // other chars - handled in the switch block
 ,0b00001010 //A
 ,0b01000100 //B
 ,0b01010100 //C
 ,0b01000011 //D
 ,0b00000001 //E
 ,0b00010100 //F
,0b00011011 //G
 ,0b00000101 //H
 ,0b00000010 //I
 ,0b00111100 //J
 ,0b00101011 //K
 ,0b00100100 //L
 ,0b00011010 //M
 ,0b00010010 //N
 ,0b00111011 //O
 ,0b00110100 //P
 ,0b01101100 //Q
 ,0b00010011 //R
 ,0b00111011 //S
 ,0b00001001 //T
 ,0b00001011 //U
 ,0b00001100 //V
 ,0b00011011 //W
 ,0b01001100 //X
 ,0b01011100 //Y
 ,0b01100100 //Z

};

void wait(int d)
{
 // The following two lines implement a very crude delay loop.
 // The actual length of the delay can vary significantly.
 //This approach may not work with all compilers.
 //
 d*=5000;
 volatile int i;
 for( i = 0; i < d; i++ );

}

void pause( short delay )
{
 wait( delay*dot );
}
void dit()
{
 P1OUT ^= pin6mask;
 wait(dot);
 P1OUT ^= pin6mask;
 wait(dot);
}
void dah()
{
 P1OUT ^= pin6mask;
 wait(dash);
 P1OUT ^= pin6mask;
 wait(dot);
}
void key(unsigned char a)
{
 unsigned char n = a & 7; // beep count
 for( n = n + 2; n > 2; n--)
 {
 unsigned char mask = ( 1 << n );
 if( a & mask )
 {
 dah();
 }
 else
 {
 dit();
 }
 }
 pause(2); // 3 dots between characters, 1 was already after the beep
}

void sendChar(unsigned char a)
{
 if (a>96) {a-=32; }
 switch (a)
 {
 case ' ':
 pause(4); // 4 dots between words
 break;
 case '!':
 dah(); dit(); dah(); dit(); dah(); dah(); 
 break; 
 case 34: // "
 dit(); dah(); dah(); dah(); dah(); dit();
 break;
 case '$':
 dit(); dit(); dit(); dah(); dit(); dit(); dah();
 break;
 case '&':
 dit(); dah(); dit(); dit(); dit(); 
 break;
 case 39: // '
 dit(); dah(); dah(); dah(); dah(); dit(); 
 break;
 case '(':
 dah(); dit(); dah(); dah(); dit(); 
 break;
 case ')':
 dah(); dit(); dah(); dah(); dit(); dah(); 
 break;
 case '+':
 dit(); dah(); dit(); dah(); dit(); 
 break;
 case ',':
 dah(); dah(); dit(); dit(); dah(); dah(); 
 break;
 case '-':
 dah(); dit(); dit(); dit(); dit(); dah(); 
 break;
 case '.':
 dit(); dah(); dit(); dah(); dit(); dah(); 
 break;
 case '/':
 dah(); dit(); dit(); dah(); dit(); 
 break;
 // here go digits 0..9
 //
 case ':':
 break;
 case ';':
 break;
 case '=':
 break;
 case '?':
 break;
 case '@':
 break;
case '_': // 95
 break;
default:
 if (((a >= '0' ) && (a <= '9' )) || ((a >= 'A' ) && (a <= 'Z' )))
 {
 unsigned char k = m[a - '0'];
 key(k);
 }
}

}

void sendString( const char *str )
{
 char *c = str;
 for( ; *c ; c++ ) {
 sendChar( *c );
 }
}

int main(void) {
 /* Hold the watchdog timer so it doesn't reset our chip */
 WDTCTL = WDTPW + WDTHOLD;
/* Configure pins 0,6 on port 1 as output pins */
 P1DIR = pin0mask | pin6mask;
P1OUT = 0;
/* infinite loop */
 for( ; ; ) {
/* Blink red led once before the transmission */
 P1OUT ^= pin0mask;
 pause(6); 
 P1OUT = 0;
 pause(6); 

 /* transmit our message */
 sendString(message);
pause(6); 

 }
}
