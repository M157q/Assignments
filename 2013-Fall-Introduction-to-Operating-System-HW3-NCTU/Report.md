# OS-HW3 Report 
### 0016043 鄭順一

#### Environment: Arch Linux x86_64 with Linux 3.12.6-1

1. Download the [Linux 3.12.6.tar.xz from The Linux Kernel Archives](https://www.kernel.org/pub/linux/kernel/v3.x/linux-3.12.6.tar.xz)
    + upzip the compressed file: `$ tar Jxvf linux-3.12.6.tar.xz`
2. Add a custom system call to the syscall table
    + `$ vim linux-3.12.6/arch/x86/syscall/syscall_64.tbl`
    + add `315 common lookup_paddr sys_lookup_paddr` in line 325.
3. Add the system call definition to the syscall interface
    + `$ vim linux-3.12.6/include/linux/syscalls.h`
    + add `asmlinkage unsigned long sys_lookup_paddr(pid_t pid, unsigned long vaddr);` in front of the `#endif` in line 852.
4. Copy the file `lookup_paddr.c` to `linux-3.12.6/kernel/` and modify the code.
    + The missing code of `linux-3.12.6/kernel/lookup_paddr.c` in the else block should be like this: 
    
    ```
        pte = pte_offset_kernel(pmd, vaddr);
        printk("pte_val = 0x%lx\n", pte_val(*pte));
        printk("pte_index = %lx\n", pte_index(vaddr));
        if(pte_none(*pte)){
            printk("not mapped in pte\n");
            return INVALID_ADDR;
        }

        paddr = (pte_val(*pte) & PAGE_MASK);
        paddr = paddr | (vaddr & ~PAGE_MASK);
        return paddr;
    ```
5. Modify the Makefile
    + `$ vim linux-3.12.6/kernel/Makefile`
    + add ``lookup_paddr.o` at the end of obj-y
    + like this:
    
    ```
    obj-y     = fork.o exec_domain.o panic.o \
            cpu.o exit.o itimer.o time.o softirq.o resource.o \
            sysctl.o sysctl_binary.o capability.o ptrace.o timer.o user.o \
            signal.o sys.o kmod.o workqueue.o pid.o task_work.o \
            rcupdate.o extable.o params.o posix-timers.o \
            kthread.o wait.o sys_ni.o posix-cpu-timers.o mutex.o \
            hrtimer.o rwsem.o nsproxy.o srcu.o semaphore.o \
            notifier.o ksysfs.o cred.o reboot.o \
            async.o range.o groups.o lglock.o smpboot.o \
            lookup_paddr.o
    ```
6. Make a new kernel
    + Make sure at `linux-3.12.6`
    + `$ make mrproper` - Prepare for compilation, delete all generated files and current configuration.
    + `$ zcat /proc/config.gz > .config` - Copy the configuration file from the running system.
    + `$ make menuconfig` - Make a customized configuration.
    + `$ make -j 16` on the linux5.cs.nctu.edu.tw
    + `# make modules_install` Install modules under /lib/modules/ after compilation.
7. Setup the new kernel
    + `# cp linux-3.12.6/arch/x86_64/boot/bzImage /boot/vmlinuz-os_hw3`
    + `# mkinitcpio /boot/vmlinuz-os_hw3 -c /etc/mkinitcpio.conf -g /boot/initramfs-os_hw3.img`
    + `# cp linux-3.12.6/System.map /boot/System.map-os_hw3`
    + `# grub-mkconfig -o /boot/grub/grub.cfg` - Update the configuration file of GRUB.
    + `# reboot`
8. Modify `fork_ex.c`
    + Use the custom system call `lookup_paddr()` to get the physical address of virtual memory. 
    + The modified part of the source code should be like this:
    
    ```
    #include <stdlib.h>

    printf("Child pid: %d.  [Var 'mem_alloc']vaddr: 0x%lx, paddr: 0x%lx, val: %d\n",
            getpid(), mem_alloc, syscall(315, getpid(), mem_alloc), *mem_alloc);

    printf("Parent pid: %d. [Var 'mem_alloc']vaddr: 0x%lx, paddr: 0x%lx, val: %d\n",
            getpid(), mem_alloc, syscall(315, getpid(), mem_alloc), *mem_alloc);
    ```
9. Compile and Execute fork_ex
    + Get result like this:
    ![Result of this homework](http://i.imgur.com/LcfPJOw.jpg)
