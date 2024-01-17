#include "LED.hpp"
#include "74LS47.hpp"
#include "Ncounter.hpp"
#include <thread>
#include <mutex>

#define SLEEP(x) std::this_thread::sleep_for(std::chrono::seconds(x))
#define SLEEP_MILLI(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))
#define CLOCK for(;;)

#define ALL_REF_LIST { &cir_hour.high4,&cir_minute.high4,&cir_second.high4,\
                &cir_hour.low4,&cir_minute.low4,&cir_second.low4 }

#define CIR_EXIT 0
#define CIR_PAUSE 1
#define CIR_WORK 2

std::mutex mtx;
int state=CIR_PAUSE;

cir_8bitCounter cir_hour,cir_minute,cir_second;

void set_RD(bool f){
    std::lock_guard<std::mutex> lock(mtx);
    cir_hour.high4.RD=cir_hour.low4.RD=f;
    cir_minute.high4.RD=cir_minute.low4.RD=f;
    cir_second.high4.RD=cir_second.low4.RD=f;
}
void set_second_EP_ET(bool f){
    std::lock_guard<std::mutex> lock(mtx);
    cir_second.low4.EP=cir_second.high4.ET=f;
}
void circuit_working(){
    char**g=init_g();
    start_74161(ALL_REF_LIST);
    preset_74161(cir_hour.high4,bit4("0000"));
    preset_74161(cir_hour.low4,bit4("0000"));
    preset_74161(cir_minute.high4,bit4("0000"));
    preset_74161(cir_minute.low4,bit4("0000"));
    preset_74161(cir_second.high4,bit4("0000"));
    preset_74161(cir_second.low4,bit4("0000"));

    cir_hour.high4.EP=cir_hour.high4.ET=0;
    cir_hour.low4.EP=cir_hour.low4.ET=0;
    cir_minute.high4.EP=cir_minute.high4.ET=0;
    cir_minute.low4.EP=cir_minute.low4.ET=0;

    CLOCK{
        LEDshow(g,
            func_7447(cir_hour.high4.Q),func_7447(cir_hour.low4.Q),
            func_7447(cir_minute.high4.Q),func_7447(cir_minute.low4.Q),
            func_7447(cir_second.high4.Q),func_7447(cir_second.low4.Q)
        );
        if(state==CIR_EXIT) break;

        //DEBUG(cir_hour,cir_minute,cir_second);
        counter_second(cir_second);
        counter_minute(cir_minute,cir_second);
        counter_hour(cir_hour,cir_minute,cir_second);
        SLEEP_MILLI(1000);
    }

    release_g(g);
}

void wait_for_input(){
    std::string cmd;
    while(1){
        std::getline(std::cin,cmd);
        if(cmd=="exit"){
            state=CIR_EXIT;
            break;
        }else if(cmd=="pause"){
            state=CIR_PAUSE;
            set_second_EP_ET(0);
        }else if(cmd=="work"){
            state=CIR_WORK;
            set_second_EP_ET(1);
        }else if(cmd=="start"){
            set_RD(1);
        }else if(cmd=="zero"){
            set_RD(0);
        }
    } 
}

int main(){
    set_RD(0);
    std::thread work_thread(circuit_working);
    std::thread input_thread(wait_for_input);
    //std::thread pause_thread(set_RD_zero);
    work_thread.join();
    input_thread.join();
    //pause_thread.join();
    return 0;
}