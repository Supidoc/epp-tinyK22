/*
 * Copyright (c) 2026, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

 #ifndef TRIGGER_H__
 #define TRIGGER_H__

void Trigger_Assert(void);
void Trigger_Deassert(void);

void Trigger_Deinit(void);
void Trigger_Init(void);

 #endif /* TRIGGER_H__ */