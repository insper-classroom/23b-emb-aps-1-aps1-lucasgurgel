#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#define BUZZER_PIO		   PIOD 
#define BUZZER_PIO_ID	   ID_PIOD
#define BUZZER_PIO_IDX	   20
#define BUZZER_PIO_IDX_MASK (1u << BUZZER_PIO_IDX)

#define START_PIO 		 PIOC 
#define START_PIO_ID	 ID_PIOC
#define START_PIO_IDX	 31
#define START_PIO_IDX_MASK (1u << START_PIO_IDX)

void init(void){
	board_init();
	sysclk_init();
	delay_init();
	// Desativa watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// Configura buzzer
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	pio_configure(BUZZER_PIO, PIO_OUTPUT_0, BUZZER_PIO_IDX_MASK, PIO_DEFAULT);

	// Configura botao
	pmc_enable_periph_clk(START_PIO_ID);
	pio_configure(START_PIO, PIO_INPUT, START_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(START_PIO, START_PIO_IDX_MASK, 60);

	pio_enable_interrupt(START_PIO, START_PIO_IDX_MASK);
  	pio_get_interrupt_status(START_PIO);

	NVIC_EnableIRQ(START_PIO_ID);
	NVIC_SetPriority(START_PIO_ID, 0); 
}

void set_buzzer(void){
    pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
}

void clear_buzzer(void){
    pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
}
int get_startstop(){
	return pio_get(START_PIO, PIO_INPUT, START_PIO_IDX_MASK);
}

int main (void)
{
	board_init();
	sysclk_init();
	delay_init();

  // Init OLED
	gfx_mono_ssd1306_init();
  
  // Escreve na tela um circulo e um texto
	gfx_mono_draw_filled_circle(20, 16, 16, GFX_PIXEL_SET, GFX_WHOLE);
  gfx_mono_draw_string("mundo", 50,16, &sysfont);

  /* Insert application code here, after the board has been initialized. */
	while(1) {

	}
}
