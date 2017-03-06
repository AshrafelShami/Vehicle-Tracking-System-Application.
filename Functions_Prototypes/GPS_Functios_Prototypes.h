
#ifndef GPS_FUNCTIOS_PROTOTYPES_H_
#define GPS_FUNCTIOS_PROTOTYPES_H_
#include "../DataTypes/DataTypes.h"


void	GPS_Data			( void );
void	GPS_GPGGA			( void );
void	GPS_Update			( void );
u8*		GPS_Longitude		( void );
u8*		GPS_Latitude		( void );
u8*		GPS_Altitude		( void );
u8*		GPS_Time			( void );
u8*		GPS_Satellite_No	( void );
u8*		GPS_HDOP			( void );

#endif /* GPS_FUNCTIOS_PROTOTYPES_H_ */