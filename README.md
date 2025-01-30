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

## Código
```c
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define BUTTON_GPIO 5
#define LED_AZUL 11
#define LED_VERMELHO 12
#define LED_VERDE 13

volatile bool system_active = false; // Controla o estado do sistema
volatile int led_state = 0; // Controla o estado dos LEDs

// Função chamada após o temporizador expirar
int64_t led_off_callback(alarm_id_t id, void *user_data) {
    if (led_state == 1) {
        gpio_put(LED_AZUL, 0); // Apaga LED azul
        add_alarm_in_ms(3000, led_off_callback, NULL, false);
    } else if (led_state == 2) {
        gpio_put(LED_VERMELHO, 0); // Apaga LED vermelho
        add_alarm_in_ms(3000, led_off_callback, NULL, false);
    } else if (led_state == 3) {
        gpio_put(LED_VERDE, 0); // Apaga LED verde
        system_active = false; // Permite novo acionamento do botão
    }
    led_state++;
    return 0;
}

// Função de debounce do botão
bool debounce_button() {
    sleep_ms(50); // Delay para estabilizar leitura
    return !gpio_get(BUTTON_GPIO);
}

// Função de callback do botão
void button_callback(uint gpio, uint32_t events) {
    if (!system_active && debounce_button()) {
        system_active = true; 
        led_state = 1;
        
        // Liga todos os LEDs
        gpio_put(LED_AZUL, 1);
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 1);
        
        // Inicia o temporizador de 3 segundos para apagar LEDs
        add_alarm_in_ms(3000, led_off_callback, NULL, false);
    }
}

int main() {
    stdio_init_all();

    // Configura GPIOs dos LEDs como saída
    gpio_init(LED_AZUL);
    gpio_init(LED_VERMELHO);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Configura o botão como entrada com pull-up interno
    gpio_init(BUTTON_GPIO);
    gpio_set_dir(BUTTON_GPIO, GPIO_IN);
    gpio_pull_up(BUTTON_GPIO);

    // Configura interrupção do botão corretamente
    gpio_set_irq_enabled_with_callback(BUTTON_GPIO, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    while (1) {
        tight_loop_contents(); // Mantém o loop rodando
    }
}
```
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

