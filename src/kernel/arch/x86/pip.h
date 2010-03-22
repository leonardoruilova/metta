/*!
 * Public information page contains information publicly available to non-privileged domains.
 */
#include "processor_info.h"

struct public_info_page
{
    uint64_t            now;       /*! 0x00 Current time in ns. */
    uint64_t            alarm;     /*! 0x08 Alarm time in ns. */
    void              **pvs;       /*! 0x10 Pointer to current domain's pervasives record. */
    uint32_t            pvs_pad;   /*! 0x14 Pad to uint64_t */
    processor_info_t    processor; /*! Processor information               */
};

#define INFO_PAGE_ADDRESS 0x1000
#define INFO_PAGE (((public_info_page*)INFO_PAGE_ADDRESS)[0])
//TODO: SMP per-CPU accessors