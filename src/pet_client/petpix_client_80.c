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
#define VMEM_START_1    0x8000
#define VMEM_START_2    0x8100
#define VMEM_START_3    0x8200
#define VMEM_START_4    0x8300
#define VMEM_START_5    0x8400
#define VMEM_START_6    0x8500
#define VMEM_START_7    0x8600
#define VMEM_START_8    0x8700

#define CURR_KEY        0x0097
#define Q_KEY           81

#define RUN_STOP 3

int main (void)
{
    unsigned char data;
    unsigned char key = 0;
    
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
    asm("ldx #$00");

    jumper1:
j1wait0:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j1wait0);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$ED");
    asm("sta %w,x", VMEM_START_1);
    asm("inx");
j1wait1:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j1wait1);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$CD");
    asm("sta %w,x", VMEM_START_1);
    asm("inx");
    asm("bne %g", jumper1);
jumper2:
j2wait0:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j2wait0);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$ED");
    asm("sta %w,x", VMEM_START_2);
    asm("inx");
j2wait1:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j2wait1);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$CD");
    asm("sta %w,x", VMEM_START_2);
    asm("inx");
    asm("bne %g", jumper2);
jumper3:
j3wait0:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j3wait0);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$ED");
    asm("sta %w,x", VMEM_START_3);
    asm("inx");
j3wait1:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j3wait1);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$CD");
    asm("sta %w,x", VMEM_START_3);
    asm("inx");
    asm("bne %g", jumper3);
jumper4:
j4wait0:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j4wait0);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$ED");
    asm("sta %w,x", VMEM_START_4);
    asm("inx");
j4wait1:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j4wait1);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$CD");
    asm("sta %w,x", VMEM_START_4);
    asm("inx");
    asm("bne %g", jumper4);
jumper5:
j5wait0:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j5wait0);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$ED");
    asm("sta %w,x", VMEM_START_5);
    asm("inx");
j5wait1:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j5wait1);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$CD");
    asm("sta %w,x", VMEM_START_5);
    asm("inx");
    asm("bne %g", jumper5);
jumper6:
j6wait0:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j6wait0);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$ED");
    asm("sta %w,x", VMEM_START_6);
    asm("inx");
j6wait1:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j6wait1);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$CD");
    asm("sta %w,x", VMEM_START_6);
    asm("inx");
    asm("bne %g", jumper6);
jumper7:
j7wait0:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j7wait0);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$ED");
    asm("sta %w,x", VMEM_START_7);
    asm("inx");
j7wait1:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j7wait1);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$CD");
    asm("sta %w,x", VMEM_START_7);
    asm("inx");
    asm("bne %g", jumper7);
jumper8:
j8wait0:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j8wait0);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$ED");
    asm("sta %w,x", VMEM_START_8);
    asm("inx");
j8wait1:
    asm("lda %w", CA1_STATUS);
    asm("and #$02");
    asm("beq %g", j8wait1);
    asm("lda %w", USERPORT_DATA);
    asm("sty %w", CA1_TRIGGER);
    asm("ldy #$CD");
    asm("sta %w,x", VMEM_START_8);
    asm("inx");
    asm("bne %g", jumper8);



    //TEST
        //key = PEEK(CURR_KEY);
    asm("lda %w", CURR_KEY);
    asm("cmp #$51");
    asm("beq %g", done);
    asm("jmp %g", jumper1);
done:
    return EXIT_SUCCESS;
}