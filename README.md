# Projeto Hands-On: Dispensador de Remédio com Servo Motor 

Este projeto faz parte das **atividades práticas** do curso **Maloca das iCoisas**. O sistema demonstra uma solução básica de dispensação de remédios utilizando um **Arduino Mega**, um **servo motor**, um **LCD não I2C**, um **buzzer**, **LEDs**, **3 botões** e um **potenciômetro**. O objetivo principal deste projeto é permitir o controle da dispensação de medicamentos de forma automatizada, com feedback visual e sonoro.

---

## **Visão Geral do Projeto**

### **Objetivo**
O objetivo deste projeto é criar um sistema simples de dispensação de remédio controlado por um Arduino, onde o usuário pode ajustar o tempo em que o remédio deve ser dispensado e visualizar o status da operação no LCD. O sistema conta com botões para controle, um potenciômetro para ajustes e feedback sonoro e visual para indicar o estado do processo.

### **Funcionalidades**
- Controle da dispensação do remédio com servo motor.
- Feedback sonoro com buzzer e visual com LEDs.
- Exibição de mensagens no LCD durante o processo de dispensação.
- Botões para set, change e reset da operação.

---

## **Requisitos de Hardware**

- **Arduino Mega 2560** (ou equivalente)
- **Servo Motor** (para controlar a dispensação do remédio)
- **LCD 16x2** (sem I2C, para exibição de status)
- **Buzzer** (para indicar o estado do processo)
- **LED** (para indicar visualmente o status da operação)
- **3 Botões** (Set, ChangeTime e Reset)
- **Potenciômetro** (para ajustar a luminosidade do LCD)
- Fios jumper e uma protoboard

### **Conexões**

#### **Servo Motor**
| Pino do Servo | Pino do Arduino Mega |
|----------------|----------------------|
| Controle (S)   | 7                    |
| VCC            | 5V                   |
| GND            | GND                  |

#### **LCD 16x2**
| Pino do LCD | Pino do Arduino Mega |
|-------------|-----------------------|
| RS          | 13                    |
| EN          | 12                    |
| D4          | 8                    |
| D5          | 9                   |
| D6          | 10                   |
| D7          | 11                   |
| VCC         | 5V                   |
| GND         | GND                  |
| V0          | Potenciômetro        |

#### **Botões**
| Botão         | Pino do Arduino Mega |
|---------------|----------------------|
| Botão Set | 2                    |
| Botão Reset| 3                    |
| Botão ChangeTime   | 4                    |

#### **LED e Buzzer**
| Componente   | Pino do Arduino Mega |
|--------------|----------------------|
| LED Vermelho | 5                   |
| Buzzer       | 6                    |

---

## **Requisitos de Software**

- **Arduino IDE** (versão mais recente)
- Bibliotecas Necessárias:
  - `Servo` (pré-instalada no Arduino IDE)
  - `LiquidCrystal` (pré-instalada no Arduino IDE)

---

## **Instalação e Uso**

### **1. Clone este Repositório**
```bash
git clone https://github.com/Luccas-H/Projeto_Dispensador_de_Remedio.git
cd Projeto_Dispensador_de_Remedio
