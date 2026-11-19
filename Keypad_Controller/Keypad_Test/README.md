# Keypad and unlock LED controller

Target: NUCLEO-L476RG / STM32L476RG. Direct-register C with CMSIS device headers and startup code only. No HAL or board-support drivers are included or enabled.

## Behavior

- Main keypad: enter up to eight digits; `*` clears; `#` confirms a nonempty number.
- Small keypad: debounced buttons 1-4 appear in debugger variables.
- Small keypad button 4: PB6 / D10 goes HIGH for approximately three seconds, then LOW. This currently drives an LED through a 220 ohm series resistor. No physical lock has been tested by this version.
- PA5 onboard LED follows a debounced main-keypad press.
- SysTick is polled at a nominal 1 ms interval. Debugger pauses stop the software countdown.

## Wiring

| Connection | Board label | MCU pin |
| --- | --- | --- |
| Main keypad rows 1-4 | D2, D3, D4, D5 | PA10, PB3, PB5, PB4 |
| Main keypad columns 1-3 | D6, D7, D8 | PB10, PA8, PA9 |
| Small keypad connector 1-5 | A0, A1, A2, A3, A4 | PA0, PA1, PA4, PB0, PC1 |
| Unlock LED output | D10 | PB6 |

Connect D10 through the 220 ohm resistor and LED to GND. Connector pin 1 of the small keypad is the common connection. The MCU output is a control signal; it cannot power the 12 V lock directly.

## Import and build

1. Extract this archive to a separate folder, preserving the original project as a backup.
2. Use a separate STM32CubeIDE workspace if it already contains a project named Keypad_Test.
3. Choose File > Import > General > Existing Projects into Workspace, and select the extracted Keypad_Test folder.
4. Clean and build the project, then run on the NUCLEO-L476RG and repeat the keypad / button 4 LED test.

The project remains a managed CubeIDE project. CubeMX generation metadata was removed so regenerating a template does not restore peripheral drivers. Both Debug and Release build settings use Core/Inc and CMSIS include paths with STM32L476xx defined.

## Cleanup and validation

The uploaded main.c, keypad.c and keypad.h are byte-for-byte unchanged. Removed the peripheral driver library, board-support library, generated driver configuration and initialization file, driver build flags and include paths. Removed generated interrupt-handler calls; SysTick_Handler is empty because the application polls the timer. The unused blue-button interrupt override was removed; its startup vector uses the default handler.

The CMSIS family header had optional peripheral-driver include hooks removed. Comments in the CMSIS clock source and header were adjusted to describe direct-register use; register definitions and clock calculations were retained. Original copyright notices and included licenses are preserved.

All retained C source files passed GCC syntax checks in the preparation environment; project XML and include dependencies were checked. An ARM compiler, STM32CubeIDE and the physical board were unavailable there, so a full target build and hardware retest are still required.

Porting to the partner's STM32N657 requires that target's device headers, startup code, linker script, GPIO clock setup and pin mapping.
