/* load-cell-v2-bricklet
 * Copyright (C) 2018 Ishraq Ibne Ashraf <ishraq@tinkerforge.com>
 *
 * config_lp2sshb.h: LPS22HB specific configurations
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef CONFIG_LPS22HB_H
#define CONFIG_LPS22HB_H

#include "xmc_usic.h"
#include "xmc_gpio.h"

#define LPS22HB_SPI_BAUDRATE         100000
#define LPS22HB_USIC_CHANNEL         XMC_USIC0_CH1
#define LPS22HB_USIC_SPI             XMC_SPI0_CH1

#define LPS22HB_SCLK_PORT            XMC_GPIO_PORT0
#define LPS22HB_SCLK_PIN             8
#define LPS22HB_SCLK_PIN_MODE        (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7 | P0_8_AF_U0C1_SCLKOUT)

#define LPS22HB_SELECT_PORT          XMC_GPIO_PORT0
#define LPS22HB_SELECT_PIN           9
#define LPS22HB_SELECT_PIN_MODE      (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7 | P0_9_AF_U0C1_SELO0)

#define LPS22HB_MOSI_PORT            XMC_GPIO_PORT0
#define LPS22HB_MOSI_PIN             7
#define LPS22HB_MOSI_PIN_MODE        (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7 | P0_7_AF_U0C1_DOUT0)

#define LPS22HB_MISO_PORT            XMC_GPIO_PORT0
#define LPS22HB_MISO_PIN             6
#define LPS22HB_MISO_INPUT           XMC_USIC_CH_INPUT_DX0
#define LPS22HB_MISO_SOURCE          0b010 // DX0C

#define LPS22HB_CLOCK_PASSIVE_LEVEL  XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_DISABLED
#define LPS22HB_CLOCK_OUTPUT         XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK
#define LPS22HB_SLAVE                XMC_SPI_CH_SLAVE_SELECT_0

#define LPS22HB_RX_FIFO_DATA_POINTER 32
#define LPS22HB_TX_FIFO_DATA_POINTER 48
#define LPS22HB_RX_FIFO_SIZE         XMC_USIC_CH_FIFO_SIZE_16WORDS
#define LPS22HB_TX_FIFO_SIZE         XMC_USIC_CH_FIFO_SIZE_16WORDS

#endif
