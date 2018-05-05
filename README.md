# TSE Z80 Emulator

Implemented instructions:

```
NOP           LD A,(BC)     DJNZ
ADD A,r       LD A,(DE)     HALT
SUB A,r       LD A,(nn)
ADC A,r       LD HL,(nn)
AND A,r       LD rp,nn
XOR A,r       ADD HL,rp
OR A,r        JP cc, nn
LD r,n        JP nn
LD (HL),n     INC rp
LD (BC),A     DEC rp
LD (DE),A     INC r
LD (nn),A     DEC r
LD (nn),HL    LD r,r
```

where r and cc are found in [disassembly tables](http://www.z80.info/decoding.htm).

The [zasm](https://k1.spdns.de/Develop/Projects/zasm/Distributions/) assembler can be used to assemble the programs in assembly/src/.

Resources:
- http://sgate.emt.bme.hu/patai/publications/z80guide/
- http://www.z80.info/
