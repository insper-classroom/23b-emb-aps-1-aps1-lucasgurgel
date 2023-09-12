//--------------------------------------------
// Defines
//--------------------------------------------
typedef struct
{
	char indice;
	int tempo;
	int *melodia;
	int tamanho;
} music;
#define BUZZER_PIO		   	PIOD
#define BUZZER_PIO_ID 		ID_PIOD
#define BUZZER_PIO_IDX 		20
#define BUZZER_PIO_IDX_MASK (1 << BUZZER_PIO_IDX)

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

// # (1)
#define LED_PIO1           PIOA                 // periferico que controla o LED
#define LED_PIO1_ID        ID_PIOA                  // ID do periférico PIOC (controla LED)
#define LED_PIO1_IDX       0                    // ID do LED no PIO
#define LED_PIO1_IDX_MASK  (1 << LED_PIO1_IDX)   // Mascara para CONTROLARMOS o LED

// # (2)
#define LED_PIO2          PIOC                 // periferico que controla o LED
#define LED_PIO2_ID        ID_PIOC                  // ID do periférico PIOC (controla LED)
#define LED_PIO2_IDX       30                    // ID do LED no PIO
#define LED_PIO2_IDX_MASK  (1 << LED_PIO2_IDX)   // Mascara para CONTROLARMOS o LED

// # (3)
#define LED_PIO3           PIOB                 // periferico que controla o LED
#define LED_PIO3_ID        ID_PIOB                  // ID do periférico PIOC (controla LED)
#define LED_PIO3_IDX       2                    // ID do LED no PIO
#define LED_PIO3_IDX_MASK  (1 << LED_PIO3_IDX)   // Mascara para CONTROLARMOS o LED

#define START_PIO          PIOC
#define START_PIO_ID       ID_PIOC
#define START_PIO_IDX      31
#define START_PIO_IDX_MASK (1u << START_PIO_IDX)

#define SELECAO_PIO          PIOA
#define SELECAO_PIO_ID       ID_PIOA
#define SELECAO_PIO_IDX      19
#define SELECAO_PIO_IDX_MASK (1u << SELECAO_PIO_IDX)

void play_pause(void);
void muda_musica(void);
void set_buzzer();
void clear_buzzer();
int get_startstop();
int get_selecao();
void buzzer_teste(int freq);
void tone(int freq, int time_us);
void play_song_sequence(music m);
void play_from_list(music m[], int size);

