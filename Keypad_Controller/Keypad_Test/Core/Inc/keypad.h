#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <stdint.h>

#define MAX_DIGITS 8U

/* Variables for debugging and number entry. */
extern volatile char current_key;
extern volatile char last_key;
extern volatile uint32_t key_count;
extern volatile char dialed_number[MAX_DIGITS + 1U];
extern volatile uint32_t digit_count;
extern volatile uint32_t call_ready;

/* Configure keypad pins and LED. */
void keypad_init(void);

/* Scan, debounce, and process input; call every nominal 1 ms. */
void keypad_update(void);

#endif
