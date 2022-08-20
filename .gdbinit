set history file ~/.gdb_history
set history save on
set mi-async on
set confirm off
set mem inaccessible-by-default off
target extended-remote /dev/ttyACM0
monitor version
#On a STM32F103-based Black Magic Probe, baud rate has to be 4500000 divided by an integer: 4500000, 2250000, 1500000, 1125000, 900000, 750000, ... . On a bmp clone, 2250000 is a safe choice.
monitor traceswo 2250000 decode
monitor swdp_scan
#monitor jtag_scan
file build/bluepill-base.elf
attach 1
load
compare-sections