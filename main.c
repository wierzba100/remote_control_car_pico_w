#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "cgi.h"
#include "hardware/gpio.h"

const char WIFI_SSID[] = "Router_0";
const char WIFI_PASSWORD[] = "tajemnica54321";

void motor_pins_init(void)
{
    gpio_init(MOTOR_A_FORWARD);
    gpio_init(MOTOR_A_BACKWARD);
    gpio_init(MOTOR_B_FORWARD);
    gpio_init(MOTOR_B_BACKWARD);
    gpio_set_dir(MOTOR_A_FORWARD, GPIO_OUT);
    gpio_set_dir(MOTOR_A_BACKWARD, GPIO_OUT);
    gpio_set_dir(MOTOR_B_FORWARD, GPIO_OUT);
    gpio_set_dir(MOTOR_B_BACKWARD, GPIO_OUT);
}

int main() {
    stdio_init_all();
    cyw43_arch_init();
    cyw43_arch_enable_sta_mode();

    motor_pins_init();

    // Connect to the WiFI network - loop until connected
    while(cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000) != 0)
    {
        printf("Attempting to connect...\n");
    }
    // Print a success message once connected
    printf("Connected!\n");
    
    // Initialise web server
    httpd_init();
    printf("Http server initialised\n");

    cgi_init();
    printf("CGI Handler initialised\n");
    
    // Infinite loop
    while(1);
}