#include <stdio.h>
#include "NuMicro.h"

#define Pin_no_14   PA0 
#define Pin_no_13   PA1 
#define Pin_no_12   PA2

#define LED_ON      1
#define LED_OFF     0


void SYS_Init(void)
{
    /* Enable HXT clock (external XTAL 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Enable LIRC clock */
    CLK_EnableXtalRC(CLK_PWRCTL_LIRCEN_Msk);

    /* Wait for LIRC clock ready */
    CLK_WaitClockReady(CLK_STATUS_LIRCSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_48MHZ);

    /* Set PCLK0/PCLK1 to HCLK/2 */
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2);

	    /* Set PC.3 ~ PC.5 to GPIO  */
//    SYS->GPA_MFPL = (SYS->GPA_MFPL & ~(SYS_GPA_MFPL_PA0MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk | SYS_GPA_MFPL_PA2MFP_Msk)) |
//                    (SYS_GPA_MFPL_PA0MFP_GPIO | SYS_GPA_MFPL_PA1MFP_GPIO | SYS_GPA_MFPL_PA2MFP_GPIO);

//    /* Set PC.3 ~ PC.5 to GPIO output */
//    GPIO_SetMode(PA, (BIT0 | BIT1 | BIT2), GPIO_MODE_OUTPUT);

//    /* Let LED off after initialize */
//	Pin_no_14 = LED_OFF;
//	Pin_no_13 = LED_OFF;
//	Pin_no_12 = LED_OFF;
}


void LED_Init(void)
{    
	/* if already configure in sys init no need to do here*/
    /* Set PC.3 ~ PC.5 to GPIO */
    SYS->GPA_MFPL = (SYS->GPA_MFPL & ~(SYS_GPA_MFPL_PA0MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk | SYS_GPA_MFPL_PA2MFP_Msk)) |
                    (SYS_GPA_MFPL_PA0MFP_GPIO | SYS_GPA_MFPL_PA1MFP_GPIO | SYS_GPA_MFPL_PA2MFP_GPIO);

    /* Set PC.3 ~ PC.5 to GPIO output  here Bit0=pa0 bit1=pa1 bit2=pa2*/
    GPIO_SetMode(PA, (BIT0 | BIT1 | BIT2), GPIO_MODE_OUTPUT);

    /* Let LED off after initialize */
	Pin_no_14 = LED_OFF;
	Pin_no_13 = LED_OFF;
	Pin_no_12 = LED_OFF;
}

void delay(int z)
{
	    int i;
			for( i=0;i<z;i++) {  __NOP(); }
}

int main(void)
{
    //uint32_t sw1_cnt = 0, sw2_cnt = 0;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init LED */
    LED_Init();

    while(1)
    {
			Pin_no_12 ^= 1;    /* 1V */
			
			//CLK_SysTickDelay(10);
			
			Pin_no_14 ^= 1;   /* 1V*/
			Pin_no_13 = 1;  /* 2v*/
			delay(10000);
			Pin_no_13 = 0;
	
			
			
    }
}