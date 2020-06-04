#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "tpm.h"
#include "tpm_types.h"
#include "gpio.h"
#include "gpio_types.h"
#include "i2c.h"
#include "i2c_types.h"
#include "mkl25_clock.h"
#include "mma8451q.h"

int main(void) {
	int16_t amostra = 0;

  	// Init board hardware.
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();

	board_clock_init();

	gpio_init(GPIO_PORTE);
	PORTE->PCR[24] = (PORTE->PCR[24] & ~(7 << 8)) | (5 << 8); // MUX PORTE24 SCL
	PORTE->PCR[25] = (PORTE->PCR[25] & ~(7 << 8)) | (5 << 8); // MUX PORTE25 SDA

	i2c_setup(I2C_MOD_I2C0, 0x1F);
	tpm_init(TPM_TPM0, TPM_PRS_128, 14999); // 800hz Timer
	mma8451q_setup(0x1D, MMA8451Q_RANGE_2G, I2C0);

	GETCHAR();
	PUTCHAR('\r');
	for(;;) {
		tpm_clear_flag(TPM0);

		amostra = mma8451q_read(MMA8451Q_AXIS_X);
		if (amostra < 0) {
			PUTCHAR('-');
		}
		PRINTF("%d\n\r", amostra);

		tpm_wait(TPM0);
	}

    return 0;
}
