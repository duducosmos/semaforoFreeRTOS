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

                if(xQueueReceive(queue, &estadoatualFarol, portMAX_DELAY) == pdPASS) {
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

        while(1) {

                farol.mudar_luz();
                estadoatual = farol.get_estado();

                if(xQueueReceive(queue_bs, &reduzir_tempo, 1) == pdPASS) {

                }

                if(reduzir_tempo == true) {
                  farol.reduzir_intervalo();
                }

                if(xQueueSend(queue, &estadoatual, 1) != pdPASS) {

                }

                mudar = farol.fdelay(ti, i);


                if(mudar == true){
                  mudar = false;
                  i=0;
                  farol.mudar_estado();
                  farol.mudar_luz();
                  Serial.print("RT: ");
                  Serial.println(reduzir_tempo);
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

                        farol_pedestre.mudar_estado(estadoatualFarol);
                        farol_pedestre.mudar_luz();
                        farol_pedestre.piscar_vermelho();

                }else{
                        Serial.println("Erro ao receber mesangem Pedestre");
                        farol_pedestre.mudar_estado(vermelho);
                }

        }
}
