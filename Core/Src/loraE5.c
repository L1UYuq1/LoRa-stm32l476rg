#include "loraE5.h"
#include <string.h>
#include <stdio.h>

void LoRaE5_Init(LoRaE5_t *lora, UART_HandleTypeDef *huart) {
    lora->huart = huart;
    memset(lora->rx_buffer, 0, LORA_BUFFER_SIZE);
}

// 发送 AT 指令
bool LoRaE5_SendCommand(LoRaE5_t *lora, const char *cmd, uint32_t timeout) {
    HAL_UART_Transmit(lora->huart, (uint8_t *)cmd, strlen(cmd), timeout);
    HAL_Delay(100);  // 等待 LoRa-E5 处理命令
    return true;
}

// 发送数据
bool LoRaE5_SendData(LoRaE5_t *lora, const char *data) {
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "%s%s\r\n", LORA_AT_SEND, data);
    return LoRaE5_SendCommand(lora, cmd, LORA_UART_TIMEOUT);
}

// 接收数据
bool LoRaE5_ReceiveData(LoRaE5_t *lora, char *buffer, uint16_t buffer_size) {
    HAL_StatusTypeDef status = HAL_UART_Receive(lora->huart, (uint8_t *)buffer, buffer_size, LORA_UART_TIMEOUT);
    return (status == HAL_OK);
}
