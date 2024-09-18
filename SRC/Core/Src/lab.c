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
