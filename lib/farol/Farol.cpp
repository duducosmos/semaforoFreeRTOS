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

 #include <Farol.h>


Farol::Farol(int input_verde, int input_amarelo, int input_vermelho)
        : input_verde(input_verde),input_amarelo(input_amarelo), input_vermelho(input_vermelho)
{
        numero_lampadas = 3;
        tempo_atual = millis();
        intervalo = MAXTINTERVALO;
        estado = vermelho;
        pinMode(input_verde, OUTPUT);
        pinMode(input_amarelo, OUTPUT);
        pinMode(input_vermelho, OUTPUT);

}



void Farol::set_input_verde(int input_verde){
        input_verde = input_verde;
        pinMode(input_verde, OUTPUT);
}


char* Farol::estadoToString(){
        switch (estado) {
        case verde:
                return (char *) "verde";
        case amarelo:
                return (char *) "amarelo";
        case vermelho:
                return (char *) "vermelho";
        }
}

void Farol::set_input_amarelo(int input_amarelo){
        input_amarelo = input_amarelo;
        pinMode(input_amarelo, OUTPUT);
}

void Farol::set_input_vermelho(int input_vermelho){
        input_vermelho = input_vermelho;
        pinMode(input_vermelho, OUTPUT);
}


void Farol::reduzir_intervalo(unsigned long time){
        if(get_estado() == verde) {
                set_intervalo(get_intervalo() - time);
                if( get_intervalo() <= 1000) {
                        set_intervalo(1000);
                }
        }


}

void Farol::reduzir_intervalo(){
        if(get_estado() == verde) {
                set_intervalo(get_intervalo() - 1000);
                if( intervalo <= 1000) {
                        set_intervalo(1000);
                }
        }

}

unsigned long Farol::tempo_final(){
        return tempo_atual + intervalo;
}

bool Farol::fdelay(unsigned long & ti, int & i){

        int n = 4;
        if(i == 0) {
                ti = millis();
        }

        unsigned long tf = ti + intervalo;
        unsigned long dt = (tf - ti) / n;

        unsigned long t = ti;
        if(i<= n) {
                if(t + i * dt <= millis()) {
                        i++;
                }

        }
        if(i == n) {

                return true;
        }
        return false;

}
void Farol::_delay(){
        unsigned long tf = millis() + intervalo;
        while(tf >= millis());
}


void Farol::_delay(unsigned long deltatime){
        unsigned long atual = millis() + deltatime;

        while(atual >= millis()) ;
}



void Farol::mudar_estado(){

        switch (estado) {
        case verde:
                estado = amarelo;
                break;
        case amarelo:
                estado = vermelho;

                break;
        case vermelho:
                estado = verde;

                break;
        }
}


void Farol::mudar_luz(){
        switch (estado) {
        case amarelo:
                intervalo = MAXTINTERVALO / 10;
                digitalWrite(input_verde, LOW);
                digitalWrite(input_amarelo, HIGH);
                digitalWrite(input_vermelho, LOW);
                break;
        case vermelho:
                intervalo = MAXTINTERVALO;
                digitalWrite(input_vermelho, HIGH);
                digitalWrite(input_amarelo, LOW);
                digitalWrite(input_verde, LOW);
                break;
        case verde:
                digitalWrite(input_vermelho, LOW);
                digitalWrite(input_amarelo, LOW);
                digitalWrite(input_verde, HIGH);




        }
}


void Farol::resetar_intervalo(){
        intervalo = MAXTINTERVALO;

}
