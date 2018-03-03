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

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "queue.h"

#include <Farol.h>
#include <FarolPedestre.h>
#include <Botao.h>

QueueHandle_t queue;
QueueHandle_t queue_b;
QueueHandle_t queue_bs;
int queuSize = 10;

void TaskFarol( void *pvParameters );
void TaskFarolPedestre( void *pvParameters );
void TaskFarolBotao( void *pvParameters );


void setup() {
        Serial.begin(9600);
        queue = xQueueCreate(queuSize, sizeof(Estado));
        queue_b = xQueueCreate(queuSize, sizeof(Estado));
        queue_bs = xQueueCreate(queuSize, sizeof(int));

        if(queue == NULL) {
                Serial.println("Error creating the queue.");
        }



        xTaskCreate(
                TaskFarol
                ,  (const portCHAR *) "Farol"
                ,  128
                ,  NULL
                ,  1
                ,  NULL );


        xTaskCreate(
                TaskFarolPedestre
                ,  (const portCHAR *) "FarolPedestre"
                ,  128
                ,  NULL
                ,  1
                ,  NULL );

        xTaskCreate(
                TaskFarolBotao
                ,  (const portCHAR *) "Botao"
                ,  128
                ,  NULL
                ,  1
                ,  NULL );
}

void loop() {
}

void TaskFarolBotao(void *pvParameters)
{
        (void) pvParameters;
        Botao botao(12);
        Estado estadoatualFarol;
        int reduzir_tempo=0;

        while(1) {

                if(xQueueReceive(queue_b, &estadoatualFarol, portMAX_DELAY) == pdPASS) {
                }

                if(estadoatualFarol != verde) {
                        botao.reiniciar_contador();
                        reduzir_tempo = 0;

                }else{
                        botao.update_contador();

                        if(botao.get_contador() > 1) {
                                reduzir_tempo = 1;

                        }else{
                                reduzir_tempo = 0;
                        }
                }
                if(xQueueSend(queue_bs, &reduzir_tempo, 1) != pdPASS) {
                }
        }

}

void TaskFarol(void *pvParameters)
{
        (void) pvParameters;
        Farol farol(3, 4, 5);


        Estado estadoatual;
        int reduzir_tempo=0;
        bool mudar=false;
        unsigned long ti=0;
        int i=0;

        estadoatual = farol.get_estado();

        if(xQueueSend(queue, &estadoatual, 1) != pdPASS) {

        }

        while(1) {

                farol.mudar_luz();
                estadoatual = farol.get_estado();

                if(xQueueReceive(queue_bs, &reduzir_tempo, 1) == pdPASS) {

                }



                if(reduzir_tempo == true && estadoatual == verde) {
                  farol.reduzir_intervalo();
                  Serial.print("RT: ");
                  Serial.println(reduzir_tempo);

                }


                if(xQueueSend(queue_b, &estadoatual, 1) != pdPASS) {

                }

                mudar = farol.fdelay(ti, i);


                if(mudar == true){

                  mudar = false;
                  i=0;
                  farol.mudar_estado();
                  farol.mudar_luz();
                  estadoatual = farol.get_estado();
                  if(xQueueSend(queue, &estadoatual, 1) != pdPASS) {

                  }



                }

        }
}


void TaskFarolPedestre(void *pvParameters)
{
        (void) pvParameters;

        FarolPedestre farol_pedestre(10, 9);
        Estado estadoatualFarol;

        while(1) {
                if(xQueueReceive(queue, &estadoatualFarol, portMAX_DELAY) == pdPASS) {
                }

                farol_pedestre.mudar_estado(estadoatualFarol);
                farol_pedestre.mudar_luz();
                farol_pedestre.piscar_vermelho();

        }
}
