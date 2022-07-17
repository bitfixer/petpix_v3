#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <peekpoke.h> 
#include <time.h>
#include <pet.h>
#include <string.h>

//#define PET80COL    1

/*
original basic program
5 poke 59468,peek(59468) or 1
6 poke 59467, peek(59467) and 227
8 poke 59468,peek(59468) or 224
10 poke 59467,peek(59467) and 254
20 a = peek(59457)
30 poke 32768,45
40 if(peek(59469) and 2) > 0 then 60
42 poke 32768,92
44 if(peek(59469) and 2) > 0 then 60
45 poke 32768,93
46 if(peek(59469) and 2) > 0 then 60
47 poke 32768,47
48 if(peek(59469) and 2) > 0 then 60
50 goto 30
60 for x = 1 to 1000 step 2
80 poke 59468,(peek(59468) and 31) or 192
90 a = peek(59457)
100 poke 32767+x,a
110 poke 59468, peek(59468) or 224
120 b = peek(59457)
130 poke 32767+x+1,b
140 next x
150 goto 5
*/

//#define CA1_TRIGGER     59468
//#define CA1_DATA_LATCH  59467
//#define CA1_STATUS      59469
//#define USERPORT_DATA   59457
//#define VMEM_START      32768

#define CA1_TRIGGER     0xE84C
#define CA1_DATA_LATCH  0xE84B
#define CA1_STATUS      0xE84D
#define USERPORT_DATA   0xE841
#define VMEM_START      0x8000
#define VMEM_START_2    0x8100
#define VMEM_START_3    0x8200

#ifdef PET80COL
// for PET 8032
#define VMEM_START_4    0x8300
#define VMEM_START_5    0x8400
#define VMEM_START_6    0x8500
#define VMEM_START_7    0x8600
#define VMEM_START_8    0x86D0
#else
// for PET 2001
//#define VMEM_START_4    0x82E8
#define VMEM_START_4    0x8300
#endif

#define CURR_KEY        0x0097
#define Q_KEY           64

#define RUN_STOP 3

int main (void)
{
    unsigned char data;
    unsigned char key = 0;
    int x;
    int p;
    
    // set uppercase-graphics mode
    data = 12;
    POKE(CA1_TRIGGER, data);

    data = PEEK(CA1_TRIGGER);
    data = data | 0x01;
    POKE(CA1_TRIGGER, data);
    
    // disable shift register modes
    data = PEEK(CA1_DATA_LATCH);
    data = data & 227;
    POKE(CA1_DATA_LATCH, data);
    
    // set CB2 line low poke 59468,peek(59468) or 224
    data = PEEK(CA1_TRIGGER);
    data = data | 224;
    POKE(CA1_TRIGGER, data);
    
    // data not latched
    data = PEEK(CA1_DATA_LATCH);
    data = data & 254;
    POKE(CA1_DATA_LATCH, data);
    
    // read data, reset CA1 flag bit
    data = PEEK(USERPORT_DATA);
    
    //while(key != Q_KEY)
    //{

        asm("ldy #$CD");
        asm("ldx #$ED");

readbyte0:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte0);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+0);
readbyte1:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte1);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+1);
readbyte2:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte2);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+2);
readbyte3:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte3);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+3);
readbyte4:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte4);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+4);
readbyte5:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte5);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+5);
readbyte6:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte6);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+6);
readbyte7:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte7);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+7);
readbyte8:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte8);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+8);
readbyte9:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte9);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+9);
readbyte10:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte10);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+10);
readbyte11:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte11);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+11);
readbyte12:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte12);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+12);
readbyte13:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte13);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+13);
readbyte14:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte14);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+14);
readbyte15:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte15);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+15);
readbyte16:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte16);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+16);
readbyte17:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte17);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+17);
readbyte18:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte18);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+18);
readbyte19:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte19);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+19);
readbyte20:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte20);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+20);
readbyte21:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte21);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+21);
readbyte22:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte22);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+22);
readbyte23:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte23);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+23);
readbyte24:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte24);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+24);
readbyte25:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte25);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+25);
readbyte26:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte26);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+26);
readbyte27:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte27);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+27);
readbyte28:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte28);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+28);
readbyte29:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte29);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+29);
readbyte30:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte30);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+30);
readbyte31:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte31);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+31);
readbyte32:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte32);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+32);
readbyte33:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte33);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+33);
readbyte34:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte34);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+34);
readbyte35:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte35);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+35);
readbyte36:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte36);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+36);
readbyte37:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte37);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+37);
readbyte38:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte38);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+38);
readbyte39:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte39);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+39);
readbyte40:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte40);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+40);
readbyte41:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte41);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+41);
readbyte42:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte42);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+42);
readbyte43:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte43);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+43);
readbyte44:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte44);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+44);
readbyte45:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte45);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+45);
readbyte46:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte46);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+46);
readbyte47:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte47);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+47);
readbyte48:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte48);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+48);
readbyte49:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte49);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+49);
readbyte50:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte50);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+50);
readbyte51:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte51);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+51);
readbyte52:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte52);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+52);
readbyte53:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte53);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+53);
readbyte54:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte54);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+54);
readbyte55:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte55);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+55);
readbyte56:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte56);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+56);
readbyte57:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte57);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+57);
readbyte58:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte58);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+58);
readbyte59:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte59);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+59);
readbyte60:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte60);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+60);
readbyte61:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte61);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+61);
readbyte62:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte62);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+62);
readbyte63:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte63);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+63);
readbyte64:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte64);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+64);
readbyte65:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte65);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+65);
readbyte66:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte66);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+66);
readbyte67:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte67);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+67);
readbyte68:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte68);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+68);
readbyte69:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte69);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+69);
readbyte70:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte70);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+70);
readbyte71:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte71);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+71);
readbyte72:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte72);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+72);
readbyte73:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte73);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+73);
readbyte74:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte74);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+74);
readbyte75:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte75);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+75);
readbyte76:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte76);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+76);
readbyte77:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte77);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+77);
readbyte78:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte78);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+78);
readbyte79:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte79);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+79);
readbyte80:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte80);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+80);
readbyte81:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte81);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+81);
readbyte82:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte82);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+82);
readbyte83:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte83);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+83);
readbyte84:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte84);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+84);
readbyte85:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte85);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+85);
readbyte86:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte86);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+86);
readbyte87:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte87);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+87);
readbyte88:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte88);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+88);
readbyte89:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte89);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+89);
readbyte90:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte90);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+90);
readbyte91:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte91);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+91);
readbyte92:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte92);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+92);
readbyte93:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte93);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+93);
readbyte94:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte94);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+94);
readbyte95:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte95);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+95);
readbyte96:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte96);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+96);
readbyte97:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte97);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+97);
readbyte98:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte98);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+98);
readbyte99:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte99);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+99);
readbyte100:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte100);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+100);
readbyte101:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte101);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+101);
readbyte102:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte102);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+102);
readbyte103:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte103);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+103);
readbyte104:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte104);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+104);
readbyte105:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte105);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+105);
readbyte106:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte106);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+106);
readbyte107:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte107);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+107);
readbyte108:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte108);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+108);
readbyte109:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte109);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+109);
readbyte110:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte110);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+110);
readbyte111:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte111);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+111);
readbyte112:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte112);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+112);
readbyte113:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte113);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+113);
readbyte114:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte114);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+114);
readbyte115:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte115);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+115);
readbyte116:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte116);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+116);
readbyte117:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte117);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+117);
readbyte118:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte118);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+118);
readbyte119:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte119);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+119);
readbyte120:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte120);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+120);
readbyte121:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte121);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+121);
readbyte122:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte122);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+122);
readbyte123:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte123);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+123);
readbyte124:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte124);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+124);
readbyte125:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte125);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+125);
readbyte126:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte126);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+126);
readbyte127:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte127);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+127);
readbyte128:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte128);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+128);
readbyte129:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte129);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+129);
readbyte130:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte130);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+130);
readbyte131:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte131);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+131);
readbyte132:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte132);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+132);
readbyte133:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte133);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+133);
readbyte134:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte134);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+134);
readbyte135:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte135);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+135);
readbyte136:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte136);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+136);
readbyte137:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte137);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+137);
readbyte138:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte138);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+138);
readbyte139:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte139);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+139);
readbyte140:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte140);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+140);
readbyte141:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte141);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+141);
readbyte142:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte142);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+142);
readbyte143:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte143);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+143);
readbyte144:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte144);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+144);
readbyte145:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte145);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+145);
readbyte146:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte146);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+146);
readbyte147:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte147);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+147);
readbyte148:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte148);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+148);
readbyte149:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte149);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+149);
readbyte150:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte150);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+150);
readbyte151:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte151);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+151);
readbyte152:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte152);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+152);
readbyte153:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte153);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+153);
readbyte154:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte154);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+154);
readbyte155:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte155);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+155);
readbyte156:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte156);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+156);
readbyte157:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte157);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+157);
readbyte158:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte158);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+158);
readbyte159:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte159);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+159);
readbyte160:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte160);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+160);
readbyte161:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte161);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+161);
readbyte162:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte162);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+162);
readbyte163:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte163);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+163);
readbyte164:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte164);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+164);
readbyte165:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte165);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+165);
readbyte166:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte166);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+166);
readbyte167:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte167);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+167);
readbyte168:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte168);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+168);
readbyte169:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte169);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+169);
readbyte170:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte170);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+170);
readbyte171:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte171);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+171);
readbyte172:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte172);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+172);
readbyte173:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte173);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+173);
readbyte174:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte174);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+174);
readbyte175:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte175);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+175);
readbyte176:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte176);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+176);
readbyte177:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte177);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+177);
readbyte178:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte178);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+178);
readbyte179:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte179);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+179);
readbyte180:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte180);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+180);
readbyte181:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte181);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+181);
readbyte182:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte182);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+182);
readbyte183:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte183);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+183);
readbyte184:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte184);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+184);
readbyte185:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte185);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+185);
readbyte186:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte186);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+186);
readbyte187:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte187);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+187);
readbyte188:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte188);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+188);
readbyte189:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte189);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+189);
readbyte190:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte190);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+190);
readbyte191:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte191);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+191);
readbyte192:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte192);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+192);
readbyte193:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte193);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+193);
readbyte194:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte194);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+194);
readbyte195:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte195);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+195);
readbyte196:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte196);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+196);
readbyte197:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte197);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+197);
readbyte198:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte198);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+198);
readbyte199:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte199);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+199);
readbyte200:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte200);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+200);
readbyte201:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte201);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+201);
readbyte202:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte202);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+202);
readbyte203:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte203);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+203);
readbyte204:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte204);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+204);
readbyte205:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte205);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+205);
readbyte206:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte206);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+206);
readbyte207:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte207);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+207);
readbyte208:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte208);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+208);
readbyte209:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte209);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+209);
readbyte210:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte210);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+210);
readbyte211:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte211);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+211);
readbyte212:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte212);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+212);
readbyte213:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte213);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+213);
readbyte214:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte214);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+214);
readbyte215:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte215);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+215);
readbyte216:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte216);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+216);
readbyte217:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte217);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+217);
readbyte218:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte218);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+218);
readbyte219:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte219);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+219);
readbyte220:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte220);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+220);
readbyte221:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte221);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+221);
readbyte222:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte222);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+222);
readbyte223:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte223);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+223);
readbyte224:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte224);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+224);
readbyte225:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte225);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+225);
readbyte226:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte226);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+226);
readbyte227:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte227);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+227);
readbyte228:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte228);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+228);
readbyte229:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte229);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+229);
readbyte230:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte230);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+230);
readbyte231:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte231);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+231);
readbyte232:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte232);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+232);
readbyte233:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte233);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+233);
readbyte234:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte234);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+234);
readbyte235:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte235);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+235);
readbyte236:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte236);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+236);
readbyte237:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte237);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+237);
readbyte238:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte238);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+238);
readbyte239:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte239);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+239);
readbyte240:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte240);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+240);
readbyte241:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte241);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+241);
readbyte242:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte242);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+242);
readbyte243:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte243);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+243);
readbyte244:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte244);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+244);
readbyte245:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte245);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+245);
readbyte246:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte246);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+246);
readbyte247:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte247);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+247);
readbyte248:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte248);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+248);
readbyte249:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte249);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+249);
readbyte250:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte250);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+250);
readbyte251:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte251);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+251);
readbyte252:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte252);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+252);
readbyte253:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte253);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+253);
readbyte254:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte254);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+254);
readbyte255:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte255);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+255);
readbyte256:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte256);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+256);
readbyte257:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte257);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+257);
readbyte258:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte258);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+258);
readbyte259:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte259);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+259);
readbyte260:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte260);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+260);
readbyte261:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte261);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+261);
readbyte262:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte262);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+262);
readbyte263:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte263);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+263);
readbyte264:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte264);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+264);
readbyte265:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte265);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+265);
readbyte266:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte266);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+266);
readbyte267:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte267);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+267);
readbyte268:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte268);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+268);
readbyte269:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte269);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+269);
readbyte270:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte270);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+270);
readbyte271:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte271);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+271);
readbyte272:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte272);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+272);
readbyte273:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte273);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+273);
readbyte274:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte274);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+274);
readbyte275:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte275);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+275);
readbyte276:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte276);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+276);
readbyte277:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte277);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+277);
readbyte278:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte278);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+278);
readbyte279:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte279);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+279);
readbyte280:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte280);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+280);
readbyte281:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte281);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+281);
readbyte282:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte282);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+282);
readbyte283:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte283);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+283);
readbyte284:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte284);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+284);
readbyte285:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte285);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+285);
readbyte286:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte286);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+286);
readbyte287:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte287);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+287);
readbyte288:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte288);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+288);
readbyte289:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte289);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+289);
readbyte290:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte290);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+290);
readbyte291:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte291);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+291);
readbyte292:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte292);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+292);
readbyte293:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte293);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+293);
readbyte294:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte294);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+294);
readbyte295:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte295);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+295);
readbyte296:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte296);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+296);
readbyte297:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte297);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+297);
readbyte298:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte298);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+298);
readbyte299:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte299);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+299);
readbyte300:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte300);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+300);
readbyte301:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte301);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+301);
readbyte302:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte302);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+302);
readbyte303:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte303);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+303);
readbyte304:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte304);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+304);
readbyte305:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte305);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+305);
readbyte306:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte306);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+306);
readbyte307:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte307);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+307);
readbyte308:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte308);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+308);
readbyte309:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte309);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+309);
readbyte310:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte310);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+310);
readbyte311:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte311);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+311);
readbyte312:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte312);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+312);
readbyte313:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte313);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+313);
readbyte314:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte314);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+314);
readbyte315:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte315);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+315);
readbyte316:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte316);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+316);
readbyte317:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte317);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+317);
readbyte318:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte318);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+318);
readbyte319:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte319);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+319);
readbyte320:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte320);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+320);
readbyte321:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte321);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+321);
readbyte322:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte322);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+322);
readbyte323:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte323);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+323);
readbyte324:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte324);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+324);
readbyte325:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte325);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+325);
readbyte326:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte326);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+326);
readbyte327:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte327);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+327);
readbyte328:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte328);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+328);
readbyte329:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte329);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+329);
readbyte330:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte330);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+330);
readbyte331:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte331);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+331);
readbyte332:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte332);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+332);
readbyte333:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte333);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+333);
readbyte334:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte334);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+334);
readbyte335:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte335);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+335);
readbyte336:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte336);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+336);
readbyte337:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte337);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+337);
readbyte338:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte338);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+338);
readbyte339:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte339);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+339);
readbyte340:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte340);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+340);
readbyte341:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte341);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+341);
readbyte342:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte342);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+342);
readbyte343:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte343);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+343);
readbyte344:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte344);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+344);
readbyte345:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte345);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+345);
readbyte346:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte346);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+346);
readbyte347:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte347);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+347);
readbyte348:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte348);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+348);
readbyte349:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte349);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+349);
readbyte350:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte350);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+350);
readbyte351:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte351);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+351);
readbyte352:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte352);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+352);
readbyte353:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte353);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+353);
readbyte354:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte354);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+354);
readbyte355:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte355);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+355);
readbyte356:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte356);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+356);
readbyte357:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte357);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+357);
readbyte358:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte358);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+358);
readbyte359:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte359);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+359);
readbyte360:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte360);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+360);
readbyte361:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte361);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+361);
readbyte362:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte362);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+362);
readbyte363:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte363);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+363);
readbyte364:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte364);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+364);
readbyte365:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte365);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+365);
readbyte366:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte366);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+366);
readbyte367:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte367);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+367);
readbyte368:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte368);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+368);
readbyte369:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte369);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+369);
readbyte370:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte370);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+370);
readbyte371:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte371);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+371);
readbyte372:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte372);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+372);
readbyte373:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte373);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+373);
readbyte374:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte374);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+374);
readbyte375:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte375);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+375);
readbyte376:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte376);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+376);
readbyte377:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte377);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+377);
readbyte378:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte378);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+378);
readbyte379:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte379);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+379);
readbyte380:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte380);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+380);
readbyte381:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte381);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+381);
readbyte382:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte382);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+382);
readbyte383:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte383);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+383);
readbyte384:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte384);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+384);
readbyte385:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte385);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+385);
readbyte386:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte386);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+386);
readbyte387:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte387);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+387);
readbyte388:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte388);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+388);
readbyte389:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte389);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+389);
readbyte390:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte390);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+390);
readbyte391:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte391);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+391);
readbyte392:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte392);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+392);
readbyte393:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte393);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+393);
readbyte394:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte394);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+394);
readbyte395:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte395);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+395);
readbyte396:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte396);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+396);
readbyte397:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte397);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+397);
readbyte398:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte398);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+398);
readbyte399:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte399);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+399);
readbyte400:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte400);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+400);
readbyte401:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte401);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+401);
readbyte402:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte402);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+402);
readbyte403:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte403);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+403);
readbyte404:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte404);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+404);
readbyte405:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte405);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+405);
readbyte406:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte406);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+406);
readbyte407:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte407);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+407);
readbyte408:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte408);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+408);
readbyte409:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte409);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+409);
readbyte410:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte410);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+410);
readbyte411:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte411);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+411);
readbyte412:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte412);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+412);
readbyte413:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte413);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+413);
readbyte414:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte414);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+414);
readbyte415:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte415);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+415);
readbyte416:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte416);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+416);
readbyte417:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte417);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+417);
readbyte418:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte418);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+418);
readbyte419:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte419);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+419);
readbyte420:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte420);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+420);
readbyte421:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte421);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+421);
readbyte422:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte422);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+422);
readbyte423:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte423);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+423);
readbyte424:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte424);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+424);
readbyte425:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte425);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+425);
readbyte426:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte426);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+426);
readbyte427:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte427);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+427);
readbyte428:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte428);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+428);
readbyte429:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte429);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+429);
readbyte430:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte430);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+430);
readbyte431:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte431);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+431);
readbyte432:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte432);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+432);
readbyte433:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte433);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+433);
readbyte434:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte434);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+434);
readbyte435:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte435);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+435);
readbyte436:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte436);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+436);
readbyte437:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte437);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+437);
readbyte438:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte438);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+438);
readbyte439:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte439);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+439);
readbyte440:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte440);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+440);
readbyte441:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte441);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+441);
readbyte442:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte442);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+442);
readbyte443:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte443);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+443);
readbyte444:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte444);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+444);
readbyte445:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte445);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+445);
readbyte446:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte446);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+446);
readbyte447:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte447);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+447);
readbyte448:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte448);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+448);
readbyte449:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte449);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+449);
readbyte450:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte450);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+450);
readbyte451:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte451);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+451);
readbyte452:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte452);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+452);
readbyte453:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte453);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+453);
readbyte454:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte454);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+454);
readbyte455:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte455);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+455);
readbyte456:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte456);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+456);
readbyte457:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte457);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+457);
readbyte458:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte458);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+458);
readbyte459:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte459);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+459);
readbyte460:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte460);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+460);
readbyte461:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte461);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+461);
readbyte462:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte462);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+462);
readbyte463:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte463);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+463);
readbyte464:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte464);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+464);
readbyte465:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte465);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+465);
readbyte466:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte466);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+466);
readbyte467:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte467);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+467);
readbyte468:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte468);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+468);
readbyte469:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte469);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+469);
readbyte470:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte470);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+470);
readbyte471:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte471);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+471);
readbyte472:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte472);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+472);
readbyte473:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte473);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+473);
readbyte474:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte474);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+474);
readbyte475:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte475);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+475);
readbyte476:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte476);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+476);
readbyte477:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte477);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+477);
readbyte478:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte478);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+478);
readbyte479:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte479);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+479);
readbyte480:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte480);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+480);
readbyte481:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte481);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+481);
readbyte482:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte482);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+482);
readbyte483:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte483);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+483);
readbyte484:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte484);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+484);
readbyte485:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte485);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+485);
readbyte486:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte486);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+486);
readbyte487:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte487);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+487);
readbyte488:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte488);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+488);
readbyte489:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte489);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+489);
readbyte490:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte490);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+490);
readbyte491:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte491);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+491);
readbyte492:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte492);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+492);
readbyte493:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte493);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+493);
readbyte494:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte494);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+494);
readbyte495:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte495);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+495);
readbyte496:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte496);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+496);
readbyte497:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte497);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+497);
readbyte498:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte498);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+498);
readbyte499:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte499);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+499);
readbyte500:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte500);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+500);
readbyte501:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte501);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+501);
readbyte502:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte502);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+502);
readbyte503:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte503);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+503);
readbyte504:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte504);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+504);
readbyte505:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte505);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+505);
readbyte506:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte506);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+506);
readbyte507:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte507);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+507);
readbyte508:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte508);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+508);
readbyte509:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte509);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+509);
readbyte510:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte510);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+510);
readbyte511:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte511);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+511);
readbyte512:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte512);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+512);
readbyte513:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte513);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+513);
readbyte514:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte514);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+514);
readbyte515:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte515);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+515);
readbyte516:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte516);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+516);
readbyte517:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte517);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+517);
readbyte518:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte518);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+518);
readbyte519:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte519);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+519);
readbyte520:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte520);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+520);
readbyte521:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte521);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+521);
readbyte522:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte522);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+522);
readbyte523:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte523);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+523);
readbyte524:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte524);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+524);
readbyte525:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte525);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+525);
readbyte526:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte526);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+526);
readbyte527:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte527);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+527);
readbyte528:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte528);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+528);
readbyte529:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte529);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+529);
readbyte530:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte530);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+530);
readbyte531:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte531);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+531);
readbyte532:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte532);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+532);
readbyte533:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte533);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+533);
readbyte534:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte534);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+534);
readbyte535:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte535);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+535);
readbyte536:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte536);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+536);
readbyte537:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte537);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+537);
readbyte538:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte538);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+538);
readbyte539:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte539);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+539);
readbyte540:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte540);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+540);
readbyte541:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte541);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+541);
readbyte542:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte542);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+542);
readbyte543:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte543);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+543);
readbyte544:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte544);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+544);
readbyte545:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte545);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+545);
readbyte546:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte546);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+546);
readbyte547:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte547);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+547);
readbyte548:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte548);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+548);
readbyte549:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte549);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+549);
readbyte550:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte550);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+550);
readbyte551:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte551);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+551);
readbyte552:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte552);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+552);
readbyte553:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte553);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+553);
readbyte554:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte554);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+554);
readbyte555:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte555);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+555);
readbyte556:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte556);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+556);
readbyte557:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte557);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+557);
readbyte558:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte558);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+558);
readbyte559:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte559);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+559);
readbyte560:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte560);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+560);
readbyte561:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte561);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+561);
readbyte562:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte562);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+562);
readbyte563:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte563);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+563);
readbyte564:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte564);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+564);
readbyte565:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte565);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+565);
readbyte566:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte566);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+566);
readbyte567:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte567);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+567);
readbyte568:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte568);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+568);
readbyte569:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte569);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+569);
readbyte570:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte570);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+570);
readbyte571:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte571);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+571);
readbyte572:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte572);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+572);
readbyte573:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte573);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+573);
readbyte574:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte574);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+574);
readbyte575:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte575);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+575);
readbyte576:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte576);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+576);
readbyte577:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte577);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+577);
readbyte578:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte578);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+578);
readbyte579:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte579);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+579);
readbyte580:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte580);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+580);
readbyte581:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte581);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+581);
readbyte582:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte582);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+582);
readbyte583:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte583);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+583);
readbyte584:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte584);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+584);
readbyte585:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte585);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+585);
readbyte586:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte586);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+586);
readbyte587:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte587);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+587);
readbyte588:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte588);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+588);
readbyte589:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte589);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+589);
readbyte590:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte590);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+590);
readbyte591:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte591);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+591);
readbyte592:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte592);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+592);
readbyte593:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte593);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+593);
readbyte594:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte594);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+594);
readbyte595:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte595);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+595);
readbyte596:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte596);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+596);
readbyte597:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte597);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+597);
readbyte598:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte598);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+598);
readbyte599:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte599);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+599);
readbyte600:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte600);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+600);
readbyte601:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte601);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+601);
readbyte602:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte602);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+602);
readbyte603:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte603);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+603);
readbyte604:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte604);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+604);
readbyte605:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte605);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+605);
readbyte606:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte606);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+606);
readbyte607:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte607);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+607);
readbyte608:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte608);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+608);
readbyte609:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte609);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+609);
readbyte610:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte610);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+610);
readbyte611:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte611);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+611);
readbyte612:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte612);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+612);
readbyte613:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte613);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+613);
readbyte614:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte614);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+614);
readbyte615:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte615);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+615);
readbyte616:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte616);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+616);
readbyte617:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte617);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+617);
readbyte618:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte618);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+618);
readbyte619:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte619);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+619);
readbyte620:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte620);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+620);
readbyte621:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte621);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+621);
readbyte622:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte622);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+622);
readbyte623:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte623);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+623);
readbyte624:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte624);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+624);
readbyte625:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte625);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+625);
readbyte626:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte626);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+626);
readbyte627:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte627);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+627);
readbyte628:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte628);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+628);
readbyte629:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte629);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+629);
readbyte630:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte630);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+630);
readbyte631:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte631);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+631);
readbyte632:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte632);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+632);
readbyte633:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte633);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+633);
readbyte634:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte634);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+634);
readbyte635:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte635);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+635);
readbyte636:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte636);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+636);
readbyte637:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte637);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+637);
readbyte638:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte638);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+638);
readbyte639:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte639);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+639);
readbyte640:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte640);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+640);
readbyte641:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte641);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+641);
readbyte642:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte642);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+642);
readbyte643:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte643);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+643);
readbyte644:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte644);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+644);
readbyte645:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte645);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+645);
readbyte646:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte646);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+646);
readbyte647:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte647);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+647);
readbyte648:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte648);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+648);
readbyte649:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte649);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+649);
readbyte650:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte650);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+650);
readbyte651:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte651);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+651);
readbyte652:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte652);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+652);
readbyte653:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte653);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+653);
readbyte654:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte654);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+654);
readbyte655:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte655);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+655);
readbyte656:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte656);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+656);
readbyte657:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte657);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+657);
readbyte658:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte658);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+658);
readbyte659:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte659);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+659);
readbyte660:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte660);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+660);
readbyte661:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte661);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+661);
readbyte662:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte662);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+662);
readbyte663:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte663);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+663);
readbyte664:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte664);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+664);
readbyte665:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte665);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+665);
readbyte666:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte666);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+666);
readbyte667:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte667);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+667);
readbyte668:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte668);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+668);
readbyte669:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte669);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+669);
readbyte670:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte670);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+670);
readbyte671:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte671);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+671);
readbyte672:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte672);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+672);
readbyte673:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte673);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+673);
readbyte674:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte674);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+674);
readbyte675:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte675);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+675);
readbyte676:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte676);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+676);
readbyte677:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte677);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+677);
readbyte678:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte678);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+678);
readbyte679:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte679);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+679);
readbyte680:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte680);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+680);
readbyte681:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte681);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+681);
readbyte682:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte682);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+682);
readbyte683:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte683);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+683);
readbyte684:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte684);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+684);
readbyte685:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte685);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+685);
readbyte686:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte686);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+686);
readbyte687:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte687);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+687);
readbyte688:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte688);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+688);
readbyte689:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte689);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+689);
readbyte690:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte690);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+690);
readbyte691:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte691);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+691);
readbyte692:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte692);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+692);
readbyte693:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte693);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+693);
readbyte694:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte694);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+694);
readbyte695:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte695);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+695);
readbyte696:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte696);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+696);
readbyte697:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte697);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+697);
readbyte698:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte698);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+698);
readbyte699:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte699);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+699);
readbyte700:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte700);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+700);
readbyte701:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte701);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+701);
readbyte702:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte702);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+702);
readbyte703:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte703);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+703);
readbyte704:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte704);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+704);
readbyte705:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte705);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+705);
readbyte706:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte706);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+706);
readbyte707:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte707);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+707);
readbyte708:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte708);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+708);
readbyte709:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte709);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+709);
readbyte710:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte710);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+710);
readbyte711:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte711);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+711);
readbyte712:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte712);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+712);
readbyte713:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte713);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+713);
readbyte714:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte714);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+714);
readbyte715:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte715);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+715);
readbyte716:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte716);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+716);
readbyte717:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte717);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+717);
readbyte718:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte718);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+718);
readbyte719:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte719);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+719);
readbyte720:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte720);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+720);
readbyte721:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte721);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+721);
readbyte722:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte722);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+722);
readbyte723:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte723);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+723);
readbyte724:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte724);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+724);
readbyte725:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte725);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+725);
readbyte726:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte726);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+726);
readbyte727:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte727);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+727);
readbyte728:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte728);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+728);
readbyte729:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte729);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+729);
readbyte730:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte730);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+730);
readbyte731:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte731);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+731);
readbyte732:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte732);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+732);
readbyte733:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte733);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+733);
readbyte734:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte734);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+734);
readbyte735:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte735);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+735);
readbyte736:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte736);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+736);
readbyte737:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte737);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+737);
readbyte738:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte738);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+738);
readbyte739:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte739);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+739);
readbyte740:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte740);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+740);
readbyte741:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte741);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+741);
readbyte742:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte742);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+742);
readbyte743:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte743);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+743);
readbyte744:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte744);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+744);
readbyte745:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte745);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+745);
readbyte746:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte746);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+746);
readbyte747:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte747);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+747);
readbyte748:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte748);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+748);
readbyte749:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte749);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+749);
readbyte750:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte750);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+750);
readbyte751:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte751);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+751);
readbyte752:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte752);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+752);
readbyte753:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte753);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+753);
readbyte754:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte754);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+754);
readbyte755:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte755);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+755);
readbyte756:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte756);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+756);
readbyte757:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte757);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+757);
readbyte758:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte758);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+758);
readbyte759:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte759);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+759);
readbyte760:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte760);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+760);
readbyte761:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte761);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+761);
readbyte762:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte762);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+762);
readbyte763:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte763);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+763);
readbyte764:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte764);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+764);
readbyte765:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte765);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+765);
readbyte766:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte766);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+766);
readbyte767:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte767);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+767);
readbyte768:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte768);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+768);
readbyte769:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte769);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+769);
readbyte770:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte770);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+770);
readbyte771:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte771);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+771);
readbyte772:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte772);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+772);
readbyte773:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte773);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+773);
readbyte774:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte774);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+774);
readbyte775:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte775);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+775);
readbyte776:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte776);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+776);
readbyte777:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte777);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+777);
readbyte778:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte778);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+778);
readbyte779:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte779);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+779);
readbyte780:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte780);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+780);
readbyte781:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte781);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+781);
readbyte782:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte782);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+782);
readbyte783:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte783);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+783);
readbyte784:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte784);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+784);
readbyte785:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte785);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+785);
readbyte786:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte786);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+786);
readbyte787:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte787);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+787);
readbyte788:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte788);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+788);
readbyte789:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte789);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+789);
readbyte790:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte790);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+790);
readbyte791:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte791);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+791);
readbyte792:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte792);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+792);
readbyte793:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte793);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+793);
readbyte794:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte794);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+794);
readbyte795:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte795);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+795);
readbyte796:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte796);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+796);
readbyte797:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte797);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+797);
readbyte798:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte798);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+798);
readbyte799:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte799);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+799);
readbyte800:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte800);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+800);
readbyte801:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte801);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+801);
readbyte802:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte802);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+802);
readbyte803:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte803);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+803);
readbyte804:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte804);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+804);
readbyte805:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte805);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+805);
readbyte806:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte806);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+806);
readbyte807:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte807);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+807);
readbyte808:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte808);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+808);
readbyte809:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte809);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+809);
readbyte810:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte810);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+810);
readbyte811:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte811);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+811);
readbyte812:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte812);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+812);
readbyte813:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte813);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+813);
readbyte814:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte814);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+814);
readbyte815:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte815);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+815);
readbyte816:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte816);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+816);
readbyte817:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte817);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+817);
readbyte818:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte818);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+818);
readbyte819:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte819);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+819);
readbyte820:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte820);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+820);
readbyte821:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte821);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+821);
readbyte822:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte822);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+822);
readbyte823:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte823);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+823);
readbyte824:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte824);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+824);
readbyte825:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte825);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+825);
readbyte826:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte826);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+826);
readbyte827:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte827);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+827);
readbyte828:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte828);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+828);
readbyte829:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte829);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+829);
readbyte830:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte830);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+830);
readbyte831:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte831);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+831);
readbyte832:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte832);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+832);
readbyte833:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte833);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+833);
readbyte834:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte834);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+834);
readbyte835:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte835);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+835);
readbyte836:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte836);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+836);
readbyte837:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte837);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+837);
readbyte838:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte838);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+838);
readbyte839:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte839);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+839);
readbyte840:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte840);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+840);
readbyte841:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte841);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+841);
readbyte842:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte842);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+842);
readbyte843:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte843);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+843);
readbyte844:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte844);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+844);
readbyte845:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte845);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+845);
readbyte846:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte846);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+846);
readbyte847:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte847);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+847);
readbyte848:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte848);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+848);
readbyte849:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte849);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+849);
readbyte850:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte850);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+850);
readbyte851:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte851);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+851);
readbyte852:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte852);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+852);
readbyte853:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte853);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+853);
readbyte854:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte854);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+854);
readbyte855:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte855);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+855);
readbyte856:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte856);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+856);
readbyte857:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte857);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+857);
readbyte858:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte858);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+858);
readbyte859:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte859);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+859);
readbyte860:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte860);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+860);
readbyte861:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte861);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+861);
readbyte862:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte862);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+862);
readbyte863:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte863);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+863);
readbyte864:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte864);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+864);
readbyte865:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte865);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+865);
readbyte866:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte866);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+866);
readbyte867:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte867);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+867);
readbyte868:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte868);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+868);
readbyte869:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte869);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+869);
readbyte870:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte870);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+870);
readbyte871:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte871);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+871);
readbyte872:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte872);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+872);
readbyte873:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte873);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+873);
readbyte874:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte874);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+874);
readbyte875:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte875);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+875);
readbyte876:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte876);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+876);
readbyte877:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte877);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+877);
readbyte878:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte878);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+878);
readbyte879:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte879);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+879);
readbyte880:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte880);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+880);
readbyte881:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte881);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+881);
readbyte882:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte882);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+882);
readbyte883:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte883);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+883);
readbyte884:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte884);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+884);
readbyte885:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte885);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+885);
readbyte886:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte886);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+886);
readbyte887:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte887);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+887);
readbyte888:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte888);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+888);
readbyte889:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte889);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+889);
readbyte890:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte890);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+890);
readbyte891:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte891);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+891);
readbyte892:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte892);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+892);
readbyte893:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte893);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+893);
readbyte894:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte894);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+894);
readbyte895:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte895);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+895);
readbyte896:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte896);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+896);
readbyte897:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte897);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+897);
readbyte898:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte898);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+898);
readbyte899:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte899);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+899);
readbyte900:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte900);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+900);
readbyte901:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte901);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+901);
readbyte902:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte902);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+902);
readbyte903:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte903);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+903);
readbyte904:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte904);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+904);
readbyte905:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte905);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+905);
readbyte906:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte906);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+906);
readbyte907:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte907);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+907);
readbyte908:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte908);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+908);
readbyte909:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte909);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+909);
readbyte910:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte910);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+910);
readbyte911:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte911);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+911);
readbyte912:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte912);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+912);
readbyte913:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte913);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+913);
readbyte914:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte914);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+914);
readbyte915:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte915);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+915);
readbyte916:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte916);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+916);
readbyte917:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte917);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+917);
readbyte918:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte918);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+918);
readbyte919:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte919);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+919);
readbyte920:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte920);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+920);
readbyte921:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte921);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+921);
readbyte922:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte922);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+922);
readbyte923:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte923);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+923);
readbyte924:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte924);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+924);
readbyte925:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte925);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+925);
readbyte926:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte926);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+926);
readbyte927:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte927);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+927);
readbyte928:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte928);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+928);
readbyte929:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte929);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+929);
readbyte930:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte930);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+930);
readbyte931:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte931);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+931);
readbyte932:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte932);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+932);
readbyte933:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte933);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+933);
readbyte934:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte934);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+934);
readbyte935:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte935);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+935);
readbyte936:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte936);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+936);
readbyte937:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte937);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+937);
readbyte938:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte938);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+938);
readbyte939:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte939);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+939);
readbyte940:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte940);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+940);
readbyte941:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte941);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+941);
readbyte942:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte942);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+942);
readbyte943:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte943);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+943);
readbyte944:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte944);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+944);
readbyte945:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte945);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+945);
readbyte946:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte946);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+946);
readbyte947:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte947);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+947);
readbyte948:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte948);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+948);
readbyte949:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte949);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+949);
readbyte950:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte950);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+950);
readbyte951:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte951);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+951);
readbyte952:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte952);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+952);
readbyte953:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte953);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+953);
readbyte954:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte954);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+954);
readbyte955:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte955);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+955);
readbyte956:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte956);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+956);
readbyte957:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte957);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+957);
readbyte958:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte958);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+958);
readbyte959:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte959);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+959);
readbyte960:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte960);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+960);
readbyte961:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte961);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+961);
readbyte962:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte962);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+962);
readbyte963:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte963);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+963);
readbyte964:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte964);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+964);
readbyte965:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte965);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+965);
readbyte966:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte966);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+966);
readbyte967:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte967);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+967);
readbyte968:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte968);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+968);
readbyte969:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte969);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+969);
readbyte970:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte970);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+970);
readbyte971:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte971);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+971);
readbyte972:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte972);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+972);
readbyte973:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte973);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+973);
readbyte974:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte974);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+974);
readbyte975:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte975);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+975);
readbyte976:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte976);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+976);
readbyte977:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte977);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+977);
readbyte978:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte978);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+978);
readbyte979:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte979);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+979);
readbyte980:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte980);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+980);
readbyte981:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte981);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+981);
readbyte982:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte982);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+982);
readbyte983:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte983);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+983);
readbyte984:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte984);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+984);
readbyte985:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte985);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+985);
readbyte986:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte986);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+986);
readbyte987:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte987);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+987);
readbyte988:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte988);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+988);
readbyte989:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte989);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+989);
readbyte990:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte990);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+990);
readbyte991:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte991);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+991);
readbyte992:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte992);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+992);
readbyte993:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte993);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+993);
readbyte994:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte994);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+994);
readbyte995:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte995);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+995);
readbyte996:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte996);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+996);
readbyte997:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte997);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+997);
readbyte998:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte998);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+998);
readbyte999:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", readbyte999);
    asm("lda %w", USERPORT_DATA);
    asm("stx %w", CA1_TRIGGER);
    asm("sta %w", VMEM_START+999);


        //TEST
        //key = PEEK(CURR_KEY);
    asm("lda %w", CURR_KEY);
    asm("cmp #$40");
    asm("beq %g", done);
    asm("jmp %g", readbyte0);
done:
	return EXIT_SUCCESS;
}
