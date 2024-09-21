
#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"

//Protótipos das tarefas
void temperature(void* pvParameters);
void saturation(void* pvParameters);
void heartbeat(void* pvParameters);

//Tarefa para medir a temperatura
void temperature(void* pvParameters)
{
	char* dados = (char*)pvParameters;
	float pTemperature;
	
	//Início do loop
	for (;;)

	{
		//Variável que recebe os valores entre 34 até 41 de forma aleatória
		pTemperature = 34.0f + ((float)rand()) / ((float)RAND_MAX) * 6.0f;

		printf("%s %.2f", dados, pTemperature);

		//Hipotermia com temperatura menor que 35
		if (pTemperature < 35.0f) {
			printf("HIPOTERMIA");
		}
		//Febre com temperatura maior que 37.5
		else if (pTemperature > 37.5f) {
			printf("FEBRE");
		}

		//Tarefa bloqueada por 1s
		printf("\n");
		vTaskDelay(1000);
	}

	//Tarefa não mais disponível na memória RAM
	vTaskDelete(NULL);
}

//Tarefa para medir a saturação
void saturation(void* pvParameters)
{
	char* dados = (char*)pvParameters;
	float pSaturation;
	

	//Início do loop
	for (;;)
	{
		pSaturation = 80.0f + ((float)rand()) / (float)(RAND_MAX) * 20.0f;

		vPrintStringAndNumber(dados, pSaturation);

		if (pSaturation < 90.0f) {
			printf("SATURAÇÃO BAIXA");
		}

		//Tarefa bloequada por 1s
		printf("\n");
		vTaskDelay(1000);
	}

	//Tarefa não mais disponível na memória RAM
	vTaskDelete(NULL);
}

//Tarefa para medir os batimentos
void heartbeat(void* pvParameters)
{
	char* dados = (char*)pvParameters;
	float pHeartBeat;

	//Início do loop
	for (;;)

	{
		pHeartBeat = 20.0f + ((float)rand()) / (float)(RAND_MAX) * 120.0f;

		vPrintStringAndNumber(dados, pHeartBeat);

		if (pHeartBeat < 50.0f) {
			printf("BATIMENTO CARDÍACO BAIXO");
		}
		else if (pHeartBeat > 90.0f) {
			printf("BATIMENTO CARDÍACO ALTO");
		}

		//Tarefa bloequada por 1s
		printf("\n");
		vTaskDelay(1000);
	}

	//Tarefa não mais disponível na memória RAM
	vTaskDelete(NULL);
}

int main_(void)
{

	//Na respectiva ordem
	//pvTaskCode: pointeiro da tarefa que implementa a função
	//pcName: nome descritivo para a tarefa
	//usStackDepth: espaço alocado na memória RAM em bytes (bloco da tarefa)
	//pvParameters: parâmetro do tipo 'pointer do void (void*)'
	//uxPriority: prioridade da tarefa
	//pxCreatedTask: usado para passar um handle para a tarefa criada
	xTaskCreate(temperature, "Temperature", 1000, (void*)"- Temperatura ", 1, NULL);
	xTaskCreate(saturation, "Saturation", 1000, (void*)"- Saturação ", 1, NULL);
	xTaskCreate(heartbeat, "HeartBeat", 1000, (void*)"- Batimentos ", 1, NULL);

	//Início do escalonamento RTOS
	vTaskStartScheduler();

	for (;; );
	return 0;
}
