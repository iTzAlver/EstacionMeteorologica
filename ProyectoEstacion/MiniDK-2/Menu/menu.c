
/* Includes ------------------------------------------------------------------*/
#include "GLCD.h"
#include "TouchPanel.h"
#include <string.h>
#include "leds.h"

/* Definición de los estados */
#define SCREEN_WELCOME      0
#define SCREEN_WELCOME_WAIT 1
#define SCREEN_MAIN         2
#define SCREEN_MAIN_WAIT    3
#define SCREEN_TOGGLE       4
#define SCREEN_TOGGLE_WAIT  5

/* Variable que almacena el estado */
uint8_t screenState;   

/* Estructura que define una zona de la pantalla */
struct t_screenZone
{
   uint16_t x;         
	uint16_t y;
	uint16_t size_x;
	uint16_t size_y;
	uint8_t  pressed;
};

/* Definicion de las diferentes zonas de la pantalla */
struct t_screenZone zone_0 = { 20,  20, 200, 110, 0}; /* Botón "Enciende LEDs"   */
struct t_screenZone zone_1 = { 20,  20, 200,  50, 0}; /* Botón "Apaga LEDs"      */
struct t_screenZone zone_2 = { 20,  80, 200,  50, 0}; /* Botón "Conmuta LEDs"    */
struct t_screenZone zone_3 = { 20, 140, 200,  50, 0}; /* Botón "Volver"          */
struct t_screenZone zone_4 = { 40, 200,  60,  60, 0}; /* Botón  Led 1            */
struct t_screenZone zone_5 = {140, 200,  60,  60, 0}; /* Botón  Led 2            */

/* Flag que indica si se detecta una pulsación válida */
uint8_t pressedTouchPanel = 0;

/* Variables que reflejan el estado de los LEDs */
uint8_t led_1 = 0;
uint8_t led_2 = 0;

/*******************************************************************************
* Function Name  : squareButton
* Description    : Dibuja un cuadrado en las coordenadas especificadas colocando 
*                  un texto en el centro del recuadro
* Input          : zone: zone struct
*                  text: texto a representar en el cuadro
*                  textColor: color del texto
*                  lineColor: color de la línea
* Output         : None
* Return         : None
* Attention		  : None
*******************************************************************************/
void squareButton(struct t_screenZone* zone, char * text, uint16_t textColor, uint16_t lineColor)
{
   LCD_DrawLine( zone->x, zone->y, zone->x + zone->size_x, zone->y, lineColor);
   LCD_DrawLine( zone->x, zone->y, zone->x, zone->y + zone->size_y, lineColor);
   LCD_DrawLine( zone->x, zone->y + zone->size_y, zone->x + zone->size_x, zone->y + zone->size_y, lineColor);
   LCD_DrawLine( zone->x + zone->size_x, zone->y, zone->x + zone->size_x, zone->y + zone->size_y, lineColor);
	GUI_Text(zone->x + zone->size_x/2 - (strlen(text)/2)*8, zone->y + zone->size_y/2 - 8,
            (uint8_t*) text, textColor, Black);	
}


/*******************************************************************************
* Function Name  : screenWelcome
* Description    : Visualiza la pantalla de bienveida
* Input          : None
* Output         : None
* Return         : None
* Attention		  : None
*******************************************************************************/
void screenWelcome(void)
{
		squareButton(&zone_0, "Ejemplo de los LEDS", White, Red);
}

/*******************************************************************************
* Function Name  : screenMain
* Description    : Visualiza la pantalla principal
* Input          : None
* Output         : None
* Return         : None
* Attention		  : None
*******************************************************************************/
void screenMain(void)
{
   squareButton(&zone_1, "Enciende LEDs", White, Blue);
   squareButton(&zone_2, "Apaga LEDs", White, Blue);
   squareButton(&zone_3, "Conmuta LEDs", White, Blue);

  	squareButton(&zone_4, " ", White, Blue);
   squareButton(&zone_5, " ", White, Blue);
}

/*******************************************************************************
* Function Name  : screenToggle
* Description    : Visualiza la pantalla secundaria
* Input          : None
* Output         : None
* Return         : None
* Attention		  : None
*******************************************************************************/
void screenToggle()
{
   squareButton(&zone_0, "Pulsa en el LED", White, Blue);
	squareButton(&zone_3, "Volver", White, Blue);

  	squareButton(&zone_4, " ", White, Blue);
	squareButton(&zone_5, " ", White, Blue);
}

/*******************************************************************************
* Function Name  : checkTouchPanel
* Description    : Lee el TouchPanel y almacena las coordenadas si detecta pulsación
* Input          : None
* Output         : Modifica pressedTouchPanel
*                    0 - si no se detecta pulsación
*                    1 - si se detecta pulsación
*                        En este caso se actualizan las coordinadas en la estructura display
* Return         : None
* Attention		  : None
*******************************************************************************/
void checkTouchPanel(void)
{
	Coordinate* coord;
	
	coord = Read_Ads7846();
	
	if (coord > 0) {
	  getDisplayPoint(&display, coord, &matrix );
     pressedTouchPanel = 1;
   }   
   else
     pressedTouchPanel = 0;
}

/*******************************************************************************
* Function Name  : zonePressed
* Description    : Detecta si se ha producido una pulsación en una zona contreta
* Input          : zone: Estructura con la información de la zona
* Output         : Modifica zone->pressed
*                    0 - si no se detecta pulsación en la zona
*                    1 - si se detecta pulsación en la zona
* Return         : 0 - si no se detecta pulsación en la zona
*                  1 - si se detecta pulsación en la zona
* Attention		  : None
*******************************************************************************/
int8_t zonePressed(struct t_screenZone* zone)
{
	if (pressedTouchPanel == 1) {

		if ((display.x > zone->x) && (display.x < zone->x + zone->size_x) && 
			  (display.y > zone->y) && (display.y < zone->y + zone->size_y))
      {
         zone->pressed = 1;
		   return 1;
      }   
	}
   
	zone->pressed = 0;
	return 0;
}

/*******************************************************************************
* Function Name  : zoneNewPressed
* Description    : Detecta si se ha producido el flanco de una nueva pulsación en 
*                  una zona contreta
* Input          : zone: Estructura con la información de la zona
* Output         : Modifica zone->pressed
*                    0 - si no se detecta pulsación en la zona
*                    1 - si se detecta pulsación en la zona
* Return         : 0 - si no se detecta nueva pulsación en la zona
*                  1 - si se detecta una nueva pulsación en la zona
* Attention		  : None
*******************************************************************************/
int8_t zoneNewPressed(struct t_screenZone* zone)
{
	if (pressedTouchPanel == 1) {

		if ((display.x > zone->x) && (display.x < zone->x + zone->size_x) && 
			  (display.y > zone->y) && (display.y < zone->y + zone->size_y))
      {
         if (zone->pressed == 0)
         {   
            zone->pressed = 1;
            return 1;
         }
		   return 0;
      }
	}

   zone->pressed = 0;
	return 0;
}


/*******************************************************************************
* Function Name  : fillRect
* Description    : Rellena de un color determinado el interior de una zona 
* Input          : zone: Estructura con la información de la zona
*                  color: color de relleno
* Output         : None
* Return         : None
* Attention		  : None
*******************************************************************************/
void fillRect(struct t_screenZone* zone, uint16_t color)
{
	uint16_t i;
	
	for (i = zone->y+1; i < zone->y + zone->size_y-1; i ++) {
		LCD_DrawLine(zone->x + 1, i, zone->x + zone->size_x -1, i, color);
	}
}


/*******************************************************************************
* Function Name  : updateLEDs
* Description    : Actualiza en función de las variables led1 y led2 la visualización 
*                  de los LEDs de la Mini-DK2 y el color de los cuadros en pantalla
*                  relacionados. 
* Input          : zone: Estructura con la información de la zona
*                  color: color de relleno
* Output         : None
* Return         : None
* Attention		  : None
*******************************************************************************/
void updateLEDs(void)
{
	if (led_1 ==1) {
		fillRect(&zone_4,Red);
		LED1_ON;
  }
	else {
		fillRect(&zone_4,Blue);
		LED1_OFF;
  }
	if (led_2 ==1) {
		fillRect(&zone_5,Red);
		LED2_ON;
  }
	else {
		fillRect(&zone_5,Blue);
		LED2_OFF;
  }
}

/*******************************************************************************
* Function Name  : initScreenStateMachine
* Description    : Inicializa la máquina de estados al primer estado. 
* Input          : None
* Output         : None
* Return         : None
* Attention		  : None
*******************************************************************************/
void 	initScreenStateMachine(void)
{
	screenState = SCREEN_WELCOME;
}


/*******************************************************************************
* Function Name  : screenStateMachine
* Description    : Máquina de estados de la aplicación. 
* Input          : None
* Output         : None
* Return         : None
* Attention		  : None
*******************************************************************************/
void screenStateMachine(void)
{ 
	/* Lee posible pulsación del TouchPanel  */
   checkTouchPanel();

	switch (screenState)
	{
      case SCREEN_WELCOME:
         LCD_Clear(Black);
			screenWelcome();
			screenState = SCREEN_WELCOME_WAIT;
			break;
			 
		case SCREEN_WELCOME_WAIT:
         if (zonePressed(&zone_0)) {
			   screenState = SCREEN_MAIN;
			}					
			break;
			 
		case SCREEN_MAIN:
			LCD_Clear(Black);
			screenMain();
			updateLEDs();
			screenState = SCREEN_MAIN_WAIT;
			break;
			 
		case SCREEN_MAIN_WAIT:
			if (zonePressed(&zone_1)) {
			   led_1 = 1;
				led_2 = 1;
            updateLEDs();					
			}					
			if (zonePressed(&zone_2)) {
				led_1 = 0;
				led_2 = 0;
            updateLEDs();					
			}					

			if (zoneNewPressed(&zone_3)) {
				screenState = SCREEN_TOGGLE;
			}
		   break;
					
		case SCREEN_TOGGLE:
			LCD_Clear(Black);
			screenToggle();
			updateLEDs();
			screenState = SCREEN_TOGGLE_WAIT;
			break;
			 
		case SCREEN_TOGGLE_WAIT:
			if (zoneNewPressed(&zone_3)) {
			   screenState = SCREEN_MAIN;
			}
			if (zoneNewPressed(&zone_4)) {
				led_1 ^= 0x01;
	         updateLEDs();					
			}
			if (zoneNewPressed(&zone_5)) {
				led_2 ^= 0x01;
	         updateLEDs();					
			}
			break;

		default:
			break;
	}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
