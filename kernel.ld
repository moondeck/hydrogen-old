OUTPUT_FORMAT(elf32-i386)
ENTRY(begin)
SECTIONS
 {
   . = 0x1000000;
   kernel_start = .;

   .text : ALIGN(4K)
   {
		*(.text)
   }
   text_end = .;

   .data : ALIGN(4K)
   {
    *(.rodata)
		*(.data)
   }
   data_end = .;

   .bss : ALIGN(4K)
   {
		*(.bss)
   }
   bss_end = .;

   kernel_end = .;
 }
