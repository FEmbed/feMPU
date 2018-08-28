/* FastEmbedded Microcontroller Library
 * Copyright (c) 2018-2028 Gene Kong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef FASTEMBEDDED_FE_MPU_H_
#define FASTEMBEDDED_FE_MPU_H_

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#include "inv_mpu.h"
#include "driver.h"

#define i2c_write   fe_i2c_write
#define i2c_read    fe_i2c_read
#define delay_ms    delay_ms
#define get_ms      get_ms

void fe_mpu_init(void *i2c);
uint32_t fe_i2c_write(uint8_t addr, uint8_t reg_addr, uint16_t reg_len, uint8_t *data);
uint32_t fe_i2c_read(uint8_t addr, uint8_t reg_addr, uint16_t reg_len, uint8_t *data);

void get_ms(uint32_t *ms);
void delay_ms(uint32_t ms);
int reg_int_cb(struct int_param_s *int_param);

#ifdef __cplusplus
}
#endif

#endif /* FASTEMBEDDED_FE_MPU_H_ */
