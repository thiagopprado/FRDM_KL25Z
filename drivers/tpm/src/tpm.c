#include "tpm.h"
#include "tpm-defs.h"

tpm_err_t tpm_init(tpm_t tpm, tpm_prs_t prescaler, uint16_t max_val) {
    TPM_p tpm_ptr = NULL;

    if (tpm >= TPM_INVALID || prescaler >= TPM_PRS_INVALID) {
        return TPM_ERR_INVALID_ARGS;
    }

    switch (tpm) {
        case TPM_TPM0:
	        SIM->SCGC6 |= SGC6_TPM0_POS; // Clock gate TPM0
            tpm_ptr = TPM0;
        break;
        case TPM_TPM1:
	        SIM->SCGC6 |= SGC6_TPM1_POS; // Clock gate TPM1
            tpm_ptr = TPM1;
        break;
        case TPM_TPM2:
	        SIM->SCGC6 |= SGC6_TPM2_POS; // Clock gate TPM2
            tpm_ptr = TPM2;
        break;
        default:
            return TPM_ERR_INVALID_TPM;
    }

	SIM->SOPT2 = (SIM->SOPT2 & ~SOPT2_TPM_SRC) | SOPT2_TPM_MCGPLL; // TPM clock source

    tpm_ptr->CNT = 0;
	tpm_ptr->MOD = max_val; // f = 48Mhz / (MOD + 1)

	tpm_ptr->SC |= prescaler; // Prescaler
	tpm_ptr->SC = (tpm_ptr->SC & ~TPM_SC_CMOD) | TPM_SC_CMOD_CNT; // CMOD
    
    return TPM_ERR_NO_ERROR;
}

void tpm_set_val(TPM_p tpm_ptr, uint16_t val) {
    tpm_ptr->CNT = 0;
	tpm_ptr->MOD = val;
    tpm_ptr->SC |= TPM_SC_OVERFLOW_FLG; // Clear Overflow flag
}

inline void tpm_clear_flag(TPM_p tpm_ptr) {
    tpm_ptr->SC |= TPM_SC_OVERFLOW_FLG;
}

inline void tpm_wait(TPM_p tpm_ptr) {
    while(!(tpm_ptr->SC & TPM_SC_OVERFLOW_FLG));
}
