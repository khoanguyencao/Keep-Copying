#include "../u8g2Headers/u8g2TestHarness_main.h"
#include "../u8g2Headers/common.h"
#include "../u8g2Headers/spi_master.h"
#include "../u8g2Headers/u8g2.h"
#include "../u8g2Headers/u8x8.h"

extern uint8_t u8x8_pic32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
extern uint8_t u8x8_byte_pic32_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

static u8g2_t u8g2;

static uint16_t offset=118; // start at the rightmost character position
static uint16_t width;
char lineBuffer[] = "12345678901234";

void main(void) {
    
    // sysInit is used for timing setup for the test harness, the framework will
    // give you the timing that you need for Lab 3
    sysInit(); 
    SPI_Init(); // hmm, I wonder who will write this function :-)
    
    // build up the u8g2 structure with the proper values for our display
    // use the next 5 lines verbatim in your initialization
    u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_pic32_hw_spi, 
                                       u8x8_pic32_gpio_and_delay);
    // pass all that stuff on to the display to initialize it
    u8g2_InitDisplay(&u8g2);
    // turn off power save so that the display will be on
    u8g2_SetPowerSave(&u8g2, 0);
    // choose the font. this one is mono-spaced and has a reasonable size
    u8g2_SetFont(&u8g2, u8g2_font_t0_18_mr);
    // overwrite the background color of newly written characters
    u8g2_SetFontMode(&u8g2, 0);
    // width is used only for the scrolling demo
    width = (u8g2_GetStrWidth(&u8g2, lineBuffer)/2);

    while (1) {
       // set up for a screen update always start an update with u8g2_FirstPage                 
        u8g2_FirstPage(&u8g2);
        do {
            // offset determines where the first character will be placed
            // 0 is far left, 118 is first position on the right
            // 37 is the horizontal starting position. This puts it in the 
            // middle of the display
            u8g2_DrawStr(&u8g2, offset, 37, lineBuffer); 
          // this while loop is a total hack for the test harness.
          // you should make an event checker to call u8g2_NextPage to determine
          // when the screen update has completed.
        } while (u8g2_NextPage(&u8g2));
        // this is how we make it scroll for the demo
        // this is *not* how you want to do it for lab 3 :-)
        // the chosen font is approximately 9 pixels wide, so this steps in
        // whole character steps (approximately :-))
        offset -= 9; 
        if(offset < -width) offset = 0; // reset and start over
        
        __delay_ms(1000); // so that we can see the characters step across
    };
}
