#include<lab.h>

/* Exercise 1.
 * */
void toggle2Led(uint8_t* status) {
	if (*status == 0) {
		// Set state for two gpio pin
		HAL_GPIO_WritePin(GPIOA, LED_1_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, LED_2_Pin, SET);
		*status = 1;
	} else {
		HAL_GPIO_WritePin(GPIOA, LED_1_Pin, SET);
		HAL_GPIO_WritePin(GPIOA, LED_2_Pin, RESET);
		*status = 0;
	}
	// Delay for 2 second
	HAL_Delay(2000);
}

/* Exercise 2:
 * Extend the first exercise to simulate the behavior of a traffic light. A third LED, named
 * LED-GREEN is added to the system, which is connected to PA7. A cycle in this traffic light
 * is 5 seconds for the RED, 2 seconds for the YELLOW and 3 seconds for the GREEN. The
 * LED-GREEN is also controlled by its negative pin.
 * */
void turnOnRed() {
	HAL_GPIO_WritePin(GPIOA, LED_1_Pin, RESET);
	HAL_GPIO_WritePin(GPIOA, LED_2_Pin, SET);
	HAL_GPIO_WritePin(GPIOA, LED_3_Pin, SET);
}

void turnOnYellow() {
	HAL_GPIO_WritePin(GPIOA, LED_1_Pin, SET);
	HAL_GPIO_WritePin(GPIOA, LED_2_Pin, RESET);
	HAL_GPIO_WritePin(GPIOA, LED_3_Pin, SET);
}

void turnOnGreen() {
	HAL_GPIO_WritePin(GPIOA, LED_1_Pin, SET);
	HAL_GPIO_WritePin(GPIOA, LED_2_Pin, SET);
	HAL_GPIO_WritePin(GPIOA, LED_3_Pin, RESET);
}


void oneWayTrafficLight(uint8_t* time, int* light) {
	/* FSM:
	 * Init => turn on Red -> turn on Yellow -> turn on Green -> turn on Red -> ...
	 * */
	if (*light == 0) { // RED
		if (*time != 1) {
			*time = *time - 1;
			turnOnRed();
		}
		else {
			*time = 20;
			*light = 1;
		}
	} else if (*light == 1) { // YELLOW
		if (*time != 1) {
			*time = *time - 1;
			turnOnYellow();
		}
		else {
			*time = 30;
			*light = 2;
		}
	} else { // GREEN
		if (*time != 1) {
			*time = *time - 1;
			turnOnGreen();
		}
		else {
			*time = 50;
			*light = 0;
		}
	}
	// Delay for 100ms
	HAL_Delay(100);
}
