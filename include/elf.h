#ifndef _ELF_H
#define _ELF_H
#include <stdbool.h>
#include "elf_defs.h"

bool is_elf(void *buf);
struct elf_sheader_64 *elf_get_section(void *buf, char *name);

#endif