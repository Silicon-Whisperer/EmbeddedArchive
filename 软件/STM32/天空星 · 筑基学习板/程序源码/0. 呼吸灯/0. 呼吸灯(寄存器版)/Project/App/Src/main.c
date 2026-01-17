/**
  ************************************************************************************
  * @file              main.c
  * @author         None
  * @version       V1.0.0
  * @date            2026-01-18
  * @brief           主程序文件，实现LED呼吸灯效果
  *
  * @details        本程序实现两个LED的控制：
  *                        1. LED1以1秒为周期闪烁
  *                        2. LED2通过软件PWM实现呼吸灯效果
  *                        程序使用一个共享的延时计数机制来更新呼吸灯亮度
  *
  * @note            硬件连接：
  *                        - LED1连接PB8引脚
  *                        - LED2连接PB2引脚
  *                        - 低电平点亮LED1，高电平点亮LED2
  *
  * @attention      修改日志：
  *                        - 2026-01-18 V1.0.0 初始版本
  *
  ************************************************************************************
  */
 
#include "main.h"

/**
  * @brief           主函数
  * @param         None
  * @retval          int 程序退出状态码（嵌入式系统中通常不会退出）
  * @note            实现LED呼吸灯控制，包含LED1闪烁和LED2呼吸灯效果
  * @attention     主循环不退出，程序持续运行
  */
int main(void)
{   
    /* 完整呼吸周期(秒) =  (BRIGHTNESS_MAX ÷ STEP) ×  (UPDATE_EVERY × PWM_CYCLE ÷ 1,000,000) × 2 */
    static const int PWM_CYCLE = 500;         // PWM周期 = 500微秒/* PWM周期 */ 
     static const int BRIGHTNESS_MAX = 255; // 亮度最大值 = 255（256级亮度）
    static const int UPDATE_EVERY = 15;      // 更新间隔 = 每15个PWM周期更新一次
    static const int STEP = 1;                          // 亮度步长 = 每次变化1级/* 每次亮度变化的步进值 */       

    static int brightness = 0;                             /* 当前亮度值，范围0-255 */                                     
    static int direction = 1;                                /* 亮度变化方向：1=递增，-1=递减 */                                        
    static int counter = 0;                                  /* 循环计数器，用于控制亮度更新频率 */                                     
    
    /* 硬件初始化 */
    LED_Init();                                                  /* 初始化LED相关硬件（GPIO等） */
    
    /* 主循环 */
    while(1) {        
        /* 计算PWM占空比对应的亮灭时间 */
        int on_time =(brightness * PWM_CYCLE) / BRIGHTNESS_MAX;       /* 高电平时间（有效亮度时间） */     
        int off_time = PWM_CYCLE - on_time;                      /* 低电平时间（剩余时间） */                   
        
        /* 执行一个PWM周期 */
        if(on_time > 0) {
            LED_On_2();                 /* LED2点亮 */
            Delay_us(on_time);       /* 保持高电平时间 */
        }
        if(off_time > 0) {
            LED_Off_2();                 /* LED2熄灭 */
            Delay_us(off_time);       /* 保持低电平时间 */
        }

         /* 亮度值更新逻辑 */
        if(++counter >= UPDATE_EVERY) {
            counter = 0;                                                 /* 重置计数器 */                                          
            
            /* 更新亮度值 */
            brightness += direction * STEP;
            
             /* 亮度边界检查与方向控制 */
            if(brightness >= 255) {
                direction = -1;                                         /* 达到最大值，转为递减 */
                brightness = 255;                                    /* 防止越界，确保值为255 */
                LED_On_1();                                          /* 点亮LED1 */
            } else if(brightness <= 0) {
                direction = 1;                                           /* 达到最小值，转为递增 */          
                brightness = 0;                                         /* 防止越界，确保值为0 */
                LED_Off_1();                                           /* 熄灭LED1 */
            }
        }
    }
    
    /* 主循环理论上不应退出，此处返回语句仅用于语法完整性 */
    // return 0;
}
