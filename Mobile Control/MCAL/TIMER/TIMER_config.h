#ifndef _TIMER_CONFIG_H
#define _TIMER_CONFIG_H


/* TIMER0_MODE:
 * Options:
 * TIMER_NORMAL_MODE
 * TIMER_PWM_PHASE_CORRECR_MODE
 * TIMER_CTC_MODE
 * TIMER_FAST_PWM_MODE
*/

#define TIMER0_MODE                                TIMER_FAST_PWM_MODE

/* TIMER0_SUB_MODE:  
 * Options: 
 * TIMER_NORMAL_PORT    
 * TIMER_CLR_ON_COMP_SET_ON_TOP     
 * TIMER_SET_ON_COMP_CLEAR_ON_TOP   
 * TIMER_SET_ON_UP_COUNT_CLR_ON_DOWN_COUNT  
 * TIMER_CLR_ON_UP_COUNT_SET_ON_DOWN_COUNT  
*/  

#define TIMER0_SELECT_SUB_MODE                     TIMER_CLR_ON_COMP_SET_ON_TOP


/* TIMER_COUNTER0_PRESCALER_SELECT:
 * Options:
 * TIMER_NO_CLK_SRC             
 * TIMER_NO_PRESCALING          
 * TIMER_PRESCALER_DIV_BY_8     
 * TIMER_PRESCALER_DIV_BY_64    
 * TIMER_PRESCALER_DIV_BY_256   
 * TIMER_PRESCALER_DIV_BY_1024  
 * COUNTER0_EXTI_CLK_RISING_EDGE 
 * COUNTER0_EXTI_CLK_FALLING_EDGE
*/

#define TIMER_COUNTER_PRESCALER_SELECT             TIMER_PRESCALER_DIV_BY_8


#define TIMER1_SELECT_MODE_A                       ICU_FAST_PWM_MODE_MSK_A
#define TIMER1_SELECT_MODE_B                       ICU_FAST_PWM_MODE_MSK_B


/* TIMER1_SUB_MODE:  
 * Options: 
 * TIMER_NORMAL_PORT    
 * TIMER1_CLR_ON_COMP_SET_ON_TOP
 * TIMER1_SET_ON_COMP_CLEAR_ON_TOP
 * TIMER1_SET_ON_UP_COUNT_CLR_ON_DOWN_COUNT
 * TIMER1_CLR_ON_UP_COUNT_SET_ON_DOWN_COUNT
*/  

#define TIMER1_SELECT_SUB_MODE_A                   TIMER1_CLR_ON_COMP_SET_ON_TOP_A

#define TIMER1_SELECT_SUB_MODE_B                   TIMER1_CLR_ON_COMP_SET_ON_TOP_B

#define TIMER1_MODE                                TIMER_NORMAL_MODE
    
#define OC1A_CHANNEL                               ENABLE 
#define OC1B_CHANNEL                               DISABLE
    

#endif
