//
// Pontifícia Universidade Católica do Paraná
// Escola Politécnica
// Bacharelado em Ciência da Computação
// Disciplina: Sistemas Operacionais Ciberfísicos
// Professor: Jhonatan Geremias
// Estudantes:	Jorge Jordão
//		Josiel Queiroz Jr.
//		Mateus Alves Ramos
// Projeto FreeRTOS - Fase 2 (Tarefas FreeRTOS)
//						Curitiba, 28 de setembro de 2024
//-------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"  // Para usar semáforos

#define STACK_SIZE 1000
#define RADIO_FREQ_PRIORITY 1
#define MANEUVER_PRIORITY 2
#define STRING_SIZE 12 // Com tamanho 10 eh exibido erro devido o tamanho da palavra ANTIHORARIO

// Variáveis globais com modificador volatile
volatile char sentido[STRING_SIZE];
volatile char direcao[STRING_SIZE];
volatile char orientacao[STRING_SIZE];

// Variáveis que simulam a velocidade dos motores
volatile long motor_0;
volatile long motor_1;
volatile long motor_2;
volatile long motor_3;

// Semáforo binário
SemaphoreHandle_t xSemaphore = NULL;

// Protótipos das funções
void taskRolagem(void* pvParameters);
void taskArfagem(void* pvParameters);
void taskGuinada(void* pvParameters);
void taskRadioFrequencia(void* pvParameters);

int main_(void) {
    // Criação do semáforo binário
    vSemaphoreCreateBinary(xSemaphore);

    if (xSemaphore != NULL) {

        // Criação das tarefas de manobra
        xTaskCreate(taskRolagem, "Rolagem", STACK_SIZE, (void*)orientacao, MANEUVER_PRIORITY, NULL);
        xTaskCreate(taskArfagem, "Arfagem", STACK_SIZE, (void*)direcao, MANEUVER_PRIORITY, NULL);
        xTaskCreate(taskGuinada, "Guinada", STACK_SIZE, (void*)sentido, MANEUVER_PRIORITY, NULL);

        // Criação da tarefa de rádio frequência
        xTaskCreate(taskRadioFrequencia, "RadioFreq", STACK_SIZE, NULL, RADIO_FREQ_PRIORITY, NULL);

        // Inicia o agendador de tarefas
        vTaskStartScheduler();
    }

    for (;;);
    return 0;
}

// Função de rolagem
void taskRolagem(void* pvParameters) {
    char* orientacaoLocal = (char*)pvParameters;

    for (;;) {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
            if (strcmp(orientacaoLocal, "direita") == 0) {
                motor_0 += 50;
                motor_3 += 50;
                motor_1 -= 50;
                motor_2 -= 50;
            }
            else if (strcmp(orientacaoLocal, "esquerda") == 0) {
                motor_0 -= 50;
                motor_3 -= 50;
                motor_1 += 50;
                motor_2 += 50;
            }

            printf("\nRolagem: %s", orientacaoLocal);
            printf("\nVelocidade MOTOR 0: %ld \nVelocidade MOTOR 1: %ld \nVelocidade MOTOR 2: %ld \nVelocidade MOTOR 3: %ld\n", motor_0, motor_1, motor_2, motor_3);

            xSemaphoreGive(xSemaphore);
        }

        vTaskDelay(portTICK_RATE_MS * 20);
    }
}

//Função de arfagem
void taskArfagem(void* pvParameters) {
    char* direcaoLocal = (char*)pvParameters;

    //Início do loop
    for (;;)

    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
            //Verificação de direção da arfagem (frente ou trás)
            if (strcmp(direcaoLocal, "frente") == 0) {
                motor_2 += 25;
                motor_3 += 25;
                motor_0 -= 25;
                motor_1 -= 25;

            }
            else if (strcmp(direcaoLocal, "trás") == 0) {
                motor_2 -= 25;
                motor_3 -= 25;
                motor_0 += 25;
                motor_1 += 25;
            }

            printf("\Arfagem: %s", direcaoLocal);
            printf("\nVelocidade MOTOR 0: %ld \nVelocidade MOTOR 1: %ld \nVelocidade MOTOR 2: %ld \nVelocidade MOTOR 3: %ld\n", motor_0, motor_1, motor_2, motor_3);

            xSemaphoreGive(xSemaphore);
        }

        vTaskDelay(portTICK_RATE_MS * 40);
    }

    vTaskDelete(NULL);
}

// Função de guinada
void taskGuinada(void* pvParameters) {
    char* sentidoLocal = (char*)pvParameters;

    for (;;) {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
            //Verificação da direção no qual será realizada a guinada
            if (strcmp(sentidoLocal, "horario") == 0) { // Caso a ação seja "horário", o strcmp() retornará 0, entrando no if
                motor_0 += 100;
                motor_1 -= 100;
                motor_2 += 100;
                motor_3 -= 100;
            }
            else if (strcmp(sentidoLocal, "anti-horario") == 0) { // Caso a ação seja "anti-horário", o strcmp() retornará 0, entrando no else if
                motor_0 -= 100;
                motor_1 += 100;
                motor_2 -= 100;
                motor_3 += 100;
            }

            printf("\nGuinada: %s", sentidoLocal);
            printf("\nVelocidade MOTOR 0: %ld \nVelocidade MOTOR 1: %ld \nVelocidade MOTOR 2: %ld \nVelocidade MOTOR 3: %ld\n", motor_0, motor_1, motor_2, motor_3);

            xSemaphoreGive(xSemaphore);
        }

        vTaskDelay(portTICK_RATE_MS * 10);
    }
}

// Função de rádio frequência
void taskRadioFrequencia(void* pvParameters) {
    for (;;) {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
            // Sorteio e modificação das variáveis "sentido", "direção" e "orientação"
            int rand_val = rand() % 100;

            if (rand_val % 2 == 0) {
                sprintf((char*)sentido, "horario");
                sprintf((char*)direcao, "frente");
                sprintf((char*)orientacao, "direita");
            }
            else {
                sprintf((char*)sentido, "antihorario");
                sprintf((char*)direcao, "trás");
                sprintf((char*)orientacao, "esquerda");
            }

            printf("\nRadio Frequência alterou as manobras");
            printf("\nSentido: %s, Direção: %s, Orientação: %s", sentido, direcao, orientacao);

            xSemaphoreGive(xSemaphore);
        }


        vTaskDelay(portTICK_RATE_MS * 100);  // Gerando um atraso de 100ms em Ticks
    }
}