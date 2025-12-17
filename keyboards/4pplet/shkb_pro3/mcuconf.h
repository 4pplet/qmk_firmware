// Copyright 2024 Stefan Sundin (4pplet)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

/* Enable ADC1 for capacitive sensing on PA0 */
#undef STM32_ADC_USE_ADC1
#define STM32_ADC_USE_ADC1 TRUE

/* Enable GPT (TIM3) for precise microsecond timing */
#undef STM32_GPT_USE_TIM3
#define STM32_GPT_USE_TIM3 TRUE
