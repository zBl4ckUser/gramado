/*
 * Gramado Operating System - The main header for the kernel base. 
 * (c) Coppyright 2018 - Fred Nora.
 *
 * File: kernel.h 
 *
 * This is the header file kernel base.
 * This is a hybrid kernel. 
 * The kernel base has 4 layers: 
 *     HAL, MICROKERNEL, EXECUTIVE and GRAMADO.
 *
 * *****************************************
 * *                                       *  
 * * ;----------------------------------;  *
 * * ;                                  ;  *
 * * ;               GWS                ;  *
 * * ;                                  ;  *  
 * * ;----------------------------------;  *
 * * ;----------------------------------;  *
 * * ;                                  ;  *
 * * ;             Execve               ;  *  
 * * ;                                  ;  *
 * * ;----------------------------------;  *
 * *                                       *
 * * ;----------------------------------;  *
 * * ;               MK                 ;  *
 * * ;----------------------------------;  *
 * *                                       *
 * * ;----------------------------------;  *
 * * ;              Hal                 ;  *
 * * ;----------------------------------;  *
 * *                                       *
 * *****************************************
 *
 *
 * History:
 *     2013 - Created by Fred Nora.
 *     2014~2018 - Resision.
 */

 
#include <gramado.h> 
 

// Global definitions.
// This must be on top.
#include <gramado/gdef.h>
#include <gramado/gdevice.h>
//...



#define KERNEL      0

//layer.
//@todo: Change numbers.
#define HAL         2   //4
#define MICROKERNEL 3   //3
#define EXECUTIVE   1   //2
//#define GRAMADO     4   //1


//IOPL constants.
#define KernelMode 0
#define UserMode   3
#define RING0 0
#define RING1 1
#define RING2 2
#define RING3 3


/*
// Segments @todo: Include this constants.
#define GDT_KCODE   0x08
#define GDT_KDATA   0x10
#define GDT_UCODE   (0x18 | 3)
#define GDT_UDATA   (0x20 | 3)
*/


//Kernel status constants.
#define  KERNEL_NULL          0
#define  KERNEL_INITIALIZED   1
#define  KERNEL_ABORTED       2
#define  KERNEL_INICIALIZADO  KERNEL_INITIALIZED
#define  KERNEL_ABORTADO      KERNEL_ABORTED
//#define  KE_ (-1)
//#define  KE_ (-2)
//#define  KE_ (-3)
//#define  KE_ (-4)


//#define LOBYTE(w) ((char)(((unsigned long )(w)) & 0xff))
//#define HIBYTE(w) ((char)((((unsigned long)(w)) >> 8) & 0xff))


//
//  ## JOB CONTROL SUPPORT ##
//

#define PROCESS 10
#define THREAD  20
#define BACKGROUND 100 
#define FOREGROUND 200



//
// Externs.
//


//Stack for fome threads in kernel mode. 
extern unsigned long task0_stack;
extern unsigned long task1_stack;
extern unsigned long task2_stack;
extern unsigned long task3_stack;
extern unsigned long stack0_krn_ptr;
//...


//functions
extern void dispatch_context();
extern void do_executa_new_task();


// libC support.
//++
#include <stddef.h>
#include <types.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iso646.h>
#include <signal.h>
//...
//--


//
// MICROKERNEL (3)
//


// Global first.
#include <gramado/mk/pc/mm/memmap.h>            //Memory Map - address.


//
// HAL (4)
//

#include <gramado/execve/dd/sm/disk/diskmap.h>        //Disk Map - sectors.
#include <gramado/hal/screen.h> 
#include <gramado/hal/video.h>                           //video.
#include <gramado/hal/memory.h>                          //ram (hardware).
#include <gramado/hal/cpu.h>                             //cpu
#include <gramado/execve/dd/sm/disk/disk.h>           //disk.
#include <gramado/execve/dd/sm/disk/volume.h>         //volume.
#include <gramado/hal/serial.h>        
#include <gramado/hal/mac.h>                             //mac address info. (hw)
//...

//
// EXECUTIVE (2)
//

//Unblocked.
#include <gramado/execve/dd/sm/network/host.h>        //host info.
#include <gramado/execve/dd/unb/ports.h>        //Portas para dispositivos
#include <gramado/execve/dd/unb/ps2.h>          //ps/2 
#include <gramado/execve/dd/unb/timer.h>        //PIT. irq0.
#include <gramado/execve/dd/unb/pic.h>          //PIC.
#include <gramado/execve/dd/unb/apic.h>         //APIC - Advanced Programmable Interrupt Controller.
#include <gramado/execve/dd/unb/rtc.h>          //clock    ( South bridge).
#include <gramado/execve/dd/unb/floppy.h>       //floppy   ( South bridge).
#include <gramado/execve/dd/unb/keyboard.h>     //irq1     ( South bridge).   //keyboard

#include <gramado/execve/dd/unb/ascii.h>     //ascii table 
#include <gramado/execve/dd/unb/vk.h>         //virtual keys
#include <gramado/execve/dd/unb/abnt2.h> 
#include <gramado/execve/dd/unb/ldisc.h>        //ldisc

#include <gramado/execve/dd/unb/ide.h>          //irq14/15 ( South bridge).
//...

//Blocked.
#include <gramado/execve/dd/b/sata.h>           //(PCI BUS).
#include <gramado/execve/dd/b/usb.h>            //usb.
#include <gramado/execve/dd/b/pci.h>            //pci.
//#include                                       //pcie.
//...

//
// HAL (4)
//

//This must to be on the bottom of HAL part.    
#include <gramado/hal/device.h>      //device manager.
#include <gramado/hal/hal.h>         //*****
//--



/*
 * MICROKERNEL (3)
 */
 //++
#include <gramado/mk/cpu/context.h>
#include <gramado/mk/pc/ts.h>
#include <gramado/mk/pc/tasks.h>
#include <gramado/mk/pc/process.h>
#include <gramado/mk/pc/thread.h>
#include <gramado/mk/pc/sched/sched.h>
#include <gramado/mk/pc/ipc/ipc.h>
#include <gramado/mk/pc/ipc/sem.h>
#include <gramado/mk/pc/queue.h>
#include <gramado/mk/pc/realtime.h>
#include <gramado/mk/pc/dispatch.h>
#include <gramado/mk/pc/event.h>
#include <gramado/mk/pc/pc.h>
#include <gramado/mk/mk.h>
//--


//
// EXECUTIVE (2)
//

//tty
#include <gramado/execve/dd/tty/tty.h>


//
// GRAMADO (1)
// This must to be on the bottom.
//

//gramado - GUI. (presentation layer)
//Gramado Window Server
#include <gramado/gws/gws/ws.h>
#include <gramado/gws/gws/usession.h>
#include <gramado/gws/gws/wstation.h>
#include <gramado/gws/gws/desktop.h>
#include <gramado/gws/gws/window.h>
#include <gramado/gws/gws/menu.h>
#include <gramado/gws/gws/grid.h>
#include <gramado/gws/gws/bmp.h>
#include <gramado/gws/gws/fonts.h>
#include <gramado/gws/gws/guiconf.h>  //*principal.

// gramado/user
#include <gramado/gws/user/user.h>
//gramado/logon
#include <gramado/gws/logon/logon.h>
//gramado/logoff
#include <gramado/gws/logoff/logoff.h>
//principal
#include <gramado/gws/gws.h>                     //main file.

//uigm - User Interface Graphic Mode.
//nothing for now.

//gws/terminal 
//suporte a terminal.
#include <gramado/gws/terminal/line.h>              //lines support.
#include <gramado/gws/terminal/terminal.h>          //terminal support. 
#include <gramado/gws/terminal/console.h>           //Console. Monitor support.

//sm - System Management.  
#include <gramado/execve/dd/sm/install.h>  
#include <gramado/execve/dd/sm/init.h>
#include <gramado/execve/dd/sm/network/nic.h>         //nic - network interface controller.
#include <gramado/execve/dd/sm/network/nports.h>      //(network) Network Ports  (sw)
#include <gramado/execve/dd/sm/network/socket.h>      //(network) Sockets info. (sw)
#include <gramado/execve/dd/sm/network/ip.h>          //(network) IP info.      (sw)
#include <gramado/execve/dd/sm/network/channel.h>     //(network) Channel       (sw)
#include <gramado/execve/dd/sm/network/client.h>      //(network) Client process support. 
#include <gramado/execve/dd/sm/network/ns.h>          //(network) Network Server.
#include <gramado/execve/dd/sm/network/network.h>     //(network) Gerenciamento de rede. 
#include <gramado/execve/fs/fs.h>                     //fs.
#include <gramado/execve/fs/vfs.h>                     //vfs.
#include <gramado/execve/dd/sm/io.h>                  //io.
#include <gramado/execve/sci/syscall.h>            //system calls.
#include <gramado/execve/dd/sm/modules.h>             //module manager.
#include <gramado/execve/dd/sm/debug.h>
#include <gramado/execve/dd/sm/sys.h>                 //system calls 2.
#include <gramado/execve/dd/sm/system.h>              //system manager.
#include <gramado/execve/dd/dd.h>

//
// MICROKERNEL (3)
//

//mm
#include <gramado/mk/pc/mm/mmglobal.h>
#include <gramado/mk/pc/mm/heap.h>          //Heap pointer support.
#include <gramado/mk/pc/mm/aspace.h>        //Address Space, (data base account).
#include <gramado/mk/pc/mm/dspace.h>        //Disk Space, (data base account).
#include <gramado/mk/pc/mm/bank.h>          //Bank. database
#include <gramado/mk/pc/mm/mm.h>            //mm, memory manager support.


//
// EXECUTIVE (2)
//

#include <gramado/execve/execve.h>              //main file.
//--


//
// Some other stuff.
//

//Cursor support.
#include <gramado/cursor.h>

//Prompt support.
#include <gramado/prompt.h>

//Kernel request support.
#include <gramado/request.h>


//Kernel messages support.
#include <gramado/messages.h>

//Object Manager support.
#include <gramado/object.h>

//system signals. (SS)
#include <gramado/ss.h>

#include <gramado/brtypes.h>


#include <gramado/events.h>

//
// Globals.
//


//keyboard suppport 
//abnt2 flag.
int abnt2;
//...


// Product type.
typedef enum {
   PT_THINGS,        // Things.
   PT_EDGEDEVICES,   // Edge Devices.
   //PT_COREDEVICES,   // Core Devices. (haha)
}ProductType_t;


//Type of product.
int g_product_type; 


// Platform type.
typedef enum {
   PFT_16BIT,       //16bit processor.
   PFT_32BIT,       //32bit processor.
   PFT_64BIT,       //64bit processor.
   //...
}PlatformType_t;


//size of processor word.
int g_platform_type;


int current_user;    //gramado ?
int current_group;   //gramado ?

//#importante:
//isso foi movido para gws.h
//int current_usersession;    //gws
//int current_windowstation;  //gws
//int current_desktop;        //gws 
//int current_window;         //gws
//int current_menu; //gws

int current_process;
int current_thread;
int current_idle_thread;  //ring0
int current_disk;
int current_volume;
int current_directory;   
int current_file;        
int current_terminal;
//...


//cr3. current page directoory address.
unsigned long current_process_pagedirectory_address;

//Lista para armazenas os ponteiros das estruturas de todos os processadores.
//unsigned long processorsList[32];

//Quais processadores est�o no estado IDLE.
//int idleprocessorList[8];

//Quais processadores est�o no estado ACTIVE.
//int activeprocessorList[8];


//Tempo absoluto em que o sistema iniciou.
//unsigned long BootTime;

//Conta o n�mero de processadores.
//int processors_count;

//A arquitetura do processador.(marca)
//int processor_architecture;

//Lista os servi�os oferecidos pelo kernel atrav�z da systemcall int 200.
//endere�o da fun��o. talvez seja uma chamada � um m�dulo esterno ou server.
//unsigned long SystemServices[256];


//Contador de thread switch.
//unsigned long thread_switch_count;

//Armazena o endere�o da rotina de debug do sistema.
//unsigned long system_debugger_address;


//Armazena qual ser� o n�mero de identifica��o
//do pr�ximo processo ou thread criados.
// se for '0', tem que procurar um novo.
//se usar o n�mero contido aqui, deve atualizar para 0.
//int NewPID;
//int NewTID;


//
// Logon.
//

int g_logged;


//
// GUI
//

//flag.
//If the kernel is in graphics mode.
int g_useGUI; 


//Messages support.
unsigned long g_next_proc;      // Procedure address.
unsigned long g_nova_mensagem;  // ?? new message ??
unsigned long g_new_message;
unsigned long g_next_app;       // Procedure adreess.
unsigned long g_proc_status;    // Procedure status.


//Drivers support.
int g_driver_video_initialized;
int g_driver_apic_initialized;
int g_driver_hdd_initialized;
int g_driver_keyboard_initialized;
int g_driver_pci_initialized;
int g_driver_rtc_initialized;
int g_driver_timer_initialized;
//...


//internal modules support.
int g_module_shell_initialized;
int g_module_debug_initialized;
int g_module_disk_initialized;
int g_module_volume_initialized;
int g_module_fs_initialized;
int g_module_gui_initialized;
int g_module_logoff_initialized;
int g_module_logon_initialized;
int g_module_mm_initialized;
int g_module_objectmanager_initialized;
int g_module_runtime_initialized;
int g_module_uem_initialized;             //user environment manager.
//...

// Kernel information variables.
unsigned long KernelSize;
unsigned long KernelHeapSize;
unsigned long KernelStackSize;
unsigned long KernelPages;
unsigned long KeInitPhase;
unsigned long KernelStatus;
//...


//Task support variables.
unsigned long kernel_request;
unsigned long kernel_switch;


//
// Count support variables.
//


//Counting how much ticks the kernel is running.
unsigned long kernel_tick;

//Saving the total ticks the kernel is running.
unsigned long kernel_tick_total;


//error support.
unsigned long errno;

//
// fs support.
//



//directory entries support.
char buffer_dir_entry[512];

//log buffer
char KernelLogBuffer[512];


//
// Plataform support.
//

//environment variables.
#define PLATFORM_PATH  "/Platform"
#define HARDWARE_PATH  "/Platform/Hardware"
#define FIRMWARE_PATH  "/Platform/Firmware"
#define SYSTEM_PATH    "/Platform/System"
//#define USERS_PATH     "/Platform/Users"
//...


/*
 * ring0_exported_d:
 *  Pointers to export tables.
 */
typedef struct ring0_exported_d ring0_exported_t;
struct ring0_exported_d
{
    unsigned long bm_exported;    //Boot Manager exported functions.
    unsigned long bl_exported;    //Boot Loader exported functions.
    unsigned long bk_exported;    //Kernel exported functions.
    //... 
};
ring0_exported_t *ring0_exported;


//node od a linked list.
typedef struct node_d node_t;
struct node_d
{
    void *data;

    //struct window_d *window;
    //int msg;	
    //unsigned long long1;
    //unsigned long long2;
    
    struct node_d *flink;
    struct node_d *blink;    
};


//Linked list support.
typedef struct linkedlist_d linkedlist_t;
struct linkedlist_d
{
    struct node_d *head;
    struct node_d *tail;
};


//save args support. 
typedef struct kernel_args_d kernel_args_t;
struct kernel_args_d
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long arg4;
}; 
kernel_args_t KernelArgs;


//system classes.
typedef struct system_classes_d system_classes_t;
struct system_classes_d
{
    //unsigned long Gramado; //@todo: Include this one.
    unsigned long Executive;
    unsigned long Microkernel;
    unsigned long Hal;
};
system_classes_t SystemClasses;


//Kernel classes.
typedef struct kernel_classes_d kernel_classes_t;
struct kernel_classes_d
{
    struct system_classes_d *System;
    //..
};
kernel_classes_t KernelClasses;
//...


//Kernel Manager.
typedef struct kernel_d kernel_t;
struct kernel_d
{
    //
    // Kernel info.
    //

    char *name;
    unsigned long address;

    //Kernel information block.
    //struct kernel_block_d *KernelBlock;

    //struct process_d *process;

    //
    // Structs.
    //

    struct bootmanager_d     *BootManagerBlock;  //Boot Manager.
    struct bootloader_d      *BootLoaderBlock;   //Boot Loader.
    struct system_d          *SystemBlock;       //System.
    struct ProcessorBlock_d  *ProcessorBlock;    //Processor info.
    //...

    //
    // CPUs.
    //

    int processorCount;
    struct processor_descriptor_t *processorListHead;

    //kernel_args_t
    //kernel_classes_t

    //...
};
kernel_t *KernelInfo; 
//...


/*
 * plataform_d:
 *     Os componentes b�sicos da m�quina.
 *     As estruturas de Hardware e Software.
 *     * IMPORTANTE Essa � a estrutura BASE do kernel.
 */
typedef struct platform_d platform_t;
struct platform_d
{
    //Name.
    char *name;

    //Type.


    //  *Hardware - Componentes do hardware.
    //  *Firmware - Componentes se software embarcados. BIOS, UEFI ...
    //  *Software - Componentes do Sistema operacional.

    struct hardware_d *Hardware;    // hal\hal.h
    struct firmware_d *Firmware;    // hal\hal.h
    struct system_d   *System;      // executive\system.h


    //kernel struct ...
    struct kernel_d *Kernel;
};
platform_t *Platform; 


//
// main function.
//


int kMain(int argc, char* argv[]);


//
// Initializations support.  
//


int init_runtime();         //RunTime.
void boot();                //??
void save_kernel_args();    //Save args in the structure.


//
// Linked list support.
// 


void* newLinkedlist();
void* newNode();
void Removing_from_the_beginning(struct linkedlist_d *list);
void Removing_from_the_middle(struct linkedlist_d *list);
void Removing_from_the_end(struct linkedlist_d *list);


//
// Count support.
//

unsigned long get_tick_count();


//
// Delay support.
//

void sleep(unsigned long ms);


//
// Finalizations support.
//

void faults(unsigned long number);
void shutdown();

//
// Error support
// 
 
void abort();    //abort.c
void die();      //system.c


//
// ke - Kernel External.
// ki - Kernel Internal.
// PS: This must to be here in the end.
//


#include <gramado/ke.h>
#include <gramado/ki.h>


//
// End.
//

