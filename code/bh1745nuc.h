#ifndef _BH1745NUC_
#define _BH1745NUC_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int32_t bh1745nuc_init(void);

int32_t bh1745nuc_get_val(uint16_t * r, uint16_t * g, uint16_t * b, uint16_t * c);

#ifdef __cplusplus
}
#endif

#endif //_BH1745NUC_
