#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "ssd1306.h"
#include "image.h"
#include "UART.h"
#include "acme_5_outlines_font.h"
#include "bubblesstandard_font.h"
#include "crackers_font.h"
#include "BMSPA_font.h"
#include "renew_font.h"
#include "fivexfive_font.h"
#include "encoder.h"

//gpio designations
#define ENCSW 14
#define LED1  6
#define LED2  7
#define LED3  8
#define LED4  9

const uint8_t num_chars_per_disp[]={7,7,7,5};
const uint8_t *fonts[6]= {acme_font, bubblesstandard_font, crackers_font, BMSPA_font, renew_font, fivexfive_font};

#define SLEEPTIME 25

void setup_gpios(void);
void display_write(char *str1);  // show strings on 1306
 


//github for the 1306 lib is here. https://github.com/daschr/pico-ssd1306

int main() {
     stdio_init_all();


    printf("Welcome to encoder madness...\n");

    printf("initialed serial printing (or you wouldn't be reading this)...\n");

    printf("configuring pins...\n");
    setup_gpios(); // configure GPIOs for I2C (below)

    //configure GPIO for Encoder
    encoder_init();
    
    //write test message to SSD1306
    display_write("Welcome");
    sleep_ms(1000);

    while (2 > 0)
    {

 

    //get encoder reading.
    read_from_encoder();
   
 
    }
}
/*wiring.
POWER for 1306--connect to "-5 3V3 OUT"
The library by default uses I2C1 
use these PICO pins from dev board to the 1306 board.
SDA GP2/pin 4  
SCL GP3/pin 5

YES the 1306 can run from 3.3V supply Pico "3V3 OUT" 
MAKE SURE to ground the 1306 to the GND pin on PICO

ADDRESSING

7 bit address for 1306 by default is 0x3C
the address silked on the back 
of the shitty Chinese BoB's assumes MSB is 1--
that's slave
write to master--not what we are doing here.
So bit shift right the address on the back.
and put it into  ssd1306_init below.
*/

void setup_gpios(void) {
    //pins for I2C OLED
    i2c_init(i2c1, 400000);
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3);

    //gpio 14 is encoder switch
    //false below means input pin
    gpio_init(ENCSW);
    gpio_set_dir(ENCSW, false);

    //gpio 6-9 are LED's
    //true means output pin
    gpio_init(LED1);
    gpio_set_dir(LED1, true);
    gpio_init(LED2);
    gpio_set_dir(LED2, true);
    gpio_init(LED3);
    gpio_set_dir(LED3, true);
    gpio_init(LED4);
    gpio_set_dir(LED4, true);
    //

}


void display_write(char *str1)
{
// send string to 1306

//initialize display
    ssd1306_t disp;  // instantiate from struct
    disp.external_vcc=false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp); //blank display

/*
	@brief draw string with given font

	@param[in] p : instance of display
	@param[in] x : x starting position of text
	@param[in] y : y starting position of text
	@param[in] scale : scale font to n times of original size (default should be 1)
	@param[in] font : pointer to font
	@param[in] s : text to draw
*/
 
    ssd1306_clear(&disp);
    ssd1306_draw_string_with_font(&disp, 8, 24, 2, fonts[4], str1);
    ssd1306_show(&disp);  

} 
 


