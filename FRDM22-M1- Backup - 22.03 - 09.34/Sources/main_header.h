/*
 * main_header.h
 *
 *  Created on: 09/03/2017
 *      Author: mauro
 */

#ifndef SOURCES_MAIN_HEADER_H_
#define SOURCES_MAIN_HEADER_H_

/*AD*/

uint16_t value[3];
volatile bool adc_finished;
static float kad = 3.3/(65536);
float v_temp_sensor;
float lumi;
int ds_int;
int push_button_count;
int status;

/*Marcadores de Tempo*/

int count_1ms;
int count_10ms;
int count_100ms;
int count_200ms;
int count_500ms;
int count_1s;

int flag_1ms;
int flag_10ms;
int flag_100ms;
int flag_200ms;
int flag_500ms;
int flag_1s;

#define timer_reset 5

/*================= STRUCTS ===================*/

typedef struct {

	float number;
	int signal;
	int integer;
	int decimal;

} num_decimal;

static num_decimal vref = {0,0,0,0};
static num_decimal temp_sensor = {0,0,0,0};
static num_decimal c ={0,0,0,0};
static num_decimal v1 = {54.6,0,0,0};
static num_decimal v2 = {48,0,0,0};

// typedef struct{
//
//	int entrada;
//	unsigned char result[10];
//
//} d2h;

typedef struct {

	float nominal_capacity;
	float DoD_limit;
	float peak_discharge_limit;
	float capacity_Ah;
	float current;
	float SoC;
	float total_Ah;
	int charged;
	int stop;
	int charging;
	int discharging;
	int total_cycles_count;
	int peak_discharge_counter;
	int peak_discharge_time;

} soc_struct;

static soc_struct cc = {2600,20,100,0,100,0,0,0,0,0,0,0,0,0};

#endif /* SOURCES_MAIN_HEADER_H_ */
