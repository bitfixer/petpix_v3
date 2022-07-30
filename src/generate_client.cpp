#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int size = atoi(argv[1]);
    for (int i = 0; i < size; i+=2)
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
}