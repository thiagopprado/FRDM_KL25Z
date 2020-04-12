/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This file maps the MKL25 registers
 ************************************************/
#ifndef TPM_DEFS_H
#define TPM_DEFS_H

#define SGC6_TPM0_POS       (1 << 24)
#define SGC6_TPM1_POS       (1 << 25)
#define SGC6_TPM2_POS       (1 << 26)

#define SOPT2_TPM_SRC       (3 << 24)
#define SOPT2_TPM_MCGPLL    (1 << 24)

#define TPM_SC_CMOD         (3 << 3)
#define TPM_SC_CMOD_CNT     (1 << 3)
#define TPM_SC_OVERFLOW_FLG (1 << 7)

#endif /* TPM_DEFS_H */