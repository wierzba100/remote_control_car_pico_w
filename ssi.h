#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"

// SSI tags - tag length limited to 8 bytes by default
const char * ssi_tags[] = {"rssi"};

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen) {
    size_t printed;
    switch (iIndex) {
        case 0: // rssi
        {
            int32_t rssi;
            cyw43_wifi_get_rssi(&cyw43_state, &rssi);
            printed = snprintf(pcInsert, iInsertLen, "%d", rssi);
        }
            break;
        default:
            printed = 0;
            break;
    }

    return (u16_t)printed;
}

// Initialise the SSI handler
void ssi_init() {
    http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}
