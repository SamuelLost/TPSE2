#include "MPU6050.hpp"
#include <unistd.h>

AccelData_t accelBase_t;
GyroData_t gyroBase_t;

void initMPU6050(int AFS_SEL, int GFS_SEL) {
    //Set Clock Source to Gyro
    //set(DEVICE_ADDR, PWR_MGMT_1, 0x00);
    setSleepMode(false);
    //Disable DLPF
    set(DEVICE_ADDR, CONFIG, 0x00);
    //Set Gyro Full Scale Range
    set(DEVICE_ADDR, GYRO_CONFIG, GFS_SEL);

    //Set Accel Full Scale Range
    set(DEVICE_ADDR, ACCEL_CONFIG, AFS_SEL);
}

void initMPU6050(int AFS_SEL, int GFS_SEL, bool selfTestAccel, bool selfTestGyro) {
    //Set Clock Source to Gyro
    set(DEVICE_ADDR, PWR_MGMT_1, 0x00);
    setSleepMode(false);
    //Disable DLPF
    set(DEVICE_ADDR, CONFIG, 0x00);
    //Set Gyro Full Scale Range
    set(DEVICE_ADDR, GYRO_CONFIG, GFS_SEL | (selfTestGyro << 7));

    //Set Accel Full Scale Range
    set(DEVICE_ADDR, ACCEL_CONFIG, AFS_SEL | (selfTestAccel << 7));
}

void initMPU6050(int AFS_SEL, int GFS_SEL, bool tempSensor) {
    //Set Clock Source to Gyro
    set(DEVICE_ADDR, PWR_MGMT_1, 0x00 | (tempSensor << 3));
    setSleepMode(false);
    //Disable DLPF
    set(DEVICE_ADDR, CONFIG, 0x00);
    //Set Gyro Full Scale Range
    set(DEVICE_ADDR, GYRO_CONFIG, GFS_SEL);

    //Set Accel Full Scale Range
    set(DEVICE_ADDR, ACCEL_CONFIG, AFS_SEL);
}

void initMPU6050(int AFS_SEL, int GFS_SEL, bool selfTestAccel, bool selfTestGyro, bool tempSensor) {
    //Set Clock Source to Gyro
    set(DEVICE_ADDR, PWR_MGMT_1, 0x00 | (tempSensor << 3));
    setSleepMode(false);
    //Disable DLPF
    set(DEVICE_ADDR, CONFIG, 0x00);
    //Set Gyro Full Scale Range
    set(DEVICE_ADDR, GYRO_CONFIG, GFS_SEL | (selfTestGyro << 7));

    //Set Accel Full Scale Range
    set(DEVICE_ADDR, ACCEL_CONFIG, AFS_SEL | (selfTestAccel << 7));
}

void setTempSensorEnabled(bool enabled) {
    enabled ? set(DEVICE_ADDR, PWR_MGMT_1, 0x00) : set(DEVICE_ADDR, PWR_MGMT_1, 0x08);
}

void setSleepMode(bool sleep) {
    sleep ? set(DEVICE_ADDR, PWR_MGMT_1, 0x40) : set(DEVICE_ADDR, PWR_MGMT_1, 0x00);
}

void setGyroSelfTest(bool enabled) {
    enabled ? set(DEVICE_ADDR, GYRO_CONFIG, 0xE0) : set(DEVICE_ADDR, GYRO_CONFIG, 0x00);
}

void setAccelSelfTest(bool enabled) {
    enabled ? set(DEVICE_ADDR, ACCEL_CONFIG, 0xE0) : set(DEVICE_ADDR, ACCEL_CONFIG, 0x00);
}

void getGyroSensitivity(GyroScale scale, int16_t* GFS_SEL, float* gyroSensitivity) {
    switch (scale) {
    case GFS_250DPS:
        *gyroSensitivity = 131.0;
        *GFS_SEL = (0b00 << 3);
        break;
    case GFS_500DPS:
        *gyroSensitivity = 65.5;
        *GFS_SEL = (0b01 << 3);
        break;
    case GFS_1000DPS:
        *gyroSensitivity = 32.8;
        *GFS_SEL = (0b10 << 3);
        break;
    case GFS_2000DPS:
        *gyroSensitivity = 16.4;
        *GFS_SEL = (0b11 << 3);
        break;
    }
}

void getAccelSensitivity(AccelScale scale, int16_t* AFS_SEL, float* accelSensitivity) {
    switch (scale) {
    case AFS_2G:
        *accelSensitivity = 16384.0;
        *AFS_SEL = (0b00 << 3);
        break;
    case AFS_4G:
        *accelSensitivity = 8192.0;
        *AFS_SEL = (0b01 << 3);
        break;
    case AFS_8G:
        *accelSensitivity = 4096.0;
        *AFS_SEL = (0b10 << 3);
        break;
    case AFS_16G:
        *accelSensitivity = 2048.0;
        *AFS_SEL = (0b11 << 3);
        break;
    }
}

/*exec function that runs bash commands in c++*/
std::string exec(char* cmd) {
    std::string data;
    FILE* stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    strcat(cmd, " 2>&1");
    stream = popen(cmd, "r"); //Permite executar comando do terminal

    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
        pclose(stream);
    }
    return data;
}

//function that performs geti2c
std::string get(const char* reg1, const char* reg2) {
    char str[100];
    std::string str2;

    strcpy(str, CMD_GET);
    strcat(str, reg1);
    strcat(str, reg2);

    str2 = exec(str);
    return str2;
}

//function that performs seti2c
void set(const char* reg1, const char* reg2, int value) {
    char str[100];
    std::string str2;


    strcpy(str, CMD_SET);
    strcat(str, reg1);
    strcat(str, reg2);
    strcat(str, " ");
    strcat(str, std::to_string(value).c_str());

    str2 = exec(str);
    std::cout << str2 << std::endl;
}

//function that calibrates the sensors
void calibrateMPU6050() {
    int i = 0;
    AccelData_t temp_accelBase_t;
    GyroData_t temp_gyroBase_t;
    int16_t temp_acc_x = 0, temp_acc_y = 0, temp_acc_z = 0;
    int16_t temp_gyro_x = 0, temp_gyro_y = 0, temp_gyro_z = 0;

    std::cout << "Calibrating sensors..." << std::endl;
    std::cout << "Don't move the sensor" << std::endl;
    std::cout << "Calibrating in 3..." << std::endl;
    sleep(1);
    std::cout << "Calibrating in 2..." << std::endl;
    sleep(1);
    std::cout << "Calibrating in 1..." << std::endl;
    sleep(1);
    while (i < 30) {
        // std::cout << i << std::endl;
        getAccelData(&temp_accelBase_t);
        getGyroData(&temp_gyroBase_t);
        temp_acc_x += temp_accelBase_t.accel_x;
        temp_acc_y += temp_accelBase_t.accel_y;
        temp_acc_z += temp_accelBase_t.accel_z;
        temp_gyro_x += temp_gyroBase_t.gyro_x;
        temp_gyro_y += temp_gyroBase_t.gyro_y;
        temp_gyro_z += temp_gyroBase_t.gyro_z;
        i++;
    }

    accelBase_t.accel_x = temp_acc_x / 1000;
    accelBase_t.accel_y = temp_acc_y / 1000;
    accelBase_t.accel_z = temp_acc_z / 1000;
    gyroBase_t.gyro_x = temp_gyro_x / 1000;
    gyroBase_t.gyro_y = temp_gyro_y / 1000;
    gyroBase_t.gyro_z = temp_gyro_z / 1000;

    std::cout << "Calibration done!" << std::endl;

}


void getTempData(int16_t* tempData) {
    *tempData = (std::stoi(get(DEVICE_ADDR, TEMP_OUT_H), nullptr, 16) << 8) | (std::stoi(get(DEVICE_ADDR, TEMP_OUT_L), nullptr, 16));
    *tempData = (*tempData / 340.0) + 36.53;
}

void getAccelData(AccelData_t* accelData_t, float accelSensitivity) {
    accelData_t->accel_x = (std::stoi(get(DEVICE_ADDR, ACCEL_X_OUT_H), nullptr, 16) << 8) + (std::stoi(get(DEVICE_ADDR, ACCEL_X_OUT_L), nullptr, 16));
    accelData_t->accel_y = (std::stoi(get(DEVICE_ADDR, ACCEL_Y_OUT_H), nullptr, 16) << 8) + (std::stoi(get(DEVICE_ADDR, ACCEL_Y_OUT_L), nullptr, 16));
    accelData_t->accel_z = (std::stoi(get(DEVICE_ADDR, ACCEL_Z_OUT_H), nullptr, 16) << 8) + (std::stoi(get(DEVICE_ADDR, ACCEL_Z_OUT_L), nullptr, 16));


    accelData_t->accel_x = (accelData_t->accel_x - accelBase_t.accel_x) / accelSensitivity;
    accelData_t->accel_y = (accelData_t->accel_y - accelBase_t.accel_y) / accelSensitivity;
    accelData_t->accel_z = (accelData_t->accel_z - accelBase_t.accel_z) / accelSensitivity;

    // accelData_t->accel_x = accelData_t->accel_x / accelSensitivity;
    // accelData_t->accel_y = accelData_t->accel_y / accelSensitivity;
    // accelData_t->accel_z = accelData_t->accel_z / accelSensitivity;
}

void getAccelData(AccelData_t* accelData_t) {
    accelData_t->accel_x = (std::stoi(get(DEVICE_ADDR, ACCEL_X_OUT_H), nullptr, 16) << 8) + (std::stoi(get(DEVICE_ADDR, ACCEL_X_OUT_L), nullptr, 16));
    accelData_t->accel_y = (std::stoi(get(DEVICE_ADDR, ACCEL_Y_OUT_H), nullptr, 16) << 8) + (std::stoi(get(DEVICE_ADDR, ACCEL_Y_OUT_L), nullptr, 16));
    accelData_t->accel_z = (std::stoi(get(DEVICE_ADDR, ACCEL_Z_OUT_H), nullptr, 16) << 8) + (std::stoi(get(DEVICE_ADDR, ACCEL_Z_OUT_L), nullptr, 16));
}

void getGyroData(GyroData_t* gyroData_t, float gyroSensitivity) {
    gyroData_t->gyro_x = (std::stoi(get(DEVICE_ADDR, GYRO_X_OUT_H), nullptr, 16) << 8) + (std::stoi(get(DEVICE_ADDR, GYRO_X_OUT_L), nullptr, 16));
    gyroData_t->gyro_y = (std::stoi(get(DEVICE_ADDR, GYRO_Y_OUT_H), nullptr, 16) << 8) + (std::stoi(get(DEVICE_ADDR, GYRO_Y_OUT_L), nullptr, 16));
    gyroData_t->gyro_z = (std::stoi(get(DEVICE_ADDR, GYRO_Z_OUT_H), nullptr, 16) << 8) + (std::stoi(get(DEVICE_ADDR, GYRO_Z_OUT_L), nullptr, 16));

    gyroData_t->gyro_x = (gyroData_t->gyro_x - gyroBase_t.gyro_x) / gyroSensitivity;
    gyroData_t->gyro_y = (gyroData_t->gyro_y - gyroBase_t.gyro_y) / gyroSensitivity;
    gyroData_t->gyro_z = (gyroData_t->gyro_z - gyroBase_t.gyro_z) / gyroSensitivity;

    // gyroData_t->gyro_x = gyroData_t->gyro_x / gyroSensitivity;
    // gyroData_t->gyro_y = gyroData_t->gyro_y / gyroSensitivity;
    // gyroData_t->gyro_z = gyroData_t->gyro_z / gyroSensitivity;
}

void getGyroData(GyroData_t* gyroData_t) {
    gyroData_t->gyro_x = (std::stoi(get(DEVICE_ADDR, GYRO_X_OUT_H), nullptr, 16) << 8) + (std::stoi(get(DEVICE_ADDR, GYRO_X_OUT_L), nullptr, 16));
    gyroData_t->gyro_y = (std::stoi(get(DEVICE_ADDR, GYRO_Y_OUT_H), nullptr, 16) << 8) + (std::stoi(get(DEVICE_ADDR, GYRO_Y_OUT_L), nullptr, 16));
    gyroData_t->gyro_z = (std::stoi(get(DEVICE_ADDR, GYRO_Z_OUT_H), nullptr, 16) << 8) + (std::stoi(get(DEVICE_ADDR, GYRO_Z_OUT_L), nullptr, 16));
}
