#include <stdio.h>

int main(int argc, char** argv)
{
    for (int i = 0; i < 1000; i+=2)
    {
        printf("readbyte%d:\n", i);
        printf("    asm(\"lda %%w\", CA1_STATUS);\n");
        printf("    asm(\"and #$02\");\n");
        printf("    asm(\"beq %%g\", readbyte%d);\n", i);
        printf("    asm(\"lda %%w\", USERPORT_DATA);\n");
        printf("    asm(\"sty %%w\", CA1_TRIGGER);\n");
        printf("    asm(\"sta %%w\", VMEM_START+%d);\n", i);

        printf("readbyte%d:\n", i+1);
        printf("    asm(\"lda %%w\", CA1_STATUS);\n");
        printf("    asm(\"and #$02\");\n");
        printf("    asm(\"beq %%g\", readbyte%d);\n", i+1);
        printf("    asm(\"lda %%w\", USERPORT_DATA);\n");
        printf("    asm(\"stx %%w\", CA1_TRIGGER);\n");
        printf("    asm(\"sta %%w\", VMEM_START+%d);\n", i+1);
    }

    /*
    bb0:
        // wait for CA1
        asm("lda %w", CA1_STATUS);
        asm("and #$02");
        asm("beq %g", bb0);
        // load byte from userport, save to video memory
        // this should reset CA1 bit
        asm("lda %w", USERPORT_DATA);
        // set CB2 line low
        asm("sty %w", CA1_TRIGGER);
        asm("sta %w,x", VMEM_START);
    bb1:
        // wait for CA1
        asm("lda %w", CA1_STATUS);
        asm("and #$02");
        asm("beq %g", bb1);
        // load byte from userport, save to video memory
        asm("lda %w", USERPORT_DATA);
        
        // set CB2 line high
        asm("stx %w", CA1_TRIGGER);
        asm("sta %w,x", VMEM_START);
    */
}