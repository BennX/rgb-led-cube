
//DISPLAY
short Display::m_offtime = 5000;   //after 5 seconds
short Display::m_fadeInTime = 2000; // half second


//input def
volatile uint8_t* Input::INC_PIN = &PINB;
volatile uint8_t* Input::INC_DDR = &DDRB;
volatile uint8_t* Input::INC_PORT = &PORTB;
const uint8_t Input::INC_PHASE1_PIN = PINB0;
const uint8_t Input::INC_PHASE2_PIN = PINB1;
const uint8_t Input::INC_TASER_PIN = PINB2;

volatile uint8_t* Input::BUTTON_PIN = &PINC;
volatile uint8_t* Input::BUTTON_DDR = &DDRC;
volatile uint8_t* Input::BUTTON_PORT = &PORTC;
const uint8_t Input::BUTTON0 = PINC2;
const uint8_t Input::BUTTON1 = PINC3;
const uint8_t Input::BUTTON2 = PINC4;
const uint8_t Input::BUTTON3 = PINC5;

const uint16_t Input::INC_CLICK_DELAY = 500;