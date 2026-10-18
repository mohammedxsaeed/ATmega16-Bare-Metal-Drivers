# ATmega16 Bare-Metal Drivers

A reusable Embedded C driver collection for the **ATmega16** microcontroller. The project uses a conventional layered architecture so application code can call readable driver APIs while hardware-specific register access remains isolated in the lower layers.

> **Target assumptions:** ATmega16, 8 MHz CPU clock, AVR-GCC/Atmel Studio, and the classic ATmega16 memory map. Review the device datasheet and board wiring before using these drivers in production hardware.

## Features

- MCAL: DIO, Timer 0/1, ADC, UART, and external interrupts.
- HAL: seven-segment display, LCD, 4×4 keypad, LDR, and LM35 sensor helpers.
- LIB: fixed-width types, status types, bit manipulation macros, and ATmega16 register mappings.
- No vendor framework is required; the drivers access ATmega16 registers directly.

## Repository layout

```text
LIB/
  STD_TYPES.h       Common integer, floating-point, boolean, error, and callback types
  UTILS.h           Bit, port, and NULL macros
  MemMAP.h          ATmega16 memory-mapped register definitions
MCAL/
  DIO/              Digital I/O pin and port control
  Timer/            Timer0 and Timer1 control, compare, overflow, and ICU helpers
  ADC/              ADC initialization, conversion, and voltage calculation
  UART/             8N1 UART at 9600 baud
  Interrupt/        INT0, INT1, and INT2 setup
HAL/
  SEV_SEGMENTS/     Seven-segment initialization and digit display
  LCD/              HD44780-style LCD in 4-bit or 8-bit mode
  KEYPAD/           4×4 matrix keypad scanning
  LDR/              ADC-to-light-percentage helper
  LM35/             ADC-to-temperature/voltage helpers
```

## Layered architecture

**LIB** is the foundation. It defines portable project types and macros and maps symbolic register names such as `PORTA`, `TCCR0`, and `ADCSRA` to ATmega16 addresses.

**MCAL** is the Microcontroller Abstraction Layer. It exposes MCU peripheral services such as GPIO, timers, ADC, UART, and external interrupts. MCAL modules include the LIB headers and hide register-level operations from application code.

**HAL** is the Hardware Abstraction Layer. It composes MCAL services to control external components such as displays, a keypad, and sensors. For example, the seven-segment driver uses DIO-compatible port identifiers and writes the standard common-cathode digit lookup table.

The application layer sits above HAL/MCAL. `main.c` is intentionally not included because this repository is a driver library; add your own application entry point and select only the modules you need.

## Getting started with Atmel Studio

1. Create an **AVR GCC C Executable Project** for **ATmega16** in Atmel Studio.
2. Copy `LIB`, `MCAL`, and `HAL` into the project directory, or add these folders to the project using **Add > Existing Item**.
3. Add the required `.c` files to the project. For a seven-segment counter, add `MCAL/DIO/DIO.c` and `HAL/SEV_SEGMENTS/SEV_SEG.c`.
4. Add include search paths for `LIB`, `MCAL`, and `HAL` under **Project Properties > Toolchain > AVR/GNU C Compiler > Directories**. The existing headers use paths such as `DIO/DIO.h` and `STD_TYPES.h`.
5. Set the project device to **ATmega16** and define `F_CPU=8000000UL` if your project does not already define it. Several headers also provide this default.
6. Write `main()` and include the driver headers you use. Build, program the generated HEX file, and verify the wiring/pin configuration.

Example compiler include configuration:

```text
-I"$(ProjectDir)LIB"
-I"$(ProjectDir)MCAL"
-I"$(ProjectDir)HAL"
```

## API documentation

The declarations in each module header are the source of truth. The examples below show typical usage. Unless noted otherwise, the APIs are blocking and return no status code; validate the electrical configuration and input ranges in application code.

### LIB

- `STD_TYPES.h`: `u8`, `u16`, `u32`, `u64`, signed integer aliases, `f32`, `f64`, `boolean`, `error_t`, and `PTF` callback type.
- `UTILS.h`: `SET_BIT(REG, BIT_NUM)`, `CLR_BIT(REG, BIT_NUM)`, `TGL_BIT(REG, BIT_NUM)`, `GET_BIT(REG, BIT_NUM)`, `SET_PORT(REG)`, `CLR_PORT(REG)`, and `NULL`.
- `MemMAP.h`: volatile register aliases for GPIO (`PINx`, `DDRx`, `PORTx`), ADC, Timer0/1/2, interrupt control, and UART.

```c
#include "STD_TYPES.h"
#include "UTILS.h"
#include "MemMAP.h"

SET_BIT(PORTB, 0);              /* drive PB0 high */
boolean pressed = (GET_BIT(PIND, 2) == 0) ? TRUE : FALSE;
```

### MCAL/DIO

Types: `DIO_PORT_TYPE` (`PA`–`PD`), `DIO_PIN_STATE` (`OUTPUT`, `INPUT`, `INPULL`), and `DIO_VOLT_STATE` (`LOW`, `HIGH`).

- `GPIO_PIN_Mode(port, PIN_Num, State)` configures one pin; `PIN_Num` is 0–7.
- `GPIO_WRITE_PIN(port, PIN_Num, volt)` writes one output pin.
- `GPIO_TGL_PIN(port, PIN_Num)` toggles one output pin.
- `GPIO_PORT_Mode(port, mode)` configures all eight pins of a port.
- `GPIO_WRITE_PORT(port, volt)` writes all pins high or low.
- `GPIO_READ_PIN(port, PIN_Num)` returns `LOW` or `HIGH`.
- `GPIO_READ_PORT(port)` returns the complete input register value.

```c
#include "DIO/DIO.h"

GPIO_PORT_Mode(PB, OUTPUT);
GPIO_PIN_Mode(PD, 2, INPULL);
GPIO_WRITE_PIN(PB, 0, HIGH);
if (GPIO_READ_PIN(PD, 2) == LOW) {
    GPIO_TGL_PIN(PB, 0);
}
```

### MCAL/Timer

Timer modes: `TIMER_NORMAL_MODE`, `TIMER_PWM_PHASE_CORRECT`, `TIMER_CTC_MODE`, `TIMER_FAST_PWM`. Prescaler constants are provided for Timer0 and Timer1: stopped, 1, 8, 64, 256, and 1024.

- `Timer0_Init(mode, prescaler)` configures Timer0 mode and clock source. Normal/CTC modes enable their corresponding interrupt bit; PWM modes configure OC0/PB3.
- `Timer0_SetCompareValue(value)` writes OCR0.
- `Timer0_SetCounter(value)` writes TCNT0.
- `Timer0_Stop()` clears Timer0 clock-source bits.
- `Timer1_Init_Normal(prescaler)` configures Timer1 normal mode and enables overflow interrupt.
- `Timer1_ICU_Init(edge)` enables Timer1 input-capture interrupt and selects `RISING_EDGE` or `FALLING_EDGE`.
- `Timer1_ICU_SetEdge(edge)` changes the input-capture edge.
- `Timer1_ICU_GetCaptureValue()` returns ICR1.
- `Timer1_SetCounter(value)` writes TCNT1.
- `Timer1_Stop()` clears Timer1 clock-source bits.

```c
#include "Timer/Timer.h"

Timer0_Init(TIMER_CTC_MODE, TIMER0_PRESCALER_64);
Timer0_SetCompareValue(124);   /* application-specific compare value */
Timer1_ICU_Init(RISING_EDGE);
u16 captured_ticks = Timer1_ICU_GetCaptureValue();
```

### MCAL/ADC

- `ADC_Init()` configures PORTA as ADC input, selects AVCC as reference, uses right-adjusted results, enables the ADC, and selects a ÷64 prescaler.
- `ADC_READ(channel)` performs a blocking conversion on ADC channel 0–7 and returns a 10-bit result. Invalid channels return 0.
- `ADC_CALC_VOLT(CH)` converts a reading to volts assuming a 5 V reference.

```c
#include "ADC/ADC.h"

ADC_Init();
u16 raw = ADC_READ(0);
f32 volts = ADC_CALC_VOLT(0);
```

### MCAL/UART

The UART is configured for 8 data bits, no parity, 1 stop bit, 9600 baud, and an 8 MHz clock.

- `UART_Init()` initializes the transmitter and receiver.
- `UART_SendData(data)` blocks until the data register is ready, then transmits one byte.
- `UART_Rx()` blocks until one byte is received and returns it.
- `UART_SendString(str)` transmits a NUL-terminated string followed by a newline.

```c
#include "UART/UART.h"

UART_Init();
UART_SendString((u8 *)"ATmega16 ready");
u8 command = UART_Rx();
UART_SendData(command);
```

### MCAL/Interrupt

- `INTERRUPT_Init(pin, mode)` configures and enables `INT0_PIN`, `INT1_PIN`, or `INT2_PIN`.
- Modes: `Low_lvl`, `Change`, `Falling_edge`, and `Rising_edge`. INT2 supports edge modes only.

Enable the global interrupt flag and provide the appropriate AVR ISR in the application when using interrupt-driven behavior:

```c
#include "Interrupt/EXT_Interrupt.h"
#include <avr/interrupt.h>

INTERRUPT_Init(INT0_PIN, Falling_edge);
sei();
ISR(INT0_vect) {
    GPIO_TGL_PIN(PB, 0);
}
```

### HAL/SEV_SEGMENTS

This driver uses a common-cathode seven-segment lookup table for digits 0–9 and writes segment data to bits 0–6 of the selected port.

- `Seg_Init(port)` configures the selected port's lower seven pins as outputs.
- `Seg_Display_num(port, num)` displays digit 0–9; values ≥10 are ignored.
- `Seg_Display_All(port)` displays digits 0–9 with a 500 ms delay between digits.

```c
#include "HAL/SEV_SEGMENTS/SEV_SEG.h"

Seg_Init(PB);
Seg_Display_num(PB, 7);
```

### HAL/LCD

Configuration macros in `LCD.h` select 4-bit or 8-bit mode and define the data/control ports. Default configuration is 4-bit mode using PD4–PD7 for data and PB0/PB1 for EN/RS.

- `LCD_Init()` initializes the display.
- `LCD_CLEAR()` clears the display.
- `LCD_Print_Char(data)` prints one character.
- `LCD_Print_String(str)` prints a NUL-terminated string.
- `LCD_Printnum(num)` prints a signed integer.
- `LCD_GOTO(ROW, COL)` moves the cursor on row 0 or 1.
- `LCD_CLRLOC(ROW, COL)` clears four characters at a location.
- `LCD_Print_Float(num, width, precision)` formats and prints a float.
- `LCD_CUSTOM_Char(slot, pattern)` stores an 8-byte custom glyph in CGRAM slot 0–7.

```c
#include "HAL/LCD/LCD.h"

LCD_Init();
LCD_Print_String((s8 *)"Temperature:");
LCD_GOTO(1, 0);
LCD_Print_Float(23.5f, 4, 1);
```

### HAL/KEYPAD

The default 4×4 matrix maps rows to PC4–PC7 and columns to PC0–PC3. `Key_array` maps the keys to `7 8 9 /`, `4 5 6 *`, `1 2 3 -`, and `c 0 = +`.

- `KEYPAD_Init()` configures row outputs and column pull-up inputs.
- `KEYPAD_getkey()` scans the matrix, blocks while a detected key remains pressed, and returns the mapped character or `NO_KEY`.

```c
#include "HAL/KEYPAD/KEYPAD.h"

KEYPAD_Init();
u8 key = KEYPAD_getkey();
if (key != NO_KEY) {
    LCD_Print_Char(key);
}
```

### HAL/LDR

- `LDR_ReadPercent(channel)` reads an ADC channel and scales the 10-bit value to an approximate 0–100 light percentage.

```c
#include "HAL/LDR/LDR.h"

ADC_Init();
f32 light = LDR_ReadPercent(0);
```

### HAL/LM35

- `LM35_CALC_TEMP(CH)` returns temperature in °C, assuming a 5 V ADC reference and the LM35's 10 mV/°C output.
- `LM35_CALC_VOLT(CH)` returns the measured channel voltage in volts.

```c
#include "HAL/LM35/LM35.h"

ADC_Init();
f32 temperature_c = LM35_CALC_TEMP(1);
f32 sensor_voltage = LM35_CALC_VOLT(1);
```

## Hardware notes

- `MemMAP.h` contains direct ATmega16 register addresses; do not use these definitions with a different AVR without reviewing the datasheet.
- The ADC and UART calculations assume `F_CPU=8000000UL` and a 5 V ADC reference.
- The seven-segment table is for a common-cathode display and does not implement multiplexing by itself.
- Timer and external interrupt modules enable peripheral interrupt bits, but the application must provide ISRs and enable global interrupts with `sei()` when needed.
- Sensor “percentage” and temperature helpers are simple conversions; calibrate them for the sensor, resistor network, reference voltage, and board wiring.

## Contributing

Issues and pull requests are welcome. Keep hardware-specific code in MCAL, external-component code in HAL, and shared types/macros/register maps in LIB. Please include the target device, clock frequency, wiring assumptions, and a reproducible test case with driver changes.

## License

Released under the [MIT License](LICENSE).
