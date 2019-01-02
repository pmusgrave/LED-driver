#ifndef LED_H
#define LED_H

#define F_CPU 160000000UL
#define LED_PIN 5
#define MUX_SETTING 000
#define CLEAR 4
#define LED_THRESHOLD 10
#define REFS (1 << REFS0) | (1<<REFS1) | (1<<ADLAR)

typedef struct Timer_ouput {
  uint8_t *port_ddr;
  uint8_t *port;
  uint8_t pin;
} Timer_output;

struct timer {
  uint8_t timer_config_register;
  uint8_t timer_config_enabled_value;
  uint8_t timer_config_disabled_value;
  uint8_t *output_compare_register;
  uint8_t output_compare_value;
  Timer_output output_config;
};

void InitGPIO(void);
void InitTC0(void);
void InitTC1(void);
void InitTC2(void);
void InitADC(void);
void SetCompareValue(struct timer timer, uint8_t new_compare_value);
void SetOCR(struct timer timer);
volatile uint16_t ReadAdcChannel (int channel);

#endif
