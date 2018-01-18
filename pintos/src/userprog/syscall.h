#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

#include "filesys/file.h"
#include "threads/thread.h"

/* Struct emobodying the file descriptor (fd). */
struct file_descriptor
{
  struct file *fp;
  tid_t tid;
};

void syscall_init (void);

#endif /* userprog/syscall.h */
