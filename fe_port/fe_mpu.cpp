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

#include "fe_mpu.h"
#include "assert.h"
#include "fastembedded.h"

fastembedded::I2C *mpu_i2c;

extern "C"
{
    void fe_mpu_init(void *i2c)
    {
        assert(i2c);
        mpu_i2c = (fastembedded::I2C*)i2c;
    }

    uint32_t fe_i2c_write(uint8_t addr, uint8_t reg_addr, uint16_t reg_len, uint8_t *data)
    {
        if(mpu_i2c)
            return mpu_i2c->writeMem(addr, (uint32_t)reg_addr, fastembedded::I2CMEMAddr8Bit, data, reg_len);
        return 0;
    }

    uint32_t fe_i2c_read(uint8_t addr, uint8_t reg_addr, uint16_t reg_len, uint8_t *data)
    {
        if(mpu_i2c)
            return mpu_i2c->readMem(addr, (uint32_t)reg_addr, fastembedded::I2CMEMAddr8Bit, data, reg_len);
        return 0;
    }

    void get_ms(uint32_t *ms)
    {
        *ms = fe_get_ticks();
    }

    void delay_ms(uint32_t ms)
    {
        fe_delay(ms);
    }

    // use fastembedded gpio interrupt callback instead.
    int reg_int_cb(struct int_param_s *int_param)
    {
        (void) int_param;
        return 0;
    }
}
