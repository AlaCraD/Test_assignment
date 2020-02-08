#include "ISKRA_Buff.h"

void* ISKRABuffAssemble(void* MemoryForBuffer, __int8* TRK_No, __int8 Command, __int8* price, __int8* volume, __int8* error, __int8* code) {
	//__int8* MemoryForBuffer = MemoryForBuffer;
	__int8 i;
	*((__int8*) MemoryForBuffer) = 0x01;					// SOH
	*(((__int8*)MemoryForBuffer) + 3) = Command;				// Command
	*(((__int8*)MemoryForBuffer) + 4) = 0x02;				// STX
	for (i = 0; i < 6; i++) {
		*(((__int8*)MemoryForBuffer) + 5 +i) = *(price  + i);		// Price
		*(((__int8*)MemoryForBuffer) + 11+i) = *(volume + i);		// Volume
	}
	for (i = 0; i < 2; i++) {	
		*(((__int8*)MemoryForBuffer) + 1 +i) = *(TRK_No + i);		// TRK_No
		*(((__int8*)MemoryForBuffer) + 17+i) = *(error  + i);		// Error
		*(((__int8*)MemoryForBuffer) + 19+i) = *(code   + i);		// Code
	}
	*(((__int8*)MemoryForBuffer) + 21) =	0x03;
	*(((__int8*)MemoryForBuffer) + 22) =	0;				// ETX
	for ( i = 1; i < 22; i++) {			// CRC
		*(((__int8*)MemoryForBuffer) + 22) = *(((__int8*)MemoryForBuffer) + 22) ^ *(((__int8*)MemoryForBuffer) + i);
	}
	
	return MemoryForBuffer;
}

