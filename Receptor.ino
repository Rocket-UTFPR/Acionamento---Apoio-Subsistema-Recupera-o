#include <WiFi.h>
#include <esp_now.h>

#define LED 2

typedef struct {
  bool ledLigado;
} Mensagem;

Mensagem dadosRecebidos;

void receberDados(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  memcpy(&dadosRecebidos, incomingData, sizeof(dadosRecebidos));

  if (dadosRecebidos.ledLigado) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao iniciar ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(receberDados);

  Serial.println("Receptor pronto.");
}

void loop() {
}