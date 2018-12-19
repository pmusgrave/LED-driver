#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LEDStuff.h"
#include "spitest.h"

/*
ISR (ADC_vect){
  red_pot = ADC;
  ADCSRA |= (1 << ADSC);
}

ISR (TIMER0_OVF_vect){
  //  OCR0A = red_pot;
  //  ReadAdcChannel(0);
  //  OCR0A++;
}
*/

int main(void){
  InitGPIO();
  InitTC0();
  InitTC1();
  InitTC2();
  InitADC();
  SPI_SlaveInit();
  //  sei();

  volatile uint16_t red_pot, green_pot, blue_pot;

  Timer_output timer0_output_config = {&DDRD, &PORTD, PD6};
  Timer_output timer1_output_config = {&DDRB, &PORTB, PB1};
  Timer_output timer2_output_config = {&DDRB, &PORTB, PB3};

  struct timer timer0 = {
    TCCR0A,
    ((1<<COM0A1) | (1<<WGM00) | (1<<WGM01)),
    ((1<<WGM00) | (1<<WGM01)),
    &OCR0A,
    0,
    timer0_output_config
  };
  struct timer timer1 = {
    TCCR1A,
    ((1<<COM1A1) | (1<<WGM10)),
    (1<<WGM10),
    (uint8_t*)&OCR1A,
    0,
    timer1_output_config
  };
  struct timer timer2 = {
    TCCR2A,
    ((1<<COM2A1) | (1<<WGM20) | (1<<WGM21)),
    ((1<<WGM20) | (1<<WGM21)),
    &OCR2A,
    0,
    timer2_output_config
  };

  int SpiBuffer = 0;

  while(1){
    _delay_ms(10);
    SpiBuffer = SPI_SlaveReceive();

    // timer1.output_compare_value = ReadAdcChannel(0);
    timer1.output_compare_value = SpiBuffer % 255;
    SetOCR(timer1);

    // timer0.output_compare_value = ReadAdcChannel(1);
    timer0.output_compare_value = SpiBuffer % 255;
    SetOCR(timer0);

    // timer2.output_compare_value = ReadAdcChannel(2);
    timer2.output_compare_value = SpiBuffer % 255;
    SetOCR(timer2);
  }

  return 0;
}

void InitGPIO(void){
  DDRB |= (1 << LED_PIN) | (1<<PB1) | (1<<PB3);
  DDRD |= (1<<PD6);
}

void InitTC0(void){
  TCCR0A |= (1<<COM0A1) | (1<<WGM00) | (1<<WGM01);
  TCCR0B |= (1<<CS01);
}

void InitTC1(void){
  //  PRR &= ~(1 << PRTIM0);
  //  TIMSK0 |= (1<<TOIE0);
  //  TCCR1A |= (1 << WGM00) | (1 << WGM01);
  //  TCCR1B |= (1 << WGM02);
  //  TCCR1B |= (1 << CS02) | (1 << CS00);
  //  TCCR1A |= (1 << COM1A1);

  TCCR1A |= (1<<COM1A1) | (1<<WGM10);// | (1<<WGM11);
  TCCR1B |= (1<<WGM12) | (1<<CS11);
  //  OCR1A = 0;
}

void InitTC2(void){
  TCCR2A |= (1<<COM2A1) | (1<<WGM20) | (1<<WGM21);
  TCCR2B |= (1<<CS21);
}

void InitADC(void){
  ADCSRA |= (1 << ADEN);
  ADCSRA |= (1<<ADPS0) | (1 << ADPS2);
  ADCSRA |= (0b11);

  ADMUX |= (1 << REFS0) | (1<<REFS1) | (1<<ADLAR);

  //ADCSRA |= (1 << ADIE);
}

volatile uint16_t ReadAdcChannel(int channel){
  //  ADMUX = (0xF0 & ADMUX) | channel;
  ADMUX = REFS | channel;
  ADCSRA |= (1 << ADSC);
  while (!(ADCSRA & (1 << ADSC))){
      ;
  }
  return ADCH;
}

void SetCompareValue(struct timer timer, uint8_t new_compare_value){
  timer.output_compare_value = new_compare_value;
}

void SetOCR(struct timer timer){
  if(timer.output_compare_value < LED_THRESHOLD){
    timer.timer_config_register = timer.timer_config_disabled_value;
    *timer.output_config.port_ddr &= ~(1<<timer.output_config.pin);
    *timer.output_config.port &= ~(1<<timer.output_config.pin);
  }
  else {
    *timer.output_config.port_ddr |= (1<<timer.output_config.pin);
    *timer.output_config.port |= (1<<timer.output_config.pin);
    timer.timer_config_register = timer.timer_config_enabled_value;
    *timer.output_compare_register = timer.output_compare_value;
  }

  _delay_ms(10);
}
