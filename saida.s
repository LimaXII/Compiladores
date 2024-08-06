# --------------------
# SEGMENTO DE DADOS
# --------------------
.data
# ->Variáveis globais
global0:	.long	0
global1:	.long	0
global2:	.long	0
# ->Registradores ASM
_temp_r_0:	.long	0
_temp_r_1:	.long	0
_temp_r_2:	.long	0
_temp_r_3:	.long	0
_temp_r_4:	.long	0
_temp_r_5:	.long	0
# --------------------
# SEGMENTO DE CÓDIGO
# --------------------
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq %rsp, %rbp
	movl $4, _temp_r_0(%rip)
	movl _temp_r_0(%rip), %edx
	movl %edx, global1(%rip)
	movl $9, _temp_r_1(%rip)
	movl _temp_r_1(%rip), %edx
	movl %edx, global2(%rip)
	movl global2(%rip), %edx
	movl %edx, _temp_r_2(%rip)
	movl global1(%rip), %edx
	movl %edx, _temp_r_3(%rip)
    movl    _temp_r_2(%rip), %eax 
    movl    _temp_r_3(%rip), %edx 
    addl    %edx, %eax 
    movl    %eax, _temp_r_4(%rip) 
	movl _temp_r_4(%rip), %edx
	movl %edx, global0(%rip)
	movl global0(%rip), %edx
	movl %edx, _temp_r_5(%rip)
	movl _temp_r_5(%rip), %eax
	popq %rbp
	ret
