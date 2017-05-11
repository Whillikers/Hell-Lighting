// Debug switches //
// #define DEBUG 1
// #define DEBUG_POT 1

// System parameters //
#define NUM_LEDS_1 332
#define NUM_LEDS_2 285
#define NUM_LEDS_3 355
#define NUM_LEDS_4 251
#define NUM_LEDS_MAX 355
#define NUM_LEDS_TOTAL (332 + 285 + 355 + 251)
#define NUM_PATTERNS 10

// System topology by transformed index //
#define ARCH_START 0
#define ARCH_END 43
#define LEFT_START 44
#define LEFT_END 616
#define FAR_START 617
#define FAR_END 651
#define RIGHT_START 652
#define RIGHT_END 1222

// Hardware Constants //
#define POT_MAX 1023

// Pins //
// Interface //
#define PIN_BUTTON_RESET 2
#define PIN_BUTTON_NEXT 4
#define PIN_BUTTON_PREV 11
// Inputs //
#define PIN_POT A0
// LED //
#define PIN_LED_1 9
#define PIN_LED_2 8
#define PIN_LED_3 6
#define PIN_LED_4 7

// Pattern list //
void (*patterns[NUM_PATTERNS])(void);

// Settings //
#define BRIGHTNESS_MAX 100
#define PATTERN_DEFAULT color

// Globals //
CRGB leds[NUM_LEDS_TOTAL]; // Array of all leds taken as one strip, from the inner right corner and going clockwise
int currentPatternIndex;
jmp_buf jumpPoint; // Used for escaping functions
