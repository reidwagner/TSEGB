# TSE Z80 Emulator

Implemented instructions. Values found in [disassembly tables](http://www.z80.info/decoding.htm) - r: 8-bit register, cc: conditional.

- NOP
- ADD A, r
- SUB A, r
- ADC A, r
- AND A, r
- XOR A, r
- OR A, r
- LD r, n
- LD (HL), n
- JP cc, n
- HALT

The [zasm](https://k1.spdns.de/Develop/Projects/zasm/Distributions/) assembler can be used to assemble the programs in assembly/src/.

Resources:
- http://sgate.emt.bme.hu/patai/publications/z80guide/
- http://www.z80.info/
