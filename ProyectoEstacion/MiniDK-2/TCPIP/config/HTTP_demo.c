/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    HTTP_DEMO.C
 *      Purpose: HTTP Server demo example
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <RTL.h>
#include <Net_Config.h>
#include <LPC17xx.h>                    /* LPC17xx definitions               */
#include "GLCD.h"
//#include "debug_frmwrk.h"


BOOL LEDrun;
BOOL LCDupdate;
BOOL tick;
U32  dhcp_tout;
U8   lcd_text[2][16+1] = {" ",                /* Buffer for LCD text         */
                          "Waiting for DHCP"};

extern LOCALM localm[];                       /* Local Machine Settings      */
#define MY_IP localm[NETIF_ETH].IpAdr
#define DHCP_TOUT   50                        /* DHCP timeout 5 seconds      */

static void init_io (void);
static void init_display (void);

#ifdef RTX_KERNEL
 U64 tcp_stack[800/8];                        /* A bigger stack for tcp_task */

 /* Forward references */
 __task void init       (void);
 __task void blink_led  (void);
 __task void timer_task (void);
 __task void tcp_task   (void);
#endif

/*--------------------------- init ------------------------------------------*/

#ifndef RTX_KERNEL

static void init () {
  /* Add System initialisation code here */ 

  init_io ();
	
  init_display ();
  init_TcpNet ();

  /* Setup and enable the SysTick timer for 100ms. */
  SysTick->LOAD = (SystemCoreClock / 10) - 1;
  SysTick->CTRL = 0x05;
}

#else

__task void init (void) {
  /* Add System initialisation code here */ 

  init_io ();
  init_display ();


  init_TcpNet ();

  /* Initialize Tasks */
  os_tsk_prio_self (100);
  os_tsk_create (blink_led, 20);
  os_tsk_create (timer_task, 30);
  os_tsk_create_user (tcp_task, 0, &tcp_stack, sizeof(tcp_stack));
  os_tsk_delete_self();
}

#endif

/*--------------------------- timer_poll ------------------------------------*/

#ifndef RTX_KERNEL

static void timer_poll () {
  /* System tick timer running in poll mode */

  if (SysTick->CTRL & 0x10000) {
    /* Timer tick every 100 ms */
    timer_tick ();
    tick = __TRUE;
  }
}

#else

__task void timer_task (void) {
  /* System tick timer task */
  os_itv_set (10);
  while (1) {
    timer_tick ();
    tick = __TRUE;
    os_itv_wait ();
  }
}

#endif

/*--------------------------- init_io ---------------------------------------*/

static void init_io () {

  /* Configure the GPIO for Push Buttons */
  LPC_PINCON->PINSEL4 &= 0xFFCFFFFF;
  LPC_GPIO2->FIODIR   &= 0xFFFFFBFF;

 
  /* Configure the GPIO for LED1 and LED2. */
  LPC_GPIO3->FIODIR   |= (1<<25)|(1<<26);


  /* Configure UART0 for 115200 baud. */
  LPC_PINCON->PINSEL0 &= ~((3 << 4)|(3 << 6));
  LPC_PINCON->PINSEL0 |= (1 << 4)|(1 << 6);
//  LPC_PINCON->PINSEL4 |= 0x0000000A;
  LPC_UART0->LCR = 0x83;
  LPC_UART0->DLL = 9;                              /* 115200 Baud Rate @ 25.0 MHZ PCLK */
  LPC_UART0->FDR = 0x21;                           /* FR 1,507, DIVADDVAL = 1, MULVAL = 2 */
  LPC_UART0->DLM = 0;
  LPC_UART0->LCR = 0x03;

  /* Configure AD0.2 input. */
  LPC_PINCON->PINSEL1 &= 0xFFF3FFFF;
  LPC_PINCON->PINSEL1 |= 0x00040000;
  LPC_SC->PCONP       |= 0x00001000;
  LPC_ADC->ADCR        = 0x00200404;               /* ADC enable, ADC clock 25MHz/5, select AD0.2 pin */
}


/*--------------------------- fputc -----------------------------------------*/

int fputc(int ch, FILE *f)  {
  /* Debug output to serial port. */

  if (ch == '\n')  {
    while (!(LPC_UART0->LSR & 0x20));
    LPC_UART0->THR = 0x0D;
  }
  while (!(LPC_UART0->LSR & 0x20));
  LPC_UART0->THR = (ch & 0xFF);
  return (ch);
}


/*--------------------------- LED_out ---------------------------------------*/

void LED_out (U32 val) {
  const U8 led_pos[2] = { 25, 26 }; // LED1 and LED2 (P3.25 y P3.26)
  U32 i,mask;

  for (i = 0; i < 2; i++) {
    mask = 1 << led_pos[i];
    if (val & (1<<i)) {
    LPC_GPIO3->FIOCLR = mask;  // LED ON
    }
    else {
    LPC_GPIO3->FIOSET = mask;  // LED OFF
    }
  }

}


/*--------------------------- AD_in -----------------------------------------*/

U16 AD_in (U32 ch) {
  /* Read ARM Analog Input */
  U32 val = 0;
  U32 adcr;

  if (ch < 8) {
    adcr = 0x01000000 | (1 << ch);
    LPC_ADC->ADCR = adcr | 0x00200100;        /* Setup A/D: 10-bit @ 9MHz  */

    do {
      val = LPC_ADC->ADGDR;                   /* Read A/D Data Register    */
    } while ((val & 0x80000000) == 0);        /* Wait for end of A/D Conv. */
    LPC_ADC->ADCR &= ~adcr;                   /* Stop A/D Conversion       */
    val = (val >> 6) & 0x03FF;                /* Extract AINx Value (10 bits) */
  }
  return (val);
}


/*--------------------------- get_button ------------------------------------*/

U8 get_button (void) {
  /* Read Mini-DK2 Digital Input */
  U32 val = 0;
    /* ISP button ?*/
  if ((LPC_GPIO2->FIOPIN & (1 << 10)) == 0) val |= 0x01; // P2.10 ?
	
    /* KEY1 button ?*/
  if ((LPC_GPIO2->FIOPIN & (1 << 11)) == 0) val |= 0x02; // P2.11 ?
	
    /* KEY2 button ? */
  if ((LPC_GPIO2->FIOPIN & (1 << 12)) == 0) val |= 0x04; // P2.12 ?
  
  return (val);
}


/*--------------------------- upd_display -----------------------------------*/

static void upd_display () {
  /* Update GLCD Module display text. */

   LCD_Clear(Black);
   GUI_Text(60,144,lcd_text[0],White,Red);
   GUI_Text(52,160,lcd_text[1],White,Red);

   LCDupdate =__FALSE;
}


/*--------------------------- init_display ----------------------------------*/

static void init_display () {
  /* LCD Module init */

	LCD_Initializtion();
  LCD_Clear(Black);
  GUI_Text(60,144, "RL-ARM",White,Red);
  GUI_Text(60,160, "HTTP example",White,Red);
 
}
/*--------------------------- dhcp_check ------------------------------------*/

static void dhcp_check () {
  /* Monitor DHCP IP address assignment. */

  if (tick == __FALSE || dhcp_tout == 0) {
    return;
  }
#ifdef RTX_KERNEL
  tick = __FALSE;
#endif
  if (mem_test (&MY_IP, 0, IP_ADRLEN) == __FALSE && !(dhcp_tout & 0x80000000)) {
    /* Success, DHCP has already got the IP address. */
    dhcp_tout = 0;
    sprintf((char *)lcd_text[0]," IP address:");
    sprintf((char *)lcd_text[1]," %d.%d.%d.%d", MY_IP[0], MY_IP[1],
                                                MY_IP[2], MY_IP[3]);
    LCDupdate = __TRUE;
    return;
  }
  if (--dhcp_tout == 0) {
    /* A timeout, disable DHCP and use static IP address. */
    dhcp_disable ();
    sprintf((char *)lcd_text[1]," DHCP failed    " );
    LCDupdate = __TRUE;
    dhcp_tout = 30 | 0x80000000;
    return;
  }
  if (dhcp_tout == 0x80000000) {
    dhcp_tout = 0;
    sprintf((char *)lcd_text[0]," IP address:");
    sprintf((char *)lcd_text[1]," %d.%d.%d.%d", MY_IP[0], MY_IP[1],
                                                MY_IP[2], MY_IP[3]);
    LCDupdate = __TRUE;
  }
}


/*--------------------------- blink_led -------------------------------------*/

#ifndef RTX_KERNEL

static void blink_led () {
  /* Blink the LED1 and LED2 on Mini-DK2 board */
  const U8 led_val[2] = {0x01,0x02};
  static U32 cnt;

  if (tick == __TRUE) {
    /* Every 100 ms */
    tick = __FALSE;
    if (LEDrun == __TRUE) {
      LED_out (led_val[cnt]);
      if (++cnt >= sizeof(led_val)) {
        cnt = 0;
      }
    }
    if (LCDupdate == __TRUE) {
      upd_display ();
    }
  }
}

#else

__task void blink_led () {
  /* Blink the LED1 and LED2 on Mini-DK2 board */
  const U8 led_val[2] = {0x01, 0x02 };
  U32 cnt = 0;

  LEDrun = __TRUE;
  while(1) {
    /* Every 100 ms */
    if (LEDrun == __TRUE) {
      LED_out (led_val[cnt]);
      if (++cnt >= sizeof(led_val)) {
        cnt = 0;
      }
    }
    if (LCDupdate == __TRUE) {
      upd_display ();
    }
    os_dly_wait(10);
  }
}

#endif


/*---------------------------------------------------------------------------*/

#ifndef RTX_KERNEL

int main (void) {
  /* Main Thread of the TcpNet */

  init();
	printf("prueba2\n");

  LEDrun = __TRUE;
  dhcp_tout = DHCP_TOUT;
  while (1) {
    timer_poll ();
    main_TcpNet ();
    dhcp_check ();
    blink_led ();
  }
}

#else

__task void tcp_task (void) {
  /* Main Thread of the TcpNet. This task should have */
  /* the lowest priority because it is always READY. */
  dhcp_tout = DHCP_TOUT;
  while (1) {
    main_TcpNet();
    dhcp_check ();
    os_tsk_pass();
  }
}


int main (void) {
  /* Start with 'init' task. */
  os_sys_init(init);
  while(1);
}

#endif


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
