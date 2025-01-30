# Semáforo com Temporizador no Raspberry Pi Pico W

## Descrição
Este projeto implementa um sistema de temporização utilizando a função `add_alarm_in_ms()` do Pico SDK para controlar um conjunto de três LEDs (azul, vermelho e verde) a partir de um botão. Os LEDs são acionados progressivamente e desligados em intervalos de 3 segundos.

## Funcionalidade
1. Ao pressionar o botão (GPIO 5), os três LEDs (GPIOs 11, 12 e 13) são ligados simultaneamente.
2. Após 3 segundos, um LED é desligado.
3. Após mais 3 segundos, outro LED é desligado.
4. Após mais 3 segundos, o último LED é desligado.
5. O botão só pode ser pressionado novamente quando todos os LEDs estiverem apagados.
6. Implementa debounce por software para evitar acionamentos acidentais do botão.

## Componentes Utilizados
- **Microcontrolador:** Raspberry Pi Pico W
- **LEDs:** 3 LEDs (azul, vermelho e verde)
- **Botão:** Pushbutton conectado ao GPIO 5
- **Software:** Pico SDK e BitDogLab para simulação

## Configuração dos GPIOs
| Componente | GPIO |
|------------|------|
| Botão     | 5    |
| LED Azul   | 11   |
| LED Vermelho | 12 |
| LED Verde  | 13   |

## Como Compilar e Executar
1. Instale o [Pico SDK](https://github.com/raspberrypi/pico-sdk).
2. Clone este repositório e configure o ambiente do Pico SDK.
3. Compile o código "UN-4-Atividade-2-Temporizador-disparo-One-Shot.c" usando VSCODE
4. Suba o arquivo `.uf2` gerado para o Raspberry Pi Pico W.
5. Pressione o botão e observe a sequência de LEDs.

## Melhorias Futuras
- Adicionar suporte para ajustes dinâmicos do tempo de espera.
- Implementar um LED indicador do estado do sistema.
- Testar diferentes técnicas de debounce para maior confiabilidade.

## Autor
Renan dos Santos Ferreira

