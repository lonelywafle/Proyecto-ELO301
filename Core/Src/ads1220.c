/*
 * ads1220.c
 *
 *  Created on: Nov 28, 2024
 *      Author: Olatel
 */
#include "ads1220.h"


// Handle del SPI (lo inicializa el archivo principal)
static SPI_HandleTypeDef *ads1220_spi_handle;

// Inicialización del ADS1220
void ADS1220_Init(SPI_HandleTypeDef *spi_handle) {
    ads1220_spi_handle = spi_handle;

    // Reset del ADS1220 al inicio
    ADS1220_SendCommand(ADS1220_RESET_CMD);
    HAL_Delay(10); // Tiempo de inicialización
}

// Función para habilitar el ADS1220 (CS bajo)
void ADS1220_Select(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
}

// Función para deshabilitar el ADS1220 (CS alto)
void ADS1220_Deselect(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
}
//Funcion para leer registros(ver datasheet)
void ADS1220_READ_REG(uint8_t start_reg,uint8_t num_regs,uint8_t *data){

	if(start_reg>0x03||num_regs>0x03) return;

	uint8_t command=0x20 | (start_reg << 2) | (num_regs & 0x03);

	HAL_SPI_Transmit(&hspi1, &command, 1, HAL_MAX_DELAY);

	HAL_SPI_Receive(&hspi1, data, num_regs+1, HAL_MAX_DELAY);
}
//Funcion para escribir regristros
void ADS1220_WRITE_REG(uint8_t start_reg, uint8_t num_regs, uint8_t *data){
	if(start_reg>0x03||num_regs>0x03) return;

	uint8_t command=0x20 | (start_reg << 2) | (num_regs & 0x03);

	HAL_SPI_Transmit(&hspi1, &command, 1, HAL_MAX_DELAY);
	HAL_SPI_Transmit(&hspi1, data, num_regs+1, HAL_MAX_DELAY);
}

// Función para enviar un comando al ADS1220
void ADS1220_SendCommand(uint8_t command) {
    //ADS1220_Select();
   HAL_SPI_Transmit(ads1220_spi_handle, &command, 1, HAL_MAX_DELAY);
    //ADS1220_Deselect();
}

void ADS1220_ReadData(int32_t *data){
	uint8_t RawData[3]={0};

	int pin_status=HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7);

	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)==GPIO_PIN_SET);

	HAL_SPI_Receive(&hspi1, RawData, 3, HAL_MAX_DELAY);

	*data =((int32_t)(RawData[0]<<16)|(RawData[1]<<8)|RawData[2]);

		//if (*data & 0x800000){

		//	*data|=0xFF000000;
		//}

}
// Función para leer un registro de datos (3 bytes)
/*
int32_t ADS1220_ReadData(void) {
    uint8_t data[3] = {0};
    int32_t result = 0;

    ADS1220_Select();
    uint8_t command = ADS1220_READ_DATA_CMD;
    HAL_SPI_Transmit(ads1220_spi_handle, &command, 1, HAL_MAX_DELAY);  // Enviar comando
    HAL_SPI_Receive(ads1220_spi_handle, data, 3, HAL_MAX_DELAY);       // Leer 3 bytes
    ADS1220_Deselect();

    // Convertir los datos a un entero de 24 bits con signo
    result = (data[0] << 16) | (data[1] << 8) | data[2];
    if (result & 0x800000) { // Si el número es negativo en 24 bits
        result |= 0xFF000000; // Extender signo
    }

    return result;
}
*/

