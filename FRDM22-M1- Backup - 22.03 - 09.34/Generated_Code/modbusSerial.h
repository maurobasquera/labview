/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : modbusSerial.h
**     Project     : FRDM22-M1- Backup - 22.03 - 09.34
**     Processor   : MK22FN512VLH12
**     Component   : AsynchroSerial
**     Version     : Component 02.611, Driver 01.01, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-29, 09:02, # CodeGen: 0
**     Abstract    :
**         This component "AsynchroSerial" implements an asynchronous serial
**         communication. The component supports different settings of
**         parity, word width, stop-bit and communication speed,
**         user can select interrupt or polling handler.
**         Communication speed can be changed also in runtime.
**         The component requires one on-chip asynchronous serial channel.
**     Settings    :
**          Component name                                 : modbusSerial
**          Channel                                        : UART1
**          Interrupt service/event                        : Enabled
**            Interrupt RxD                                : INT_UART1_RX_TX
**            Interrupt RxD priority                       : medium priority
**            Interrupt TxD                                : INT_UART1_RX_TX
**            Interrupt TxD priority                       : medium priority
**            Interrupt Error                              : INT_UART1_ERR
**            Interrupt Error priority                     : medium priority
**            Input buffer size                            : 128
**            Output buffer size                           : 128
**            Handshake                                    : 
**              CTS                                        : Disabled
**              RTS                                        : Disabled
**          Settings                                       : 
**            Parity                                       : none
**            Width                                        : 8 bits
**            Stop bit                                     : 1
**            Receiver                                     : Enabled
**              RxD                                        : ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/I2C1_SCL/SPI1_SIN
**            Transmitter                                  : Enabled
**              TxD                                        : ADC1_SE4a/PTE0/CLKOUT32K/SPI1_PCS1/UART1_TX/I2C1_SDA/RTC_CLKOUT
**            Baud rate                                    : 9600 baud
**            Break signal                                 : Disabled
**            Wakeup condition                             : Idle line wakeup
**            Transmitter output                           : Not inverted
**            Receiver input                               : Not inverted
**            Stop in wait mode                            : no
**            Idle line mode                               : starts after start bit
**            Break generation length                      : Short
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Events enabled in init.                      : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : This component enabled
**            Low speed mode                               : This component disabled
**            Slow speed mode                              : This component disabled
**          Referenced components                          : 
**            Serial_LDD                                   : Serial_LDD
**     Contents    :
**         RecvChar        - byte modbusSerial_RecvChar(modbusSerial_TComData *Chr);
**         SendChar        - byte modbusSerial_SendChar(modbusSerial_TComData Chr);
**         RecvBlock       - byte modbusSerial_RecvBlock(modbusSerial_TComData *Ptr, word Size, word *Rcv);
**         SendBlock       - byte modbusSerial_SendBlock(modbusSerial_TComData *Ptr, word Size, word *Snd);
**         ClearRxBuf      - byte modbusSerial_ClearRxBuf(void);
**         ClearTxBuf      - byte modbusSerial_ClearTxBuf(void);
**         CharsInRxBuf    - byte modbusSerial_CharsInRxBuf(word *Chr);
**         GetCharsInRxBuf - word modbusSerial_GetCharsInRxBuf(void);
**         GetCharsInTxBuf - word modbusSerial_GetCharsInTxBuf(void);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file modbusSerial.h
** @version 01.01
** @brief
**         This component "AsynchroSerial" implements an asynchronous serial
**         communication. The component supports different settings of
**         parity, word width, stop-bit and communication speed,
**         user can select interrupt or polling handler.
**         Communication speed can be changed also in runtime.
**         The component requires one on-chip asynchronous serial channel.
*/         
/*!
**  @addtogroup modbusSerial_module modbusSerial module documentation
**  @{
*/         

#ifndef __modbusSerial
#define __modbusSerial

/* MODULE modbusSerial. */

/* Include inherited components */
#include "ASerialLdd1.h"
#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 



#ifndef __BWUserType_modbusSerial_TError
#define __BWUserType_modbusSerial_TError
  typedef union {
  byte err;
  struct {
    bool OverRun  : 1;                 /* Overrun error flag */
    bool Framing  : 1;                 /* Framing error flag */
    bool Parity   : 1;                 /* Parity error flag */
    bool RxBufOvf : 1;                 /* Rx buffer full error flag */
    bool Noise    : 1;                 /* Noise error flag */
    bool Break    : 1;                 /* Break detect */
    bool LINSync  : 1;                 /* LIN synchronization error */
    bool BitError  : 1;                /* Bit error flag - mismatch to the expected value happened. */
  } errName;
} modbusSerial_TError;                 /* Error flags. For languages which don't support bit access is byte access only to error flags possible. */
#endif

#ifndef __BWUserType_modbusSerial_TComData
#define __BWUserType_modbusSerial_TComData
  typedef byte modbusSerial_TComData;  /* User type for communication. Size of this type depends on the communication data witdh */
#endif

#define modbusSerial_INP_BUF_SIZE  0x80U /* Length of the RX buffer */

#define modbusSerial_OUT_BUF_SIZE  0x80U /* Length of the TX buffer */

/*
** ===================================================================
**     Method      :  modbusSerial_RecvChar (component AsynchroSerial)
**     Description :
**         If any data is received, this method returns one character,
**         otherwise it returns an error code (it does not wait for
**         data). This method is enabled only if the receiver property
**         is enabled.
**         [Note:] Because the preferred method to handle error and
**         break exception in the interrupt mode is to use events
**         <OnError> and <OnBreak> the return value ERR_RXEMPTY has
**         higher priority than other error codes. As a consequence the
**         information about an exception in interrupt mode is returned
**         only if there is a valid character ready to be read.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Pointer to a received character
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_RXEMPTY - No data in receiver
**                           ERR_BREAK - Break character is detected
**                           (only when the <Interrupt service> property
**                           is disabled and the <Break signal> property
**                           is enabled)
**                           ERR_COMMON - common error occurred (the
**                           <GetError> method can be used for error
**                           specification)
** ===================================================================
*/
byte modbusSerial_RecvChar(modbusSerial_TComData *Chr);

/*
** ===================================================================
**     Method      :  modbusSerial_SendChar (component AsynchroSerial)
**     Description :
**         Sends one character to the channel. If the component is
**         temporarily disabled (Disable method) SendChar method only
**         stores data into an output buffer. In case of a zero output
**         buffer size, only one character can be stored. Enabling the
**         component (Enable method) starts the transmission of the
**         stored data. This method is available only if the
**         transmitter property is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_TXFULL - Transmitter is full
** ===================================================================
*/
byte modbusSerial_SendChar(modbusSerial_TComData Chr);

/*
** ===================================================================
**     Method      :  modbusSerial_RecvBlock (component AsynchroSerial)
**     Description :
**         If any data is received, this method returns the block of
**         the data and its length (and incidental error), otherwise it
**         returns an error code (it does not wait for data).
**         This method is available only if non-zero length of the
**         input buffer is defined and the receiver property is enabled.
**         If less than requested number of characters is received only
**         the available data is copied from the receive buffer to the
**         user specified destination. The value ERR_EXEMPTY is
**         returned and the value of variable pointed by the Rcv
**         parameter is set to the number of received characters.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - Pointer to the block of received data
**         Size            - Size of the block
**       * Rcv             - Pointer to real number of the received data
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_RXEMPTY - The receive buffer didn't
**                           contain the requested number of data. Only
**                           available data has been returned.
**                           ERR_COMMON - common error occurred (the
**                           GetError method can be used for error
**                           specification)
** ===================================================================
*/
byte modbusSerial_RecvBlock(modbusSerial_TComData *Ptr,word Size,word *Rcv);

/*
** ===================================================================
**     Method      :  modbusSerial_SendBlock (component AsynchroSerial)
**     Description :
**         Sends a block of characters to the channel.
**         This method is available only if non-zero length of the
**         output buffer is defined and the transmitter property is
**         enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - Pointer to the block of data to send
**         Size            - Size of the block
**       * Snd             - Pointer to number of data that are sent
**                           (moved to buffer)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_TXFULL - It was not possible to send
**                           requested number of bytes
** ===================================================================
*/
byte modbusSerial_SendBlock(modbusSerial_TComData *Ptr,word Size,word *Snd);

/*
** ===================================================================
**     Method      :  modbusSerial_ClearRxBuf (component AsynchroSerial)
**     Description :
**         Clears the receive buffer.
**         This method is available only if non-zero length of the
**         input buffer is defined and the receiver property is enabled.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte modbusSerial_ClearRxBuf(void);

/*
** ===================================================================
**     Method      :  modbusSerial_ClearTxBuf (component AsynchroSerial)
**     Description :
**         Clears the transmit buffer.
**         This method is available only if non-zero length of the
**         output buffer is defined and the receiver property is
**         enabled.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte modbusSerial_ClearTxBuf(void);

/*
** ===================================================================
**     Method      :  modbusSerial_CharsInRxBuf (component AsynchroSerial)
**     Description :
**         Returns the number of characters in the input buffer. This
**         method is available only if the receiver property is enabled.
**         [deprecated method]
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Pointer to the number of characters in the
**                           input buffer
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte  modbusSerial_CharsInRxBuf(word *Chr);

/*
** ===================================================================
**     Method      :  modbusSerial_GetCharsInRxBuf (component AsynchroSerial)
**     Description :
**         Returns the number of characters in the input buffer. This
**         method is available only if the receiver property is enabled.
**     Parameters  : None
**     Returns     :
**         ---             - The number of characters in the input
**                           buffer.
** ===================================================================
*/
word modbusSerial_GetCharsInRxBuf(void);

/*
** ===================================================================
**     Method      :  modbusSerial_GetCharsInTxBuf (component AsynchroSerial)
**     Description :
**         Returns the number of characters in the output buffer. This
**         method is available only if the transmitter property is
**         enabled.
**     Parameters  : None
**     Returns     :
**         ---             - The number of characters in the output
**                           buffer.
** ===================================================================
*/
word modbusSerial_GetCharsInTxBuf(void);

/*
** ===================================================================
**     Method      :  modbusSerial_Init (component AsynchroSerial)
**
**     Description :
**         Initializes the associated peripheral(s) and the bean internal 
**         variables. The method is called automatically as a part of the 
**         application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void modbusSerial_Init(void);

/*
** ===================================================================
**     Method      :  modbusSerial_ASerialLdd1_OnBlockReceived (component AsynchroSerial)
**
**     Description :
**         This event is called when the requested number of data is 
**         moved to the input buffer.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ASerialLdd1_OnBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  modbusSerial_ASerialLdd1_OnBlockSent (component AsynchroSerial)
**
**     Description :
**         This event is called after the last character from the output 
**         buffer is moved to the transmitter.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ASerialLdd1_OnBlockSent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  modbusSerial_ASerialLdd1_OnError (component AsynchroSerial)
**
**     Description :
**         This event is called when a channel error (not the error 
**         returned by a given method) occurs.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ASerialLdd1_OnError(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  modbusSerial_ASerialLdd1_OnBreak (component AsynchroSerial)
**
**     Description :
**         This event is called when a break occurs on the input channel.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ASerialLdd1_OnBreak(LDD_TUserData *UserDataPtr);


/* END modbusSerial. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif /* ifndef __modbusSerial */
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
