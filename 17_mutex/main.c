#include "os_stdio.h"
#include <stdint.h>
#include "cm3.h"
#include "task.h"
#include "os.h"
#include "memblock.h"
#include "timer.h"
#include "mutex.h"

extern uint32_t _bss;
extern uint32_t _ebss;

static inline void clear_bss(void)
{
    uint8_t *start = (uint8_t *)_bss;
    while ((uint32_t)start < _ebss) {
        *start = 0;
        start++;
    }
}

task_t task1;
task_t task2;
task_t task3;
task_t task4;
task_stack_t task1_stk[1024];
task_stack_t task2_stk[1024];
task_stack_t task3_stk[1024];
task_stack_t task4_stk[1024];

mutex_t mutex;

void task1_entry(void *param)
{
    init_systick(10);

    mutex_init(&mutex);
    mutex_lock(&mutex, 0);
    printk("after mutex\n");
    for(;;) {
#if 0
        mutex_lock(&mutex, 0);
        mutex_lock(&mutex, 0);
        printk("%s 1\n", __func__);
        task_delay_s(1);
        mutex_unlock(&mutex);
        printk("%s 2\n", __func__);
        mutex_unlock(&mutex);
        task_delay_s(1);
#endif
        printk("%s\n", __func__);
        task_delay_s(1);
    }
}

void task2_entry(void *param)
{
    printk("%s\n", __func__);
    mutex_destory(&mutex);
    for(;;) {
#if 0
        mutex_lock(&mutex, 0);
        printk("%s\n", __func__);
        task_delay_s(1);
        mutex_unlock(&mutex);
#endif
    }
}

void task3_entry(void *param)
{
    for(;;) {
        printk("%s\n", __func__);
        task_delay_s(1);
    }

}

void task4_entry(void *param)
{
    for(;;) {
        printk("%s\n", __func__);
        task_delay_s(1);
    }
}

int main()
{

    clear_bss();

    DEBUG("Hello RTOS C03_Delay_List\n");

    DEBUG("psp:0x%x\n", get_psp());
    DEBUG("msp:0x%x\n", get_msp());

    init_task_module();
    timer_module_init();

    task_init(&task1, task1_entry, (void *)0x11111111, 0, &task1_stk[1024]);
    task_init(&task2, task2_entry, (void *)0x22222222, 1, &task2_stk[1024]);
#if 0
    task_init(&task3, task3_entry, (void *)0x33333333, 0, &task3_stk[1024]);
    task_init(&task4, task4_entry, (void *)0x44444444, 1, &task4_stk[1024]);
#endif
    g_next_task = task_highest_ready();
    task_run_first();

    for(;;);
    return 0;
}
