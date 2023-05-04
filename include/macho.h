#ifndef _MACHO_H
#define _MACHO_H
#include "macho_defs.h"

uint32_t macho_get_magic(void *buf);
void *macho_find_arch(void *buf, uint32_t arch);
uint32_t macho_get_platform(void *buf);
struct segment_command_64 *macho_get_segment(void *buf, char *name);
struct section_64 *macho_get_section(void *buf, struct segment_command_64 *segment, char *name);
struct section_64 *macho_get_last_section(struct segment_command_64 *segment);
struct section_64 *macho_find_section(void *buf, char *segment_name, char *section_name);
struct segment_command_64 *macho_get_segment_for_va(void *buf, uint64_t addr);
struct section_64 *macho_get_section_for_va(struct segment_command_64 *segment, uint64_t addr);
struct section_64 *macho_find_section_for_va(void *buf, uint64_t addr);
void *macho_va_to_ptr(void *buf, uint64_t addr);
struct nlist_64 *macho_find_symbol(void *buf, char *name);
uint64_t macho_get_symbol_size(struct nlist_64 *symbol);

#endif