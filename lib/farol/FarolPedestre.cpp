/*
 * Aplicativo das Luzes do Semaforo
 * Developed by: Eduardo S. Pereira
 * Date: 28/02/2018
 * Version: 0.0.1
 */

 #include <FarolPedestre.h>

FarolPedestre::FarolPedestre(int input_verde, int input_vermelho) : Farol(input_verde, input_vermelho){
        numero_lampadas = 2;
        tempo_atual = millis();
        intervalo = MAXTINTERVALO;
        estado = verde;
        pinMode(input_verde, OUTPUT);
        pinMode(input_vermelho, OUTPUT);
}


void FarolPedestre::mudar_estado(){
        switch (estado) {
        case verde:
                estado = vermelho;
                break;
        case vermelho:
                estado = verde;
                break;
        }
}

void FarolPedestre::mudar_estado(Estado e){

        switch (e) {
        case verde:
                estado = vermelho;
                break;
        case amarelo:
                estado = vermelho;
                break;
        case vermelho:
                estado = verde;
                break;
        }
        Serial.println(e);
        Serial.println(estadoToString());



}

void FarolPedestre::piscar_vermelho(){


        if(estado == verde) {
                digitalWrite(input_verde, HIGH);
                unsigned long dt = get_intervalo() * 0.7;
                unsigned long tf = millis() + dt;

                while(tf > millis()) {
                        if(tf - millis() < dt * 0.5) {
                                digitalWrite(input_verde, LOW);
                                digitalWrite(input_vermelho, HIGH);
                                delay(get_intervalo() * 0.1);
                                digitalWrite(input_vermelho, LOW);
                                delay(get_intervalo() * 0.1);

                        }
                }

                digitalWrite(input_vermelho, HIGH);
        }
}


void FarolPedestre::mudar_luz(){

        switch (estado) {

        case vermelho:
                digitalWrite(input_vermelho, HIGH);
                digitalWrite(input_verde, LOW);
                break;
        case verde:
                digitalWrite(input_vermelho, LOW);
                digitalWrite(input_verde, HIGH);


        }
}
