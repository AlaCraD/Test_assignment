#include "ISKRA_Buff.h"

__int8* ISKRABuffAssemble(__int8* MemoryForBuffer, __int8* TRK_No, __int8 Command, __int8* price, __int8* volume, __int8* status, __int8* error, __int8* code) {
	__int8* Buffer = MemoryForBuffer;
	__int8 i;
	*(Buffer) = 0x01;					// SOH
	*(Buffer + 3) = Command;			// Command
	*(Buffer + 4) = 0x02;				// STX
	for (i = 0; i < 6; i++) {
		*(Buffer + 5 +i) = *(price  + i);		// Price
		*(Buffer + 11+i) = *(volume + i);		// Volume
	}
	for (i = 0; i < 2; i++) {	
		*(Buffer + 1 +i) = *(TRK_No + i);		// TRK_No
		*(Buffer + 17+i) = *(status + i);		// Status
		*(Buffer + 19+i) = *(status + 2 + i);
		*(Buffer + 21+i) = *(error  + i);		// Error
		*(Buffer + 23+i) = *(code   + i);		// Code
	}
	*(Buffer + 25) =	0x03;
	*(Buffer + 26) =	0;				// ETX
	for ( i = 1; i < 26; i++) {			// CRC
		*(Buffer + 26) = *(Buffer + 26) ^ *(Buffer + i);		
	}
						
	return Buffer;
}

