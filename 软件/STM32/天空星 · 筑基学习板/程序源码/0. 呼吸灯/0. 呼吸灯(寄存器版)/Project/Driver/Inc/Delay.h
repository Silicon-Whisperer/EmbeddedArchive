/**
  ************************************************************************************
  * @file              Delay.h
  * @author         None
  * @version       V1.0.0
  * @date            2026-01-18
  * @brief           延时函数模块头文件
  *
  * @details        本文件提供了不同时间精度的延时函数接口声明
  *                        包含3个不同时间单位的延时函数：
  *                        1. 微秒延时：Delay_us()
  *                        2. 毫秒延时：Delay_ms()
  *                        3. 秒延时：Delay_s()
  *
  * @note            延时函数基于系统时钟实现，延时精度与系统时钟频率相关
  *                        使用前需确保系统时钟已正确配置
  *
  * @attention     修改日志：
  *                         - 2026-01-18 V1.0.0 初始版本
  *
  ************************************************************************************
  */
  
 #ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
  * @brief           微秒级延时函数
  * @param        us 延时时间，单位：微秒
  * @retval          None
  * @note           使用SysTick定时器或软件循环实现微秒级延时
  *                        延时时间与实际时钟频率相关
  *
  * @attention    注意事项：
  *                        1. 参数范围：1-1000000微秒
  *                        2. 延时精度受中断影响
  *                        3. 长时间延时请使用Delay_ms或Delay_s
  */
void Delay_us(uint32_t us);

/**
  * @brief           毫秒级延时函数
  * @param        ms 延时时间，单位：毫秒
  * @retval          None
  * @note           基于Delay_us函数实现的毫秒级延时
  *                        实际延时 = ms * 1000微秒
  *
  * @attention    注意事项：
  *                        1. 参数范围：1-4294967毫秒（约71.5分钟）
  *                        2. 长时间延时可能影响系统实时性
  *                        3. 延时期间CPU处于忙等待状态
  */
void Delay_ms(uint32_t ms);

/**
  * @brief           秒级延时函数
  * @param        s 延时时间，单位：秒
  * @retval          None
  * @note           基于Delay_ms函数实现的秒级延时
  *                        实际延时 = s * 1000毫秒
  *
  * @attention    注意事项：
  *                        1. 参数范围：1-4294967秒（约49.7天）
  *                        2. 超长时间延时建议使用硬件定时器
  *                        3. 延时期间CPU无法处理其他任务
  */
void Delay_s(uint32_t s);

#ifdef __cplusplus
}
#endif

#endif  /* __DELAY_H */
