# TSE Z80 Emulator

Restarting in C a Z80 project I began last year in Rust. Want to focus more on the emulator than on a new language.

Implemented instructions, with r being any 8-bit register:
- NOP
- ADD A, r
- ADC A, r
- AND A, r
- XOR A, r
- OR A, r
- LD r, n
- HALT

Resources:
- http://sgate.emt.bme.hu/patai/publications/z80guide/ - The Z80 code in assembly/src
- http://www.z80.info/
