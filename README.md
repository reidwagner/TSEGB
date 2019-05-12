# TSEGB

Implemented instructions:

```
NOP           LD A,(BC)     DJNZ          RET
ADD A,r       LD A,(DE)     HALT          JP HL
SUB A,r       LD A,(nn)     EX AF,AF'     LD SP,HL 
ADC A,r       LD HL,(nn)    JR d          DI
AND A,r       LD rp,nn      JR cc[y=4],d  EI
XOR A,r       ADD HL,rp     RLCA          CALL cc[y],nn
OR A,r        JP cc, nn     RRCA          CALL nn
LD r,n        JP nn         RLA           PUSH rp2[p]
LD (HL),n     INC rp        RRA           alu[y] n
LD (BC),A     DEC rp        CPL           RST y*8
LD (DE),A     INC r         SCF           SET y,r[z]
LD (nn),A     DEC r         CCF           RES y,r[z]
LD (nn),HL    LD r,r        RET cc[y]
```

where r, cc, alu, rp, rp2 are found in [disassembly tables](http://www.z80.info/decoding.htm).

The [zasm](https://k1.spdns.de/Develop/Projects/zasm/Distributions/) assembler can be used to assemble the programs in assembly/src/.

Resources:
- http://sgate.emt.bme.hu/patai/publications/z80guide/
- http://www.z80.info/

### WebAssembly

First need to source emsdk_env.sh.

To compile main as webasm:
emcc src/main.c -Os -s WASM=1 -s SIDE_MODULE=1 -s EXPORTED_FUNCTIONS=["_main_wasm"] -o tse.wasm

