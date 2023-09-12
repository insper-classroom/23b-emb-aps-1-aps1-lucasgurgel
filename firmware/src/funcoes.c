#include <asf.h>
#include "funcoes.h"

volatile char play_pause_flag = 0;
volatile char muda_musica_flag = 0;

void set_buzzer(void){
    pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
}

void clear_buzzer(void){
    pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
}

int get_startstop(void){
    return pio_get(START_PIO, PIO_INPUT, START_PIO_IDX_MASK);
}

int get_selecao(void){
    return pio_get(SELECAO_PIO, PIO_INPUT, SELECAO_PIO_IDX_MASK);
}

void buzzer_teste(int freq){
    int i;
    int tempo = 1000000 /freq;
    while(1){
        for(i=0;i<tempo;i++){
            set_buzzer();
            delay_us(1);
        }
        for(i=0;i<tempo;i++){
            clear_buzzer();
            delay_us(1);
        }
    }
}

void tone(int freq, int time_us){
    // play the tone with the given frequency (in hertz) and duration (in microseconds).
    if (freq == 0) {
        delay_us(time_us);
        return;
    }
    int i;
    int tempo = 1000000 /freq;
    for(i=0;i<time_us/tempo;i++){
        set_buzzer();
        delay_us(tempo/2);
        clear_buzzer();
        delay_us(tempo/2);
    }
    
}

void play_pause(void)
{
	play_pause_flag = !play_pause_flag;
}

void muda_musica(void)
{
	muda_musica_flag += 1;
    if (muda_musica_flag > 2){
        muda_musica_flag = 0;
    }
}


volatile int  recentPlayedNote = 0;

void play_song_sequence(music m) {
	int tempo = m.tempo;
	int size = m.tamanho;
	int notes = size/2;
	int wholenote = (60000000 * 4) / tempo;

	int divider = 0, noteDuration = 0;

		// calculates the duration of each note
	int currentNode =recentPlayedNote;
    while ((currentNode < notes * 2)&&(!play_pause_flag)&&(!muda_musica_flag)) {
        // calculates the duration of each note
		divider =  (m.melodia)[currentNode + 1];
		if (divider > 0) {
			// regular note, just proceed
			noteDuration = (wholenote) / divider;
			} else if (divider < 0) {
			// dotted notes are represented with negative durations!!
			noteDuration = (wholenote) / abs(divider);
			noteDuration *= 1.5; // increases the duration in half for dotted notes
		}

		// we only play the note for 90% of the duration, leaving 10% as a pause
		tone((m.melodia)[currentNode], noteDuration*0.9);
		recentPlayedNote = currentNode;
        currentNode += 2;
    }
}

volatile int current_playlist_song = 0;
void play_from_list(music m[], int qtdMusicas){


    if (muda_musica_flag){

        muda_musica_flag = 0;
        recentPlayedNote = 0;
        current_playlist_song+=1;
        if (current_playlist_song == 1){
            pio_set(LED_PIO1, LED_PIO1_IDX_MASK);
            pio_set(LED_PIO3, LED_PIO3_IDX_MASK);
            pio_clear(LED_PIO2, LED_PIO2_IDX_MASK);
        } else if (current_playlist_song == 2){
            pio_set(LED_PIO1, LED_PIO1_IDX_MASK);
            pio_set(LED_PIO2, LED_PIO2_IDX_MASK);
            pio_clear(LED_PIO3, LED_PIO3_IDX_MASK);
        }

    }
    if (current_playlist_song >= qtdMusicas){
        current_playlist_song = 0;
        pio_set(LED_PIO2, LED_PIO2_IDX_MASK);
        pio_set(LED_PIO3, LED_PIO3_IDX_MASK);
        pio_clear(LED_PIO1, LED_PIO1_IDX_MASK);
    }
    play_song_sequence(m[current_playlist_song]);
}