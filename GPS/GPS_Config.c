#include "../Functions_Prototypes/UART_Function_Prototypes.h"
#include "GPS_Config.h"

GPS_Frames	GPS;
/********************************************************************************************
  Name:     GPS_Data.
  Purpose:  Function used to Receive all the GPS data and saves it in an array GPS_Data.
  Entry:    No parameters.
  Exit:		No parameters.
********************************************************************************************/
void GPS_Data( void ){
	u8 i;
	for(i = 0; i < GPS_Array_Size; i++)
		GPS.Data[i] = USART_Receive();
}

/********************************************************************************************
  Name:     GPS_GPGGA.
  Purpose:  Function used to Search for the $GPGGA frame in the received data and saves it in 
			a global Struct of arrays.
  Entry:    No parameters.
  Exit:		No parameters.
********************************************************************************************/
void GPS_GPGGA( void ){
	u8 i;
	u8  k = 0, j = 0;
	for(i = 0; i < GPS_Array_Size; i++){
		if  (GPS.Data[i] == '$' && GPS.Data[i+1] == 'G' && GPS.Data[i+2] == 'P'
		&& GPS.Data[i+3] == 'G' && GPS.Data[i+4] == 'G' && GPS.Data[i+5] == 'A')
			for(k = i + 6; k < (GPS_GPGGA_Size + i + 6) ; k++)
				GPS.GPGGA[j++] = GPS.Data[k];
	}
}

/********************************************************************************************
  Name:     GPS_Longitude.
  Purpose:  Function used to Update the Longitude Level.
  Entry:    No parameters.
  Exit:		return GPS.Longitude, Update the GPS_Frames Struct
********************************************************************************************/
u8* GPS_Longitude( void ){
	u8 i, L, Comma_Flag = 0, Long = 8;
	for(i = 0; i < GPS_GPGGA_Size; i++){
		if(GPS.GPGGA[i] == ',')
			Comma_Flag++;
		
		if(Comma_Flag == 2){
			for (L = 0; L < Long; L++){
				GPS.Longitude[L] = GPS.GPGGA[i+1];
				if (GPS.GPGGA[i++] == ','){
					Comma_Flag++;
				}
			}
		}
	}
	return GPS.Longitude;
}

/********************************************************************************************
  Name:     GPS_Latitude.
  Purpose:  Function used to Update the Latitude Level.
  Entry:    No parameters.
  Exit:		return GPS.Latitude, Update the GPS_Frames Struct
********************************************************************************************/
u8* GPS_Latitude( void ){
	u8 i, L, Comma_Flag = 0, Lati = 9;
	for(i = 0; i < GPS_GPGGA_Size; i++){
		if(GPS.GPGGA[i] == ',')
			Comma_Flag++;
			
		if (Comma_Flag == 4){
			for(L = 0; L < Lati; L++){
				GPS.Latitude[L] = GPS.GPGGA[i+1];
				if(GPS.GPGGA[i++] == ',')
					Comma_Flag++;
			}
		}
	}
	return GPS.Latitude;
}

/********************************************************************************************
  Name:     GPS_Altitude.
  Purpose:  Function used to Update the Altitude Level (meters).
  Entry:    No parameters.
  Exit:		return GPS.Altitude, Update the GPS_Frames Struct
********************************************************************************************/
u8* GPS_Altitude( void ){
	u8 i, A, Comma_Flag = 0, Alti = 5;
	for(i = 0; i < GPS_GPGGA_Size; i++){
		if(GPS.GPGGA[i] == ',')
		Comma_Flag++;
		
		if (Comma_Flag == 9){
			for(A = 0; A < Alti; A++){
				GPS.Altitude[A] = GPS.GPGGA[i+1];
				if(GPS.GPGGA[i++] == ',')	
					Comma_Flag++;
			}
		}
	}
	return GPS.Altitude;
}

/********************************************************************************************
  Name:     GPS_Time.
  Purpose:  Function used to Update the Time.
  Entry:    No parameters.
  Exit:		return GPS.Time, Update the GPS_Frames Struct
********************************************************************************************/
u8* GPS_Time( void ){
	u8 i, T, Comma_Flag = 0, Alti = 11;
	for(i = 0; i < GPS_GPGGA_Size; i++){
		if(GPS.GPGGA[i++] == ',')
			Comma_Flag++;
		
		if (Comma_Flag == 1){
			for(T = 0; T < Alti; T++){
				if (T == 2 || T == 5){
					GPS.Time[T++] = ':' ;
					GPS.Time[T] = GPS.GPGGA[i] ;	
				}
				else
					GPS.Time[T] = GPS.GPGGA[i];
				if(GPS.GPGGA[i++] == ',')
					Comma_Flag++;
			}
		}
	}
	return GPS.Time;
}

/********************************************************************************************
  Name:     GPS_Satellite_No.
  Purpose:  Function used to get the number of satellites.
  Entry:    No parameters.
  Exit:		return GPS.Satellite_No, Update the GPS_Frames Struct
********************************************************************************************/
u8* GPS_Satellite_No( void ){
	u8 i, S, Comma_Flag = 0, Alti = 2;
	for(i = 0; i < GPS_GPGGA_Size; i++){
		if(GPS.GPGGA[i] == ',')
		Comma_Flag++;
		
		if (Comma_Flag == 7){
			for(S = 0; S < Alti; S++){
				GPS.Satellite_No[S] = GPS.GPGGA[i+1];
				if(GPS.GPGGA[i++] == ',')
				Comma_Flag++;
			}
		}
	}
	return GPS.Satellite_No;
}

/********************************************************************************************
  Name:     GPS_HDOP.
  Purpose:  Function used to Update the  horizontal dilution of precision data.
  Entry:    No parameters.
  Exit:		return GPS.HDOP, Update the GPS_Frames Struct.
********************************************************************************************/
u8* GPS_HDOP( void ){
	u8 i, H, Comma_Flag = 0, Alti = 4;
	for(i = 0; i < GPS_GPGGA_Size; i++){
		if(GPS.GPGGA[i] == ',')
		Comma_Flag++;
		
		if (Comma_Flag == 8){
			for(H = 0; H < Alti; H++){
				GPS.HDOP[H] = GPS.GPGGA[i+1];
				if(GPS.GPGGA[i++] == ',')
				Comma_Flag++;
			}
		}
	}
	return GPS.HDOP;
}


/********************************************************************************************
  Name:     GPS_Update.
  Purpose:  Function used to Update the received GPS data.
  Entry:    No parameters.
  Exit:		No parameters.
********************************************************************************************/

void GPS_Update ( void ){
	GPS_Data			();
	GPS_GPGGA			();
	GPS_Longitude		();
	GPS_Latitude		();
	GPS_Altitude		();
	GPS_Time			();
	GPS_Satellite_No	();
	GPS_HDOP			();
}