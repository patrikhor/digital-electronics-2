# Lab 2

## Pre-Lab preparation

1. Fill in the following table and enter the number of bits and numeric range for the selected data types defined by C.

   | **Data type** | **Number of bits** | **Range** | **Description** |
   | :-: | :-: | :-: | :-- |
   | `uint8_t`  | 8 | 0, 1, ..., 255 | Unsigned 8-bit integer |
   | `int8_t`   | 8 | -128, ..., 0, ..., 127 | Signed 8-bit integer |
   | `uint16_t` | 16 | 0,1, ..., 65535 | Unsigned 16-bit integer |
   | `int16_t`  | 16 | -32768, ..,0, .., 32767 | Signed 16-bit integer |
   | `float`    | 32 | -3.4e+38, ..., 3.4e+38 | Single-precision floating-point |
   | `void`     |  |  |  |

# Lab 3: Interrupts and polling

## Pre-Lab preparation

Consider an n-bit number that we increment based on the clock signal. If we reach its maximum value and try to increase it, the value will be reset. We call this state an **overflow**. The overflow time depends on the frequency of the clock signal, the number of bits, and on the prescaler value:

&nbsp;
![Timer overflow](images/timer_overflow.png)
&nbsp;

1. Calculate the overflow times for three Timer/Counter modules that contain ATmega328P if CPU clock frequency is 16&nbsp;MHz. Complete the following table for given prescaler values. Note that, Timer/Counter2 is able to set 7 prescaler values, including 32 and 128 and other timers have only 5 prescaler values.

   | **Module** | **Number of bits** | **1** | **8** | **32** | **64** | **128** | **256** | **1024** |
   | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
   | Timer/Counter0 | 8  | 16u | 128u | -- | 1024u | -- | 4m | 16m |
   | Timer/Counter1 | 16 | 4m | 32m | -- | 262m | -- | 1s | 4s |
   | Timer/Counter2 | 8  | 16u | 128u | 512u | 1024u | 2m | 4m | 16m |


# Lab 4: Liquid crystal display (LCD)

## Pre-Lab preparation

1. Use schematic of the [LCD keypad shield](https://oshwlab.com/tomas.fryza/arduino-shields) and find out the connection of LCD display. What data and control signals are used? What is the meaning of these signals?

   | **LCD signal(s)** | **AVR pin(s)** | **Description** |
   | :-: | :-: | :-- |
   | RS | PB0 | Register selection signal. Selection between Instruction register (RS=0) and Data register (RS=1) |
   | R/W | Ground |  |
   | E | PB1 |  |
   | D[3:0] |  |  |
   | D[7:4] | PD[4:7] |  |
   | K |  |  |

2. What is the ASCII table? What are the codes/values for uppercase letters `A` to `Z`, lowercase letters `a` to `z`, and numbers `0` to `9` in this table?

   | **Char** | **Decimal** | **Hexadecimal** |
   | :-: | :-: | :-: |
   | `A` | 65 | 0x41 |
   | `B` | 66 | 0x42 |
   | ... |  |  |
   | `a` | 97 | 0x61 |
   | `b` | 98 | 0x62 |
   | ... |  |  |
   | `0` | 48 | 0x30 |
   | `1` | 49 | 0x31 |
   | ... |  |  |

<a name="part1"></a>


## Pre-Lab preparation

1. Use **AVR® Instruction Set Manual** from Microchip [Online Technical Documentation](https://onlinedocs.microchip.com/), find the description of selected instructions, and complete the table.

   | **Instruction** | **Operation** | **Description** | **Cycles** |
   | :-- | :-: | :-- | :-: |
   | `add Rd, Rr` | Rd = Rd and Rr | Adds two registers without the C flag | 1 |
   | `andi Rd, K` | Rd = Rd and K | Logical AND between register Rd and 8-bit constant K | 1 |
   | `bld Rd, b` | Rd(b) = T | Copies the T bit in the SREG (Status Register) to bit b in register Rd | 1 |
   | `bst Rd, b` | T = Rd(b) | Stores bit b from Rd to the T bit in SREG | 1 |
   | `com Rd` | Rd = 0xFF - Rd | This instruction performs a One’s Complement of register Rd. | 1 |
   | `eor Rd, Rr` | Rd = Rd EOR Rr | Performs the logical EOR between the contents of register Rd and register Rr and places the result in the destination register Rd | 1 |
   | `mul Rd, Rr` | R1:R0 = Rd x Rr | The multiplicand Rd and the multiplier Rr are two registers containing unsigned numbers | 1 |
   | `pop Rd` | Rd = STACK | This instruction loads register Rd with a byte from the STACK | 1 |
   | `push Rr` | STACK = Rd | This instruction stores the contents of register Rr on the STACK | 1 |
   | `ret` | PC(15:0) = STACK | Devices with 16-bit PC, 128 KB program memory maximum | 2 |
   | `rol Rd` | C
   | Shifts all bits in Rd one place to the left. The C flag is shifted into bit 0 of Rd. Bit 7 is shifted into the C flag. This operation, combined with LSL, effectively multiplies multi-byte signed and unsigned values by two. | 1 |
   | `ror Rd` |  | Shifts all bits in Rd one place to the right. The C flag is shifted into bit 7 of Rd. Bit 0 is shifted into the C flag. This operation, combined with ASR, effectively divides multi-byte signed values by two. Combined with LSR, it effectively divides multi-byte unsigned values by two. The Carry flag can be used to round the result. | 1 |
