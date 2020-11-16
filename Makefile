# Setup commands for building:
CP 							:= 	cp
RM 							:= 	rm -rf
MKDIR 						:= 	mkdir -pv

INCLUDE_PATH				:= 	-Iinclude
DEFAULT_INCLUDE_PATH		:= 	$(INCLUDE_PATH)
LINKER						:= 	i686-elf-gcc -T linker.ld
NASM						:=	nasm -f elf32
ASM							:= 	i686-elf-as
COMPILER_C					:= 	i686-elf-gcc -c
COMPILER_CPP				:=	i686-elf-g++ -c
CPP_FLAGS					:= 	-ffreestanding -nostdlib -Wall -Wextra $(DEFAULT_INCLUDE_PATH)
C_FLAGS						:= 	-std=gnu99 $(CPP_FLAGS)


# Set the basic paths and compilation:
BIN 						:= 	aos32.bin
CFG 						:= 	grub.cfg
ISO_PATH 					:= 	iso
ISO_FILE					:= 	AdamantineOS_0.04-4a.iso
ISO_OUTPUT_PATH				:= 	build/
ISO_OUTPUT					:= 	$(ISO_OUTPUT_PATH)/$(ISO_FILE)
BOOT_PATH					:= 	$(ISO_PATH)/boot
GRUB_PATH					:= 	$(BOOT_PATH)/grub

# Setup OS specific directories:
ADAMANTINE_PATH				:= 	adamantine
ASSEMB_PATH					:= 	asm
FS_PATH						:=	filesys
INIT_PATH					:= 	security
KERNEL_PATH					:= 	kernel
DRIVER_PATH					:= 	$(KERNEL_PATH)/drivers
MEMORY_PATH					:= 	$(KERNEL_PATH)/memory
SYSTEM_PATH					:= 	$(KERNEL_PATH)/system
X86_PATH					:=	$(KERNEL_PATH)/x86
LIB_PATH					:= 	lib
MAIN_PATH					:= 	main
SECURITY_PATH				:=	security
TOOL_PATH					:= 	tool
USER_PATH					:= 	user
MATH_PATH					:= 	math

ASM_FILES_IN				:=	$(ASSEMB_PATH)/boot/boot.S		\
								$(ASSEMB_PATH)/boot/crti.S		\
								$(ASSEMB_PATH)/boot/crtn.S		\
								$(ASSEMB_PATH)/boot/test.S		\
								$(ASSEMB_PATH)/descriptors.asm	\
								$(ASSEMB_PATH)/interrupt.asm	\
								$(ASSEMB_PATH)/cpuid.asm		\
								$(ASSEMB_PATH)/setup.S

C_FILES_IN					:=	$(MAIN_PATH)/main.c				\
								$(KERNEL_PATH)/adamantine.c	\
								$(KERNEL_PATH)/cmd.c			\
								$(KERNEL_PATH)/cpu.c			\
								$(KERNEL_PATH)/mutex.c			\
								$(DRIVER_PATH)/device.c			\
								$(DRIVER_PATH)/keyboard.c		\
								$(FS_PATH)/aos32/aos-fs.c		\
								$(FS_PATH)/ext2/ext2.c			\
								$(FS_PATH)/vfs.c				\
								$(LIB_PATH)/string.c			\
								$(MEMORY_PATH)/balloon.c		\
								$(MEMORY_PATH)/mem-util.c		\
								$(SECURITY_PATH)/centrix.c		\
								$(SYSTEM_PATH)/io.c				\
								$(KERNEL_PATH)/irq.c			\
								$(KERNEL_PATH)/isr.c			\
								$(KERNEL_PATH)/pic.c			\
								$(KERNEL_PATH)/pit.c			\
								$(SYSTEM_PATH)/system.c			\
								$(SYSTEM_PATH)/terminal.c		\
								$(X86_PATH)/descriptor-tables.c	\
								$(MEMORY_PATH)/paging.c
								#$(X86_PATH)/gdt.c				\
								#$(X86_PATH)/idt.c				\
								$(X86_PATH)/tss.c				\
								$(X86_PATH)/syscall.c			\
								$(MATH_PATH)/math-util.c		\
								task/task.c						

# Put all input files here separated by a '\':
OUTPUT_FILES 				:= 	boot.o			\
								descriptors.o	\
								interrupt.o		\
								adamantine.o	\
								cpuid.o			\
								timer.o			\
								setup.o			\
								main.o			\
								cmd.o			\
								cpu.o			\
								mutex.o			\
								device.o		\
								keyboard.o		\
								aos-fs.o		\
								ext2.o			\
								vfs.o			\
								string.o		\
								balloon.o		\
								mem-util.o		\
								centrix.o		\
								io.o			\
								irq.o			\
								isr.o			\
								pic.o			\
								pit.o			\
								system.o		\
								terminal.o		\
								descriptor-tables.o \
								paging.o

# AOS_OUTPUT					:= 	$(AOS_DIR)/Adamantine.o	\
# 								$(AOS_DIR)/Registry.o	

# Compile all of the files into the iso:
.PHONY: all
all: bootloader kernel linker iso
	@echo Make has completed compilation of AdamantineOS Kernel.

# Compile the bootloader files:
bootloader: $(ASM_FILES_IN)
	$(ASM) $(ASSEMB_PATH)/boot/boot.S				-o boot.o
	$(NASM) $(ASSEMB_PATH)/descriptors.asm			-o descriptors.o
	$(NASM) $(ASSEMB_PATH)/interrupt.asm			-o interrupt.o
	$(NASM)	$(ASSEMB_PATH)/cpuid.asm				-o cpuid.o
	$(NASM)	$(ASSEMB_PATH)/timer.asm				-o timer.o
	$(COMPILER_C) $(ASSEMB_PATH)/setup.S			-o setup.o

# Compile the kernel files:
kernel: $(C_FILES_IN)
	$(COMPILER_C) $(DRIVER_PATH)/device.c -o device.o $(C_FLAGS)
	$(COMPILER_C) $(DRIVER_PATH)/keyboard.c -o keyboard.o $(C_FLAGS)
	$(COMPILER_C) $(FS_PATH)/aos32/aos-fs.c -o aos-fs.o $(C_FLAGS)
	$(COMPILER_C) $(FS_PATH)/ext2/ext2.c -o ext2.o $(C_FLAGS)
	$(COMPILER_C) $(FS_PATH)/vfs.c -o vfs.o $(C_FLAGS)
	$(COMPILER_C) $(KERNEL_PATH)/adamantine.c -o adamantine.o $(C_FLAGS)
	$(COMPILER_C) $(KERNEL_PATH)/cmd.c -o cmd.o $(C_FLAGS)
	$(COMPILER_C) $(KERNEL_PATH)/cpu.c -o cpu.o $(C_FLAGS)
	$(COMPILER_C) $(KERNEL_PATH)/mutex.c -o mutex.o $(C_FLAGS)
	$(COMPILER_C) $(KERNEL_PATH)/irq.c -o irq.o $(C_FLAGS)
	$(COMPILER_C) $(KERNEL_PATH)/isr.c -o isr.o $(C_FLAGS)
	$(COMPILER_C) $(KERNEL_PATH)/pic.c -o pic.o $(C_FLAGS)
	$(COMPILER_C) $(KERNEL_PATH)/pit.c -o pit.o $(C_FLAGS)
	$(COMPILER_C) $(LIB_PATH)/string.c -o string.o $(C_FLAGS)
	$(COMPILER_C) $(MAIN_PATH)/main.c -o main.o $(C_FLAGS)
	$(COMPILER_C) $(MATH_PATH)/math-util.c -o math-util.o $(C_FLAGS)
	$(COMPILER_C) $(MEMORY_PATH)/balloon.c -o balloon.o $(C_FLAGS)
	$(COMPILER_C) $(MEMORY_PATH)/mem-util.c -o mem-util.o $(C_FLAGS)
	$(COMPILER_C) $(SECURITY_PATH)/centrix.c -o centrix.o $(C_FLAGS)
	$(COMPILER_C) $(SYSTEM_PATH)/io.c -o io.o $(C_FLAGS)
	$(COMPILER_C) $(SYSTEM_PATH)/system.c -o system.o $(C_FLAGS)
	$(COMPILER_C) $(SYSTEM_PATH)/terminal.c -o terminal.o $(C_FLAGS)
	$(COMPILER_C) $(X86_PATH)/descriptor-tables.c -o descriptor-tables.o $(C_FLAGS)
	$(COMPILER_C) $(MEMORY_PATH)/paging.c -o paging.o $(C_FLAGS)
	$(COMPILER_C) $(X86_PATH)/tss.c -o tss.o $(C_FLAGS)
	$(COMPILER_C) $(X86_PATH)/syscall.c -o syscall.o $(C_FLAGS)
 
# Link all input files into one file:
linker: linker.ld $(OUTPUT_FILES)
	$(LINKER) -o $(BIN) $(C_FLAGS) $(OUTPUT_FILES) -lgcc

# Build the Kernel iso:
iso: kernel
	$(MKDIR) $(GRUB_PATH)
	$(CP) $(BIN) $(BOOT_PATH)
	$(CP) $(CFG) $(GRUB_PATH)
	grub-file --is-x86-multiboot $(BOOT_PATH)/$(BIN)
	grub-mkrescue -o $(ISO_FILE) $(ISO_PATH)
	$(MKDIR) $(ISO_OUTPUT_PATH)
	$(CP) $(ISO_FILE) $(ISO_OUTPUT)
#	qemu-system-x86_64 -machine ubuntu -drive format=raw,file=$(ISO_FILE)
	qemu-system-i386 -cdrom $(ISO_FILE)
	$(RM) *.o $(BIN) *iso

# This might need to get updated...
.PHONY: clean
clean:
	$(RM) *.o $(BIN) *iso
