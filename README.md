# feMPU
这是一个InvenSense的MPU产品的FastEmbedded移植版本
# 移植事项 #
> 移植参考文件放到了`fe_port`目录,在使用FastEmbedded生成系统时，文件会自动拷贝到你的系统中，请修改自动生成的文件。
> 请根据你自己的产品来定义宏`MPU6050`/`MPU9250`/`MPU6500`/`AK89xx_SECONDARY`等;  
> 宏`MOTION_DRIVER_TARGET_FASTEMBEDDED`会自动添加到你的项目系统中。


# 默认初始化函数 #
添加一个`fe_mpu_init`函数用于传递I2C对象，I2C对象动态申请，在还需要使用MPU库的时候不要释放此对象。
``` c++
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
```
**用户可以在自己的Port目录下任意修改此函数**。