.section .init
    /* gcc will put crtend.o's .init here */
    popq %rbp
    ret

.section .fini
    /* gcc will put crtend.o's .init here */
    popq %rbp
    ret
