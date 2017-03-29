/*
 * modbusMaster.c
 *
 *  Created on: 20/03/2017
 *      Author: mauro
 */
#include "ASerialLdd1.h"
#include "sleepModbus.h"
#include "indicationModbus.h"
#include "BitIoLdd1.h"
#include "enableModbus.h"
#include "BitIoLdd2.h"
#include "pooling_delay.h"
#include "timeout_delay.h"
#include "modbusSerial.h"
#include "delay.h"
#include "modbusMaster.h"
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "red.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "MCUC1.h"
#include "green.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "blue.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "delay.h"
//#include "adc.h"
#include "main_header.h"
#include "math.h"

// modbus specific exceptions
#define ILLEGAL_FUNCTION 1
#define ILLEGAL_DATA_ADDRESS 2
#define ILLEGAL_DATA_VALUE 3

unsigned char transmission_ready_Flag;
unsigned char messageOkFlag, messageErrFlag;
unsigned char TxEnablePin;
unsigned char lixoOverflow;

#define BUFFER_SIZE 128

unsigned int timeout = 3000;
unsigned int polling = 200;
unsigned int retry_count = 10;
unsigned int baud = 9600;

// frame[] is used to recieve and transmit packages.
// The maximum number of bytes in a modbus packet is 256 bytes
// This is limited to the serial buffer of 128 bytes

unsigned char frame[BUFFER_SIZE];
unsigned char frame_receive[BUFFER_SIZE];
unsigned int T1_5; // inter character time out in microseconds
unsigned int T3_5; // frame delay in microseconds
unsigned int previousTimeout, previousPolling;
unsigned int total_no_of_packets;

unsigned int polling_passed;
unsigned int timeout_passed;

static Packet packet; // current packet

void checkResponse();
void verifyData();
void check_F3_data(unsigned char buffer);
void check_F16_data();
void getData();
unsigned int calculateCRC(unsigned char bufferSize);
void sendPacket(unsigned char bufferSize);
void transmitData(unsigned char ID, unsigned char FC, unsigned int AD, unsigned int REG_NUM);

void modbus_configure(){

	enableModbus_PutVal(FALSE);

	if (baud > 19200)
	{
		T1_5 = 750;
		T3_5 = 1750;
	}
	else
	{
		T1_5 = 15000000/baud; // 1T * 1.5 = T1.5
		T3_5 = 35000000/baud; // 1T * 3.5 = T3.5
	}

	// initialize
  transmission_ready_Flag = 1;
  messageOkFlag = 0;
  messageErrFlag = 0;
  previousTimeout = 0;
  previousPolling = 0;

  modbusSerial_ClearTxBuf();
  modbusSerial_ClearRxBuf();

}

//unsigned int modbus_update(Packet* pack)
//{
//
//	unsigned int connection_status = total_no_of_packets;
//
//  if (transmission_ready_Flag)
//	{
//		static unsigned int packet_index;
//		unsigned int failed_connections = 0;
//		unsigned char current_connection;
//
//		while (!current_connection)
//		{
//
//			if (packet_index == total_no_of_packets) // wrap around to the beginning
//				packet_index = 0;
//
//			// proceed to the next packet
//			packet = &packets[packet_index];
//
//			// get the current connection status
//			current_connection = pack->connection;
//
//			if (!current_connection)
//			{
//				connection_status = packet_index;
//
//				// If all the connection attributes are false return
//				// immediately to the main sketch
//				if (++failed_connections == total_no_of_packets)
//					return connection_status;
//			}
//			packet_index++;
//		}
//
//		constructPacket();
//	}
//
//	checkResponse();
//
//  check_packet_status();
//
//	return connection_status;
//}

void check_packet_status()
{

  pooling_delay_GetTimeMS(&polling_passed);
  timeout_delay_GetTimeMS(&timeout_passed);

  unsigned char pollingFinished =  polling_passed > polling;

  if (messageOkFlag && pollingFinished) // if a valid message was received and the polling delay has expired clear the flag
  {
    messageOkFlag = 0;
    pack.successful_requests++; // transaction sent successfully
    pack.retries = 0; // if a request was successful reset the retry counter
    transmission_ready_Flag = 1;
  }

  // if an error message was recieved and the polling delay has expired clear the flag
  if (messageErrFlag && pollingFinished)
  {
    messageErrFlag = 0; // clear error flag
    pack.retries++;
    transmission_ready_Flag = 1;
  }

  // if the timeout delay has past clear the slot number for next request
  if (!transmission_ready_Flag && (timeout_passed > timeout))
  {
    pack.timeout++;
    pack.retries++;
    transmission_ready_Flag = 1;
  }

  // if the number of retries have reached the max number of retries
  // allowable, stop requesting the specific packet
  if (pack.retries == retry_count)
	{
    pack.connection = 0;
	pack.retries = 0;
	}

	if (transmission_ready_Flag)
	{
		// update the total_errors atribute of the
		// packet before requesting a new one
		pack.total_errors = pack.timeout +
													 pack.incorrect_id_returned +
													 pack.incorrect_function_returned +
													 pack.incorrect_bytes_returned +
													 pack.checksum_failed +
													 pack.buffer_errors +
													 pack.illegal_function +
													 pack.illegal_data_address +
													 pack.illegal_data_value;
	}
}

void sendPacket(unsigned char bufferSize)
{
	modbusSerial_ClearTxBuf();
	enableModbus_PutVal(TRUE);
	unsigned char i = 0;

	for (i = 0; i < bufferSize; i++) modbusSerial_SendChar(frame[i]);

	sleepModbus_Waitus(T3_5); //end of transmission

	enableModbus_PutVal(FALSE);
}

void transmitData(unsigned char ID, unsigned char FC, unsigned int AD, unsigned int REG_NUM)
{
	polling_passed = 0;
	timeout_passed = 0;

	extern unsigned int value1;
	extern unsigned int value2;
	extern unsigned int value3;

	pack.id = ID;
	pack.function = FC;
	pack.address = AD;
	pack.no_of_registers = REG_NUM;

	unsigned int regs[3];
	regs[0] = value1;
	regs[1] = value2;
	regs[2] = value3;

	pack.register_array = regs;

	frame[0] = pack.id;
	frame[1] = pack.function;
	frame[2] = pack.address >> 8; // address Hi
	frame[3] = pack.address & 0xFF; // address Lo
	frame[4] = pack.no_of_registers >> 8; // no_of_registers Hi
	frame[5] = pack.no_of_registers & 0xFF; // no_of_registers Lo

  unsigned int crc16;

  // construct the frame according to the modbus function
  if (frame[1] == PRESET_MULTIPLE_REGISTERS)
  {
    unsigned char no_of_bytes = pack.no_of_registers * 2;
    unsigned char frameSize = 9 + no_of_bytes; // first 7 bytes of the array + 2 bytes CRC+ noOfBytes
    frame[6] = no_of_bytes; // number of bytes
    unsigned char index = 7; // user data starts at index 7
    unsigned int temp;
	unsigned char no_of_registers = pack.no_of_registers;

    for (unsigned char i = 0; i < no_of_registers; i++)
    {
      temp = pack.register_array[i]; // get the data
      frame[index] = temp >> 8;
      index++;
      frame[index] = temp & 0xFF;
      index++;
    }
    crc16 = calculateCRC(frameSize - 2);
    frame[frameSize - 2] = crc16 >> 8; // split crc into 2 bytes
    frame[frameSize - 1] = crc16 & 0xFF;
    sendPacket(frameSize);

  }
	else // READ_HOLDING_REGISTERS is assumed
	{
	crc16 = calculateCRC(6); // the first 6 bytes of the frame is used in the CRC calculation
    frame[6] = crc16 >> 8; // crc Lo
    frame[7] = crc16 & 0xFF; // crc Hi
    sendPacket(8); // a request with function 3, 4 & 6 is always 8 bytes in size
	}

  if (pack.id == 0) // check broadcast id
  {
			messageOkFlag = 1; // message successful, there will be no response on a broadcast
		    pooling_delay_Reset();
  }

}

unsigned int calculateCRC(unsigned char bufferSize)
{
  unsigned int temp, temp2, flag;
  temp = 0xFFFF;
  for (unsigned char i = 0; i < bufferSize; i++)
  {
    temp = temp ^ frame[i];
    for (unsigned char j = 1; j <= 8; j++)
    {
      flag = temp & 0x0001;
      temp >>= 1;
      if (flag)
        temp ^= 0xA001;
    }
  }
  // Reverse byte order.
  temp2 = temp >> 8;

  temp = (temp << 8) | temp2;
  temp &= 0xFFFF;
  return temp; // the returned value is already stopped - crcLo byte is first & crcHi byte is last
}

unsigned int calculateCRC_received(unsigned char bufferSize)
{
  unsigned int temp, temp2, flag;
  temp = 0xFFFF;
  for (unsigned char i = 0; i < bufferSize; i++)
  {
    temp = temp ^ frame_receive[i];
    for (unsigned char j = 1; j <= 8; j++)
    {
      flag = temp & 0x0001;
      temp >>= 1;
      if (flag)
        temp ^= 0xA001;
    }
  }
  // Reverse byte order.
  temp2 = temp >> 8;

  temp = (temp << 8) | temp2;
  temp &= 0xFFFF;
  return temp; // the returned value is already stopped - crcLo byte is first & crcHi byte is last
}

void getData(){

	unsigned char buffer = 0;
	unsigned char overflow = 0;
	unsigned int timeout_count = 0;
	unsigned int exit_receive_loop = 0;
	unsigned int timeout_flag = 0;

    pack.buffer = buffer;

	indicationModbus_PutVal(TRUE);
    pooling_delay_Reset();

	while((timeout_count<timeout) && !exit_receive_loop){
	if (modbusSerial_GetCharsInRxBuf()){

		while (modbusSerial_GetCharsInRxBuf()){

			if (overflow) modbusSerial_RecvChar(&lixoOverflow);
			else{
					if (buffer == BUFFER_SIZE) {overflow = 1;}

				modbusSerial_RecvChar(&frame_receive[buffer]);
				buffer++;
			    pack.buffer = buffer;
			    }
					sleepModbus_Waitus(T1_5); // inter character time out
											  }
						 if ((buffer > 0 && buffer < 5) || overflow)
							  {
								buffer = 0;
								pack.buffer_errors++;
								messageErrFlag = 1; // set an error
								pooling_delay_Reset();
							  }

			modbusSerial_ClearRxBuf();
			exit_receive_loop = 1;
			timeout_flag = 0;

	 	}
	pooling_delay_GetTimeMS(&timeout_count);
	}

	if (timeout_count>=timeout){
	timeout_flag = 1;
	}

}

void verifyData(){
//	if (!messageOkFlag && !messageErrFlag) // check for response
//	  {
	    if (pack.buffer > 0) // if there's something in the buffer continue
	    {
	      if (frame_receive[0] == pack.id) // check id returned
	      {
			// to indicate an exception response a slave will 'OR'
	        // the requested function with 0x80
					if ((frame_receive[1] & 0x80) == 0x80) // extract 0x80
					{
						// the third byte in the exception response packet is the actual exception
						switch (frame_receive[2])
						{
							case ILLEGAL_FUNCTION: pack.illegal_function++; break;
							case ILLEGAL_DATA_ADDRESS: pack.illegal_data_address++; break;
							case ILLEGAL_DATA_VALUE: pack.illegal_data_value++; break;
							default: pack.misc_exceptions++;
						}
						messageErrFlag = 1; // set an error
						pooling_delay_Reset(); // start the polling delay
					}
					else // the response is valid
					{
						if (frame_receive[1] == pack.function) // check function number returned
						{
							// receive the frame according to the modbus function
							if (pack.function == PRESET_MULTIPLE_REGISTERS)
								{
								  unsigned int recieved_address = ((frame_receive[2] << 8) | frame_receive[3]);
								  unsigned int recieved_registers = ((frame_receive[4] << 8) | frame_receive[5]);
								  unsigned int recieved_crc = ((frame_receive[6] << 8) | frame_receive[7]); // combine the crc Low & High bytes
								  unsigned int calculated_crc = calculateCRC(6); // only the first 6 bytes are used for crc calculation

								  // check the whole packet
								  if (recieved_address == pack.address &&
								      recieved_registers == pack.no_of_registers &&
								      recieved_crc == calculated_crc)
								      messageOkFlag = 1; // message successful
								  else
								  {
								    pack.checksum_failed++;
								    messageErrFlag = 1;
								  }
								  // start the polling delay for messageOkFlag & messageErrFlag
								  pooling_delay_Reset();
								}

							else {
								  unsigned char no_of_registers = pack.no_of_registers;
								  unsigned char no_of_bytes = no_of_registers * 2;
								  if (frame_receive[2] == no_of_bytes) // check number of bytes returned
								  {
								    // combine the crc Low & High bytes
								    unsigned int recieved_crc = ((frame_receive[pack.buffer - 2] << 8) | frame_receive[pack.buffer - 1]);
								    unsigned int calculated_crc = calculateCRC_received(pack.buffer - 2);

								    if (calculated_crc == recieved_crc) // verify checksum
								    {
								      unsigned char index = 3;
											for (unsigned char i = 0; i < no_of_registers; i++)
								      {
								        // start at the 4th element in the recieveFrame and combine the Lo byte
												pack.register_array[i] = (frame_receive[index] << 8) | frame_receive[index + 1];
								        index += 2;
								      }
								      messageOkFlag = 1; // message successful
								    }
								    else // checksum failed
								    {
								      pack.checksum_failed++;
								      messageErrFlag = 1; // set an error
								    }

								    // start the polling delay for messageOkFlag & messageErrFlag
								    pooling_delay_Reset();
								  }
								  else // incorrect number of bytes returned
								  {
								    pack.incorrect_bytes_returned++;
								    messageErrFlag = 1; // set an error
								    pooling_delay_Reset();
								  }
								}
						}
						else // incorrect function number returned
						{
							pack.incorrect_function_returned++;
							messageErrFlag = 1; // set an error
							pooling_delay_Reset(); // start the polling delay
						}
					} // check exception response
				}
				else // incorrect id returned
				{
					pack.incorrect_id_returned++;
					messageErrFlag = 1; // set an error
					pooling_delay_Reset(); // start the polling delay
				}
			} // check buffer
} // check message booleans
//}

//void check_F3_data(unsigned char buffer)
//{
//  unsigned char no_of_registers = pack.no_of_registers;
//  unsigned char no_of_bytes = no_of_registers * 2;
//  if (frame_receive[2] == no_of_bytes) // check number of bytes returned
//  {
//    // combine the crc Low & High bytes
//    unsigned int recieved_crc = ((frame_receive[buffer - 2] << 8) | frame_receive[buffer - 1]);
//    unsigned int calculated_crc = calculateCRC(buffer - 2);
//
//    if (calculated_crc == recieved_crc) // verify checksum
//    {
//      unsigned char index = 3;
//			for (unsigned char i = 0; i < no_of_registers; i++)
//      {
//        // start at the 4th element in the recieveFrame and combine the Lo byte
//				pack.register_array[i] = (frame_receive[index] << 8) | frame_receive[index + 1];
//        index += 2;
//      }
//      messageOkFlag = 1; // message successful
//    }
//    else // checksum failed
//    {
//      pack.checksum_failed++;
//      messageErrFlag = 1; // set an error
//    }
//
//    // start the polling delay for messageOkFlag & messageErrFlag
//    pooling_delay_Reset();
//  }
//  else // incorrect number of bytes returned
//  {
//    pack.incorrect_bytes_returned++;
//    messageErrFlag = 1; // set an error
//    pooling_delay_Reset();
//  }
//}
//
//void check_F16_data()
//{
//  unsigned int recieved_address = ((frame_receive[2] << 8) | frame_receive[3]);
//  unsigned int recieved_registers = ((frame_receive[4] << 8) | frame_receive[5]);
//  unsigned int recieved_crc = ((frame_receive[6] << 8) | frame_receive[7]); // combine the crc Low & High bytes
//  unsigned int calculated_crc = calculateCRC(6); // only the first 6 bytes are used for crc calculation
//
//  // check the whole packet
//  if (recieved_address == pack.address &&
//      recieved_registers == pack.no_of_registers &&
//      recieved_crc == calculated_crc)
//      messageOkFlag = 1; // message successful
//  else
//  {
//    pack.checksum_failed++;
//    messageErrFlag = 1;
//  }
//  // start the polling delay for messageOkFlag & messageErrFlag
//  pooling_delay_Reset();
//}
//





