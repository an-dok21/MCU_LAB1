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
