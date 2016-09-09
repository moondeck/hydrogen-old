extern page_dir_base

global paging_en

paging_en:
	cli
	mov eax,[page_dir_base]
	mov cr3,eax
	mov eax,cr0
	or eax,0x80000000
	mov cr0,eax
	sti
