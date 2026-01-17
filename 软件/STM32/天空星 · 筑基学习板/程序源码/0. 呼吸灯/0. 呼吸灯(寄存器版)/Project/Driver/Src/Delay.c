/**
  ************************************************************************************
  * @file              Delay.c
  * @author         None
  * @version       V1.0.0
  * @date            2026-01-18
  * @brief           延时函数模块源文件
  *
  * @details        本文件实现了基于SysTick定时器的延时函数：
  *                        1. 微秒级延时（Delay_us）
  *                        2. 毫秒级延时（Delay_ms）
  *                        3. 秒级延时（Delay_s）
  *                        使用SystemCoreClock自动计算计数值，支持不同频率MCU
  *
  * @note            SysTick配置：
  *                        - 使用HCLK作为时钟源
  *                        - 24位递减计数器
  *                        - 最大计数值：0xFFFFFF (16,777,215)
  *
  * @attention      注意事项：
  *                        1. 延时精度受系统时钟频率影响
  *                        2. 延时期间会占用CPU资源（忙等待）
  *                        3. 微秒延时最大值为0xFFFFFF/(SystemCoreClock/1000000)
  *                        
  *                        修改日志：
  *                        - 2026-01-18 V1.0.0 初始版本
  *
  ************************************************************************************
  */
#include "stm32f4xx.h"

/**
  * @brief           微秒级延时函数
  * @param         xus 延时时长，单位：微秒 (μs)
  * @retval          None
  * @note           使用SysTick定时器实现精确微秒延时
  *                        - 根据SystemCoreClock自动计算计数值
  *                        - 24位计数器最大值为0xFFFFFF
  *                        - F407系统时钟为168MHz时，最大延时约233,015μs
  *
  * @attention    注意事项：
  *                        1. 延时期间会阻塞CPU执行
  *                        2. 超过最大值的延时将被截断为最大值
  *                        3. 使用前需确保SystemCoreClock已正确设置
  */
void Delay_us(uint32_t xus)
{
    /* 计算需要的计数值 */
    uint32_t ticks = SystemCoreClock / 1000000 * xus; 
    
    /* 防止计数值超过24位计数器最大值 */
    if(ticks > 0xFFFFFF) ticks = 0xFFFFFF;
    
    /* 配置SysTick定时器 */
    SysTick->LOAD = ticks;                                       /* 设置定时器重装值，F407的时钟频率是168MHz */
    SysTick->VAL = 0x00;                                          /* 清空当前计数值 */
    SysTick->CTRL = 0x00000005;                          /* 设置时钟源为HCLK，启动定时器 */
    
    /* 等待计数到0 */
    while(!(SysTick->CTRL & 0x00010000));           
    
    /* 关闭定时器 */
    SysTick->CTRL = 0x00000004;                          
}

/**
  * @brief           毫秒级延时函数
  * @param        xms 延时时长，单位：毫秒 (ms)
  * @retval          None
  * @note           基于Delay_us函数实现的毫秒级延时
  *                        - 通过循环调用Delay_us(1000)实现
  *                        - 支持最大延时：4,294,967,295毫秒
  *
  * @attention    注意事项：
  *                        1. 延时精度受微秒延时精度影响
  *                        2. 长时间延时会占用CPU资源
  *                        3. 参数为0时函数直接返回
  */
void Delay_ms(uint32_t xms)
{
    /* 循环调用微秒延时函数实现毫秒延时 */
	while(xms--)
	{
		Delay_us(1000);             /* 延时1毫秒 */
	}
}
 
/**
  * @brief           秒级延时函数
  * @param        xs 延时时长，单位：秒 (s)
  * @retval          None
  * @note           基于Delay_ms函数实现的秒级延时
  *                        - 通过循环调用Delay_ms(1000)实现
  *                        - 支持最大延时：4,294,967,295秒
  *
  * @attention    注意事项：
  *                        1. 延时精度受毫秒延时精度影响
  *                        2. 非常长的延时可能因计数器溢出而不准确
  *                        3. 实际应用中建议使用硬件定时器实现长时间延时
  */
void Delay_s(uint32_t xs)
{
    /* 循环调用毫秒延时函数实现秒延时 */
	while(xs--)
	{
		Delay_ms(1000);             /* 延时1秒 */
	}
} 
