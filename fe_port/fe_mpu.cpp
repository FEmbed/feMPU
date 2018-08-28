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
        if (mpu_init(NULL)) {
            log_e("Could not initialize MPU.");
        }
        // Wake up all sensors.
#ifdef AK89xx_SECONDARY
        if(mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS))
#else
        if(mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL))
#endif
        {
            log_e("mpu set sensors failed.");
        }
        // Push both gyro and accel data into the FIFO.
        if(mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL))
        {
            log_e("mpu configure fifo failed.");
        }
        if(mpu_set_sample_rate(20))
        {
            log_e("mpu set sample rate failed.");
        }
#ifdef AK89xx_SECONDARY
        // The compass sampling rate can be less than the gyro/accel sampling rate.
        // Use this function for proper power management.
        if(mpu_set_compass_sample_rate(10))
        {
            log_e("mpu set compass sample rate failed.");
        }
#endif
    }

    uint32_t fe_i2c_write(uint8_t addr, uint8_t reg_addr, uint16_t reg_len, uint8_t *data)
    {
        int ret = 0;
        if(mpu_i2c)
            ret = mpu_i2c->writeMem(addr, (uint32_t)reg_addr, fastembedded::I2CMEMAddr8Bit, data, reg_len);
        if(ret == reg_len)
            return 0;
        return 1;
    }

    uint32_t fe_i2c_read(uint8_t addr, uint8_t reg_addr, uint16_t reg_len, uint8_t *data)
    {
        int ret = 0;
        if(mpu_i2c)
            ret = mpu_i2c->readMem(addr, (uint32_t)reg_addr, fastembedded::I2CMEMAddr8Bit, data, reg_len);
        if(ret == reg_len)
            return 0;
        return 1;
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
