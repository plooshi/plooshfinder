#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "elf.h"
#include "elf_defs.h"

bool is_elf(void *buf) {
    struct elf_header_64 *hdr = (struct elf_header_64 *) buf;
    char elf_magic[5] = { 0x7f, 'E', 'L', 'F' };

    if (strncmp(hdr->ident.signature, elf_magic, 4) == 0) {
        return true;
    } else {
        printf("%s: Not an ELF!\n", __FUNCTION__);
    }

    return false;
}

struct elf_sheader_64 *elf_get_section(void *buf, char *name) {
    if (!is_elf(buf)) {
        return NULL;
    }

    struct elf_header_64 *hdr = (struct elf_header_64 *) buf;
    struct elf_sheader_64 *section_hdr = buf + hdr->sh_off;

    struct elf_sheader_64 *sname_hdr = section_hdr + hdr->sect_table_ind;
    void *sname_tbl = buf + sname_hdr->offset;
    

    for (uint16_t i = 0; i < hdr->sh_count; i++) {
        struct elf_sheader_64 *section = section_hdr + i;
        char *sect_name = sname_tbl + section->name_off;
        
        if (strcmp(sect_name, name) == 0) {
            return section;
        }
    }

    printf("%s: Unable to find section %s!\n", __FUNCTION__, name);
    return NULL;
}