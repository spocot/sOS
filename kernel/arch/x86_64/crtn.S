.section .init
    /* gcc will put crtend.o's .init here */
    popl %ebp
    ret

.section .fini
    /* gcc will put crtend.o's .init here */
    popl %ebp
    ret
