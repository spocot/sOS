.section .init
.global _init
.type _init, @function
_init:
    push %rbp
    movq %rsp, %rbp
    /* gcc will put crtbegin.o's .init here */

.section .fini
.global _fini
.type _fini, @function
_fini:
    push %rbp
    movq %rsp, %rbp
    /* gcc will put crtbegin.o's .fini here */
