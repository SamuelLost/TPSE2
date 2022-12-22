/*BBB-MPU6050.cpp
by OP from teachmemicro.com
*/

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string>
#include <memory>
#include <array>

using namespace std;
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

GyroScale gyroScale = GFS_250DPS;
AccelScale accelScale = AFS_2G;
// int8_t accelScale = AFS_2G;
// int8_t gyroScale = GFS_250DPS;

float accelSensitivity;
float gyroSensitivity;

int AFS_SEL = 0;
int GFS_SEL = 0;

int16_t accel_x;
int16_t accel_y;
int16_t accel_z;
int16_t gyro_x;
int16_t gyro_y;
int16_t gyro_z;
int temp;

//Address of MPU6050
const char* deviceADDR = " 0x68";
//Address of Power Management Register
const char* PWR_MGMT_1 = " 0x6B";
//Address of Configuration Register
const char* CONFIG = " 0x1A";
//Address of Gyroscope Configuration Register
//XG_ST = 1, YG_ST = 1, ZG_ST = 1 (Self Test) -> BITS 7, 6, 5
const char* GYRO_CONFIG = " 0x1B";
//Address of Accelerometer Configuration Register
const char* ACCEL_CONFIG = " 0x1C";
//Address of Accelerometer X-Register
const char* ACCEL_X_OUT_H = " 0x3B";
const char* ACCEL_X_OUT_L = " 0x3C";
//Address of Accelerometer Y-Register
const char* ACCEL_Y_OUT_H = " 0x3D";
const char* ACCEL_Y_OUT_L = " 0x3E";
//Address of Accelerometer Z-Register
const char* ACCEL_Z_OUT_H = " 0x3F";
const char* ACCEL_Z_OUT_L = " 0x40";
//Address of Temperature Register
const char* TEMP_OUT_H = " 0x41";
const char* TEMP_OUT_L = " 0x42";
//Address of Gyroscope X-Register
const char* GYRO_X_OUT_H = " 0x43";
const char* GYRO_X_OUT_L = " 0x44";
//Address of Gyroscope Y-Register
const char* GYRO_Y_OUT_H = " 0x45";
const char* GYRO_Y_OUT_L = " 0x46";
//Address of Gyroscope Z-Register
const char* GYRO_Z_OUT_H = " 0x47";
const char* GYRO_Z_OUT_L = " 0x48";

const char* cmdGet = "i2cget -y 2";
const char* cmdSet = "i2cset -y 2";

//Get Accelerometer Sensitivity
void getAccelSensitivity() {
	switch (accelScale) {
		case AFS_2G:
			AFS_SEL = (0b0 << 3);
			accelSensitivity = 16384.0;
			break;
		case AFS_4G:
			AFS_SEL = (0b1 << 3);
			accelSensitivity = 8192.0;
			break;
		case AFS_8G:
			AFS_SEL = (0b10 << 3);
			accelSensitivity = 4096.0;
			break;
		case AFS_16G:
			AFS_SEL = (0b11 << 3);
			accelSensitivity = 2048.0;
			break;
	}
}
//Get Gyroscope Sensitivity
void getGyroSensitivity() {
	switch (gyroScale) {
		case GFS_250DPS:
			GFS_SEL = (0b0 << 3);
			gyroSensitivity = 131;
			break;
		case GFS_500DPS:
			GFS_SEL = (0b1 << 3);
			gyroSensitivity = 65.5;
			break;
		case GFS_1000DPS:
			GFS_SEL = (0b10 << 3);
			gyroSensitivity = 32.8;
			break;
		case GFS_2000DPS:
			GFS_SEL = (0b11 << 3);
			gyroSensitivity = 16.4;
			break;
	}
}
/*exec function that runs bash commands in c++*/
string exec(char* cmd) {
	string data;
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
string get(const char* reg1, const char* reg2) {
	char str[100];
	string str2;

	strcpy(str, cmdGet);
	strcat(str, reg1);
	strcat(str, reg2);

	str2 = exec(str);
	return str2;
}

//function that performs seti2c
void set(const char* reg1, const char* reg2, int value) {
	char str[100];
	string str2;

	strcpy(str, cmdSet);
	strcat(str, reg1);
	strcat(str, reg2);
	strcat(str, " ");
	strcat(str, to_string(value).c_str());

	str2 = exec(str);
	cout << str2 << endl;
}

int main() {
	getAccelSensitivity();
	getGyroSensitivity();
	//SDA = P9_18;SCL = P9_17 - I2C1
	//SDA = P9_20;SCL = P9_19 - I2C2
	set(deviceADDR, CONFIG, 0x04); //DLPF_CFG = 0x04 -> BITS 2, 1, 0
	set(deviceADDR, PWR_MGMT_1, 0);	//turn on the MPU6050
	set(deviceADDR, GYRO_CONFIG, GFS_SEL);	//set the gyro to 250 degrees per second
	set(deviceADDR, ACCEL_CONFIG, AFS_SEL);	//set the accel to 4g

	while (true) {
		accel_x = stoi(get(deviceADDR, ACCEL_X_OUT_H), nullptr, 16) << 8 + stoi(get(deviceADDR, ACCEL_X_OUT_L), nullptr, 16);
		accel_y = stoi(get(deviceADDR, ACCEL_Y_OUT_H), nullptr, 16) << 8 + stoi(get(deviceADDR, ACCEL_Y_OUT_L), nullptr, 16);
		accel_z = stoi(get(deviceADDR, ACCEL_Z_OUT_H), nullptr, 16) << 8 + stoi(get(deviceADDR, ACCEL_Z_OUT_L), nullptr, 16);
		
		accel_x = accel_x / accelSensitivity;
		accel_y = accel_y / accelSensitivity;
		accel_z = accel_z / accelSensitivity;

		gyro_x = stoi(get(deviceADDR, GYRO_X_OUT_H), nullptr, 16) << 8 + stoi(get(deviceADDR, GYRO_X_OUT_L), nullptr, 16);
		gyro_y = stoi(get(deviceADDR, GYRO_Y_OUT_H), nullptr, 16) << 8 + stoi(get(deviceADDR, GYRO_Y_OUT_L), nullptr, 16);
		gyro_z = stoi(get(deviceADDR, GYRO_Z_OUT_H), nullptr, 16) << 8 + stoi(get(deviceADDR, GYRO_Z_OUT_L), nullptr, 16);
		gyro_x = gyro_x / gyroSensitivity;
		gyro_y = gyro_y / gyroSensitivity;
		gyro_z = gyro_z / gyroSensitivity;

		// string temp_h = get(deviceADDR, TEMP_OUT_H);
		// string temp_l = get(deviceADDR, TEMP_OUT_L);
		// printf("Temp_h: %s Temp_l:%s\n", temp_h.c_str(), temp_l.c_str());
		// int16_t temp2_h = stoi(temp_h, nullptr, 16);
		// int16_t temp2_l = stoi(temp_l, nullptr, 16);
		// printf("Temp2_h: %d Temp2_l:%d\n", temp2_h, temp2_l);
		// temp = (temp2_h << 8) | temp2_l;
		// temp = 36 - (temp2_h/340 + temp2_l);
		// printf("Temp: %d\n", temp);
		// printf("Temp_h: %s Temp_l: %s\n", temp_h.c_str(), temp_l.c_str());
		//temp = (temp / 340.0) + 36.53;

		cout << "X-acc: " << accel_x << " Y-acc: " << accel_y << " Z-acc: " << accel_z << endl;
		// printf("X-gyro: %d Y-gyro: %d Z-gyro: %d Temp: %d\r\n", gyro_x, gyro_y, gyro_z, temp);
		cout << "X-gyro: " << gyro_x << " Y-gyro: " << gyro_y << " Z-gyro: " << gyro_z << endl;

	}
	return 0;
}