/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This module manage the Timer/PWM Module
 ************************************************/
#ifndef TPM_H
#define TPM_H

#include <string.h>
#include "mkl25_registers.h"
#include "tpm_types.h"

tpm_err_t tpm_init(tpm_t tpm, tpm_prs_t prescaler, uint16_t max_val);
void tpm_set_val(TPM_p tpm_ptr, uint16_t val);
void tpm_clear_flag(TPM_p tpm_ptr);
void tpm_wait(TPM_p tpm_ptr);

#endif /* TPM_H */
