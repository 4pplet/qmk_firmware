// Copyright 2024 Stefan Sundin (4pplet)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define HAL_USE_PWM FALSE
#define HAL_USE_SPI FALSE
#define HAL_USE_I2C FALSE

/* Enable ADC for capacitive sensing */
#define HAL_USE_ADC TRUE

/* Enable GPT for precise microsecond timing */
#define HAL_USE_GPT TRUE

#include_next <halconf.h>
