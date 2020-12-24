#include "mem.h"

#ifndef SME_MEMORY_H
#define SME_MEMORY_H

#include "types.h"
#include "os.h"
#include "funcs.hxx"

namespace Memory
{
    inline void *malloc(const size_t size, const size_t alignment) { return __nw__FUli(size, alignment); }
    inline void *hmalloc(const JKRHeap *heap, const size_t size, const size_t alignment) { return __nw__FUlP7JKRHeapi(size, heap, alignment); }
    inline void *calloc(const size_t size, const size_t alignment) { return __nw__FUli(size, alignment); }
    inline void *hcalloc(const JKRHeap *heap, const size_t size, const size_t alignment) { return __nw__FUlP7JKRHeapi(size, heap, alignment); }
    inline void free(const void *ptr) { __dl__FPv(ptr); }

    namespace PPC
    {
        inline u32 *getBranchDest(u32 *bAddr)
        {
            s32 offset;
            if (*bAddr & 0x2000000)
                offset = (*bAddr & 0x3FFFFFD) - 0x4000000;
            else
                offset = *bAddr & 0x3FFFFFD;
            return (u32 *)((u32)bAddr + offset);
        }
    }
}

namespace Cache
{
    inline void flush(void *addr, size_t size)
    {
        DCFlushRange(addr, size);
        ICInvalidateRange(addr, size);
    }

    inline void flash()
    {
        ICFlashInvalidate();
    }

    inline void store(void *addr, size_t size)
    {
        DCStoreRange(addr, size);
        ICInvalidateRange(addr, size);
    }

    inline void zero(void *addr, size_t size)
    {
        DCZeroRange(addr, size);
    }

    inline void enable()
    {
        DCEnable();
        ICEnable();
    }

    inline void disable()
    {
        DCDisable();
        ICDisable();
    }
}

#endif


