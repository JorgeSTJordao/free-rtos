#include <stdio.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"

// Definindo o tamanho padrao da pilha para facilitar manutencao
#define STACK_SIZE 1000

// Variaveis que simulam a velocidade dos motores
int motor_0 = 0;
int motor_1 = 0;
int motor_2 = 0;
int motor_3 = 0;

//Protótipos das tarefas

//Função de arfagem
void taskArfagem(void* pvParameters);
//Função de rolagem
void taskRolagem(void* pvParameters);


int main_(void)
{

	xTaskCreate(taskArfagem, "taskArfagem", STACK_SIZE, (void*)"frente", 1, NULL);
	xTaskCreate(taskRolagem, "taskRolagem", STACK_SIZE, (void*)"direita", 1, NULL);


	vTaskStartScheduler();

	for (;; );
	return 0;
}

// Funcao que define a funcionalidade de arfagem do quadricoptero
void taskArfagem(void* pvParameters)
{

	char* direction = (char*)pvParameters;

	//Início do loop
	for (;;)

	{
		//Direção vertical
		//Sentido: frente
		if (strcmp(direction, "frente") == 0) {
			motor_2 += 25;
			motor_3 += 25;
			motor_0 -= 25;
			motor_1 -= 25;

		}
		//Sentido: trás
		else if (strcmp(direction, "trás") == 0) {
			motor_2 -= 25;
			motor_3 -= 25;
			motor_0 += 25;
			motor_1 += 25;
		}

		vPrintString(direction);
		printf("ARFAGEM | motor 0: %d |  motor 1: %d | motor 2: %d |  motor 3: %d", motor_0, motor_1, motor_2, motor_3);

		// Simula o delay de 40ms para a rolagem
		vTaskDelay(pdMS_TO_TICKS(40));
	}

	//Tarefa de arfagem deletada
	vTaskDelete(NULL);
}

// Funcao que define a funcionalidade de rolagem do quadricoptero
void taskRolagem(void* pvParameters) {
	char* direction = (char*)pvParameters;

	for (;;) {
		if (strcmp(direction, "direita") == 0) {
			// Alteracao para rolagem para a direita
			motor_0 += 50;
			motor_3 += 50;
			motor_1 -= 50;
			motor_2 -= 50;
		}
		else if (strcmp(direction, "esquerda") == 0) {
			// Alteracao para rolagem para a esquerda
			motor_0 -= 50;
			motor_3 -= 50;
			motor_1 += 50;
			motor_2 += 50;
		}

		vPrintString(direction);
		printf("ROLAGEM | motor 0: %d |  motor 1: %d | motor 2: %d |  motor 3: %d", motor_0, motor_1, motor_2, motor_3);

		// Simula o delay de 20ms para a rolagem
		vTaskDelay(pdMS_TO_TICKS(20));
	}

	// Exclui a tarefa
	vTaskDelete(NULL);
}
