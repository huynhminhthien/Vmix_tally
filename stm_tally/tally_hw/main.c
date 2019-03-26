
#include "stm8s.h"
#include "mystm8sxxx.h"

// adc pin C4


volatile uint16_t adc_value=0;
volatile uint8_t receive_data=0;
volatile uint8_t data[10];
volatile uint8_t cam=3;


#define LED_GREEN  GPIO_PIN_2
#define LED_RED  GPIO_PIN_3

#define Button  GPIO_PIN_7
//portC
#define LED_1  GPIO_PIN_3
#define LED_2  GPIO_PIN_4
//portb
#define LED_3  GPIO_PIN_4
#define LED_4  GPIO_PIN_5

static void UART_Config(void);

void display()
{
  switch (cam)
    {
      case 0:
      {
        GPIO_WriteHigh(GPIOC,(GPIO_Pin_TypeDef)(LED_1));
        GPIO_WriteLow(GPIOC,(GPIO_Pin_TypeDef)(LED_2));
        GPIO_WriteLow(GPIOB,(GPIO_Pin_TypeDef)(LED_3));
        GPIO_WriteLow(GPIOB,(GPIO_Pin_TypeDef)(LED_4));
        break;
      }
      case 1:
      {
        GPIO_WriteLow(GPIOC,(GPIO_Pin_TypeDef)(LED_1));
        GPIO_WriteHigh(GPIOC,(GPIO_Pin_TypeDef)(LED_2));
        GPIO_WriteLow(GPIOB,(GPIO_Pin_TypeDef)(LED_3));
        GPIO_WriteLow(GPIOB,(GPIO_Pin_TypeDef)(LED_4));
        break;
      }
      case 2:
      {
        GPIO_WriteLow(GPIOC,(GPIO_Pin_TypeDef)(LED_1));
        GPIO_WriteLow(GPIOC,(GPIO_Pin_TypeDef)(LED_2));
        GPIO_WriteHigh(GPIOB,(GPIO_Pin_TypeDef)(LED_3));
        GPIO_WriteLow(GPIOB,(GPIO_Pin_TypeDef)(LED_4));
        break;
      }
      case 3:
      {
        GPIO_WriteLow(GPIOC,(GPIO_Pin_TypeDef)(LED_1));
        GPIO_WriteLow(GPIOC,(GPIO_Pin_TypeDef)(LED_2));
        GPIO_WriteLow(GPIOB,(GPIO_Pin_TypeDef)(LED_3));
        GPIO_WriteHigh(GPIOB,(GPIO_Pin_TypeDef)(LED_4));
        break;
      }
      default:  break;
    }
}

void main(void)
{
  clk_config_16MHz_hsi();
  UART_Config();
  delay_using_timer2_init();

  /*ADC1_DeInit();
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,
  			ADC1_CHANNEL_2,
  			ADC1_PRESSEL_FCPU_D2,
  			ADC1_EXTTRIG_TIM,
  			DISABLE,
  			ADC1_ALIGN_RIGHT,
  			ADC1_SCHMITTTRIG_CHANNEL2,
  			DISABLE);
  ADC1_Cmd(ENABLE);
  ADC1_ITConfig(ADC1_IT_EOCIE,ENABLE);
  enableInterrupts();*/

  GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)(LED_2|LED_1), GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOB, (GPIO_Pin_TypeDef)(LED_3|LED_4), GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOD, (GPIO_Pin_TypeDef)(GPIO_PIN_4), GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOD, (GPIO_Pin_TypeDef)(LED_GREEN|LED_RED), GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)(Button), GPIO_MODE_IN_PU_NO_IT);
  
  GPIO_WriteHigh(GPIOD,(GPIO_Pin_TypeDef)(GPIO_PIN_4));
  
  GPIO_WriteHigh(GPIOC,(GPIO_Pin_TypeDef)(LED_2|LED_1));
  GPIO_WriteHigh(GPIOB,(GPIO_Pin_TypeDef)(LED_3|LED_4));
  GPIO_WriteHigh(GPIOD,(GPIO_Pin_TypeDef)(LED_GREEN));
  delay_ms(200);
  
  GPIO_WriteLow(GPIOC,(GPIO_Pin_TypeDef)(LED_2|LED_1));
  GPIO_WriteLow(GPIOB,(GPIO_Pin_TypeDef)(LED_3|LED_4));
  GPIO_WriteLow(GPIOD,(GPIO_Pin_TypeDef)(LED_GREEN));
  GPIO_WriteHigh(GPIOD,(GPIO_Pin_TypeDef)(LED_RED));
  delay_ms(200);
  
  GPIO_WriteHigh(GPIOC,(GPIO_Pin_TypeDef)(LED_2|LED_1));
  GPIO_WriteHigh(GPIOB,(GPIO_Pin_TypeDef)(LED_3|LED_4));
  GPIO_WriteHigh(GPIOD,(GPIO_Pin_TypeDef)(LED_GREEN));
  GPIO_WriteLow(GPIOD,(GPIO_Pin_TypeDef)(LED_RED));
  delay_ms(200);
  
  GPIO_WriteLow(GPIOC,(GPIO_Pin_TypeDef)(LED_2|LED_1));
  GPIO_WriteLow(GPIOB,(GPIO_Pin_TypeDef)(LED_3|LED_4));
  GPIO_WriteLow(GPIOD,(GPIO_Pin_TypeDef)(LED_GREEN));
  GPIO_WriteLow(GPIOD,(GPIO_Pin_TypeDef)(LED_RED));

  while (1)
  {
    
    /*if(GPIO_ReadInputPin(GPIOC,(GPIO_Pin_TypeDef)Button)==0)
    {
      display();
      delay_ms(700);
      if(GPIO_ReadInputPin(GPIOC,(GPIO_Pin_TypeDef)Button)==0)
      {
        while(GPIO_ReadInputPin(GPIOC,(GPIO_Pin_TypeDef)Button)==0);
        cam++;
        if(cam>=4)
        {
          cam=0;
        }
      }
    }
    //UART1_SendData8(cam);
    display();
    GPIO_WriteLow(GPIOC,(GPIO_Pin_TypeDef)(LED_1));
    GPIO_WriteLow(GPIOC,(GPIO_Pin_TypeDef)(LED_2));
    GPIO_WriteLow(GPIOB,(GPIO_Pin_TypeDef)(LED_3));
    GPIO_WriteLow(GPIOB,(GPIO_Pin_TypeDef)(LED_4));
    delay_ms(500);*/
    /*ADC1_StartConversion();
    if(adc_value <= 763)
    {
    	GPIO_WriteReverse(GPIOD,(GPIO_Pin_TypeDef)GPIO_PIN_7);
    	delay_ms(200);
    }
    else GPIO_WriteLow(GPIOD,(GPIO_Pin_TypeDef)GPIO_PIN_7);
*/
  }
}


static void UART_Config(void)
{
    /* Deinitializes the UART1 peripheral */
    UART1_DeInit();

    /* UART1 Initialize*/
	UART1_Init(9600,
			UART1_WORDLENGTH_8D,
			UART1_STOPBITS_1,
			UART1_PARITY_NO,
			UART1_SYNCMODE_CLOCK_DISABLE,
			UART1_MODE_TXRX_ENABLE);

	/* Enable UART1 receive complete interrupt */
	UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE);

	/* Enable UART1 Module */
	UART1_Cmd(ENABLE);

	/* Enable Global Interrupt */
	enableInterrupts();
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

