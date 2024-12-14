#include <LiquidCrystal.h>
#include <Servo.h>

// Pinos
const int buttonSetPin = 2;       // Botão para setar o horário
const int buttonResetPin = 3;     // Botão para resetar o cronograma
const int buttonChangeTimePin = 4;  // Botão para mudar o horário quando em modo "set"
const int servoPin = 7;           // Pino de controle do servo motor
const int buzzerPin = 6;          // Pino do buzzer
const int ledPin = 5;             // Pino do LED
const int potPin = A0;            // Pino do potenciômetro para controlar a luminosidade

// Definir LCD (sem I2C)
LiquidCrystal lcd(13,12,8,9,10,11);  // Pinos conforme sua conexão

// Inicialização do servo motor
Servo servo;

// Variáveis
int targetHour = -1;              // Horário para o servo atuar (em UTC)
bool settingTime = false;         // Modo de configuração de horário
unsigned long lastMillis = 0;     // Controle de tempo para evitar múltiplos cliques rápidos nos botões
unsigned long lastSecondMillis = 0; // Armazenar o tempo da última atualização (em milissegundos)
unsigned long lastButtonMillisSet = 0;
unsigned long lastButtonMillisReset = 0;
unsigned long lastButtonMillisChangeTime = 0;
int currentHour = 0;
int currentMinute = 0;
int currentSecond = 0;

// Hora inicial fixa (ajuste conforme necessário)
int initialHour = 0;  // Hora de início (10h)
int initialMinute = 59;  // Minuto de início (30min)
int initialSecond = 40;   // Segundo de início (0s)

void setup() {
  lcd.begin(16, 2);
  servo.attach(servoPin);

  pinMode(buttonSetPin, INPUT_PULLUP);
  pinMode(buttonResetPin, INPUT_PULLUP);
  pinMode(buttonChangeTimePin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);    // Definir pino do buzzer como saída
  pinMode(ledPin, OUTPUT);       // Definir pino do LED como saída

  // Inicializar hora, minuto e segundo com valores predefinidos
  currentHour = initialHour;
  currentMinute = initialMinute;
  currentSecond = initialSecond;
}

void loop() {
  // Atualizar o tempo (usando millis() para manter o tempo sem o uso de RTC ou TimeLib)
  unsigned long currentMillis = millis();
  if (currentMillis - lastSecondMillis >= 1000) {  // A cada 1 segundo
    lastSecondMillis = currentMillis;
    currentSecond++;

    if (currentSecond >= 60) {
      currentSecond = 0;
      currentMinute++;
    }
    if (currentMinute >= 60) {
      currentMinute = 0;
      currentHour++;
    }
    if (currentHour >= 24) {
      currentHour = 0;
    }
  }

  // Ajustar o contraste do LCD com o valor do potenciômetro conectado ao VO do LCD
  int potValue = analogRead(potPin);  // Lê o valor do potenciômetro (0 a 1023)
  int contrastValue = map(potValue, 0, 1023, 0, 255);  // Mapeia o valor para o intervalo 0-255
  // O ajuste do contraste será feito diretamente no pino VO do LCD, então não precisamos de 'analogWrite'
  // O controle físico do potenciômetro já está lidando com isso diretamente

  // Exibir hora no LCD
  lcd.setCursor(0, 0);
  lcd.print("Hora UTC: ");
  lcd.print(currentHour);
  lcd.print(":");
  if (currentMinute < 10) lcd.print("0");
  lcd.print(currentMinute);
  lcd.print(":");
  if (currentSecond < 10) lcd.print("0");
  lcd.print(currentSecond);

  // Verificar se é o momento de acionar o servo (se o horário atingir o horário configurado)
  if (currentHour == targetHour && currentMinute == 0 && currentSecond == 0) {
    // Acionar o servo
    servo.write(180);  // Mover o servo para 90 graus (exemplo)
    delay(1000);  // Mover o servo e esperar para evitar múltiplos acionamentos
    servo.write(0);  // Voltar o servo para a posição inicial

    // Acionar o buzzer
    tone(buzzerPin, 1000);  // Emite um som de 1000 Hz
    digitalWrite(ledPin, HIGH);  // Acende o LED

    delay(2000);  // Aguarda 2 segundos (tempo de buzzer e LED ligado)

    // Desligar o buzzer e o LED
    noTone(buzzerPin);  // Desliga o buzzer
    digitalWrite(ledPin, LOW);  // Apaga o LED
    delay(1000);  // Atraso para evitar múltiplos acionamentos
  }

  // Verificar os botões
  checkButtons();

  delay(500);  // Atraso para evitar flicker no LCD
}

// Função para verificar os botões
void checkButtons() {
  
  // Botão "Set" (Alterna entre configuração de horário e modo normal)
  if (digitalRead(buttonSetPin) == LOW && (millis() - lastButtonMillisSet) > 500) {
    lastButtonMillisSet = millis(); // Controla o debounce

    // Alterna entre o modo de configuração e o modo normal
    settingTime = !settingTime;

    if (settingTime) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Modo Set");
      delay(1000); // Exibe "Modo Set" por 1 segundo para indicar que está no modo de configuração
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Modo Normal");
      delay(1000); // Exibe "Modo Normal" por 1 segundo para indicar que voltou ao modo normal
    }
  }

  // Botão "Reset" (Apaga o cronograma)
  if (digitalRead(buttonResetPin) == LOW && (millis() - lastButtonMillisReset) > 500) {
    lastButtonMillisReset = millis();
    targetHour = -1;  // Resetar horário configurado
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Horario Resetado");
    delay(2000);
  }

  // Botão "Mudar Hora" (Só funciona quando está no modo de configuração)
  if (digitalRead(buttonChangeTimePin) == LOW && (millis() - lastButtonMillisChangeTime) > 500) {
    lastButtonMillisChangeTime = millis();
    
    if (settingTime) {
      // Mudar a hora configurada em 1 hora
      targetHour = (targetHour + 1) % 24;  // Incrementa 1 hora, e se passar de 23, volta para 0
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Hora +1: ");
      lcd.print(targetHour);
      lcd.print(":00 UTC");
      delay(2000);
    }
  }
}
