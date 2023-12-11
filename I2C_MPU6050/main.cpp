#include "MPU6050.hpp"
#include <unistd.h>

AccelData_t accelData_t;
GyroData_t gyroData_t;
TempData_t tempData_t;

GyroScale gyroScale = GFS_250DPS;
AccelScale accelScale = AFS_4G;

int16_t AFS_SEL;
int16_t GFS_SEL;

float accelSensitivity;
float gyroSensitivity;

using namespace std;

int main() {
    getAccelSensitivity(accelScale, &AFS_SEL, &accelSensitivity);
    getGyroSensitivity(gyroScale, &GFS_SEL, &gyroSensitivity);
    initMPU6050(AFS_SEL, GFS_SEL, false, false, false);
    calibrateMPU6050();
    while (1) {
        getAccelData(&accelData_t, accelSensitivity);
        getGyroData(&gyroData_t, gyroSensitivity);
        // getTempData(&tempData_t.temp); // not working: disabled in initMPU6050()
        //clear display
        cout << "\033[2J\033[1;1H";

        cout << "Accel X: " << accelData_t.accel_x << " Accel Y: " << accelData_t.accel_y << " Accel Z: " << accelData_t.accel_z << endl;
        cout << "Gyro X: " << gyroData_t.gyro_x << " Gyro Y: " << gyroData_t.gyro_y << " Gyro Z: " << gyroData_t.gyro_z << endl;
        usleep(100000);
    }
    return 0;
}