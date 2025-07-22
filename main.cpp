#include "mbed.h"
#include "LITE_EPS.h"
#include "hcsr04.h"
#include "LITE_CDH.h"
#include "LITE_COM.h"

LITE_EPS eps(PA_0,PA_4);
RawSerial pc(USBTX,USBRX,9600);
HCSR04  usensor(PB_1,PA_11);
LITE_CDH cdh(PB_5, PB_4, PB_3, PA_8, "sd", PA_3);
LITE_COM com(PA_9,PA_10,9600);
PwmOut In1(PB_0); // モーター左　入力1 (PWM)
PwmOut In2(PA_6); // モーター右　入力2 (PWM)

int main(){
    int dist;
    eps.turn_on_regulator();
    In1.period_ms(20);
    In2.period_ms(20);
    while(1){
        usensor.start();
        dist = usensor.get_dist_cm();
        pc.printf("distance = %d [cm]\r\n",dist);
        wait_ms(20);
        if(dist <= 20){
            In1.pulsewidth_us(0);
            In2.pulsewidth_us(0);    
        }else if(dist >= 20){
            In1.pulsewidth_us(1600);
            In2.pulsewidth_us(1300);
        }
    }
}