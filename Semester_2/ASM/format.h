#ifndef ASM_FORMAT_H
#define ASM_FORMAT_H

#define TRUE 1
#define FALSE 0

#define RET 0
#define LD 1
#define ST 2
#define LDC 3
#define ADD 4
#define SUB 5
#define CMP 6
#define JMP 7
#define BR 8

#define RET_TEXT "ret"
#define LD_TEXT  "ld"
#define ST_TEXT  "st"
#define LDC_TEXT "ldc"
#define ADD_TEXT "add"
#define SUB_TEXT "sub"
#define CMP_TEXT "cmp"
#define JMP_TEXT "jmp"
#define BR_TEXT  "br"

#define MAX_STRING_LEN 255

#define DATA_SIZE 1 << 18

#endif
