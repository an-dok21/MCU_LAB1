#include<lab.h>

uint8_t seg7Pin[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6};
int ledStateArray[] = {0, 0, 0, 0, 0, 0, 0};

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
	HAL_GPIO_WritePin(GPIOA, LED_1_Pin, SET);
	HAL_GPIO_WritePin(GPIOA, LED_2_Pin, RESET);
	HAL_GPIO_WritePin(GPIOA, LED_3_Pin, RESET);
}

void turnOnYellow() {
	HAL_GPIO_WritePin(GPIOA, LED_1_Pin, RESET);
	HAL_GPIO_WritePin(GPIOA, LED_2_Pin, SET);
	HAL_GPIO_WritePin(GPIOA, LED_3_Pin, RESET);
}

void turnOnGreen() {
	HAL_GPIO_WritePin(GPIOA, LED_1_Pin, RESET);
	HAL_GPIO_WritePin(GPIOA, LED_2_Pin, RESET);
	HAL_GPIO_WritePin(GPIOA, LED_3_Pin, SET);
}

void extraTurnOnRed() {
	HAL_GPIO_WritePin(GPIOA, LED_4_Pin, SET);
	HAL_GPIO_WritePin(GPIOA, LED_5_Pin, RESET);
	HAL_GPIO_WritePin(GPIOA, LED_6_Pin, RESET);
}
void extraTurnOnYellow() {
	HAL_GPIO_WritePin(GPIOA, LED_4_Pin, RESET);
	HAL_GPIO_WritePin(GPIOA, LED_5_Pin, SET);
	HAL_GPIO_WritePin(GPIOA, LED_6_Pin, RESET);
}
void extraTurnOnGreen() {
	HAL_GPIO_WritePin(GPIOA, LED_4_Pin, RESET);
	HAL_GPIO_WritePin(GPIOA, LED_5_Pin, RESET);
	HAL_GPIO_WritePin(GPIOA, LED_6_Pin, SET);
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
			*time = 30;
			*light = 2;
		}
	} else if (*light == 1) { // GREEN
		if (*time != 1) {
			*time = *time - 1;
			turnOnGreen();
		}
		else {
			*time = 20;
			*light = 1;
		}
	} else { // YELLOW
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


/* Exercise 3:
 * */
void fourWayTrafficLight(uint8_t* time1, uint8_t* time2, int* light1, int* light2) {
	if (*light1 == 0 && *light2 == 1) { // RED1 and GREEN2
		if (*time1 != 0 && *time2 != 0) {
			*time1 = *time1 - 1;
			*time2 = *time2 - 1;
			turnOnRed();
			extraTurnOnGreen();
		} else { // RED1 and YELLOW2
			*time2 = 20; // set time for yellow led
 			*light2 = 2; // turn to Yellow
			turnOnRed();
		}
	} else if (*light1 == 0 && *light2 == 2) { // RED1 and YELLOW2
		if (*time1 != 0 && *time2 != 0) {
			*time1 = *time1 - 1;
			*time2 = *time2 - 1;
			turnOnRed();
			extraTurnOnYellow();
		} else {
			*time1 = 30; // set time for GREEN1
			*time2 = 50; // set time for RED2
			*light1 = 1;
			*light2 = 0;
			turnOnGreen();
			extraTurnOnRed();
		}
	} else if (*light1 == 1 && *light2 == 0) {
		if (*time1 != 0 && *time2 != 0) {
			*time1 = *time1 - 1;
			*time2 = *time2 - 1;
			extraTurnOnRed();
			turnOnGreen();
		} else { // YELLOW1 and RED2
			*time1 = 20; // set time for yellow led
			*light1 = 2; // turn to Yellow
			extraTurnOnRed();
		}
	} else if (*light1 == 2 && *light2 == 0) {
		if (*time1 != 0 && *time2 != 0) {
			*time1 = *time1 - 1;
			*time2 = *time2 - 1;
			extraTurnOnRed();
			turnOnYellow();
		} else {
			*time1 = 50; // set time for RED1
			*time2 = 30; // set time for GREEN2
			*light1 = 0;
			*light2 = 1;
			turnOnRed();
			extraTurnOnGreen();
		}
	}
	HAL_Delay(100);
}

/* Exercise 4
 * */
int convertBinChar(char bin) {
	return (bin == '1') ? 1 : 0;
}

int* convertState(char* stateStr, int count) {
	for (int i = 0; i < count; i++) {
		ledStateArray[i] = 0;
	}
	int *result = ledStateArray;
	for (int i = 0; i < count; i++) {
		result[i] = convertBinChar(stateStr[i]);
	}
	return result;
}

void display(uint8_t gpios[7], char* stateStr) {
	int* states = convertState(stateStr, 7);
	for (int i = 0; i < 7; i++) {
		HAL_GPIO_WritePin(GPIOB, gpios[i], states[i]);
	}
}

void display7Segment(uint8_t number) {
	switch (number) {
	case 0:
		display(seg7Pin, "0000001");
		break;
	case 1:
		display(seg7Pin, "1001111");
		break;
	case 2:
		display(seg7Pin, "0010010");
		break;
	case 3:
		display(seg7Pin, "0000110");
		break;
	case 4:
		display(seg7Pin, "1001100");
		break ;
	case 5:
		display(seg7Pin, "0100100");
		break;
	case 6:
		display(seg7Pin, "0100000");
		break ;
	case 7:
		display(seg7Pin, "0001111");
		break;
	case 8:
		display(seg7Pin, "0000000");
		break;
	case 9:
		display(seg7Pin, "0000100");
		break;
	default:
		break;
	}
}





