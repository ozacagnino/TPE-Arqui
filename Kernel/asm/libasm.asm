GLOBAL cpuVendor
GLOBAL get_hours
GLOBAL get_minutes
GLOBAL get_seconds



section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret


%macro enter_func 0
	push rbp
	mov rbp, rsp
%endmacro

%macro leave_func 0
	mov rsp, rbp
	pop rbp
	ret
%endmacro

%macro get_rtc_value 1
	xor rax, rax
	xor rdi, rdi
	mov al, 0x0B
	out 70h, al
	in al, 71h 
	or al, 0x04 
	out 71h, al
	mov al, %1
	out 70h, al
	in al, 71h
	mov rdi, rax
%endmacro


get_seconds:
	enter_func
	get_rtc_value 00
	leave_func

get_minutes:
	enter_func
	get_rtc_value 02
	leave_func

get_hours:
	enter_func
	get_rtc_value 04
	leave_func
