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
