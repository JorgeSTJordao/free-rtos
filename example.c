//
//
// Pontifícia Universidade Católica do Paraná
// Escola Politécnica
// Bacharelado em Ciência da Computação
// Disciplina: Sistemas Operacionais Ciberfísicos
// Professor: Jhonatan Geremias
// Estudantes:	Jorge Jordão
//		Josiel Queiroz Jr.
//		Mateus Alves Ramos
// Projeto FreeRTOS - Fase 1 (Tarefas FreeRTOS)
//						Curitiba, 21 de setembro de 2024
//-------------------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
//Função de guinada
void taskGuinada(void* pvParameters);

int main_(void)
{

	xTaskCreate(taskArfagem, "taskArfagem", STACK_SIZE, (void*)"frente", 1, NULL);
	xTaskCreate(taskRolagem, "taskRolagem", STACK_SIZE, (void*)"direita", 1, NULL);
	// Realizando a criação da tarefa, definindo a mesma prioridade das outras (prioridade 1) e passando o sentido da guinda.
	xTaskCreate(taskGuinada, "taskGuinada", STACK_SIZE, (void*)"horario", 1, NULL);

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
		printf(" | ARFAGEM \nmotor 0: %d \nmotor 1: %d \nmotor 2: %d \nmotor 3: %d \n\n", motor_0, motor_1, motor_2, motor_3);

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
		printf(" | ROLAGEM \nmotor 0: %d \nmotor 1: %d \nmotor 2: %d \nmotor 3: %d\n\n", motor_0, motor_1, motor_2, motor_3);

		// Simula o delay de 20ms para a rolagem
		vTaskDelay(pdMS_TO_TICKS(20));
	}

	// Exclui a tarefa
	vTaskDelete(NULL);
}

// Funcao que define a funcionalidade de guinada do quadricoptero
void taskGuinada(void* pvParameters)
{
	//Cadeia de char (string) de entrada, que definirá se o movimento de guindada será no sentido horário ou antihorário
	char* sense = (char*)pvParameters;

	//Início do loop
	for (;;)
	{
		//Verificação da direção no qual será realizada a guinada
		if (strcmp(sense, "horario") == 0) { // Caso a ação seja "horário", o strcmp() retornará 0, entrando no if
			motor_0 += 100;
			motor_1 -= 100;
			motor_2 += 100;
			motor_3 -= 100;
		}
		else if (strcmp(sense, "anti-horario") == 0) { // Caso a ação seja "anti-horário", o strcmp() retornará 0, entrando no else if
			motor_0 -= 100;
			motor_1 += 100;
			motor_2 -= 100;
			motor_3 += 100;
		}

		vPrintString(sense);
		printf(" | GUINADA \nmotor 0: %d \nmotor 1: %d \nmotor 2: %d \nmotor 3: %d\n\n", motor_0, motor_1, motor_2, motor_3);

		// Simula o delay de 10ms para a guinada
		vTaskDelay(pdMS_TO_TICKS(10));
	}

	//Ralizando a exclusão explícita da tarefa quando não for mais utilizada
	vTaskDelete(NULL);
}
