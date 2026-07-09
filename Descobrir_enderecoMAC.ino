#include <WiFi.h>
#include <esp_now.h>

#define BOTAO 4

// Troque pelo MAC do ESP32 receptor
uint8_t macReceptor[] = {0x28, 0x56, 0x2F, 0x4A, 0x0D, 0xBC};

typedef struct {
  bool ledLigado;
} Mensagem;

Mensagem dados;

void setup() {
  Serial.begin(115200);

  pinMode(BOTAO, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao iniciar ESP-NOW");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, macReceptor, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Erro ao adicionar receptor");
    return;
  }

  Serial.println("Transmissor pronto.");
}

void loop() {
  bool botaoApertado = digitalRead(BOTAO) == LOW;

  dados.ledLigado = botaoApertado;

  esp_now_send(macReceptor, (uint8_t *) &dados, sizeof(dados));

  delay(50);
}