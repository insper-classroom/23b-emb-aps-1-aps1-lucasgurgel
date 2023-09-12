#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#include "funcoes.h"
#include "musicas.h"

void init(void)
{
	board_init();
	sysclk_init();
	delay_init();

	// Desativa watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

 	// Init OLED
	gfx_mono_ssd1306_init();

  	// Configura led
	pmc_enable_periph_clk(LED_PIO1_ID);
	pio_configure(LED_PIO1, PIO_OUTPUT_0, LED_PIO1_IDX_MASK, PIO_DEFAULT);

	pmc_enable_periph_clk(LED_PIO2_ID);
	pio_configure(LED_PIO2, PIO_OUTPUT_0, LED_PIO2_IDX_MASK, PIO_DEFAULT);

	pmc_enable_periph_clk(LED_PIO3_ID);
	pio_configure(LED_PIO3, PIO_OUTPUT_0, LED_PIO3_IDX_MASK, PIO_DEFAULT);
  	// Configura buzzer
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	pio_configure(BUZZER_PIO, PIO_OUTPUT_0, BUZZER_PIO_IDX_MASK, PIO_DEFAULT);

  	// Inicializa clock do periférico PIO responsavel pelo botao
	pmc_enable_periph_clk(START_PIO_ID);
	pmc_enable_periph_clk(SELECAO_PIO_ID);

  // Configura PIO para lidar com o pino do botão como entrada
  // com pull-up
	pio_configure(START_PIO, PIO_INPUT, START_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(START_PIO, START_PIO_IDX_MASK, 100);

	pio_configure(SELECAO_PIO, PIO_INPUT, SELECAO_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(SELECAO_PIO, SELECAO_PIO_IDX_MASK, 60);

  // Configura interrupção no pino referente ao botao e associa
  // função de callback caso uma interrupção for gerada
  // a função de callback é a: but_callback()

  	pio_handler_set(START_PIO,
				  START_PIO_ID,
				  START_PIO_IDX_MASK,
				  PIO_IT_FALL_EDGE,
				  play_pause);

	pio_handler_set(SELECAO_PIO,
	  			  SELECAO_PIO_ID,
				  SELECAO_PIO_IDX_MASK,
				  PIO_IT_FALL_EDGE,
				  muda_musica);

  // Ativa interrupção e limpa primeira IRQ gerada na ativacao
  
  pio_enable_interrupt(START_PIO, START_PIO_IDX_MASK);
  pio_get_interrupt_status(START_PIO);

  pio_enable_interrupt(SELECAO_PIO, SELECAO_PIO_IDX_MASK);
  pio_get_interrupt_status(SELECAO_PIO);

  pio_enable_interrupt(LED_PIO1, LED_PIO1_IDX_MASK);
  pio_get_interrupt_status(LED_PIO1);

  pio_enable_interrupt(LED_PIO2, LED_PIO2_IDX_MASK);
  pio_get_interrupt_status(LED_PIO2);

  pio_enable_interrupt(LED_PIO3, LED_PIO3_IDX_MASK);
  pio_get_interrupt_status(LED_PIO3);

  // Configura NVIC para receber interrupcoes do PIO do botao
  // com prioridade 4 (quanto mais próximo de 0 maior)

  NVIC_EnableIRQ(START_PIO_ID);
  NVIC_SetPriority(START_PIO_ID, 4); // Prioridade 4

  NVIC_EnableIRQ(SELECAO_PIO_ID);
  NVIC_SetPriority(SELECAO_PIO_ID, 4); // Prioridade 4
}



int main (void)
{
	init();	
	music harrypotter = {0, harrypotter_tempo, &harrypotter_melodia, harrypotter_tamanho};
	music mario = {1, mario_tempo, &mario_melodia, mario_tamanho};
	music natal = {2, natal_tempo, &natal_melodia, natal_tamanho};
	music musicas[3] = {harrypotter, mario, natal};
	pio_set(LED_PIO2, LED_PIO2_IDX_MASK);
    pio_set(LED_PIO3, LED_PIO3_IDX_MASK);
    pio_clear(LED_PIO1, LED_PIO1_IDX_MASK);

  /* Insert application code here, after the board has been initialized. */
	while(1) {
		
		play_from_list(musicas, 3);
	}
}