#ifndef LORA_E5_H
#define LORA_E5_H

#include "stm32l4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

#define LORA_UART_TIMEOUT 1000  // UART 超时时间
#define LORA_BUFFER_SIZE 256    // LoRa 接收缓冲区大小

// LoRa-E5 AT 指令
#define LORA_AT "AT\r\n"
#define LORA_AT_RESET "AT+RESET\r\n"
#define LORA_AT_JOIN "AT+JOIN\r\n"
#define LORA_AT_SEND "AT+MSG="  // 发送数据命令前缀

typedef struct {
    UART_HandleTypeDef *huart;  // UART 句柄
    uint8_t rx_buffer[LORA_BUFFER_SIZE];  // 接收缓冲区
} LoRaE5_t;

// 初始化 LoRa-E5
void LoRaE5_Init(LoRaE5_t *lora, UART_HandleTypeDef *huart);

// 发送 AT 指令
bool LoRaE5_SendCommand(LoRaE5_t *lora, const char *cmd, uint32_t timeout);

// 发送数据
bool LoRaE5_SendData(LoRaE5_t *lora, const char *data);

// 接收数据
bool LoRaE5_ReceiveData(LoRaE5_t *lora, char *buffer, uint16_t buffer_size);

#endif // LORA_E5_H
