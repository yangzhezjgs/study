movb $0xF, (%bl)
movl %ax, (%esp)
movw (%eax), 4(%esp)
movb %ah, %sh
movl %eax, $0x123
movl %eax, %dx
movb %si, 8(%ebp)
