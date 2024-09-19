#include<lab.h>

/* Exercise 1.
 * */
void toggle2Led() {
	// Set state for two gpio pin
	HAL_GPIO_WritePin(GPIOA, LED_1_Pin, RESET);
	HAL_GPIO_WritePin(GPIOA, LED_2_Pin, SET);

	// Delay for 2 second
	HAL_Delay(2000);

	// Toggle two pin
	HAL_GPIO_WritePin(GPIOA, LED_1_Pin, SET);
	HAL_GPIO_WritePin(GPIOA, LED_2_Pin, RESET);

	// Delay for 2 seconds
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

void oneWayTrafficLight() {
	/* FSM:
	 * Init => turn on Red -> turn on Yellow -> turn on Green -> turn on Red -> ...
	 * */
	turnOnRed();
	HAL_Delay(5000);
	turnOnYellow();
	HAL_Delay(2000);
	turnOnGreen();
	HAL_Delay(3000);
}
