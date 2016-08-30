OUTPUT_FORMAT(elf32-i386)
ENTRY(begin)
SECTIONS
 {
   . = 1M;
   .text : ALIGN(4K) 
   { 
		*(.text) 
   }
   .data : ALIGN(4K) 
   { 
                *(.rodata) 
		*(.data) 
   }
   .bss : ALIGN(4K) 
   { 
		*(.bss) 
   }
 }
