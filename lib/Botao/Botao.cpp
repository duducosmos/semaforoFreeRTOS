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

 #include "Botao.h"

Botao::Botao(int input_b){
        input_botao = input_b;
        estado_botao = 0;
        contador = 0;
        Serial.print("Botao na porta: ");
        Serial.println(input_botao);
        pinMode(12, input_botao);

}

void Botao::update_contador(){
        if(pressionado() == true) {
                if(get_contador() >= MAXCONTADOR) {
                        set_contador(MAXCONTADOR);
                }else{
                        set_contador(get_contador() + 1);
                }

        }

}

bool Botao::pressionado(){

        estado_botao = digitalRead(input_botao);
        delay(ATRASODELEITURA);

        if(estado_botao == LOW) {
                return false;
        }
        return true;
}
