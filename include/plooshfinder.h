#ifndef _PLOOSHFINDER_H
#define _PLOOSHFINDER_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

void pf_find_maskmatch32(void *buf, size_t size, uint32_t matches[], uint32_t masks[], uint32_t count, bool (*callback)(void* stream));
void pf_find_maskmatch64(void *buf, size_t size, uint64_t matches[], uint64_t masks[], uint32_t count, bool (*callback)(void* stream));
uint32_t *pf_find_next(uint32_t *stream, uint32_t count, uint32_t match, uint32_t mask);
uint32_t *pf_find_prev(uint32_t *stream, uint32_t count, uint32_t match, uint32_t mask);
int32_t pf_signextend_32(int32_t val, uint8_t bits);
int64_t pf_signextend_64(int64_t val, uint8_t bits);
uint32_t *pf_follow_branch(uint32_t *insn);
int64_t pf_adrp_offset(uint32_t adrp);
void *pf_follow_xref(uint32_t *stream);

#endif
