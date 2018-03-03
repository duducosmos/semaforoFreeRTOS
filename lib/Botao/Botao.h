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

 #ifndef BOTAO_H
 #define BOTAO_H

 #include <stdbool.h>
 #if defined(ARDUINO) && ARDUINO >=100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

class Botao
{

protected:
  #define MAXCONTADOR 100
  #define ATRASODELEITURA 200
int contador;
int input_botao;
int estado_botao;

public:

Botao(int input_b);
void set_input_botao(int input_b){
        input_botao = input_b;
}

int get_input_botao(){
        return input_botao;
}

void set_contador(int cont){
        contador = cont;
}

int get_contador(){
        return contador;
}


void reiniciar_contador(){
        contador = 0;
}

void update_contador();

bool pressionado();

};

#endif
