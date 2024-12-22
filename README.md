# Nano ID for C

<img src="logo-small.svg" align="right" alt="Logo" width="180" height="94">

Tiny, secure, URL-friendly unique string ID generator for C.

- **Small** file size. Header-only. Depends only on libc.
- **Safe.** Uses [`getentropy(3)`][], a modern, reliable, secure randomness source.
- **Short IDs.** While UUIDs are 36 chars, similarly unique Nano IDs are just 21 due to the larger alphabet.
- **Portable.** Nano ID has been ported to 20+ programming languages.

```c
#include <nanoid.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  size_t length = 21;
  char id[22];
  if (nanoid(id, length)) {
    perror("nanoid");
    return EXIT_FAILURE;
  }
  puts(id);
  return EXIT_SUCCESS;
}
```

```
$ cc main.c -o example
$ ./example
V1StGXR8_Z5jdHi6B-myT
```

## Overview

Works out of the box on Linux, Android, macOS, iOS, FreeBSD, NetBSD, OpenBSD,
Illumos, Fuchsia, and WASI. Windows support requires a [`getentropy(3)`][] shim
which is provided in the example program `nanoidgen`.

## Documentation

- function `int nanoid(char *e, size_t t)`
  
  Generates a Nano ID of the given length `t` ≤256 and stores it in `e`.

  Returns 0 on success. On error, -1 is returned, and errno is set to indicate
  the error.

[`getentropy(3)`]: https://man7.org/linux/man-pages/man3/getentropy.3.html

## Attribution

Port of [Nano ID](https://github.com/ai/nanoid) by [Andrey Sitnik](https://sitnik.ru).

Original logo by [Anton Lovchikov](https://github.com/antiflasher).

Social preview background texture by [Tuomo](https://x.com/tuomodesign).

Social preview logo assistance by [Tanya Nevskaya](https://github.com/unparalloser).
