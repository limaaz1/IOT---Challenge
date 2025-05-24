Link do projeto: https://wokwi.com/projects/431744941082328065

Monitoramento de Temperatura com ESP32 e Sensor LM35

Este projeto tem como objetivo monitorar a temperatura usando o sensor LM35 conectado ao ESP32. As leituras são feitas constantemente e enviadas para um broker MQTT usando Wi-Fi. Também é possível simular tudo no Wokwi.

Funcionalidades
Leitura da temperatura com o sensor LM35.

Conversão do sinal analógico em graus Celsius.

Verificação se a temperatura está na faixa considerada normal (entre 90 e 100 graus).

Se a temperatura passar de 105 graus, um alerta é exibido no monitor serial.

Envio da temperatura via MQTT para o tópico fiap/iot/temperatura.

Como funciona:

O ESP32 lê os dados do sensor LM35 e calcula a temperatura. Se a temperatura estiver entre 90 e 100 graus, é considerada normal. Se ultrapassar 105 graus, aparece um alerta. O valor da temperatura é enviado a cada 2 segundos para o broker MQTT.

Resultados:

Durante os testes, foi possível ver a temperatura variando no monitor serial. Quando a temperatura passou de 105 graus, o alerta apareceu corretamente. A comunicação com o MQTT também funcionou, e os dados foram publicados com sucesso no tópico.

Tecnologias usadas:
Simulador Wokwi ([https://wokwi.com](https://wokwi.com/projects/431744941082328065))

ESP32

Sensor de temperatura LM35


Protocolo MQTT

Broker público HiveMQ (broker.hivemq.com)

Arduino IDE

Bibliotecas:
WiFi.h

PubSubClient.h

ArduinoJson.h
