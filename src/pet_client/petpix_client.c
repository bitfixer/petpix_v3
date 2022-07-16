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
    
    while(key != Q_KEY)
    {
        // load 1000 bytes from the userport
        asm("lda %w", CA1_TRIGGER);
        asm("ora #$E0");
        asm("tay");

    pagestart:
        // raise CB2
        asm("ldx #$00");
    
    jumper1:

    j1waita:
        // wait for CA1
        asm("lda %w", CA1_STATUS);
        asm("and #$02");
        asm("beq %g", j1waita);

        // load byte from userport, save to video memory
        // this should reset CA1 bit
        asm("lda %w", USERPORT_DATA);
        asm("sta %w,x", VMEM_START);
        
        // set CB2 line low
        asm("tya");
        asm("and #$DF");
        asm("sta %w", CA1_TRIGGER);
        
        // step video mem pointer
        asm("inx");

    j1waitb:
        // wait for CA1
        asm("lda %w", CA1_STATUS);
        asm("and #$02");
        asm("beq %g", j1waitb);

        // load byte from userport, save to video memory
        asm("lda %w", USERPORT_DATA);
        asm("sta %w,x", VMEM_START);
        
        // set CB2 line high
        asm("tya");
        asm("ora #$E0");
        asm("sta %w", CA1_TRIGGER);
        
        // step video mem pointer
        asm("inx");
        // jump if x != 0
        asm("bne %g", jumper1);

    jumper2:

    j2waita:
        // wait for CA1
        asm("lda %w", CA1_STATUS);
        asm("and #$02");
        asm("beq %g", j2waita);

        // load byte from userport, save to video memory
        // this should reset CA1 bit
        asm("lda %w", USERPORT_DATA);
        asm("sta %w,x", VMEM_START_2);
        
        // set CB2 line low
        asm("tya");
        asm("and #$DF");
        asm("sta %w", CA1_TRIGGER);
        
        // step video mem pointer
        asm("inx");

    j2waitb:
        // wait for CA1
        asm("lda %w", CA1_STATUS);
        asm("and #$02");
        asm("beq %g", j2waitb);

        // load byte from userport, save to video memory
        asm("lda %w", USERPORT_DATA);
        asm("sta %w,x", VMEM_START_2);
        
        // set CB2 line high
        asm("tya");
        asm("ora #$E0");
        asm("sta %w", CA1_TRIGGER);
        
        // step video mem pointer
        asm("inx");
        // jump if x != 0
        asm("bne %g", jumper2);

    jumper3:

    j3waita:
        // wait for CA1
        asm("lda %w", CA1_STATUS);
        asm("and #$02");
        asm("beq %g", j3waita);

        // load byte from userport, save to video memory
        // this should reset CA1 bit
        asm("lda %w", USERPORT_DATA);
        asm("sta %w,x", VMEM_START_3);
        
        // set CB2 line low
        asm("tya");
        asm("and #$DF");
        asm("sta %w", CA1_TRIGGER);
        
        // step video mem pointer
        asm("inx");

    j3waitb:
        // wait for CA1
        asm("lda %w", CA1_STATUS);
        asm("and #$02");
        asm("beq %g", j3waitb);

        // load byte from userport, save to video memory
        asm("lda %w", USERPORT_DATA);
        asm("sta %w,x", VMEM_START_3);
        
        // set CB2 line high
        asm("tya");
        asm("ora #$E0");
        asm("sta %w", CA1_TRIGGER);
        
        // step video mem pointer
        asm("inx");
        // jump if x != 0
        asm("bne %g", jumper3);

    jumper4:

    j4waita:
        // wait for CA1
        asm("lda %w", CA1_STATUS);
        asm("and #$02");
        asm("beq %g", j4waita);

        // load byte from userport, save to video memory
        // this should reset CA1 bit
        asm("lda %w", USERPORT_DATA);
        asm("sta %w,x", VMEM_START_4);
        
        // set CB2 line low
        asm("tya");
        asm("and #$DF");
        asm("sta %w", CA1_TRIGGER);
        
        // step video mem pointer
        asm("inx");

    j4waitb:
        // wait for CA1
        asm("lda %w", CA1_STATUS);
        asm("and #$02");
        asm("beq %g", j4waitb);

        // load byte from userport, save to video memory
        asm("lda %w", USERPORT_DATA);
        asm("sta %w,x", VMEM_START_4);
        
        // set CB2 line high
        asm("tya");
        asm("ora #$E0");
        asm("sta %w", CA1_TRIGGER);
        
        // step video mem pointer
        asm("inx");
        // jump if x != 0
        asm("bne %g", jumper4);
        
        //TEST
        key = PEEK(CURR_KEY);
    }
	return EXIT_SUCCESS;
}
