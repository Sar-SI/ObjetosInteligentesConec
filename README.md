Plataforma de Monitoramento de Conforto Ambiental

Contexto & Problema
Em salas de aula, flutuações de temperatura prejudicam a concentração dos estudantes e incentivam o uso excessivo de ar‐condicionado, elevando custos e impactando o meio ambiente.

Objetivo
Desenvolver uma solução acessível e open-source que monitore, em tempo real, a temperatura de duas salas, calculando sua média e acionando um único ar-condicionado apenas quando necessário.

Solução Proposta
	1.	Sensores Virtuais (Wokwi + DHT22) capturam temperatura a cada 15 s em duas salas.
	2.	MQTT transporte leve para enviar leituras ao Node-RED.
	3.	Node-RED:
	•	Armazena leituras brutas no InfluxDB para histórico.
	•	Calcula a média das duas salas.
	•	Dispara alerta via WhatsApp (CallMeBot) sempre que a média ≥ 28 °C (“ligar o ar”) ou ≤ 16 °C (“desligar o ar”).
	4.	Grafana exibe dashboards dinâmicos das temperaturas individuais e da média, facilitando a análise.

Benefícios & Impactos
	•	Conforto térmico garantido ao manter a sala na faixa ideal (20 °C–24 °C).
	•	Eficiência energética, reduzindo em até 30 % o consumo ao operar o ar-condicionado apenas sob demanda.
	•	Engajamento dos alunos e sustentabilidade, alinhados aos Objetivos de Desenvolvimento Sustentável (ODS 3, 4 e 13).



Membros do Projeto: Matheus Ramalho Malicia, Guilherme Miranda Bertinato da Rocha, Sara de Oliveira Silva Omena, Pedro Gabriel Marotta Silva, Wallace Santana, da Universidade Mackenzie. 5° Semestre
