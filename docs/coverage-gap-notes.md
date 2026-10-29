# 覆盖缺口三档分类报告

- 数据源：`/nfs/home/xiaokaiyuan/Project/HBL2-Test/tl-test-new-matrix/build_vcs/coverage/reports/final_11vdb`（urg 合并报告）
- 口径：按模块 mod 页的 Total/Covered 计数 × 层级页各实例百分比，得到每个实例的未覆盖量；与 session.xml 总分对账。
- 档位：结构性死区 / 需改配置 / 随机模式可达，另单列"插桩/外围"（TLLogger 等测试侧记录器，不属于 DUT 缓存逻辑）。

## 总览

| 指标 | session.xml | 按实例累计 | 差值 |
|---|---|---|---|
| Line | 10792/11896 | 10846/11896 | -54/+0 |
| Cond | 7255/9061 | 7237/9061 | +18/+0 |
| Toggle | 446763/725314 | 445988/725314 | +775/+0 |
| FSM | 6/24 | 6/24 | +0/+0 |

## 未覆盖量按档汇总

### Line 未覆盖量按档汇总

| 档 | 未覆盖量 | 占比 |
|---|---|---|
| 结构性死区（当前构建下不可达） | 0 | 0.0% |
| 需改配置（改 testbench/DUT 参数或端口拓扑，需与上游讨论） | 68 | 6.5% |
| 随机模式可达（FUZZ_ARI / FUZZ_STREAM 激励可打） | 395 | 37.6% |
| 插桩/外围（testbench instrumentation，非 DUT 缓存逻辑） | 587 | 55.9% |

### Cond 未覆盖量按档汇总

| 档 | 未覆盖量 | 占比 |
|---|---|---|
| 结构性死区（当前构建下不可达） | 0 | 0.0% |
| 需改配置（改 testbench/DUT 参数或端口拓扑，需与上游讨论） | 87 | 4.8% |
| 随机模式可达（FUZZ_ARI / FUZZ_STREAM 激励可打） | 1709 | 93.7% |
| 插桩/外围（testbench instrumentation，非 DUT 缓存逻辑） | 28 | 1.5% |

### Toggle 未覆盖量按档汇总

| 档 | 未覆盖量 | 占比 |
|---|---|---|
| 结构性死区（当前构建下不可达） | 832 | 0.3% |
| 需改配置（改 testbench/DUT 参数或端口拓扑，需与上游讨论） | 14248 | 5.1% |
| 随机模式可达（FUZZ_ARI / FUZZ_STREAM 激励可打） | 133522 | 47.8% |
| 插桩/外围（testbench instrumentation，非 DUT 缓存逻辑） | 130724 | 46.8% |

### FSM 未覆盖量按档汇总

| 档 | 未覆盖量 | 占比 |
|---|---|---|
| 结构性死区（当前构建下不可达） | 0 | 0.0% |
| 需改配置（改 testbench/DUT 参数或端口拓扑，需与上游讨论） | 0 | 0.0% |
| 随机模式可达（FUZZ_ARI / FUZZ_STREAM 激励可打） | 18 | 100.0% |
| 插桩/外围（testbench instrumentation，非 DUT 缓存逻辑） | 0 | 0.0% |

## Line 未覆盖量 Top40（按模块，实例累计）

| 模块 | 实例数 | Line 缺 | Cond 缺 | Toggle 缺 | FSM 缺 | 档 | 理由 | 主要实例 |
|---|---|---|---|---|---|---|---|---|
| TLLogger_3 | 1 | 471 | 0 | 62347 | 0 | tb | 同 TLLogger | logger_3 |
| MSHR_16 | 16 | 166 | 1257 | 9376 | 0 | fuzz | 同 MSHR | l3.slices_0.ms_15<br>l3.slices_0.ms_14<br>l3.slices_0.ms_13 |
| MSHR | 16 | 91 | 193 | 8103 | 0 | fuzz | MSHR 任务 FSM 的并发/参数分支组合 | l2.slices_0.mshrCtl.mshrs_15<br>l2.slices_0.mshrCtl.mshrs_11<br>l2.slices_0.mshrCtl.mshrs_12 |
| SinkA_1 | 1 | 50 | 79 | 11238 | 0 | config | l3.sinkA：未覆盖行主要是 CMO/自定义 hint 操作码；CFuzzer 的 CBO 只在 cmo 区间发，hint 无来源 | l3.slices_0.sinkA |
| SinkC_1 | 1 | 41 | 11 | 20610 | 0 | fuzz | 同 SinkC（另一实例侧） | l3.slices_0.sinkC |
| TLLogger | 1 | 41 | 0 | 8566 | 0 | tb | 端口事务记录器：未 fire 的通道/操作码分支 | logger |
| SinkC | 1 | 40 | 3 | 6538 | 0 | fuzz | C 通道 probeAck/Release 参数变体（TIP/Branch/Trunk、grow/shrink 组合），随机 grow/shrink 可枚举 | l2.slices_0.sinkC |
| TLLoggerM | 1 | 23 | 0 | 3426 | 0 | tb | M 通道记录器，本构建 M 通道从不 fire | logm |
| GrantBuffer | 1 | 20 | 19 | 1464 | 0 | fuzz | grant 合并/拆分路径需特定 acquire 参数组合 | l2.slices_0.grantBuf |
| TLLogger_1 | 1 | 20 | 0 | 5875 | 0 | tb | 同 TLLogger | logger_1 |
| TLLogger_2 | 1 | 20 | 0 | 4124 | 0 | tb | 同 TLLogger | logger_2 |
| SourceA | 1 | 18 | 7 | 1952 | 0 | config | l3.sourceA：未覆盖行含向内存发的 hint/prefetch 操作码，当前激励不生成 | l3.slices_0.sourceA |
| Slice_1 | 1 | 16 | 4 | 10702 | 8 | fuzz | 目录写状态机 FSM 迁移（N/S/M 态巡回） | l3.slices_0 |
| LatchFastArbiter_1 | 1 | 8 | 1 | 458 | 0 | fuzz | 仲裁竞争翻转分支 | l3.slices_0.sourceB_task_arb |
| TLLogWriter | 21 | 5 | 26 | 16276 | 0 | tb | ChiselDB 写出路径 | logger_1.b_writer.writer<br>logger_1.c_writer.writer<br>logger_2.b_writer.writer |
| Queue2_TLBundleD_1 | 3 | 3 | 0 | 3318 | 0 | fuzz | 随机并发/参数分支组合 | cork.q_1<br>cork.q<br>l3.slices_0.sinkD_io_d_q |
| MSHRBuffer | 2 | 3 | 24 | 1134 | 0 | fuzz | MSHR 相关并发/参数分支 | l2.slices_0.refillBuf<br>l2.slices_0.releaseBuf |
| Queue6_PutBufferBeatEntry | 1 | 3 | 4 | 1754 | 0 | fuzz | 随机并发/参数分支组合 | l3.slices_0.sourceD.pbQueue |
| SourceD | 1 | 2 | 35 | 2213 | 0 | fuzz | 写回 putBuffer 路径需驱逐压力下的脏块流 | l3.slices_0.sourceD |
| TLLogWriter_9 | 4 | 2 | 0 | 3099 | 0 | tb | ChiselDB 通道写出器，同 TLLogger 插桩 | logger_1.b_writer<br>logger_1.c_writer<br>logger_1.a_writer |
| TLLogWriter_17 | 4 | 2 | 0 | 2610 | 0 | tb | ChiselDB 通道写出器，同 TLLogger 插桩 | logger_2.b_writer<br>logger_2.c_writer<br>logger_2.d_writer |
| TLLogger_4 | 1 | 2 | 0 | 3608 | 0 | tb | 同 TLLogger | logger_4 |
| TLCacheCork | 1 | 1 | 6 | 2837 | 0 | fuzz | 随机并发/参数分支组合 | cork |
| Queue2_TLBundleB_1 | 1 | 1 | 0 | 668 | 0 | fuzz | B 通道队列深层 toggle：需 probe 并发 | l3.slices_0.sinkB_io_b_q |
| TLLogWriter_33 | 4 | 1 | 0 | 2516 | 0 | tb | ChiselDB 通道写出器，同 TLLogger 插桩 | logger_4.b_writer<br>logger_4.a_writer<br>logger_4.c_writer |
| TLXbar | 1 | 0 | 0 | 2658 | 0 | fuzz | 随机并发/参数分支组合 | L1_xbar |
| BankBinder | 1 | 0 | 0 | 2316 | 0 | fuzz | 随机并发/参数分支组合 | binder |
| BankBinder_1 | 1 | 0 | 0 | 1140 | 0 | fuzz | 随机并发/参数分支组合 | binder_1 |
| TLBuffer | 1 | 0 | 0 | 2336 | 0 | fuzz | 随机并发/参数分支组合 | buffer |
| Queue2_TLBundleB_2 | 1 | 0 | 0 | 1676 | 0 | fuzz | 随机并发/参数分支组合 | buffer.nodeIn_b_q |
| Queue2_TLBundleD_2 | 2 | 0 | 0 | 1224 | 0 | fuzz | 随机并发/参数分支组合 | buffer_1.nodeIn_d_q<br>buffer.nodeIn_d_q |
| Queue2_TLBundleA_2 | 1 | 0 | 0 | 1644 | 0 | fuzz | 随机并发/参数分支组合 | buffer.nodeOut_a_q |
| Queue2_TLBundleC_1 | 1 | 0 | 0 | 67 | 0 | fuzz | 随机并发/参数分支组合 | buffer.nodeOut_c_q |
| Queue2_TLBundleE_2 | 1 | 0 | 0 | 18 | 0 | fuzz | 随机并发/参数分支组合 | buffer.nodeOut_e_q |
| TLBuffer_1 | 1 | 0 | 0 | 1816 | 0 | fuzz | 随机并发/参数分支组合 | buffer_1 |
| Queue2_TLBundleA_3 | 1 | 0 | 0 | 1700 | 0 | fuzz | 随机并发/参数分支组合 | buffer_1.nodeOut_a_q |
| IDPool | 1 | 0 | 7 | 48 | 0 | fuzz | id 分配/释放交错时序 | cork.pool |
| TLFragmenter | 1 | 0 | 0 | 171 | 0 | fuzz | 随机并发/参数分支组合 | fragmenter |
| Repeater | 1 | 0 | 0 | 96 | 0 | fuzz | 随机并发/参数分支组合 | fragmenter.repeater |
| TL2TLCoupledL2 | 1 | 0 | 0 | 1188 | 0 | fuzz | 随机并发/参数分支组合 | l2 |

## Cond 未覆盖量 Top40（按模块，实例累计）

| 模块 | 实例数 | Line 缺 | Cond 缺 | Toggle 缺 | FSM 缺 | 档 | 理由 | 主要实例 |
|---|---|---|---|---|---|---|---|---|
| MSHR_16 | 16 | 166 | 1257 | 9376 | 0 | fuzz | 同 MSHR | l3.slices_0.ms_15<br>l3.slices_0.ms_14<br>l3.slices_0.ms_13 |
| MSHR | 16 | 91 | 193 | 8103 | 0 | fuzz | MSHR 任务 FSM 的并发/参数分支组合 | l2.slices_0.mshrCtl.mshrs_15<br>l2.slices_0.mshrCtl.mshrs_11<br>l2.slices_0.mshrCtl.mshrs_12 |
| DataStorage_1 | 1 | 0 | 89 | 4839 | 0 | fuzz | bank 部分写/掩码条件需非整块数据 | l3.slices_0.dataStorage |
| SinkA_1 | 1 | 50 | 79 | 11238 | 0 | config | l3.sinkA：未覆盖行主要是 CMO/自定义 hint 操作码；CFuzzer 的 CBO 只在 cmo 区间发，hint 无来源 | l3.slices_0.sinkA |
| SourceD | 1 | 2 | 35 | 2213 | 0 | fuzz | 写回 putBuffer 路径需驱逐压力下的脏块流 | l3.slices_0.sourceD |
| TLLogWriter | 21 | 5 | 26 | 16276 | 0 | tb | ChiselDB 写出路径 | logger_1.b_writer.writer<br>logger_1.c_writer.writer<br>logger_2.b_writer.writer |
| MSHRBuffer | 2 | 3 | 24 | 1134 | 0 | fuzz | MSHR 相关并发/参数分支 | l2.slices_0.refillBuf<br>l2.slices_0.releaseBuf |
| GrantBuffer | 1 | 20 | 19 | 1464 | 0 | fuzz | grant 合并/拆分路径需特定 acquire 参数组合 | l2.slices_0.grantBuf |
| array_3_ext | 4 | 0 | 12 | 0 | 0 | fuzz | SRAM 行为模型小 residue | l2.slices_0.dataStorage.array.array_0_0_0.array.array.array_ext<br>l2.slices_0.dataStorage.array.array_0_0_1.array.array.array_ext<br>l2.slices_0.dataStorage.array.array_0_0_2.array.array.array_ext |
| SinkC_1 | 1 | 41 | 11 | 20610 | 0 | fuzz | 同 SinkC（另一实例侧） | l3.slices_0.sinkC |
| Directory | 1 | 0 | 8 | 393 | 0 | fuzz | 目录读写竞争时序 | l2.slices_0.directory |
| array_0_0_ext | 8 | 0 | 8 | 0 | 0 | fuzz | SRAM 行为模型小 residue | l3.slices_0.dataStorage.bankedData_0.banks_0.array_0.array_0_ext<br>l3.slices_0.dataStorage.bankedData_1.banks_0.array_0.array_0_ext<br>l3.slices_0.dataStorage.bankedData_2.banks_0.array_0.array_0_ext |
| IDPool | 1 | 0 | 7 | 48 | 0 | fuzz | id 分配/释放交错时序 | cork.pool |
| SourceA | 1 | 18 | 7 | 1952 | 0 | config | l3.sourceA：未覆盖行含向内存发的 hint/prefetch 操作码，当前激励不生成 | l3.slices_0.sourceA |
| TLCacheCork | 1 | 1 | 6 | 2837 | 0 | fuzz | 随机并发/参数分支组合 | cork |
| Slice_1 | 1 | 16 | 4 | 10702 | 8 | fuzz | 目录写状态机 FSM 迁移（N/S/M 态巡回） | l3.slices_0 |
| SourceB_1 | 1 | 0 | 4 | 545 | 0 | fuzz | 同 SourceB | l3.slices_0.sourceB |
| Queue6_PutBufferBeatEntry | 1 | 3 | 4 | 1754 | 0 | fuzz | 随机并发/参数分支组合 | l3.slices_0.sourceD.pbQueue |
| MSHRCtl | 1 | 0 | 3 | 4804 | 0 | fuzz | MSHR 相关并发/参数分支 | l2.slices_0.mshrCtl |
| SinkC | 1 | 40 | 3 | 6538 | 0 | fuzz | C 通道 probeAck/Release 参数变体（TIP/Branch/Trunk、grow/shrink 组合），随机 grow/shrink 可枚举 | l2.slices_0.sinkC |
| RRArbiterInit | 1 | 0 | 3 | 2708 | 10 | fuzz | 仲裁轮转 FSM：迁移需持续竞争翻转 grant | l2.slices_0.sinkC.taskArb |
| array_ext | 2 | 0 | 2 | 0 | 0 | fuzz | SRAM 行为模型小 residue | l2.slices_0.directory.tagArray.array_0_0_0.array.array.array_ext<br>l2.slices_0.directory.tagArray.array_0_1_0.array.array.array_ext |
| Directory_Anon | 1 | 0 | 2 | 2 | 0 | fuzz | 随机并发/参数分支组合 | l3.slices_0.directory.selfDir |
| array_0_ext | 1 | 0 | 1 | 64 | 0 | fuzz | SRAM 行为模型小 residue | l2.slices_0.directory.metaArray.array.array.array_ext |
| array_2_ext | 1 | 0 | 1 | 0 | 0 | fuzz | SRAM 行为模型小 residue | l2.slices_0.directory.origin_bit_opt.array.array.array_ext |
| array_1_ext | 1 | 0 | 1 | 0 | 0 | fuzz | SRAM 行为模型小 residue | l2.slices_0.directory.replacer_sram_opt.array.array.array_ext |
| MainPipe | 1 | 0 | 1 | 1805 | 0 | fuzz | 主管线 cond 残留为并发时序组合 | l2.slices_0.mainPipe |
| L2MPWriter | 1 | 0 | 1 | 83 | 0 | tb | L2 matrix 写出路径，依赖 M 通道 | l2.slices_0.monitor.writer |
| RequestArb | 1 | 0 | 1 | 2318 | 0 | fuzz | 随机并发/参数分支组合 | l2.slices_0.reqArb |
| SubDirectory | 1 | 0 | 1 | 3 | 0 | fuzz | 随机并发/参数分支组合 | l3.slices_0.directory.clientDir |
| array_4_ext | 1 | 0 | 1 | 0 | 0 | fuzz | SRAM 行为模型小 residue | l3.slices_0.directory.clientDir.metaArray.array.array_ext |
| array_5_ext | 1 | 0 | 1 | 0 | 0 | fuzz | SRAM 行为模型小 residue | l3.slices_0.directory.clientDir.tagArray.array.array_ext |
| array_6_ext | 1 | 0 | 1 | 0 | 0 | fuzz | SRAM 行为模型小 residue | l3.slices_0.directory.selfDir.metaArray.array.array_ext |
| array_0_1_ext | 1 | 0 | 1 | 0 | 0 | fuzz | SRAM 行为模型小 residue | l3.slices_0.directory.selfDir.repl_state_replacer_sram.array_0.array_0_ext |
| array_7_ext | 1 | 0 | 1 | 0 | 0 | fuzz | SRAM 行为模型小 residue | l3.slices_0.directory.selfDir.tagArray.array.array_ext |
| Queue5_MSHRRequest | 1 | 0 | 1 | 254 | 0 | config | probeHelperOpt.queue：同 ProbeHelper，排队路径 只有 dir_conflict 才进 | l3.slices_0.probeHelperOpt.queue |
| RefillBuffer | 1 | 0 | 1 | 43 | 0 | fuzz | 随机并发/参数分支组合 | l3.slices_0.refillBuffer |
| LatchFastArbiter_1 | 1 | 8 | 1 | 458 | 0 | fuzz | 仲裁竞争翻转分支 | l3.slices_0.sourceB_task_arb |
| LatchFastArbiter_4 | 1 | 0 | 1 | 120 | 0 | fuzz | 仲裁竞争翻转分支 | l3.slices_0.sourceE_task_arb |
| TLRAM | 1 | 0 | 1 | 16 | 0 | fuzz | 随机并发/参数分支组合 | ram |

## Toggle 未覆盖量 Top40（按模块，实例累计）

| 模块 | 实例数 | Line 缺 | Cond 缺 | Toggle 缺 | FSM 缺 | 档 | 理由 | 主要实例 |
|---|---|---|---|---|---|---|---|---|
| TLLogger_3 | 1 | 471 | 0 | 62347 | 0 | tb | 同 TLLogger | logger_3 |
| SinkC_1 | 1 | 41 | 11 | 20610 | 0 | fuzz | 同 SinkC（另一实例侧） | l3.slices_0.sinkC |
| TLLogWriter | 21 | 5 | 26 | 16276 | 0 | tb | ChiselDB 写出路径 | logger_1.b_writer.writer<br>logger_1.c_writer.writer<br>logger_2.b_writer.writer |
| TestTop | 1 | 0 | 0 | 13292 | 0 | tb | 顶层组装模块，gap 为端口位翻转 | （层级表截断，按 union 缺口） |
| SinkA_1 | 1 | 50 | 79 | 11238 | 0 | config | l3.sinkA：未覆盖行主要是 CMO/自定义 hint 操作码；CFuzzer 的 CBO 只在 cmo 区间发，hint 无来源 | l3.slices_0.sinkA |
| Slice_1 | 1 | 16 | 4 | 10702 | 8 | fuzz | 目录写状态机 FSM 迁移（N/S/M 态巡回） | l3.slices_0 |
| MSHR_16 | 16 | 166 | 1257 | 9376 | 0 | fuzz | 同 MSHR | l3.slices_0.ms_15<br>l3.slices_0.ms_14<br>l3.slices_0.ms_13 |
| TLLogger | 1 | 41 | 0 | 8566 | 0 | tb | 端口事务记录器：未 fire 的通道/操作码分支 | logger |
| MSHR | 16 | 91 | 193 | 8103 | 0 | fuzz | MSHR 任务 FSM 的并发/参数分支组合 | l2.slices_0.mshrCtl.mshrs_15<br>l2.slices_0.mshrCtl.mshrs_11<br>l2.slices_0.mshrCtl.mshrs_12 |
| SinkC | 1 | 40 | 3 | 6538 | 0 | fuzz | C 通道 probeAck/Release 参数变体（TIP/Branch/Trunk、grow/shrink 组合），随机 grow/shrink 可枚举 | l2.slices_0.sinkC |
| TLLogger_1 | 1 | 20 | 0 | 5875 | 0 | tb | 同 TLLogger | logger_1 |
| Slice | 1 | 0 | 0 | 5591 | 0 | fuzz | 随机并发/参数分支组合 | l2.slices_0 |
| DataStorage_1 | 1 | 0 | 89 | 4839 | 0 | fuzz | bank 部分写/掩码条件需非整块数据 | l3.slices_0.dataStorage |
| MSHRCtl | 1 | 0 | 3 | 4804 | 0 | fuzz | MSHR 相关并发/参数分支 | l2.slices_0.mshrCtl |
| TLLogger_2 | 1 | 20 | 0 | 4124 | 0 | tb | 同 TLLogger | logger_2 |
| TLLogger_4 | 1 | 2 | 0 | 3608 | 0 | tb | 同 TLLogger | logger_4 |
| TLLoggerM | 1 | 23 | 0 | 3426 | 0 | tb | M 通道记录器，本构建 M 通道从不 fire | logm |
| Queue2_TLBundleD_1 | 3 | 3 | 0 | 3318 | 0 | fuzz | 随机并发/参数分支组合 | cork.q_1<br>cork.q<br>l3.slices_0.sinkD_io_d_q |
| TLLogWriter_9 | 4 | 2 | 0 | 3099 | 0 | tb | ChiselDB 通道写出器，同 TLLogger 插桩 | logger_1.b_writer<br>logger_1.c_writer<br>logger_1.a_writer |
| TLCacheCork | 1 | 1 | 6 | 2837 | 0 | fuzz | 随机并发/参数分支组合 | cork |
| RRArbiterInit | 1 | 0 | 3 | 2708 | 10 | fuzz | 仲裁轮转 FSM：迁移需持续竞争翻转 grant | l2.slices_0.sinkC.taskArb |
| TLXbar | 1 | 0 | 0 | 2658 | 0 | fuzz | 随机并发/参数分支组合 | L1_xbar |
| TLLogWriter_17 | 4 | 2 | 0 | 2610 | 0 | tb | ChiselDB 通道写出器，同 TLLogger 插桩 | logger_2.b_writer<br>logger_2.c_writer<br>logger_2.d_writer |
| TLLogWriter_33 | 4 | 1 | 0 | 2516 | 0 | tb | ChiselDB 通道写出器，同 TLLogger 插桩 | logger_4.b_writer<br>logger_4.a_writer<br>logger_4.c_writer |
| TLLogWriter_1 | 4 | 0 | 0 | 2454 | 0 | tb | ChiselDB 通道写出器，同 TLLogger 插桩 | logger.b_writer<br>logger.a_writer<br>logger.d_writer |
| TLLogWriter_25 | 4 | 0 | 0 | 2448 | 0 | tb | ChiselDB 通道写出器，同 TLLogger 插桩 | logger_3.b_writer<br>logger_3.a_writer<br>logger_3.c_writer |
| TLBuffer | 1 | 0 | 0 | 2336 | 0 | fuzz | 随机并发/参数分支组合 | buffer |
| RequestArb | 1 | 0 | 1 | 2318 | 0 | fuzz | 随机并发/参数分支组合 | l2.slices_0.reqArb |
| BankBinder | 1 | 0 | 0 | 2316 | 0 | fuzz | 随机并发/参数分支组合 | binder |
| SourceD | 1 | 2 | 35 | 2213 | 0 | fuzz | 写回 putBuffer 路径需驱逐压力下的脏块流 | l3.slices_0.sourceD |
| SourceA | 1 | 18 | 7 | 1952 | 0 | config | l3.sourceA：未覆盖行含向内存发的 hint/prefetch 操作码，当前激励不生成 | l3.slices_0.sourceA |
| TLBuffer_1 | 1 | 0 | 0 | 1816 | 0 | fuzz | 随机并发/参数分支组合 | buffer_1 |
| MainPipe | 1 | 0 | 1 | 1805 | 0 | fuzz | 主管线 cond 残留为并发时序组合 | l2.slices_0.mainPipe |
| Queue2_TLBundleA | 1 | 0 | 0 | 1776 | 0 | fuzz | 随机并发/参数分支组合 | l2.slices_0.io_out_a_q |
| FastArbiter_4 | 1 | 0 | 0 | 1756 | 0 | fuzz | 仲裁竞争翻转分支 | l2.slices_0.mshrCtl.mshr_task_arb |
| Queue6_PutBufferBeatEntry | 1 | 3 | 4 | 1754 | 0 | fuzz | 随机并发/参数分支组合 | l3.slices_0.sourceD.pbQueue |
| Queue2_TLBundleA_3 | 1 | 0 | 0 | 1700 | 0 | fuzz | 随机并发/参数分支组合 | buffer_1.nodeOut_a_q |
| Queue2_TLBundleB | 1 | 0 | 0 | 1684 | 0 | fuzz | 随机并发/参数分支组合 | l2.slices_0.sinkB_io_b_q |
| Queue2_TLBundleB_2 | 1 | 0 | 0 | 1676 | 0 | fuzz | 随机并发/参数分支组合 | buffer.nodeIn_b_q |
| Queue2_TLBundleA_2 | 1 | 0 | 0 | 1644 | 0 | fuzz | 随机并发/参数分支组合 | buffer.nodeOut_a_q |

## FSM 未覆盖量 Top40（按模块，实例累计）

| 模块 | 实例数 | Line 缺 | Cond 缺 | Toggle 缺 | FSM 缺 | 档 | 理由 | 主要实例 |
|---|---|---|---|---|---|---|---|---|
| RRArbiterInit | 1 | 0 | 3 | 2708 | 10 | fuzz | 仲裁轮转 FSM：迁移需持续竞争翻转 grant | l2.slices_0.sinkC.taskArb |
| Slice_1 | 1 | 16 | 4 | 10702 | 8 | fuzz | 目录写状态机 FSM 迁移（N/S/M 态巡回） | l3.slices_0 |
| TLXbar | 1 | 0 | 0 | 2658 | 0 | fuzz | 随机并发/参数分支组合 | L1_xbar |
| BankBinder | 1 | 0 | 0 | 2316 | 0 | fuzz | 随机并发/参数分支组合 | binder |
| BankBinder_1 | 1 | 0 | 0 | 1140 | 0 | fuzz | 随机并发/参数分支组合 | binder_1 |
| TLBuffer | 1 | 0 | 0 | 2336 | 0 | fuzz | 随机并发/参数分支组合 | buffer |
| Queue2_TLBundleB_2 | 1 | 0 | 0 | 1676 | 0 | fuzz | 随机并发/参数分支组合 | buffer.nodeIn_b_q |
| Queue2_TLBundleD_2 | 2 | 0 | 0 | 1224 | 0 | fuzz | 随机并发/参数分支组合 | buffer_1.nodeIn_d_q<br>buffer.nodeIn_d_q |
| Queue2_TLBundleA_2 | 1 | 0 | 0 | 1644 | 0 | fuzz | 随机并发/参数分支组合 | buffer.nodeOut_a_q |
| Queue2_TLBundleC_1 | 1 | 0 | 0 | 67 | 0 | fuzz | 随机并发/参数分支组合 | buffer.nodeOut_c_q |
| Queue2_TLBundleE_2 | 1 | 0 | 0 | 18 | 0 | fuzz | 随机并发/参数分支组合 | buffer.nodeOut_e_q |
| TLBuffer_1 | 1 | 0 | 0 | 1816 | 0 | fuzz | 随机并发/参数分支组合 | buffer_1 |
| Queue2_TLBundleA_3 | 1 | 0 | 0 | 1700 | 0 | fuzz | 随机并发/参数分支组合 | buffer_1.nodeOut_a_q |
| TLCacheCork | 1 | 1 | 6 | 2837 | 0 | fuzz | 随机并发/参数分支组合 | cork |
| IDPool | 1 | 0 | 7 | 48 | 0 | fuzz | id 分配/释放交错时序 | cork.pool |
| Queue2_TLBundleD_1 | 3 | 3 | 0 | 3318 | 0 | fuzz | 随机并发/参数分支组合 | cork.q_1<br>cork.q<br>l3.slices_0.sinkD_io_d_q |
| TLFragmenter | 1 | 0 | 0 | 171 | 0 | fuzz | 随机并发/参数分支组合 | fragmenter |
| Repeater | 1 | 0 | 0 | 96 | 0 | fuzz | 随机并发/参数分支组合 | fragmenter.repeater |
| TL2TLCoupledL2 | 1 | 0 | 0 | 1188 | 0 | fuzz | 随机并发/参数分支组合 | l2 |
| Arbiter1_L2ToL1Hint | 1 | 0 | 0 | 112 | 0 | config | L1 hint 通路，无激励来源 | l2.l1HintArb |
| Slice | 1 | 0 | 0 | 5591 | 0 | fuzz | 随机并发/参数分支组合 | l2.slices_0 |
| RequestBuffer | 1 | 0 | 0 | 1474 | 0 | fuzz | 随机并发/参数分支组合 | l2.slices_0.a_reqBuf |
| Queue1_ChosenQBundle | 1 | 0 | 0 | 608 | 0 | fuzz | 随机并发/参数分支组合 | l2.slices_0.a_reqBuf.chosenQ |
| FastArbiter | 1 | 0 | 0 | 322 | 0 | fuzz | 仲裁竞争翻转分支 | l2.slices_0.a_reqBuf.issueArb |
| DataStorage | 1 | 0 | 0 | 2 | 0 | fuzz | 随机并发/参数分支组合 | l2.slices_0.dataStorage |
| GatedSplittedSRAM | 1 | 0 | 0 | 2 | 0 | fuzz | SRAM 行为模型小 residue | l2.slices_0.dataStorage.array |
| ClockGate | 4 | 0 | 0 | 8 | 0 | fuzz | 随机并发/参数分支组合 | l2.slices_0.dataStorage.array.ClockGate<br>l2.slices_0.dataStorage.array.ClockGate_1<br>l2.slices_0.dataStorage.array.ClockGate_2 |
| array_3_ext | 4 | 0 | 12 | 0 | 0 | fuzz | SRAM 行为模型小 residue | l2.slices_0.dataStorage.array.array_0_0_0.array.array.array_ext<br>l2.slices_0.dataStorage.array.array_0_0_1.array.array.array_ext<br>l2.slices_0.dataStorage.array.array_0_0_2.array.array.array_ext |
| Directory | 1 | 0 | 8 | 393 | 0 | fuzz | 目录读写竞争时序 | l2.slices_0.directory |
| SRAMTemplate_2 | 1 | 0 | 0 | 95 | 0 | fuzz | SRAM 行为模型小 residue | l2.slices_0.directory.metaArray |
| sram_array_1p64x72m9s1h0l1_l2_meta | 1 | 0 | 0 | 65 | 0 | fuzz | 随机并发/参数分支组合 | l2.slices_0.directory.metaArray.array |
| array_0 | 1 | 0 | 0 | 63 | 0 | fuzz | SRAM 行为模型小 residue | l2.slices_0.directory.metaArray.array.array |
| array_0_ext | 1 | 0 | 1 | 64 | 0 | fuzz | SRAM 行为模型小 residue | l2.slices_0.directory.metaArray.array.array.array_ext |
| array_2_ext | 1 | 0 | 1 | 0 | 0 | fuzz | SRAM 行为模型小 residue | l2.slices_0.directory.origin_bit_opt.array.array.array_ext |

## FUZZ 验收目标模块清单

FUZZ_ARI / FUZZ_STREAM 首轮的观察对象：fuzz 档模块按 Line+Cond 未覆盖量排序（纯 toggle 小残留已略去），跑完后对照本表逐模块核对增量。

| 模块 | Line 缺 | Cond 缺 | Toggle 缺 | FSM 缺 | 理由 |
|---|---|---|---|---|---|
| MSHR_16 | 166 | 1257 | 9376 | 0 | 同 MSHR |
| MSHR | 91 | 193 | 8103 | 0 | MSHR 任务 FSM 的并发/参数分支组合 |
| DataStorage_1 | 0 | 89 | 4839 | 0 | bank 部分写/掩码条件需非整块数据 |
| SinkC_1 | 41 | 11 | 20610 | 0 | 同 SinkC（另一实例侧） |
| SinkC | 40 | 3 | 6538 | 0 | C 通道 probeAck/Release 参数变体（TIP/Branch/Trunk、grow/shrink 组合），随机 grow/shrink 可枚举 |
| GrantBuffer | 20 | 19 | 1464 | 0 | grant 合并/拆分路径需特定 acquire 参数组合 |
| SourceD | 2 | 35 | 2213 | 0 | 写回 putBuffer 路径需驱逐压力下的脏块流 |
| MSHRBuffer | 3 | 24 | 1134 | 0 | MSHR 相关并发/参数分支 |
| Slice_1 | 16 | 4 | 10702 | 8 | 目录写状态机 FSM 迁移（N/S/M 态巡回） |
| array_3_ext | 0 | 12 | 0 | 0 | SRAM 行为模型小 residue |
| LatchFastArbiter_1 | 8 | 1 | 458 | 0 | 仲裁竞争翻转分支 |
| Directory | 0 | 8 | 393 | 0 | 目录读写竞争时序 |
| array_0_0_ext | 0 | 8 | 0 | 0 | SRAM 行为模型小 residue |
| TLCacheCork | 1 | 6 | 2837 | 0 | 随机并发/参数分支组合 |
| IDPool | 0 | 7 | 48 | 0 | id 分配/释放交错时序 |
| Queue6_PutBufferBeatEntry | 3 | 4 | 1754 | 0 | 随机并发/参数分支组合 |
| SourceB_1 | 0 | 4 | 545 | 0 | 同 SourceB |
| Queue2_TLBundleD_1 | 3 | 0 | 3318 | 0 | 随机并发/参数分支组合 |
| MSHRCtl | 0 | 3 | 4804 | 0 | MSHR 相关并发/参数分支 |
| RRArbiterInit | 0 | 3 | 2708 | 10 | 仲裁轮转 FSM：迁移需持续竞争翻转 grant |
| array_ext | 0 | 2 | 0 | 0 | SRAM 行为模型小 residue |
| Directory_Anon | 0 | 2 | 2 | 0 | 随机并发/参数分支组合 |
| array_0_ext | 0 | 1 | 64 | 0 | SRAM 行为模型小 residue |
| array_2_ext | 0 | 1 | 0 | 0 | SRAM 行为模型小 residue |
| array_1_ext | 0 | 1 | 0 | 0 | SRAM 行为模型小 residue |
| MainPipe | 0 | 1 | 1805 | 0 | 主管线 cond 残留为并发时序组合 |
| RequestArb | 0 | 1 | 2318 | 0 | 随机并发/参数分支组合 |
| SubDirectory | 0 | 1 | 3 | 0 | 随机并发/参数分支组合 |
| array_4_ext | 0 | 1 | 0 | 0 | SRAM 行为模型小 residue |
| array_5_ext | 0 | 1 | 0 | 0 | SRAM 行为模型小 residue |
| array_6_ext | 0 | 1 | 0 | 0 | SRAM 行为模型小 residue |
| array_0_1_ext | 0 | 1 | 0 | 0 | SRAM 行为模型小 residue |
| array_7_ext | 0 | 1 | 0 | 0 | SRAM 行为模型小 residue |
| RefillBuffer | 0 | 1 | 43 | 0 | 随机并发/参数分支组合 |
| Queue2_TLBundleB_1 | 1 | 0 | 668 | 0 | B 通道队列深层 toggle：需 probe 并发 |
| LatchFastArbiter_4 | 0 | 1 | 120 | 0 | 仲裁竞争翻转分支 |
| TLRAM | 0 | 1 | 16 | 0 | 随机并发/参数分支组合 |
| TLXbar | 0 | 0 | 2658 | 0 | 随机并发/参数分支组合 |
| BankBinder | 0 | 0 | 2316 | 0 | 随机并发/参数分支组合 |
| BankBinder_1 | 0 | 0 | 1140 | 0 | 随机并发/参数分支组合 |
| TLBuffer | 0 | 0 | 2336 | 0 | 随机并发/参数分支组合 |
| Queue2_TLBundleB_2 | 0 | 0 | 1676 | 0 | 随机并发/参数分支组合 |
| Queue2_TLBundleD_2 | 0 | 0 | 1224 | 0 | 随机并发/参数分支组合 |
| Queue2_TLBundleA_2 | 0 | 0 | 1644 | 0 | 随机并发/参数分支组合 |
| TLBuffer_1 | 0 | 0 | 1816 | 0 | 随机并发/参数分支组合 |
| Queue2_TLBundleA_3 | 0 | 0 | 1700 | 0 | 随机并发/参数分支组合 |
| TL2TLCoupledL2 | 0 | 0 | 1188 | 0 | 随机并发/参数分支组合 |
| Slice | 0 | 0 | 5591 | 0 | 随机并发/参数分支组合 |
| RequestBuffer | 0 | 0 | 1474 | 0 | 随机并发/参数分支组合 |
| Queue2_TLBundleA | 0 | 0 | 1776 | 0 | 随机并发/参数分支组合 |
| Arbiter3_1_Anon | 0 | 0 | 1344 | 0 | 仲裁竞争翻转分支 |
| FastArbiter_4 | 0 | 0 | 1756 | 0 | 仲裁竞争翻转分支 |
| SourceB | 0 | 0 | 1187 | 0 | probe 发射：hit/miss × 脏净 × TIP/Trunk/Branch 组合 |
| Queue2_TLBundleB | 0 | 0 | 1684 | 0 | 随机并发/参数分支组合 |
| HuanCun | 0 | 0 | 1464 | 0 | 随机并发/参数分支组合 |
| Queue2_TLBundleA_1 | 0 | 0 | 1602 | 0 | 随机并发/参数分支组合 |
| MSHRAlloc | 0 | 0 | 1090 | 0 | MSHR 相关并发/参数分支 |
| TLClientsMerger | 0 | 0 | 1132 | 0 | 随机并发/参数分支组合 |

## 结论

- **Line**：总缺口 1050，其中插桩 587（56%），单 TLLogger_3（L3 出口 256-bit 记录器，未 fire 通道/操作码的记录分支）一家占 471。
- **Cond**：总缺口 1824，其中插桩 28（2%）。
- **Toggle**：总缺口 279326，其中插桩 130724（47%），单 TLLogger_3（L3 出口 256-bit 记录器，未 fire 通道/操作码的记录分支）一家占 62347。

若把 TLLogger/TLLogWriter/mem_ext 等插桩从 `hbl2_coverage.hier` 排除，等效口径（DUT 缓存逻辑）覆盖率为：

| 指标 | 全口径（当前） | 排除插桩后 |
|---|---|---|
| Line | 90.72% (10792/11896) | 95.01% (9854/10371) |
| Cond | 80.07% (7255/9061) | 80.21% (7208/8986) |
| Toggle | 61.60% (446763/725314) | 72.37% (387109/534936) |

排除插桩属于报告口径调整，不影响仿真本身；是否改 `hbl2_coverage.hier` 建议与上游确认。

## 档位说明

- **结构性死区**：当前 testbench/DUT 构建下激励在拓扑上到不了（如 L3 上游不发 probe、M 通道未启用）。换激励方式无解，要么接受、要么改构建。
- **需改配置**：路径本身存在，但被参数锁死（clientDir 容量、端口通道、hint 激励来源）。涉及 testbench/DUT 配置，需先与上游（陈熙）讨论再动。
- **随机模式可达**：trace 回放表达不了（单发顺序、64B 整块）但随机激励可以：并发时序、参数组合、CMO、非整块数据等。这是 FUZZ 首轮的验收范围。
- **插桩/外围**：TLLogger/mem_ext 等测试侧组件，gap 不反映缓存逻辑质量，可考虑后续用 cm_hier 排除。
