#ifndef LCD_H
#define LCD_H
#include <stdint.h>
void lcd_init(void);
void lcd_set_cursor(uint32_t row, uint32_t column);
void lcd_print(const char *text);
void lcd_delay_ms(uint32_t ms);
#endif
