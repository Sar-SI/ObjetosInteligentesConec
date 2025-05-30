1. Wokwi – Sensores Virtuais
Acesse Wokwi e crie um novo projeto ESP32 + DHT22.
2. Broker MQTT
3. Node-RED
4. InfluxDB
5. Grafana
6. API de WhatsApp (CallMeBot)

Uso
Inicie todos os containers/serviços:

InfluxDB

Grafana

Eclipse Mosquitto (se usar local)

Node-RED

Abra o Wokwi (ESP32 + DHT22) e inicie a simulação.

Observe:

No Node-RED Debug, aparecerão logs de leitura e alertas.

No InfluxDB Data Explorer, visualize measurement=conforto com dois tipos:

sensor = Sensor1

sensor = Sensor2

tipo = media (média das duas salas)

No Grafana, veja os painéis atualizarem em tempo real.

Teste cenários:

“Condição Normal”: nenhuma mensagem WhatsApp (média entre 16 °C e 28 °C).

“Temperatura Alta”: média ≥ 28 °C → recebe alerta para ligar o ar.

“Temperatura Baixa”: média ≤ 16 °C → recebe alerta para desligar o ar.

Fluxo Node-RED (Export / Import)
O arquivo node-red/fluxo_conforto.json contém o fluxo completo.

No Node-RED: Menu → Import → Clipboard → cole o conteúdo de fluxo_conforto.json → clique em Import → Deploy.

Este fluxo já inclui:

Nó MQTT in (assinando TrabalhoObjetos/#).

Function 1 (armazenamento bruto e gravação no InfluxDB).

Function 2 (cálculo de média e envio de mensagem ao WhatsApp).

Nós InfluxDB out, WhatsApp out e Debug.

Exemplos de Mensagens
Alerta de Temperatura Alta

mathematica
Copiar
Editar
Sala 1 faz 31.2°C
Sala 2 faz 30.0°C
Média 30.6°C → convém LIGAR o ar condicionado
Alerta de Temperatura Baixa

mathematica
Copiar
Editar
Sala 1 faz 14.7°C
Sala 2 faz 15.5°C
Média 15.1°C → convém DESLIGAR o ar condicionado
Condição Normal
(nenhuma mensagem, pois a média ficou entre 16 °C e 28 °C)
