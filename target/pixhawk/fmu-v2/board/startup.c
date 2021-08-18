/******************************************************************************
 * Copyright 2020-2021 The Firmament Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include <bsp.h>
#include <firmament.h>
#ifdef FMT_USING_CM_BACKTRACE
#include <cm_backtrace.h>
#endif

#include "module/task_manager/task_manager.h"

static rt_thread_t tid0;

void assert_failed(uint8_t* file, uint32_t line)
{
    rt_hw_interrupt_disable();

#ifdef FMT_USING_CM_BACKTRACE
    cm_backtrace_assert(cmb_get_sp());
#endif
    while (1)
        ;
}

static void assert_hook(const char* ex, const char* func, rt_size_t line)
{
    console_printf("(%s) assertion failed at function:%s, line number:%d \n", ex, func, line);

    assert_failed((uint8_t*)func, (uint32_t)line);
}

static void rt_init_thread_entry(void* parameter)
{
    rt_assert_set_hook(assert_hook);

#if defined(RT_USING_CPLUSPLUS)
    /* c++ component initialization */
    int cplusplus_system_init(void);
    cplusplus_system_init();
#endif 

    /* bsp initialization */
    bsp_initialize();

    /* task initialization */
    task_init();

    /* bsp post initialization */
    bsp_post_initialize();

    /* start task */
    task_start();

    /* delete itself */
    rt_thread_delete(tid0);
}

int rt_application_init()
{
    tid0 = rt_thread_create("init",
        rt_init_thread_entry, RT_NULL,
        8192, RT_THREAD_PRIORITY_MAX / 2, 20);

    if (tid0 != RT_NULL)
        rt_thread_startup(tid0);

    return 0;
}

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    /* init board */
    rt_hw_board_init();

    /* init tick */
    rt_system_tick_init();

    /* init kernel object */
    rt_system_object_init();

    /* init timer system */
    rt_system_timer_init();

    rt_system_heap_init((void*)SYSTEM_FREE_MEM_BEGIN, (void*)SYSTEM_FREE_MEM_END);

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init application */
    rt_application_init();

    /* init timer thread */
    rt_system_timer_thread_init();

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return;
}

int main(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* startup RT-Thread RTOS */
    rtthread_startup();

    return 0;
}
