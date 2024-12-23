#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <wincrypt.h>

#include "nanoid.h"

#ifdef _MSC_VER
# if _MSC_VER >= 1500

#  ifndef BCRYPT_SUCCESS
#   define BCRYPT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#  endif

#  define BCRYPT_USE_SYSTEM_PREFERRED_RNG 0x00000002
typedef NTSTATUS(WINAPI *BCryptGenRandomFn)(void *, PUCHAR, ULONG, ULONG);
#  define NANOIDGEN_ENABLE_BCRYPT
# endif
#endif

int getentropy(void *buffer, size_t length) {
	HCRYPTPROV hProv;

#ifdef NANOIDGEN_ENABLE_BCRYPT
	static BCryptGenRandomFn bcrypt_gen_random = NULL;
	static int bcrypt_checked = 0;

	// Check for bcrypt availability (only once). Supported by >=Vista.
	if (!bcrypt_checked) {
		HMODULE bcrypt_dll = LoadLibraryA("bcrypt.dll");
		if (bcrypt_dll) {
			bcrypt_gen_random =
				(void *)GetProcAddress(bcrypt_dll,
						"BCryptGenRandom");
		}
		bcrypt_checked = 1;
	}

	// Try bcrypt first
	if (bcrypt_gen_random) {
		NTSTATUS status = bcrypt_gen_random(NULL, (PUCHAR)buffer,
				(ULONG)length,
				BCRYPT_USE_SYSTEM_PREFERRED_RNG);
		if (BCRYPT_SUCCESS(status))
			return 0;
		else
			return -1;
	}
#endif

	// Fallback to Wincrypt. Supported by Windows 95.
	if (CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
		if (CryptGenRandom(hProv, (DWORD)length, (BYTE *)buffer)) {
			CryptReleaseContext(hProv, 0);
			return 0; // Success
		}
		CryptReleaseContext(hProv, 0);
	}

	return -1; // Failure
}

#ifdef __GNUC__
__attribute((externally_visible))
#endif
#ifdef __i686__
__attribute((force_align_arg_pointer))
#endif
int mainCRTStartup(void)
{
	char e[23];
	int r;

	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hc == NULL || hc == INVALID_HANDLE_VALUE) return 1;

	r = nanoid(e, 22, &getentropy);
	if(r != 0) return 1;

	e[22] = '\n';
	WriteConsoleA(hc, e, 23, NULL, NULL);

	return 0;
}
