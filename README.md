# Trabalho-PIC
## Robô Autônomo
O projeto consiste em um robô autônomo, controlado por Arduino, que
deverá percorrer uma determinada área e retornar de volta para o ponto de partida e
também será capaz de desviar de obstáculos fazendo para isso uso de um sensor
ultrassônico.
## Lista de componentes:
- 1 ponte h
- 2 motores dc com rodas
- 1 arduino uno
- 1 servo motor
- 1 sensor ultrasonico
- 2 bateria de 9V
- 1 chassi de carro robô
- 1 protoboard
- Jumpers

## Descrição:
O robô será composto por um conjunto de componentes eletrônicos interligados para o
seu funcionamento. Um sensor ultrassônico estará acoplado a um servomotor, ambos

conectados ao Arduino Uno, que por sua vez será alimentado por uma bateria de 9V.
O servomotor terá a função de girar o sensor ultrassônico para varrer o ambiente à
frente do robô, detectando obstáculos e medindo distâncias. Além disso, um módulo
ponte H estará ligado ao Arduino, recebendo alimentação de uma bateria de 9V, e
será responsável por controlar dois motores DC. A ponte H permitirá a mudança de
direção do robô, acionando os motores das rodas em sentidos opostos para
realizarem os giros necessários. Juntos, esses componentes permitirão que o robô se
movimente de forma autônoma, detectando obstáculos, evitando colisões e realizando
trajetórias programadas.

## Resumo:
Robô autônomo controlado por Arduino Uno, equipado com sensor ultrassônico em um servomotor para detectar obstáculos e medir distâncias. Uma ponte H, alimentada por bateria de 9V, controla motores DC, permitindo direcionar o robô. Integração dos componentes garante movimento autônomo, detecção de obstáculos e prevenção de colisões.

## Bibliotecas usadas:
- <AFMotor.h>
Responsavel por cuidar dos motores

- <Servo.h>
Responsavel por cuidar da rotação do servo motor

- <HCSR04.h>
Responsavel por cuidar da captura da distancia e do calculo dela

##Tópicos de atenção / Dificuldades apresentadas no trabalho:
- Incapacidade de sustentação dos motores usando as pilhas
- Mal contato dos jumpers com o sensor, o que impede o funcionamento dos motores
- Cuidado com o posicionamento dos jumpers conectando os motores a ponte h, pode ocorrer a inversão de direção das rodas

## Cronograma:
- Conclusão do robô: 25/02/2025
- Conclusão do vídeo e documentação para Mostra PIC: 05/03/2025

## Membros do grupo:
- Pedro Henrique Peixoto da Silva
- Heron Garcia Lodi e Silva
- Wesley Vieira de Moraes
