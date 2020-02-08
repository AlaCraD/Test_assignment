#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "ISKRA_Buff.h"


int main() {
	char mass[27];
	void* buff = (__int8*)malloc(27);
	__int8	TRK_No[2] = {'1','2'},
			Command = '5',
			price[6] = { 'p','r','i','c','e','!' },
			volume[6] = {'v','o','l','u','m','e'},
			status[4] = {'s','t','u','s'},
			error[2] = {'r','r'},
			code[2] = {'c','d'};
	__int8* df = ISKRABuffAssemble(buff, TRK_No, Command, price, volume, error, code);
	int count = 0;
	while (count < 27) {
		printf("%c ", *((__int8*)buff + (int)count));
		count++;
		
	}
	return 0;
}