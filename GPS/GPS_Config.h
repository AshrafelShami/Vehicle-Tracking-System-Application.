
#ifndef GPS_CONFIG_H_
#define GPS_CONFIG_H_
#include "../Functions_Prototypes/GPS_Functios_Prototypes.h"
#include "../DataTypes/DataTypes.h"

#define GPS_Array_Size	149
#define GPS_GPGGA_Size	72

typedef struct{
	u8 Data		[GPS_Array_Size];
	u8 GPGGA	[GPS_GPGGA_Size];
	u8 Longitude	[9];
	u8 Latitude	[10];
	u8 Altitude	[6];
	u8 Time		[12];
	u8 Satellite_No	[3];
	u8 HDOP		[5];
}GPS_Frames;

#endif /* GPS_CONFIG_H_ */
