/*
 * Bafang LCD 850C firmware
 *
 * Copyright (C) Casainho, 2018.
 *
 * Released under the GPL License, Version 3
 */

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stdio.h"

#include "pins.h"
#include "lcd.h"
#include "delay.h"
#include "UTFT-STM8S/UTFT.h"

#include "ugui/ugui.h"
#include "ugui_driver/ugui_bafang_500c.h"

void SetSysClockTo128Mhz(void);

void system_power (uint32_t ui32_state)
{
  if (ui32_state)
  {
    GPIO_SetBits(SYSTEM_POWER_ON_OFF__PORT, SYSTEM_POWER_ON_OFF__PIN);
  }
  else
  {
    GPIO_ResetBits(SYSTEM_POWER_ON_OFF__PORT, SYSTEM_POWER_ON_OFF__PIN);
  }
}

int main(void)
{
  extern uint8_t BigFont[];

  SetSysClockTo128Mhz();

  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, DISABLE);

  pins_init();
  delay_init();
  system_power(ENABLE);

  UG_COLOR color[3];

  color[0] = C_RED;
  color[1] = C_GREEN;
  color[2] = C_BLUE;

//  lcd_init ();

  /* Place your initialization/startup code here (e.g. MyInst_Start()) */
  Display_Init();

  while (1) {
  /* Clear screen. */
//  UTFT_clrScr();
//  UG_DrawFrame(100, 100, 10, 10, C_PINK);     // Draw a Frame

//  UG_DrawCircle( UG_S16 x0, UG_S16 y0, UG_S16 r, UG_COLOR c );
  UG_FillCircle(100, 100, 50, C_MAGENTA);

  while (1) ;



//  UG_FillScreen(VGA_YELLOW);

//      UG_FontSelect(&FONT_8X14);
//      UG_PutString(10, 10, "Hello World!");


//        UG_DrawLine(10, 10, 10, 100, C_PINK);     // Draw a Frame


//  delay_ms(2000);
//
//  UTFT_clrScr();
//  UTFT_fillScr(VGA_YELLOW);
//
//  delay_ms(2000);

  }

//  lcd_init();
//
//  UTFT_clrScr();
//  UTFT_fillScr(VGA_AQUA);
//
//  UTFT_setColor(VGA_RED);
//  UTFT_setBackColor(VGA_AQUA);
//  UTFT_setFont(BigFont);
//  UTFT_print("TSDZ2", 10, 140);
//  UTFT_print("Flexible OpenSource firmware", 10, 180);
//  UTFT_print("firmware", 10, 200);

  while (1)
  {

  }
}

void SetSysClockTo128Mhz(void)
{
  ErrorStatus HSEStartUpStatus;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);

    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_16);

    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock configuration.
       User can add here some code to deal with this error */

    /* Go to infinite loop */
    while (1)
    {
    }
  }
}