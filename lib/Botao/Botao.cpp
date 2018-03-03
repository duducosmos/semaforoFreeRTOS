/*
 * Aplicativo do Botao
 * Developed by: Eduardo S. Pereira
 * Date: 28/02/2018
 * Version: 0.0.1
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
        Serial.print("Bt: ");
        Serial.println(estado_botao);
        if(estado_botao == LOW) {
                return false;
        }
        return true;
}
