/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : red.h
**     Project     : FRDM22-M1- Backup - 22.03 - 09.34
**     Processor   : MK22FN512VLH12
**     Component   : LED
**     Version     : Component 01.072, Driver 01.00, CPU db: 3.00.000
**     Repository  : My Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-29, 09:02, # CodeGen: 0
**     Abstract    :
**          This component implements a universal driver for a single LED.
**     Settings    :
**          Component name                                 : red
**          SDK                                            : KSDK1
**          Turned On with initialization                  : no
**          HW Interface                                   : 
**            Anode on port side, HIGH is ON               : no
**            On/Off                                       : Enabled
**              Pin                                        : LEDpin
**            PWM                                          : Disabled
**          Shell                                          : Disabled
**     Contents    :
**         On         - void red_On(void);
**         Off        - void red_Off(void);
**         Neg        - void red_Neg(void);
**         Get        - uint8_t red_Get(void);
**         Put        - void red_Put(uint8_t val);
**         SetRatio16 - void red_SetRatio16(uint16_t ratio);
**         Deinit     - void red_Deinit(void);
**         Init       - void red_Init(void);
**
**     License   : Open Source (LGPL)
**     Copyright : Erich Styger, 2013-2016, all rights reserved.
**     Web       : www.mcuoneclipse.com
**     This an open source software implementing a driver using Processor Expert.
**     This is a free software and is opened for education, research and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file red.h
** @version 01.00
** @brief
**          This component implements a universal driver for a single LED.
*/         
/*!
**  @addtogroup red_module red module documentation
**  @{
*/         

#ifndef __red_H
#define __red_H

/* MODULE red. */
#ifndef __HIWARE__ /* Hiware compiler (S08, S12) only supports C89 */
  #include <stdint.h>
#endif
/* Include inherited beans */
#include "KSDK1.h"
#include "LEDpin1.h"

#if KSDK1_SDK_VERSION_USED == KSDK1_SDK_VERSION_NONE
  /* Include shared modules, which are used for whole project */
  #include "PE_Types.h"
  #include "PE_Error.h"
  #include "PE_Const.h"
  #include "IO_Map.h"
  #include "Cpu.h"
#endif


#define red_ClrVal()    LEDpin1_ClrVal() /* put the pin on low level */
#define red_SetVal()    LEDpin1_SetVal() /* put the pin on high level */
#define red_SetInput()  LEDpin1_SetInput() /* use the pin as input pin */
#define red_SetOutput() LEDpin1_SetOutput() /* use the pin as output pin */

#define red_PARSE_COMMAND_ENABLED  0 /* set to 1 if method ParseCommand() is present, 0 otherwise */


#define red_On() LEDpin1_ClrVal()
/*
** ===================================================================
**     Method      :  red_On (component LED)
**     Description :
**         This turns the LED on.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define red_Off() LEDpin1_SetVal()
/*
** ===================================================================
**     Method      :  red_Off (component LED)
**     Description :
**         This turns the LED off.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define red_Neg() LEDpin1_NegVal()
/*
** ===================================================================
**     Method      :  red_Neg (component LED)
**     Description :
**         This negates/toggles the LED
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define red_Get() (!(LEDpin1_GetVal()))
/*
** ===================================================================
**     Method      :  red_Get (component LED)
**     Description :
**         This returns logical 1 in case the LED is on, 0 otherwise.
**     Parameters  : None
**     Returns     :
**         ---             - Status of the LED (on or off)
** ===================================================================
*/

void red_Init(void);
/*
** ===================================================================
**     Method      :  red_Init (component LED)
**     Description :
**         Performs the LED driver initialization.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define red_Put(val)  ((val) ? red_On() : red_Off())
/*
** ===================================================================
**     Method      :  red_Put (component LED)
**     Description :
**         Turns the LED on or off.
**     Parameters  :
**         NAME            - DESCRIPTION
**         val             - value to define if the LED has to be on or
**                           off.
**     Returns     : Nothing
** ===================================================================
*/

void red_Deinit(void);
/*
** ===================================================================
**     Method      :  red_Deinit (component LED)
**     Description :
**         Deinitializes the driver
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void red_SetRatio16(uint16_t ratio);
/*
** ===================================================================
**     Method      :  red_SetRatio16 (component LED)
**     Description :
**         Method to specify the duty cycle. If using a PWM pin, this
**         means the duty cycle is set. For On/off pins, values smaller
**         0x7FFF means off, while values greater means on.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ratio           - Ratio value, where 0 means 'off' and
**                           0xffff means 'on'
**     Returns     : Nothing
** ===================================================================
*/

/* END red. */

#endif
/* ifndef __red_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/