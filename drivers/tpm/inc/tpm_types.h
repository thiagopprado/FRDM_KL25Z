/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This file maps the MKL25 registers
 ************************************************/
#ifndef TPM_TYPES_H
#define TPM_TYPES_H

typedef enum {
    TPM_ERR_NO_ERROR = 0,
    TPM_ERR_INVALID_ARGS,    
    TPM_ERR_INVALID_TPM,
} tpm_err_t;

typedef enum {
    TPM_TPM0 = 0,
    TPM_TPM1,    
    TPM_TPM2,
    TPM_INVALID,
} tpm_t;

typedef enum {
    TPM_PRS_1 = 0,
    TPM_PRS_2,    
    TPM_PRS_4,
    TPM_PRS_8,
    TPM_PRS_16,
    TPM_PRS_32,
    TPM_PRS_64,
    TPM_PRS_128,
    TPM_PRS_INVALID,
} tpm_prs_t;

#endif /* TPM_TYPES_H */