/*
 * Copyright (c) 2018 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __STM32L5XX_CFG_H__
#define __STM32L5XX_CFG_H__
#include "main.h"
#include "platform/ext/common/uart_stdout.h"
#include "tfm_peripherals_def.h"

#define TFM_DRIVER_STDIO    TFM_Driver_USART0
#define NS_DRIVER_STDIO     TFM_Driver_USART0

/*
// <o>Floating Point Unit usage
//     <0=> Secure state only
//     <3=> Secure and Non-Secure state
//   <i> Value for SCB->NSACR register bits CP10, CP11
*/
#define SCB_NSACR_CP10_11_VAL       3

/*
// <o>Treat floating-point registers as Secure
//     <0=> Disabled
//     <1=> Enabled
//   <i> Value for FPU->FPCCR register bit TS
*/
#define FPU_FPCCR_TS_VAL            0

/*
// <o>Clear on return (CLRONRET) accessibility
//     <0=> Secure and Non-Secure state
//     <1=> Secure state only
//   <i> Value for FPU->FPCCR register bit CLRONRETS
*/
#define FPU_FPCCR_CLRONRETS_VAL     0

/*
// <o>Clear floating-point caller saved registers on exception return
//     <0=> Disabled
//     <1=> Enabled
//   <i> Value for FPU->FPCCR register bit CLRONRET
*/
#define FPU_FPCCR_CLRONRET_VAL      1

/**
  * \brief Defines the word offsets of Slave Peripheral Protection Controller
  *        Registers
  */
enum ppc_bank_e
{
  PPC_SP_DO_NOT_CONFIGURE = -1,
  PPC_SP_AHB_PPC0 = 0,
  PPC_SP_RES0,
  PPC_SP_RES1,
  PPC_SP_RES2,
  PPC_SP_AHB_PPC_EXP0,
  PPC_SP_AHB_PPC_EXP1,
  PPC_SP_AHB_PPC_EXP2,
  PPC_SP_AHB_PPC_EXP3,
  PPC_SP_APB_PPC0,
  PPC_SP_APB_PPC1,
  PPC_SP_RES3,
  PPC_SP_RES4,
  PPC_SP_APB_PPC_EXP0,
  PPC_SP_APB_PPC_EXP1,
  PPC_SP_APB_PPC_EXP2,
  PPC_SP_APB_PPC_EXP3,
};

/**
  * \brief Store the addresses of memory regions
  */
struct memory_region_limits
{
  uint32_t non_secure_code_start;
  uint32_t non_secure_partition_base;
  uint32_t non_secure_partition_limit;
  uint32_t veneer_base;
  uint32_t veneer_limit;
};

/**
  * \brief Holds the data necessary to do isolation for a specific peripheral.
  */
struct tfm_spm_partition_platform_data_t
{
  uint32_t periph_start;
  uint32_t periph_limit;
  int16_t periph_ppc_bank;
  int16_t periph_ppc_loc;
};

/**
  * \brief Configures the Memory Protection Controller.
  */
void mpc_init_cfg(void);

/**
  * \brief Configures the Peripheral Protection Controller.
  */
void ppc_init_cfg(void);

/**
  * \brief pin mux configuration for non secure access
  * */
void pinmux_conf_init_ns(void);

/**
  * \brief Restict access to peripheral to secure
  */
void ppc_configure_to_secure(enum ppc_bank_e bank, uint16_t loc);

/**
  * \brief Allow non-secure access to peripheral
  */
void ppc_configure_to_non_secure(enum ppc_bank_e bank, uint16_t loc);

/**
  * \brief Enable secure unprivileged access to peripheral
  */
void ppc_en_secure_unpriv(enum ppc_bank_e bank, uint16_t pos);

/**
  * \brief Clear secure unprivileged access to peripheral
  */
void ppc_clr_secure_unpriv(enum ppc_bank_e bank, uint16_t pos);

/**
  * \brief Clears PPC interrupt.
  */
void ppc_clear_irq(void);

/**
  * \brief Configures SAU and IDAU.
  */
void sau_and_idau_cfg(void);


#endif /* __STM32L5XX_CFG_H__ */