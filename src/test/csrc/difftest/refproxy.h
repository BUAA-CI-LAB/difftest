/***************************************************************************************
* Copyright (c) 2020-2021 Institute of Computing Technology, Chinese Academy of Sciences
* Copyright (c) 2020-2021 Peng Cheng Laboratory
*
* XiangShan is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#ifndef __NEMU_PROXY_H
#define __NEMU_PROXY_H

#include <unistd.h>
#include <dlfcn.h>

#include "common.h"

class RefProxy {
public:
  // public callable functions
  void (*memcpy)(paddr_t nemu_addr, void* dut_buf, size_t n, bool direction);
  void (*regcpy)(void* dut, bool direction, bool do_csr);
  void (*csrcpy)(void* dut, bool direction);
  void (*uarchstatus_cpy)(void* dut, bool direction);
  int (*store_commit)(uint64_t saddr, uint64_t sdata);
  void (*exec)(uint64_t n);
  vaddr_t (*guided_exec)(void* disambiguate_para);
  void (*raise_intr)(uint64_t no);
  void (*isa_reg_display)();
  void (*tlbfill_index_set)(uint32_t index);
  void (*timercpy)(void* dut);
  void (*estat_sync)(uint32_t index, uint32_t mask);
  int  (*check_end)();
  void (*tlbcpy)(uint32_t index, void *dut); // copy specified tlb entry from nemu to difftest
  void (*tlbcpy_to_nemu)(uint32_t index, void *dut); // copy specified tlb entry from difftest to nemu
};

#define NEMU_ENV_VARIABLE "NEMU_HOME"
#define NEMU_SO_FILENAME  "build/la32r-nemu-interpreter-so"
class NemuProxy : public RefProxy {
public:
  NemuProxy(int coreid);
private:
};

#define SPIKE_ENV_VARIABLE "SPIKE_HOME"
#define SPIKE_SO_FILENAME  "difftest/build/riscv64-spike-so"
// class SpikeProxy : public RefProxy {
// public:
//   SpikeProxy(int coreid);
// private:
// };

struct SyncState {
  uint64_t lrscValid;
  uint64_t lrscAddr;
};

struct ExecutionGuide {
  // force raise exception
  bool force_raise_exception;
  uint64_t exception_num;
  uint64_t mtval;
  uint64_t stval;
  // force set jump target
  bool force_set_jump_target;
  uint64_t jump_target;
};

typedef struct DynamicConfig {
  bool ignore_illegal_mem_access = false;
  bool debug_difftest = false;
} DynamicSimulatorConfig;

void ref_misc_put_gmaddr(uint8_t* ptr);

#endif