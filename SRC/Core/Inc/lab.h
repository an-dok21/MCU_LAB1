/*
 * lab.h
 *
 *  Created on: Sep 18, 2024
 *      Author: Msi
 */

#ifndef INC_LAB_H_
#define INC_LAB_H_
#include<main.h>

/* Exercise 1:
 * In this exercise, the status of two LEDs are switched every 2 seconds, as demonstrated in
 * the figure bellow.
 * */
void toggle2Led(uint8_t* status);

/* Exercise2
 * */
void oneWayTrafficLight(uint8_t* time, int* light);

/* Exercise 3
 * */
void fourWayTrafficLight(uint8_t* time1, uint8_t* time2, int* light1, int* light2);

/* Exercise 4
 * */
void display7Segment(uint8_t number, int gpioPin[7]);

#endif /* INC_LAB_H_ */
