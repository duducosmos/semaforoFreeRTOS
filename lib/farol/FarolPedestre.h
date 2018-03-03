/*
 * Aplicativo das Luzes do Semaforo
 * Developed by: Eduardo S. Pereira
 * Date: 28/02/2018
 * Version: 0.0.1
 */

 #include <Farol.h>

 #ifndef FAROLPEDESTRE_H
 #define FAROLPEDESTRE_H

 #include <stdbool.h>
 #if defined(ARDUINO) && ARDUINO >=100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
class FarolPedestre : public Farol
{
public:
FarolPedestre(int input_verde, int input_vermelho);
void mudar_estado();
void mudar_estado(Estado e);
void piscar_vermelho();
void mudar_luz();

};

#endif
