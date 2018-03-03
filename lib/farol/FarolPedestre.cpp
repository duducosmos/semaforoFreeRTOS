/*
Author: Eduardo S. Pereira.
Versio: 0.0.1
Date: 03/03/2018

This file is part of SemaforofreeRTOS.
copyright : Eduardo dos Santos Pereira
pystar is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License.
pystar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

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




}

void FarolPedestre::piscar_vermelho(){


        if(estado == verde) {
                digitalWrite(input_verde, HIGH);
                unsigned long dt = get_intervalo() * 0.72;
                unsigned long tf = millis() + dt;

                while(tf > millis()) {
                        if(tf - millis() < dt * 0.3) {
                                digitalWrite(input_verde, LOW);
                                digitalWrite(input_vermelho, HIGH);
                                delay(dt * 0.01);
                                digitalWrite(input_vermelho, LOW);
                                delay(dt* 0.01);

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
