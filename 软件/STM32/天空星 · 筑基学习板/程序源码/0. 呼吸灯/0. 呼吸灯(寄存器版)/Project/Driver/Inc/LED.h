/**
  ************************************************************************************
  * @file              LED.h
  * @author         Yan
  * @version       V1.0.0
  * @date            2026-01-18
  * @brief            LED驱动模块头文件
  *
  * @details        本文件提供了LED模块的初始化、控制函数接口声明
  *                        包含2个LED的控制函数：
  *                        1. LED1控制：LED_On_1() / LED_Off_1()
  *                        2. LED2控制：LED_On_2() / LED_Off_2()
  *
  * @note            使用前需确保对应的GPIO端口时钟已使能
  *                        具体引脚定义在LED.c文件中配置
  *
  * @attention     修改日志：
  *                         - 2026-01-18 V1.0.0 初始版本
  *
  ************************************************************************************
  */
  
#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

/**
  * @brief           LED模块初始化函数
  * @param        None
  * @retval          None
  * @note           初始化LED对应的GPIO引脚为推挽输出模式
  *                        配置引脚为高速输出，无上拉下拉电阻
  *                        初始化后LED默认状态为熄灭
  *
  * @attention    注意事项：
  *                        1. 调用前需确保RCC外设时钟已使能
  *                        2. 会修改对应GPIO引脚的配置寄存器
  *                        3. 重复调用不会影响已初始化的引脚
  */
void LED_Init(void);

/**
  * @brief           点亮LED1函数
  * @param        None
  * @retval          None
  * @note           通过BSRR寄存器设置对应位点亮LED1
  *                        使用原子操作，不影响同一端口其他引脚
  *
  * @attention    注意事项：
  *                        1. LED1连接PB8引脚
  *                        2. 高电平点亮，低电平熄灭
  */
void LED_On_1(void);

/**
  * @brief           熄灭LED1函数
  * @param        None
  * @retval          None
  * @note           通过BSRR寄存器清除对应位熄灭LED1
  *                        使用原子操作，不影响同一端口其他引脚
  *
  * @attention    注意事项：
  *                        1. LED1连接PB8引脚
  *                        2. 高电平点亮，低电平熄灭
  */
void LED_Off_1(void);

/**
  * @brief           点亮LED2函数
  * @param        None
  * @retval          None
  * @note           通过ODR寄存器设置对应位点亮LED2
  *                        直接操作ODR寄存器，非原子操作
  *
  * @attention    注意事项：
  *                        1. LED2连接PB2引脚
  *                        2. 高电平点亮，低电平熄灭
  *                        3. 操作ODR会影响同一端口其他引脚的输出状态
  */
void LED_On_2(void);

/**
  * @brief           熄灭LED2函数
  * @param        None
  * @retval          None
  * @note           通过ODR寄存器清除对应位熄灭LED2
  *                        直接操作ODR寄存器，非原子操作
  *
  * @attention    注意事项：
  *                        1. LED2连接PB2引脚
  *                        2. 高电平点亮，低电平熄灭
  *                        3. 操作ODR会影响同一端口其他引脚的输出状态
  */
void LED_Off_2(void);

#ifdef __cplusplus
}
#endif

#endif  /* __LED_H */
