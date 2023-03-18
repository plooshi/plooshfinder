#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "macho.h"

bool is_macho(void *buf) {
    uint32_t *buf_ptr = (uint32_t *) buf;
    uint32_t magic = buf_ptr[0];

    if (magic != 0xfeedfacf && magic != 0xcafebabe) {
        printf("Not a mach-o!\n");
        return false;
    }
    
    return true;
}

struct segment_command_64 *macho_get_segment(void *buf, char *name) {
    if (!is_macho(buf)) {
        return NULL;
    }

    struct load_command_64 *after_header = buf + sizeof(struct mach_header_64);
    struct mach_header_64 *header = buf;

    for (int i = 0; i < header->ncmds; i++) {
        if (after_header->cmd == LC_SEGMENT_64) {
            struct segment_command_64 *segment = (struct segment_command_64 *) after_header;

            if (strcmp(segment->segname, name) == 0) {
                return segment;
            }
        } else {
            break;
        }

        after_header = (struct load_command_64 *) ((char *) after_header + after_header->cmdsize);

        printf("next seg: 0x%lx\n", (uint64_t) after_header - (uint64_t) buf);
    }

    printf("unable to find segment\n");
    return NULL;
}

struct section_64 *macho_get_section(void *buf, struct segment_command_64 *segment, char *name) {
    if (!segment || !is_macho(buf)) {
        return NULL;
    }

    struct section_64 *section = (struct section_64 *)((char *)segment + sizeof(struct segment_command_64));

    for (int i = 0; i < segment->nsects; i++) {
        if (strcmp(section->sectname, name) == 0) {
            return section;
        }

        section = (struct section_64 *) ((char *) section + sizeof(struct section_64));
    }

    printf("unable to find section\n");
    return NULL;
}

struct section_64 *macho_find_section(void *buf, char *segment_name, char *section_name) {
    if (!is_macho(buf)) {
        return NULL;
    }

    struct segment_command_64 *segment = macho_get_segment(buf, segment_name);
    if (!segment) {
        return NULL;
    }

    struct section_64 *section = macho_get_section(buf, segment, section_name);
    if (!segment) {
        return NULL;
    }

    return section;
}