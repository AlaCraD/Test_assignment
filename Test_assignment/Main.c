#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "ISKRA_Buff.h"


int main() {
	char mass[23];
	void* buff = (__int8*)malloc(23);
	__int8	TRK_No = 12,
			Command = 5,
			error = 34,
			code = 65;
	__int32 price = 123456,
			volume = 987654;
	__int8 df = ISKRABuffAssemble(buff, TRK_No, Command, price, volume, error, code);
	int count = 0;
	while (count < 23) {
		printf("%c ", *((__int8*)buff + (int)count));
		count++;
		
	}
	return 0;
}