/**
  ************************************************************************************
  * @file              LED.c
  * @author         Yan
  * @version       V1.0.0
  * @date            2026-01-18
  * @brief            LED驱动模块源文件
  *
  * @details        本文件实现了LED模块的初始化和控制函数
  *                        包含2个LED的控制函数：
  *                        1. LED1控制：使用ODR寄存器直接操作
  *                        2. LED2控制：使用BSRR寄存器原子操作
  *
  * @note            硬件连接：
  *                         - LED1/LED2共用PB2引脚
  *                         - 高电平点亮LED，低电平熄灭LED
  *
  * @attention     修改日志：
  *                         - 2026-01-18 V1.0.0 初始版本
  *
  ************************************************************************************
  */
 
#include "LED.h"

/**
  * @brief           LED初始化函数
  * @param        None
  * @retval          None
  * @note           初始化PB2引脚为推挽输出模式，配置输出速度为高速
  * @attention    使用寄存器直接操作方式配置GPIO
  */
void LED_Init()
{
    /* 1. 使能GPIOB时钟 */
    // RCC->AHB1ENR |= (0x01 << 1);                                 // 使用位运算使能GPIOB时钟
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;       // 使用预定义宏使能GPIOB时钟
   
    /* 2. 配置输出模式 */
    GPIOB->MODER &= ~(3U << (2 * 2));                           // 清除PB2的模式位
    GPIOB->MODER |= (1U << (2 * 2));                               // 将PB2配置为输出模式
    GPIOB->MODER &= ~(3U << (2 * 8));                           // 清除PB8的模式位
    GPIOB->MODER |= (1U << (2 * 8));                               // 将PB8配置为输出模式
       
    // 3. 配置为推挽输出，无上拉下拉 */
    GPIOB->OTYPER &= ~(1U << 2);                                 // 配置PB2为推挽输出
    GPIOB->PUPDR &= ~(3U << (2 * 2));                           // 配置PB2无上拉下拉
    GPIOB->OTYPER &= ~(1U << 8);                                 // 配置PB8为推挽输出
    GPIOB->PUPDR &= ~(3U << (2 * 8));                           // 配置PB8无上拉下拉
      
    /* 4. 配置输出速度 */
    GPIOB->OSPEEDR |= ( 0x03 << 2 * 2 );                      // 配置PB2输出速度为超高速
    GPIOB->OSPEEDR |= ( 0x03 << 2 * 8 );                      // 配置PB8输出速度为超高速
    
    GPIOB->ODR &= ~ (0x01 << 2); 
    GPIOB->BSRR = (1U << 8);
}

/**
  * @brief           点亮LED1
  * @param        None
  * @retval          None
  * @note           通过BSRR寄存器设置位点亮LED
  * @attention    使用BSRR寄存器原子操作，不影响同一端口其他引脚
  */
void LED_On_1(void) 
{
    GPIOB->BSRR = (1U << (8 + 16));                                 // BSRR低16位写1，将ODR对应位清零
}

/**
  * @brief           熄灭LED1
  * @param        None
  * @retval          None
  * @note           通过BSRR寄存器清除位熄灭LED（输出高电平）
  * @attention    使用BSRR寄存器原子操作，不影响同一端口其他引脚
  */
void LED_Off_1(void)
{
    GPIOB->BSRR = (1U << 8);                                            // BSRR高16位写1，将ODR对应位置1
}

/**
  * @brief           点亮LED2
  * @param        None
  * @retval          None
  * @note           通过ODR寄存器清除对应位点亮LED
  * @attention    使用ODR寄存器操作，非原子操作
  */
void LED_On_2(void)
{
    GPIOB->ODR |= ( 0x01 << 2);                                      // 设置ODR第2位，输出高电平点亮LED
}

/**
  * @brief           熄灭LED2
  * @param        None
  * @retval          None
  * @note           通过ODR寄存器设置对应位熄灭LED
  * @attention    使用ODR寄存器操作，非原子操作
  */
void LED_Off_2(void)
{
    GPIOB->ODR &= ~ (0x01 << 2);                                   // 清除ODR第2位，输出低电平熄灭LED
}


