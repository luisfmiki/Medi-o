#include <Arduino.h>

#define N_AMOSTRAS_POT 160		// numero de amostras para o calculo da potencia

unsigned long tempo[N_AMOSTRAS_POT];
uint16_t corrente[N_AMOSTRAS_POT];
uint16_t tensao[N_AMOSTRAS_POT];
uint16_t luminancia;
uint16_t temperatura;

uint8_t CanalAtual = 0;               // A0 = corrente, A1 = tensão, A2 = luminancia, A3 = temperatura
uint8_t m,n = 0;                  // variaveis de iteração;
uint8_t flag = 0;                 // flag para indicar que completou um ciclo de amostras

ISR(ADC_vect) {
  switch(CanalAtual) {
    case 0:
      corrente[m] = ADC;
      tempo[m] = micros();
      CanalAtual = 1;
      ADMUX |= 1;                       // vai pro canal A1
      m++;
      break;
    case 1:
      tensao[n] = ADC;
      CanalAtual = 0;
      ADMUX = 0x40;                     // volta pro canal A0
      n++;
      break;
    case 2:
      delayMicroseconds(500);         // aparentemene as funcões de delay() e micros() funcionam dentro da ISR
      flag = 1;
      luminancia = ADC;
      break;
    case 3:
      ADMUX = 0b01000010;           // vai pro canal da luminancia
      CanalAtual = 2;
      temperatura = ADC;
      break;
  }
}


void setup() {
  cli();
  ADMUX = _BV(REFS0);                     // ref de 5V
  ADCSRA = _BV(ADATE) | _BV(ADIE) | 0x07; // ativa conversion complete interrupt, e seta prescale de 128 (freq de amostragem = 9.6kHz)
  ADCSRB = 0;                             // free-running mode
  DIDR0 = 0xFF;                           // desativa o input buffer

  
  ADCSRA |= _BV(ADEN);              // ativa o ADC
  ADCSRA |= _BV(ADSC);              // começa a primeira conversao
  sei();
  Serial.begin(115200);
}

void loop() {

  /* se n >= N_AMOSTRAS_POT, completamos um ciclo de amostras*/  
  if(n >= N_AMOSTRAS_POT) {
    ADCSRA ^= _BV(ADEN);              // desativa o ADC
    n = 0;
    m = 0;
    ADMUX = 0b01000011;               // muda para o canal da luminancia
    CanalAtual = 3;
    ADCSRA ^= _BV(ADEN);              // reativa o ADC
    ADCSRA |= _BV(ADSC);              // começa a primeira conversao

  }
  if(flag) {
    ADCSRA ^= _BV(ADEN);                // desativa o ADC
    cli();
    /* envia os dados de um ciclo de amostra para o LabVIEW*/
    for(int i=0;i<N_AMOSTRAS_POT;i++) {
      Serial.print(corrente[i]);
      Serial.print(',');
      Serial.print(tensao[i]);
      Serial.print(',');
    }
    Serial.print(':');
    for(int i=0;i<N_AMOSTRAS_POT;i++) {
      Serial.print(tempo[i]);
      Serial.print(',');
    }
    Serial.print(';');
    Serial.print(luminancia);
    Serial.print(',');
    Serial.print(temperatura);
    Serial.println();
    sei();
    flag = 0;
    ADMUX = 0x40;                     // muda para o canal da corrente
    CanalAtual = 0;
    ADCSRA ^= _BV(ADEN);              // reativa o ADC
    ADCSRA |= _BV(ADSC);              // começa a primeira conversao

  }
}
