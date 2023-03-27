// got some of this from here.
//https://www.reddit.com/r/raspberrypipico/comments/pacarb/sharing_some_c_code_to_read_a_rotary_encoder/
#include <stdio.h>
#include <stdint.h>
#include "encoder.h"
#include "ssd1306.h"
#include "hardware/gpio.h"
void display_write(char *str1);  // show strings on 1306--function is in main.c

/*Encoder GPIO*/
// GPIO 10 is Encoder phase A,  
// GPIO 15 is Encoder phase B,
// GPIO 12 is the encoder push botton switch.
// change these as needed


void encoder_init()
{
#define ENC_A	10
#define ENC_B	15
 #define ENC_SW	16

//initialize encoder

	// GPIO Setup for Encoder
	gpio_init(ENC_SW);					//Initialise a GPIO for (enabled I/O and set func to GPIO_FUNC_SIO)
    gpio_set_dir(ENC_SW,GPIO_IN);
	gpio_disable_pulls(ENC_SW);

	gpio_init(ENC_A);
    gpio_set_dir(ENC_A,GPIO_IN);
	gpio_disable_pulls(ENC_A);

	gpio_init(ENC_B);
    gpio_set_dir(ENC_B,GPIO_IN);
	gpio_disable_pulls(ENC_B);
 
    

}


uint8_t A = 0;
uint8_t B = 0;
uint8_t A_prev = 0;
uint8_t bool_to_bit= 0;
void read_from_encoder()
{
//. https://howtomechatronics.com/tutorials/arduino/rotary-encoder-works-use-arduino/

 

 
A = gpio_get(ENC_A);
if (A != A_prev)  // new pulse
    {
    //A = gpio_get(ENC_A);
 
    B = gpio_get(ENC_B);
    
    
  //  printf("A is: %x and B is: %x \n",A,B);
   
 
    if (A == 0 && B == 0)
        {
        printf("CCW \n");
        display_write("CCW");
        sleep_ms(250);
        }

    if (A == 1 && B == 0)
        {
        printf("CW \n");
        display_write("CW");
        sleep_ms(250);
        }
 

    if (A == 0 && B == 1)
        {
        printf("CW \n");
        display_write("CW");
        sleep_ms(250);
        }
        

    A_prev = A;
    }

}
 