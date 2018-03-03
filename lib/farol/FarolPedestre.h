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
