#include "ISKRA_Buff.h"

__int8 ISKRABuffAssemble(void* MemoryForBuffer, const __int8 trk_no, const __int8 command, const __int32 price, const __int32 volume, __int8 error, const __int8 code) {
	//__int8* MemoryForBuffer = MemoryForBuffer;
	__int8 i;
	__int8 Error;
   	Error =  (trk_no > 0 && trk_no < 100)		? 0 : 1;		//Error on TRK_NO	- 0x000001
	Error += (command > 0 && command < 8)		? 0 : 2;		//Error on command	- 0x000010
	Error += (price > 0 && price < 1000000)		? 0 : 4;		//Error on price	- 0x000100
	Error += (volume > 0 && volume < 1000000)	? 0 : 8;		//Error on volume	- 0x001000
	Error += (error > 0 && error < 100)			? 0 : 16;		//Error on error	- 0x010000
	Error += (code > 0 && code < 100)			? 0 : 32;		//Error on code		- 0x100000
	if (Error) return Error;										//If Error!=0

	*((__int8*) MemoryForBuffer) = 0x01;							// SOH
	*(((__int8*)MemoryForBuffer) + 3) = command + '0';				// Command value into ASCII
	*(((__int8*)MemoryForBuffer) + 4) = 0x02;						// STX
	__int32 Price = price, Volume = volume;
	for (i = 0; i < 6; i++) {
		*(((__int8*)MemoryForBuffer) + 10 - i) = ((Price  % 10) + '0');		// Price value into ASCII
		Price  = Price  / 10;
		*(((__int8*)MemoryForBuffer) + 16 - i) = ((Volume % 10) + '0');		// Volume value into ASCII
		Volume = Volume / 10;
	}
	__int8 TRK_No = trk_no, Code = code;
		Error = error;
	for (i = 0; i < 2; i++) {	
		*(((__int8*)MemoryForBuffer) + 2  - i) = ((TRK_No % 10)  + '0');	// TRK_No value into ASCII
		TRK_No	= TRK_No / 10;
		*(((__int8*)MemoryForBuffer) + 18 - i) = ((Error  % 10) + '0');		// Error value into ASCII
		Error	= Error  / 10;
		*(((__int8*)MemoryForBuffer) + 20 - i) = ((Code   % 10) + '0');		// Code value into ASCII
		Code	= Code   / 10;
	}
	*(((__int8*)MemoryForBuffer) + 21) =	0x03;					// ETX
	*(((__int8*)MemoryForBuffer) + 22) =	0;						
	for ( i = 1; i < 22; i++) {										// CRC
		*(((__int8*)MemoryForBuffer) + 22) = *(((__int8*)MemoryForBuffer) + 22) ^ *(((__int8*)MemoryForBuffer) + i);
	}
	return 0;	// Return with 0 errors
}

