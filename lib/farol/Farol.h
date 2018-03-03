/*
 * Aplicativo das Luzes do Semaforo
 * Developed by: Eduardo S. Pereira
 * Date: 28/02/2018
 * Version: 0.0.1
 */

 #ifndef FAROL_H
 #define FAROL_H

 #include <stdbool.h>
 #if defined(ARDUINO) && ARDUINO >=100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif




enum Estado {vermelho, amarelo, verde};

class Farol
{
protected:
  #define MAXTINTERVALO 10000
int numero_lampadas;
unsigned long intervalo;
unsigned long  tempo_atual;
Estado estado;
int input_verde;
int input_amarelo;
int input_vermelho;
int input_bina_port;

void _delay();
void _delay(unsigned long deltatime);

public:
Farol(int input_verde, int input_vermelho): input_verde(input_verde), input_vermelho(input_vermelho){};
Farol(int input_verde, int input_amarelo, int input_vermelho);


char* estadoToString();

void set_input_verde(int input_verde);
void set_input_amarelo(int input_amarelo);
void set_input_vermelho(int input_vermelho);


bool fdelay(unsigned long & ti, int & i);

void set_numero_lampadas(int num){
        numero_lampadas = num;
}
int get_numero_lampadas(){
        return numero_lampadas;
}

unsigned long get_intervalo(){
        return intervalo;
}
void set_intervalo(int inter){
        intervalo = inter;
}

unsigned long get_tempo_atual(){
        return tempo_atual;
}
void set_tempo_atual(int inter){
        tempo_atual = inter;
}

enum Estado get_estado(){
        return estado;
}
void set_estado(Estado e){
        estado = e;
}

unsigned long tempo_final();
void mudar_estado();
void mudar_luz();

void resetar_intervalo();

void reduzir_intervalo();
void reduzir_intervalo(unsigned long tempo);

void rodar();

};

#endif
