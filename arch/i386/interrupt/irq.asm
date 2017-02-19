bits 32

global idt_load

global exception_0x00
global exception_0x0E

global interrupt_0x20
global interrupt_0x21
global interrupt_0x24

extern pit_isr
extern kbd_isr
extern com1_isr
extern div_by_0
extern page_fault

extern idtp

idt_load:							;loads the idt

	cli
	lidt[idtp+2]					;idtp points to the idt
	sti
	ret

;exceptions go here

exception_0x00:	;division by 0
	pusha
	cld

	call div_by_0

	popa
	iret

exception_0x0E:	;page fault
	pusha
	cld

	mov ecx,cr2
	call page_fault

	popa
	iret

;interrupts go here

interrupt_0x20:	;PIT interrupt
	pusha
	cld

	call pit_isr

	popa
	iret

interrupt_0x21:	;Keyboard interrupt
	pusha
	cld

	call kbd_isr

	popa
	iret

interrupt_0x24: ;serial port interrupt
	pusha
	cld

	call com1_isr

	popa
	iret
