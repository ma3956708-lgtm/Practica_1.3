#include <Arduino.h>

const int PIN_BOTON_ENCENDER = 32;
const int PIN_BOTON_APAGAR   = 33;

const int PIN_RELAY_IN1 = 26; 
const int PIN_RELAY_IN2 = 27; 

const bool RELE_ACTIVO_EN_BAJO = true;

unsigned long ultimoOn = 0;
unsigned long ultimoOff = 0;
const unsigned long DEBOUNCE_MS = 50;

bool focoEncendido = false;

void activarRelay(int pin, bool activar) {
  if (RELE_ACTIVO_EN_BAJO) {
    digitalWrite(pin, activar ? LOW : HIGH);
  } else {
    digitalWrite(pin, activar ? HIGH : LOW);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_BOTON_ENCENDER, INPUT_PULLUP);
  pinMode(PIN_BOTON_APAGAR, INPUT_PULLUP);

  pinMode(PIN_RELAY_IN1, OUTPUT);
  pinMode(PIN_RELAY_IN2, OUTPUT);

  activarRelay(PIN_RELAY_IN1, false); // Foco apagado al iniciar
  activarRelay(PIN_RELAY_IN2, false); // Canal 2 en reposo

  Serial.println("Sistema listo: presiona ENCENDER o APAGAR.");
}

void loop() {
  unsigned long ahora = millis();

  if (digitalRead(PIN_BOTON_ENCENDER) == LOW && (ahora - ultimoOn) > DEBOUNCE_MS) {
    ultimoOn = ahora;
    if (!focoEncendido) {
      focoEncendido = true;
      activarRelay(PIN_RELAY_IN1, true);
      Serial.println("Foco ENCENDIDO");
    }
  }

  if (digitalRead(PIN_BOTON_APAGAR) == LOW && (ahora - ultimoOff) > DEBOUNCE_MS) {
    ultimoOff = ahora;
    if (focoEncendido) {
      focoEncendido = false;
      activarRelay(PIN_RELAY_IN1, false);
      Serial.println("Foco APAGADO");
    }
  }
}