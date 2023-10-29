#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "cgi.h"

const char WIFI_SSID[] = "Router_0";
const char WIFI_PASSWORD[] = "tajemnica54321";

int main() {
    stdio_init_all();
    cyw43_arch_init();
    cyw43_arch_enable_sta_mode();

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