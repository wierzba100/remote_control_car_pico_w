#ifndef REMOTE_CONTROL_CAR_CGI_H
#define REMOTE_CONTROL_CAR_CGI_H

#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"

#define MOTOR_A_FORWARD 12
#define MOTOR_A_BACKWARD 13
#define MOTOR_B_FORWARD 14
#define MOTOR_B_BACKWARD 15

// CGI handler which is run when a request for /led.cgi is detected
const char * cgi_led_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    // Check if an request for LED has been made (/led.cgi?led=x)
    if (strcmp(pcParam[0] , "led") == 0)
    {
        // Look at the argument to check if LED is to be turned on (x=1) or off (x=0)
        if(strcmp(pcValue[0], "0") == 0)
        {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        }else if(strcmp(pcValue[0], "1") == 0)
        {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        }
    }
    // Send the index page back to the user
    return "/index.html";
}

void set_motor_pins(bool motor_a_forw, bool motor_a_back, bool motor_b_forw, bool motor_b_back)
{
    gpio_put(MOTOR_A_FORWARD, motor_a_forw);
    gpio_put(MOTOR_A_BACKWARD, motor_a_back);
    gpio_put(MOTOR_B_FORWARD, motor_b_forw);
    gpio_put(MOTOR_B_BACKWARD, motor_b_back);
}

const char * car_movement_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    if (strcmp(pcParam[0] , "direction") == 0)
    {
        if(strcmp(pcValue[0], "forward") == 0)
        {
            set_motor_pins(true,false,true,false);
        }else if(strcmp(pcValue[0], "left") == 0)
        {
            set_motor_pins(false,false,true,false);
        }else if(strcmp(pcValue[0], "right") == 0)
        {
            set_motor_pins(true,false,false,false);
        }else if(strcmp(pcValue[0], "backward") == 0)
        {
            set_motor_pins(false,true,false,true);
        }
    }

    // Send the index page back to the user
    return "/index.html";
}

// tCGI Struct
// Fill this with all of the CGI requests and their respective handlers
static const tCGI cgi_handlers[] = {
    {
        // Html request for "/led.cgi" triggers cgi_handler
        "/led.cgi", cgi_led_handler
    },
    {
        "/car_movement.cgi", car_movement_handler
    },
};

void cgi_init(void)
{
    http_set_cgi_handlers(cgi_handlers, 2);
}

#endif //REMOTE_CONTROL_CAR_CGI_H