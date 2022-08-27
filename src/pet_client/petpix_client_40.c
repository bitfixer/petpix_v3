#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <peekpoke.h> 
#include <time.h>
#include <pet.h>
#include <string.h>

#define CA1_TRIGGER     0xE84C
#define CA1_DATA_LATCH  0xE84B
#define CA1_STATUS      0xE84D
#define USERPORT_DATA   0xE841
#define VMEM_START_1    0x8000
#define VMEM_START_2    0x8100
#define VMEM_START_3    0x8200
#define VMEM_START_4    0x82E8

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
        asm("ldy #$CD");

    pagestart:
        // raise CB2
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

        asm("ldx #$18");
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
        
        key = PEEK(CURR_KEY);
    }
	return EXIT_SUCCESS;
}
