bits 32

global idt_load

global exception_0x00

global interrupt_0x20
global interrupt_0x21
global interrupt_0x24

extern pit_isr
extern kbd_isr
extern com_1_interrupt
extern div_by_0

extern idtp

idt_load:							;loads the idt
	lidt[idtp]					;idtp points to the idt
	sti
	ret

exception_0x00:
	pusha
	cld

	call div_by_0
	
	popa
	iret

interrupt_0x20:
	pusha
	cld

	call pit_isr

	popa
	iret

interrupt_0x21:
	pusha
	cld

	call kbd_isr

	popa
	iret

interrupt_0x24:
	pusha
	cld

	call com_1_interrupt

	popa
	iret
