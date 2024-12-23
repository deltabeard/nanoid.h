#include "nanoid.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#ifdef _WIN32
int getentropy(void *buffer, size_t length);
#else
#include <unistd.h>
#endif

int main(int argc, char *argv[]) {
  size_t length = 21;
  char id[257];

  if (argc == 2) {
    length = strtoul(argv[1], NULL, 10);

    if (length < 1 || length > 256) {
      fprintf(stderr, "Length %s not within 1...256\n", argv[1]);
      goto usage;
    }
  } else if (argc > 2) {
    fprintf(stderr, "Expected no more than 1 argument, got %d\n", argc - 1);
  usage:
    fprintf(stderr, "Usage: %s [length]\n", argv[0]);
    return 64;
  }

  /* Compensate for nul terminator. */
  length++;

  if (nanoid(id, length, &getentropy)) {
    perror(argv[0]);
    return EXIT_FAILURE;
  }

  puts(id);
  return EXIT_SUCCESS;
}

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <bcrypt.h>
#include <errno.h>

int getentropy(void *buffer, size_t length) {
    NTSTATUS status = BCryptGenRandom(NULL, buffer, (ULONG)length, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    if (!BCRYPT_SUCCESS(status)) {
        errno = EIO;
        return -1;
    }
    return 0;
}
#endif
