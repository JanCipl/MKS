/*
 * sct.c
 *
 *  Created on: Oct 9, 2024
 *      Author: Martin
 */

#include "main.h"
#include "sct.h"

static const uint32_t reg_values[3][10] = { {
//PCDE--------GFAB @ DIS1
		0b0111000000000111 << 16, 0b0100000000000001 << 16, 0b0011000000001011
				<< 16, 0b0110000000001011 << 16, 0b0100000000001101 << 16,
		0b0110000000001110 << 16, 0b0111000000001110 << 16, 0b0100000000000011
				<< 16, 0b0111000000001111 << 16, 0b0110000000001111 << 16, }, {
//----PCDEGFAB---- @ DIS2
		0b0000111101110000 << 0, 0b0000110000010000 << 0, 0b0000101110110000
				<< 0, 0b0000111010110000 << 0, 0b0000110011010000 << 0,
		0b0000111011100000 << 0, 0b0000111111100000 << 0, 0b0000110000110000
				<< 0, 0b0000111111110000 << 0, 0b0000111011110000 << 0, }, {
//PCDE--------GFAB @ DIS3
		0b0111000000000111 << 0, 0b0100000000000001 << 0, 0b0011000000001011
				<< 0, 0b0110000000001011 << 0, 0b0100000000001101 << 0,
		0b0110000000001110 << 0, 0b0111000000001110 << 0, 0b0100000000000011
				<< 0, 0b0111000000001111 << 0, 0b0110000000001111 << 0, }, };

void sct_led(uint32_t value) {

	for (int i = 0; i < 32; ++i) {

		HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, (value & 1));
		value >>= 1;

		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0);
	}

	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1);
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0);
}

void sct_init(void) {
	sct_led(0);
}

void sct_value(uint16_t value) {
	uint32_t reg = 1;
	reg |= reg_values[0][value / 100 % 10];
	reg |= reg_values[1][value / 10 % 10];
	reg |= reg_values[2][value / 1 % 10];
	sct_led(reg);
}
