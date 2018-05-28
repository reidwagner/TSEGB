# TSE Z80 Emulator

Implemented instructions:

```
NOP           LD A,(BC)     DJNZ          RET
ADD A,r       LD A,(DE)     HALT          JP HL
SUB A,r       LD A,(nn)     EX AF,AF'     LD SP,HL 
ADC A,r       LD HL,(nn)    JR d
AND A,r       LD rp,nn      JR cc[y=4],d
XOR A,r       ADD HL,rp     RLCA
OR A,r        JP cc, nn     RRCA
LD r,n        JP nn         RLA
LD (HL),n     INC rp        RRA
LD (BC),A     DEC rp        CPL
LD (DE),A     INC r         SCF
LD (nn),A     DEC r         CCF
LD (nn),HL    LD r,r        RET cc[y]
```

where r and cc are found in [disassembly tables](http://www.z80.info/decoding.htm).

The [zasm](https://k1.spdns.de/Develop/Projects/zasm/Distributions/) assembler can be used to assemble the programs in assembly/src/.

Resources:
- http://sgate.emt.bme.hu/patai/publications/z80guide/
- http://www.z80.info/
