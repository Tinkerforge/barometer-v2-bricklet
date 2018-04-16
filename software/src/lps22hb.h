/* load-cell-v2-bricklet
 * Copyright (C) 2018 Ishraq Ibne Ashraf <ishraq@tinkerforge.com>
 *
 * lps22hb.h: LPS22HB air pressure sensor driver
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

#ifndef LPS22HB_H
#define LPS22HB_H

#include "bricklib2/utility/moving_average.h"
#include "bricklib2/hal/system_timer/system_timer.h"

void lps22hb_init(void);
void lps22hb_tick(void);

int32_t lps22hb_get_air_pressure(void);
int32_t lps22hb_get_altitude(void);
int32_t lps22hb_get_temperature(void);

#endif
