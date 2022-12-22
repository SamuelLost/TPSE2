#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string>
#include <memory>
#include <array>

//Address of MPU6050
#define DEVICE_ADDR " 0x68"
//Address of Power Management Register
#define PWR_MGMT_1 " 0x6B"
//Address of Configuration Register
#define CONFIG " 0x1A"
//Address of Gyroscope Configuration Register
//XG_ST = 1, YG_ST = 1, ZG_ST = 1 (Self Test) -> BITS 7, 6, 5
#define GYRO_CONFIG " 0x1B"
//Address of Accelerometer Configuration Register
#define ACCEL_CONFIG " 0x1C"
//Address of Accelerometer X-Register
#define ACCEL_X_OUT_H " 0x3B"
#define ACCEL_X_OUT_L " 0x3C"
//Address of Accelerometer Y-Register
#define ACCEL_Y_OUT_H " 0x3D"
#define ACCEL_Y_OUT_L " 0x3E"
//Address of Accelerometer Z-Register
#define ACCEL_Z_OUT_H " 0x3F"
#define ACCEL_Z_OUT_L " 0x40"
//Address of Temperature Register
#define TEMP_OUT_H " 0x41"
#define TEMP_OUT_L " 0x42"
//Address of Gyroscope X-Register
#define GYRO_X_OUT_H " 0x43"
#define GYRO_X_OUT_L " 0x44"
//Address of Gyroscope Y-Register
#define GYRO_Y_OUT_H " 0x45"
#define GYRO_Y_OUT_L " 0x46"
//Address of Gyroscope Z-Register
#define GYRO_Z_OUT_H " 0x47"
#define GYRO_Z_OUT_L " 0x48"

#define CMD_GET "i2cget -y 2"
#define CMD_SET "i2cset -y 2"

typedef enum{
	AFS_2G = 0,
	AFS_4G,
	AFS_8G,
	AFS_16G
} AccelScale;

typedef enum{
	GFS_250DPS = 0,
	GFS_500DPS,
	GFS_1000DPS,
	GFS_2000DPS
} GyroScale;

typedef struct {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
} AccelData_t;

typedef struct {
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
} GyroData_t;

typedef struct {
	int16_t temp;
} TempData_t;

std::string exec(char* cmd);
std::string get(const char* reg1, const char* reg2);
void set(const char* reg1, const char* reg2, int value);

void initMPU6050(int AFS_SEL, int GFS_SEL);
void initMPU6050(int AFS_SEL, int GFS_SEL, bool tempSensor);
void initMPU6050(int AFS_SEL, int GFS_SEL, bool selfTestAccel, bool selfTestGyro);
void initMPU6050(int AFS_SEL, int GFS_SEL, bool selfTestAccel, bool selfTestGyro, bool tempSensor);

void calibrateMPU6050();

void getAccelSensitivity(AccelScale scale, int16_t* AFS_SEL, float* gyroSensitivity);
void getGyroSensitivity(GyroScale scale, int16_t* GFS_SEL, float* accelSensitivity);

void getAccelData(AccelData_t* accelData, float accelSensitivity);
void getAccelData(AccelData_t* accelData);

void getGyroData(GyroData_t* gyroData, float gyroSensitivity);
void getGyroData(GyroData_t* gyroData);

void getTempData(float* tempData);
void setAccelScale(AccelScale scale);
void setGyroScale(GyroScale scale);
void setClockSource(char* source);
void setSleepMode(bool mode);
void setTempSensor(bool mode);
void setGyroSelfTest(bool mode);
void setAccelSelfTest(bool mode);

#endif /* INC_MPU6050_H_ */