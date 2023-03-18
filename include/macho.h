#ifndef _MACHO_H
#define _MACHO_H
#include "macho-defs.h"

bool is_macho(void *buf);
struct segment_command_64 *macho_get_segment(void *buf, char *name);
struct section_64 *macho_get_section(void *buf, struct segment_command_64 *segment, char *name);
struct section_64 *macho_find_section(void *buf, char *segment_name, char *section_name);

#endif