# GS-EDGE
# Sistema de Monitoramento e Automação com ESP32 e MQTT

Este projeto visa criar um sistema de monitoramento e automação usando o microcontrolador **ESP32**, sensores de **temperatura** e **umidade** (DHT22), sensor de **luz ambiente** (LDR), atuadores como **relé** e **buzzer**, e a comunicação via **MQTT** para monitoramento remoto.

## Objetivo

O objetivo principal deste projeto é permitir o monitoramento de condições ambientais (temperatura, umidade e luz) e realizar ações automáticas baseadas nesses dados. O sistema é capaz de:
- Medir a temperatura e a umidade ambiente.
- Acionar um relé quando a temperatura ultrapassar um limite.
- Ativar um buzzer quando a umidade estiver abaixo de um determinado valor.
- Enviar dados para um **broker MQTT** para monitoramento remoto e integração com outras plataformas de IoT.

## Componentes Utilizados

- **ESP32**: Microcontrolador para coleta de dados, controle de atuadores e comunicação MQTT.
- **DHT22**: Sensor para medir temperatura e umidade.
- **LDR**: Sensor para medir a intensidade de luz ambiente.
- **Relé**: Atuação de dispositivos externos, como ventiladores ou lâmpadas.
- **Buzzer**: Emite alertas sonoros em caso de condições específicas (ex: baixa umidade).
- **Wi-Fi**: Utilizado para conexão com a rede e o broker MQTT.
- **Broker MQTT**: Comunicação em tempo real dos dados coletados.

## Requisitos

### Hardware:
- **ESP32**
- **DHT22**
- **LDR**
- **Relé**
- **Buzzer**
- **Fios de conexão**

### Software:
- **Arduino IDE** com suporte para ESP32 (instale a placa ESP32 no Arduino IDE).
- Bibliotecas:
  - **DHTesp** para leitura do sensor DHT22.
  - **PubSubClient** para comunicação MQTT.
  - **WiFi.h** para conexão com a rede Wi-Fi.

## Instruções de Uso

### 1. Configuração do Ambiente de Desenvolvimento

1. **Instalar o Arduino IDE**:
   - Baixe e instale a versão mais recente do Arduino IDE [aqui](https://www.arduino.cc/en/software).

2. **Instalar a placa ESP32 no Arduino IDE**:
   - Vá em **File** -> **Preferences**.
   - No campo **Additional Boards Manager URLs**, adicione o seguinte link:
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Vá em **Tools** -> **Board** -> **Boards Manager**, pesquise por "ESP32" e instale a plataforma.

3. **Instalar as bibliotecas necessárias**:
   - **DHTesp**: No Arduino IDE, vá em **Sketch** -> **Include Library** -> **Manage Libraries**, pesquise por "DHTesp" e instale.
   - **PubSubClient**: Da mesma forma, pesquise e instale a biblioteca "PubSubClient" para comunicação MQTT.

### 2. Conectar o Hardware

Conecte os componentes da seguinte maneira:

- **DHT22**:
  - VCC -> 3.3V do ESP32
  - GND -> GND do ESP32
  - Data -> Pino 15 do ESP32

- **LDR**:
  - Pino analógico do LDR no pino GPIO de sua escolha (no código, foi utilizado o pino 34).

- **Relé**:
  - VCC do relé no 5V ou 3.3V do ESP32, dependendo do seu modelo.
  - GND no GND do ESP32.
  - IN do relé no pino GPIO (no código, utilizado o pino 2).

- **Buzzer**:
  - VCC no 5V ou 3.3V do ESP32.
  - GND no GND do ESP32.
  - IN do buzzer no pino GPIO (no código, utilizado o pino 2).

### 3. Código

Carregue o código no ESP32 usando o Arduino IDE, com as configurações da rede Wi-Fi e o broker MQTT desejado.

### 4. Monitoramento dos Dados

- Conecte-se ao **broker MQTT** (por exemplo, `test.mosquitto.org` ou qualquer outro broker MQTT).
- Inscreva-se nos tópicos relevantes:
  - `/ThinkIOT/temp` para monitorar a temperatura.
  - `/ThinkIOT/hum` para monitorar a umidade.
  - `/ThinkIOT/light` para monitorar o nível de luz.
  
Você pode utilizar ferramentas como **MQTT Explorer** ou **Node-RED** para visualizar e interagir com os dados em tempo real.

## Funções de Automação

- **Relé**: Aciona dispositivos (como ventiladores) quando a temperatura supera 30°C.
- **Buzzer**: Emite um alerta sonoro quando a umidade está abaixo de 40%.
- **MQTT**: Envia dados de temperatura, umidade e luz para monitoramento remoto.


## Resultados Esperados

- **Eficiência energética**: A automação pode controlar dispositivos com base nas condições do ambiente, economizando energia.
- **Conforto e qualidade de vida**: O sistema ajusta automaticamente o ambiente com base na temperatura e umidade.
- **Monitoramento remoto**: Os dados são disponibilizados em tempo real, permitindo controle e ajustes à distância.

## Impacto Esperado

A implementação deste sistema tem o potencial de:
- Otimizar o consumo de energia.
- Melhorar a qualidade do ambiente, tornando-o mais confortável.
- Promover a integração de soluções de IoT em lares e empresas, permitindo um controle remoto eficaz e acessível.

## Licença

Este projeto é de código aberto, licenciado sob a licença MIT. Sinta-se à vontade para modificar e distribuir este código conforme necessário.

## Contribuições

Sinta-se livre para contribuir com melhorias no código ou novas funcionalidades. Para contribuir:
1. Faça um **fork** deste repositório.
2. Crie uma nova **branch**.
3. Realize suas alterações.
4. Abra um **pull request** para revisão.

# Participantes

Este repositório conta com as contribuições das seguintes pessoas:

- [Guilherme Flores](https://github.com/guiflores)
- [Bruno Oliveira](https://github.com/Brunootavioliveira)


