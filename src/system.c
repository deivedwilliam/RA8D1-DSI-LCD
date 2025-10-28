/*
 * system.c
 *
 *  Created on: 26 de out. de 2025
 *      Author: Deived
 */


#include "hal_entry.h"



 int  __weak _write(int file, char *ptr, int len){
    (void)file;
    return len;
}

 int __weak _close(int file){
     (void)file;
     return 0;
 }

 int __weak _fstat(int file, struct stat *st){
     (void)file;
     return 0;
 }

int __weak _isatty(int file){
    if (file == 1 || file == 2) {
        return 1;
    }
    return 0;
}

int __weak _lseek(int file, int ptr, int dir){
    (void)file;
    (void)ptr;
    (void)dir;
    // Não suportamos "seeking" (mudança de posição)
    return 0;
}

int __weak _read(int file, char *ptr, int len){
    (void)file;
    (void)ptr;
    (void)len;

    return 0;
}
