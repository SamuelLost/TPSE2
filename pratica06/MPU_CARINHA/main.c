/*
 * main.c
 *
 *  Created on: 15 Ara 2021
 *      Author: Ali
 */

#include "mpu6050.h"
#include <sys/ioctl.h>

/*
 ==========================================================================
 MPU6050 	 BBB PIN NO
 VCC			P9_3
 GND			P9_1
 SCL			P9_19
 SDA			P9_20
 ==========================================================================
 */

MPU6050_ACC_DATA_t mpu6050_accData;
MPU6050_GYRO_DATA_t mpu6050_gyroData;

int fd2;

int main(void) {
	fd2 = open(I2C_DEVICE_FILE_PATH,O_RDWR);

    if ( fd2 < 0) {
        perror("Failed to open I2C device file.\n");
        return -1;
    }

    /*set the I2C slave address  */
    if (ioctl(fd2,I2C_SLAVE,MPU6050_SLAVE_ADDRESS) < 0) {
            perror("Failed to set I2C slave address.\n");
            close(fd2);
            return -1;
    }

    mpu6050_init();

    while(1) {
    	mpu6050_readAcc();
    	mpu6050_readGyro();

    	printf("accX:  %0.2f accY:  %.02f accZ:  %0.2f\n", mpu6050_accData.accX, mpu6050_accData.accY, mpu6050_accData.accZ);
    	printf("gyroX: %0.2f gyroY: %.02f gyroZ: %0.2f\n", mpu6050_gyroData.gyroX, mpu6050_gyroData.gyroY, mpu6050_gyroData.gyroZ);
    	printf("Temp %0.2f\n\n", mpu6050_readTemp() );
    	usleep(500* 1000);
    }
	return 0;
}