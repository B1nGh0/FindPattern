#include <windows.h>
#include <stdio.h>

uintptr_t FindPattern(uintptr_t start, size_t size, const unsigned char *pattern, const char *mask)
{
	uintptr_t i, j;
	size_t len;
	unsigned char fnd = 0;

	if(!size || !pattern || !mask) return 0;
	if(!(len = strlen(mask)) || len > size) return 0;

	for(i = 0; !fnd && i <= size - len; i++)
		for(fnd = 1, j = 0; fnd && j < len; j++)
			fnd &= mask[j] == '?' || pattern[j] == ((unsigned char*)start)[i + j];

	return fnd ? start + i - 1 : 0;
}

void test(void)
{
	uintptr_t Base = (uintptr_t)GetModuleHandle(NULL);
	PIMAGE_DOS_HEADER Dos = (PIMAGE_DOS_HEADER)Base;
	PIMAGE_NT_HEADERS Nt = (PIMAGE_NT_HEADERS)(Base + Dos->e_lfanew);
	printf("%s: 0x%p\n", "Found", (void*)FindPattern(Base, Nt->OptionalHeader.SizeOfImage, (unsigned char *)"Found", "xxxxx"));
}

int main(void)
{
	test();
	return 0;
}
