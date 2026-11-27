# PROJECT 478 – Keypad and LCD Prototype

## Current setup

- NUCLEO-L476RG: both keypads and MOSFET driver.
- NUCLEO-N657X0-Q: 16×2 LCD.
- Application code uses direct register access without HAL.

This is the tested development setup. The final design will place
the main keypad, LCD, and lock on the N657 door station.

## Connection between boards

| L476 | N657 |
|---|---|
| PC10, CN7 pin 1 — USART3 TX | D0 / PD9 — USART3 RX |
| GND | GND |

UART settings: 9600 baud, 8 data bits, no parity, 1 stop bit.

Power each board through its own USB connection. Do not connect
the boards' 3.3 V or 5 V rails together.

## LCD connections

| LCD pin | Signal | N657 connection |
|---|---|---|
| 1 | VSS | GND |
| 2 | VDD | 5 V |
| 3 | Contrast / VO | GND |
| 4 | RS | D2 / PD0 |
| 5 | R/W | GND |
| 6 | Enable | D3 / PE9 |
| 7–10 | DB0–DB3 | Unused |
| 11 | DB4 | D4 / PE0 |
| 12 | DB5 | D5 / PE10 |
| 13 | DB6 | D6 / PD5 |
| 14 | DB7 | D7 / PE11 |
| 15 | Backlight anode | 5 V through 220-ohm resistor |
| 16 | Backlight cathode | GND |

## Keypad connections on L476

Main 3×4 keypad:

| Signal | Board pin | GPIO |
|---|---|---|
| Row 1 | D2 | PA10 |
| Row 2 | D3 | PB3 |
| Row 3 | D4 | PB5 |
| Row 4 | D5 | PB4 |
| Column 1 | D6 | PB10 |
| Column 2 | D7 | PA8 |
| Column 3 | D8 | PA9 |

Small 1×4 keypad:

| Signal | Board pin | GPIO |
|---|---|---|
| Common | A0 | PA0 |
| Button 1 | A2 | PA4 |
| Button 2 | A1 | PA1 |
| Button 3 | A4 | PC1 |
| Button 4 | A3 | PB0 |

## MOSFET driver LED test

The Adafruit STEMMA MOSFET + Diode Driver is connected as follows:

| Driver connection | Connection |
|---|---|
| White signal wire | L476 D10 / PB6 |
| Red V+ wire | L476 3.3 V for the LED test |
| Black ground wire | L476 GND |
| Positive output terminal | 220-ohm resistor, then LED anode |
| Negative output terminal | LED cathode |

The physical 12 V lock is not connected in this test setup.

## Verified behavior

- Both projects build with zero errors in STM32CubeIDE.
- Main keypad digits appear on the LCD.
- Number entry supports up to eight digits.
- `*` clears the entry.
- `#` confirms a nonempty entry and displays "Number confirmed".
- Small keypad button 4 activates the MOSFET LED test for
  approximately three seconds.
- The LCD displays "Unlock active" during that interval and then
  returns to the number-entry or confirmed screen.

"Number confirmed" indicates local keypad confirmation.
"Unlock active" indicates the software output command;
it does not confirm physical lock movement.

## Running the prototype

1. Connect both boards to USB.
2. Keep the PC10-to-D0 connection and common ground connected.
3. In STM32CubeIDE, open Run > Debug Configurations.
4. Launch Keypad_Test and resume with F8 if paused at main.
5. Launch LCD_N657_Ready_FSBL and resume with F8 if paused.
6. Enter digits on the main keypad to verify the LCD updates.

When both ST-LINK probes are connected, select the matching
ST-LINK serial number in each debug configuration.

Use separate GDB server ports:
- Keypad_Test: 61234
- LCD_N657_Ready_FSBL: 61244

The N657 project runs from RAM and must be loaded again after
power is disconnected. The L476 program is stored in flash.

If the LCD displays "Waiting keypad", check that the L476
program is running, PC10 connects to N657 D0, and grounds
are connected.

## Remaining work

- Test the complete MOSFET driver and physical lock using
  the appropriate 12 V supply.
- Add PIN validation on the main keypad.
- Integrate keypad, LCD, and lock control on the N657 door station.
- Integrate audio and communication between stations.
- Implement the indoor station's remote unlock request.

No PIN currently unlocks the lock. In this prototype, small
keypad button 4 controls the local L476 MOSFET output.
