##$Id: Makefile 1.5 2014/11/25 14:50:43 ITS tnt $
##$Log: Makefile $
##Revision 1.5  2014/11/25 14:50:43  ITS
##Version from ITS
##Revision 1.5  2014/11/18 09:04:00  carsten
##Updated usercode and bootloader name
##Revision 1.4  2014/07/18 09:57:49  jacob
##Updated bootloader name
##Revision 1.3  2014/07/18 09:51:34  jacob
##Backup
##Revision 1.2  2014/06/18 08:24:39  jacob
##using avr.makeinc
##Revision 1.1  2014/06/17 14:25:12  jacob

PROGRAM_NAME	= SID88

# Source files here:
SOURCE =	Main.cpp		\
		avrutils.cpp
		
CODESIZE	:= 	0x1E000
CRCPATCHADRR	:= 	0x1DFFC

WINAVR_VERSION     = 3.4.2.1573

F_CPU              = 11059200UL	# Core freq in Hz

# Fuses 
FB_LOW	= FF

# Max boot sector size and boot into it too
FB_HIGH	= D8
FB_EXT	= FF

DEVICE = ATMEGA128

BOOTLOADERIMAGE = .//bootloader//SID88BL.bin

HWVERSION	= 1_00
OPTIMIZE	= -O2
DEFINES		+= -DHW101

include avr.makeinc 





