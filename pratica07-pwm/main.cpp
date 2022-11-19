#include "PWM.hpp"

int main() {
    // CONFIG-PIN P9.22 pwm
    system("config-pin P9.22 pwm");
    set_pwm_period("20000000");
    set_pwm_enable("1");

    while (1) {
        // Set 90 step (RIGHT)
        set_pwm_duty("600000"); // 3% duty cycle

        usleep(1000000);

        // Set 0 step (middle)
        set_pwm_duty("1500000"); //7.5% duty cycle

        usleep(1000000);

        // Set 180 (-90) step (LEFT)
        set_pwm_duty("2600000"); //13% duty cycle

        usleep(1000000);
    }

    return (0);
}