#include "PWM.hpp"


const char* pwm_period = "/sys/class/pwm/pwmchip1/pwm-1:0/period";
const char* pwm_duty = "/sys/class/pwm/pwmchip1/pwm-1:0/duty_cycle";
const char* pwm_enable = "/sys/class/pwm/pwmchip1/pwm-1:0/enable";

void set_pwm_period(const char* period) {
    FILE* fp = fopen(pwm_period, "w");
    if (fp == NULL) {
        printf("Error opening file %s for writing period value %d");
        exit(1);
    }
    fputs(period, fp);
    fclose(fp);
}

void set_pwm_duty(const char* duty) {
    FILE* fp = fopen(pwm_duty, "w");
    if (fp == NULL) {
        printf("Error opening file %s for writing duty value %d");
        exit(1);
    }
    fputs(duty, fp);
    fclose(fp);
}

void set_pwm_enable(const char* enable) {
    FILE* fp = fopen(pwm_enable, "w");
    if (fp == NULL) {
        printf("Error opening file %s for writing enable value %d");
        exit(1);
    }
    fputs(enable, fp);
    fclose(fp);
}