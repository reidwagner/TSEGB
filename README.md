# TSE Z80 Emulator

Restarting in C a Z80 project I began last year in Rust. Want to focus more on the emulator than on a new language. Just begun this weekend so it runs only one program, found in assembly/.

Implemented instructions are: 
- NOP
- ADD A, B
- LD A, n
- LD B, n
- LD (HL), a
- HALT

Resources:
- http://sgate.emt.bme.hu/patai/publications/z80guide/ - The Z80 code in assembly/src
- http://www.z80.info/
