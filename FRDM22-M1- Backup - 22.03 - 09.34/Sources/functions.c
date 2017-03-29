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

void blink_blue(void){

	red_Off();
	green_Off();
	if (flag_500ms==1){blue_Neg();}

}

void init_led(void){

	red_On();
	delay_Waitms(1000);
	green_On();
	delay_Waitms(1000);

}

void float2int (num_decimal *c) {

	if (c->number < 0){
		c->signal = (int)1; //se for negativo, a variável signal é setada pra 1
		c->integer = (int)(-1*c->number); //converte o valor para positivo para poder obter a parte decimal
		c->decimal = ((-1*c->number) - c->integer)*100; //obtem a parte decimal
		}
		else{
		c->signal = (int)0;
		c->integer = (int)(c->number);
		c->decimal = (c->number - c->integer)*100;
		}

}

void time_stamp(){

	extern int count_1ms;
	extern int count_10ms;
	extern int count_100ms;
	extern int count_200ms;
	extern int count_500ms;
	extern int count_1s;

	extern int flag_1ms;
	extern int flag_10ms;
	extern int flag_100ms;
	extern int flag_200ms;
	extern int flag_500ms;
	extern int flag_1s;

	if (count_1ms >= 10) {flag_1ms = 1; count_1ms = 0;}
	else {flag_1ms = 0;}

	if (count_10ms >= 10) {flag_10ms = 1; count_10ms = 0;}
	else {flag_10ms = 0;}

	if (count_100ms >= 100) {flag_100ms = 1; count_100ms = 0;}
	else {flag_100ms = 0;}

	if (count_200ms >= 200) {flag_200ms = 1; count_200ms = 0;}
	else {flag_200ms = 0;}

	if (count_500ms >= 500) {flag_500ms = 1; count_500ms = 0;}
	else {flag_500ms = 0;}

	if (count_1s >= 1000) {flag_1s = 1; count_1s = 0;}
	else {flag_1s = 0;}

}


void ad_measure(){

	extern volatile bool adc_finished;
	extern uint16_t value[3];
	extern int flag_500ms;

	if (flag_500ms == 1){
	adc_finished = FALSE; /* reset flag */
	adc_Measure(NULL);
	}

	vref.number = (float)value[0]*kad;

	//sensor de temperatura do chip
	v_temp_sensor = (float)value[1]*kad;

	if (v_temp_sensor >= 0.7012){
	temp_sensor.number = 25 - (v_temp_sensor - 0.7012)/0.001646;}
	else{
	temp_sensor.number = 25 - (v_temp_sensor - 0.7012)/0.001749;}

	//valor de lux
	lumi = (float) value[2]*(1000/0.54)*kad;

	float2int(&vref);
	float2int(&temp_sensor);

}

void push_button(){

	if (status == 1){
					if (flag_100ms==1){
					push_button_count++;}
				    }

	if (status == 2){

					if (push_button_count<timer_reset*10){
											  red_On();
											  blue_Off();
						 					 }
					else {
						red_Off();
						blue_On();
					}

					status =0;
				    push_button_count=0;
   				    delay_Waitms(1000);
					red_Off();
					blue_Off();

				    }

}

void inrush_control (){

	float ds;
	float P = 15;
	float R = 0.68;
	float deltaV;
	extern int ds_int;

	deltaV = v1.number - v2.number;

	ds = (P*R)/((float)powf(deltaV,2));

	if (ds>=1){ds=1;}

	ds_int = ds*65535;
}

//void state_of_charge(){
//
//extern float SoC;
//extern int flag_1s;
//
//if (flag_1s == 1){
//
//				  if (cc.current > 0) {cc.charging = 1;}
//				  else {cc.charging = 0;}
//
//				  if (cc.current < 0) {cc.discharging = 1;}
//				  else {cc.discharging = 0;}
//
//
//				  	 	if (cc.discharging == 1) {
//          		  	 							  cc.total_Ah = cc.total_Ah + (abs(cc.current/3600)); //total de Ah descarregado da bateria
//				  	 							  if (abs(cc.current/3600) >= cc.peak_discharge_limit) {cc.peak_discharge_counter++;}
//				  	 							  if (cc.peak_discharge_counter > cc.peak_discharge_time) {cc.stop = 1;}
//				  	 						     }
//
//				  cc.capacity_Ah = cc.capacity_Ah + cc.current/3600; // capacidade atual
//				  cc.SoC = (1 - (cc.nominal_capacity - cc.capacity_Ah)/cc.nominal_capacity)*100; //estado de carga = 100*(1 - (Cn - C)/Cn)
//
//				  if (cc.SoC >= 100) {
//					  	  	  	  	  cc.SoC = 100;
//				     				  cc.charged = 1;
//				   	  	  	  	  	  cc.stop = 1;
//				         			 }
//				  else {
//					    cc.charged = 0;
//					    cc.stop = 1;
//				       }
//
//
//				  if (cc.SoC <= (100 - cc.DoD_limit)) {
//					  	  	  	  	  	  	  	  	   cc.stop = 1; //flag para parar a descarga
//				                                       cc.total_cycles_count++; //contador de ciclos totais
//				  	  	  	  	  	  	  	  	  	  }
//				  else {cc.stop = 0;}
//
//                }
//}
//
//
/*CONVERTE DECIMAL PARA INTEIRO PARA TRANSFERIR */

//
/////*CONVERTE INTEIRO PARA HEXADECIMAL */
////void dec_hex(d2h *t, int x) {
////
////int i=0,length=0;
////int temp = 0;
////
////temp = t->entrada; //utiliza a variavel temporaria para não sobreescrever o numero real
////
////while(temp > 0)
////   {
////	  t->result[i]= temp%16; //divide por 16 sem resto
////      temp = temp/16; //divide por 16 com resto
////      i++;
////      length++;
////   }
////
////for(i=length-1;i>=0;i--)
////  {
////    switch(t->result[i]) //modifica a variavel da posição [i] caso seja maior que 10; padrao hexadecimal
////    {
////      case 10:
////    	  t->result[i]=(char)10;
////          break;
////      case 11:
////    	  t->result[i]=(char)11;
////          break;
////      case 12:
////    	  t->result[i]=(char)12;
////          break;
////      case 13:
////    	  t->result[i]=(char)13;
////          break;
////      case 14:
////    	  t->result[i]=(char)14;
////          break;
////      case 15:
////    	  t->result[i]=(char)15;
////          break;
////      default :
////    	  t->result[i];
////    }
////  }
////}
////
