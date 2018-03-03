/*
 * Aplicativo do Botao
 * Developed by: Eduardo S. Pereira
 * Date: 28/02/2018
 * Version: 0.0.1
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
  #define ATRASODELEITURA 500
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
