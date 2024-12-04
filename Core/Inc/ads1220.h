/*
 * ads1220.h
 *
 *  Created on: Nov 28, 2024
 *      Author: Olatel
 */

#ifndef INC_ADS1220_H_
#define INC_ADS1220_H_

#include "main.h"

// Definición de pines y comandos
//#define ADS1220_CS_Pin GPIO_PIN_0  // Cambia según tu diseño
//#define ADS1220_CS_GPIO_Port GPIOA // Cambia según tu diseño

extern SPI_HandleTypeDef hspi1;

// Comandos del ADS1220
#define ADS1220_RESET_CMD      0x06    // Resetear el dispositivo
#define ADS1220_START_SYNC_CMD 0x08    // Iniciar o reiniciar conversiones
#define ADS1220_POWERDOWN_CMD  0x02    // Modo de bajo consumo
#define ADS1220_RDATA_CMD      0x10    // Leer datos mediante comando

// Macros para leer y escribir registros (con operandos rr y nn)
#define ADS1220_RREG_CMD(rr, nn)  (0x20 | ((rr & 0x03) << 2) | (nn & 0x03)) // Leer registros
#define ADS1220_WREG_CMD(rr, nn)  (0x40 | ((rr & 0x03) << 2) | (nn & 0x03)) // Escribir registros

// Prototipos de funciones
void ADS1220_Init(SPI_HandleTypeDef *spi_handle);
void ADS1220_Select(void);
void ADS1220_Deselect(void);
void ADS1220_SendCommand(uint8_t command);
void ADS1220_READ_REG(uint8_t start_reg,uint8_t num_regs,uint8_t *data);
void ADS1220_WRITE_REG(uint8_t start_reg,uint8_t num_regs,uint8_t *data);
void ADS1220_ReadData(int32_t *data);

//int32_t ADS1220_ReadData(void);


#endif /* INC_ADS1220_H_ */
