#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

// Definindo o tamanho padrao da pilha para facilitar manutencao
#define STACK_SIZE 1000

// Variaveis que simulam a velocidade dos motores
int motor_0 = 0;
int motor_1 = 0;
int motor_2 = 0;
int motor_3 = 0;

// Prototipo da funcao de rolagem
void taskRolagem(void *pvParameters);


// MAIN -------------------------------------------------------------
int main(void) {
    // Cria a tarefa de rolagem, passando a direcao como parametro
    xTaskCreate(taskRolagem, "taskRolagem", STACK_SIZE, (void*) "direita", 1, NULL);

    // Inicia o agendador de tarefas
    vTaskStartScheduler();

    for(;;);

    return 0;
}
//-------------------------------------------------------------


// Funcao que define a funcionalidade de rolagem do quadricoptero
void taskRolagem(void *pvParameters) {
    char* direcao = (char*) pvParameters;

    for (;;) {
        if (strcmp(direcao, "direita") == 0) {
            // Alteracao para rolagem para a direita
            motor_0 += 50;
            motor_3 += 50;
            motor_1 -= 50;
            motor_2 -= 50;
        } else if (strcmp(direcao, "esquerda") == 0) {
            // Alteracao para rolagem para a esquerda
            motor_0 -= 50;
            motor_3 -= 50;
            motor_1 += 50;
            motor_2 += 50;
        }

        printf("\nRolagem: %s", direcao);
		printf("\nVelocidade MOTOR 0: %d \nVelocidade MOTOR 1: %d \nVelocidade MOTOR 2: %d \nVelocidade MOTOR 3: %d\n", motor_0, motor_1, motor_2, motor_3);

        // Simula o delay de 20ms para a rolagem
        vTaskDelay(pdMS_TO_TICKS(20));
    }

    // Exclui a tarefa
    vTaskDelete(NULL);
}
