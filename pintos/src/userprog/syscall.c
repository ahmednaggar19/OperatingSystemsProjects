#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/shutdown.h"
#include "threads/vaddr.h"
#include "userprog/pagedir.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "devices/input.h"
#include "lib/kernel/stdio.h"
#include "lib/user/syscall.h"

#define FDS_MAX 1000

const int INT_SIZE = sizeof(int);
const int EMPTY_ENTRY = -4;

const int BUFF_MAX_SIZE = 100;

struct file_descriptor file_descriptor_table[FDS_MAX];
struct lock fd_lock;

static void syscall_handler (struct intr_frame *);

void
initialize_file_descriptor_table ()
{
  for (int i = 0; i < FDS_MAX; i++)
  {
    file_descriptor_table[i].tid = EMPTY_ENTRY;
  }
  return;
}

void
syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
  initialize_file_descriptor_table ();
  lock_init(&fd_lock);
}

void *                                               ///////// NEEDS EDITS
is_valid_address (void *addr)
{
  int *vaddr = (int *) (addr);
  void *vaddr_value = (void *) *vaddr;
  uint32_t *pd = thread_current() -> pagedir;
  if (vaddr_value == NULL || !is_user_vaddr (vaddr_value)
      || (int) vaddr_value < 0
      || pagedir_get_page (pd, vaddr_value) == NULL)
      return NULL;
  return vaddr_value;
}

bool
valid_exec_args (struct intr_frame *f)
{
  // validation
  uint32_t *pd = thread_current() -> pagedir;
  char *vaddr = (char *) (f->esp);
  void *vaddr_value = (void *) *vaddr;
  if (vaddr_value == NULL || is_user_vaddr (vaddr_value)
      || (int) vaddr_value < 0
      || pagedir_get_page (pd, vaddr_value) == NULL)
      return false;
  f->esp += INT_SIZE;
  // Execute the child process and return its ID.
  tid_t child = process_execute ((char*) vaddr);
  f->eax = (uint32_t) child;
  return true;
}

void                                                ///////// NEEDS EDITS
exit_process (struct intr_frame *f)
{
  int status = *((int *)(&f->esp));
  f->esp += INT_SIZE;
  tid_t tid = thread_current() -> tid;
  for (int i = 3; i < FDS_MAX; i++)
    {
      if (file_descriptor_table[i].tid == tid)
        file_descriptor_table[i].tid = EMPTY_ENTRY;
    }
  if (thread_current()->is_parent_waiting)
      {
        thread_current () -> parent -> child_status  = status;
        cond_signal (&thread_current () -> parent -> child_exit_cond,
          &thread_current () -> parent -> child_exit_lock);
      }
  file_allow_write (thread_current () -> elf);
  process_exit();
  printf ("%s: exit(%d)\n", thread_current () -> name, status);
  f->eax = status;
  thread_exit();
}

void                                                ///////// NEEDS EDITS
wait_process (struct intr_frame *f)
{
  pid_t pid = *((pid_t *)(&f->esp));
  int status = process_wait ((tid_t) pid);
  f->eax = status;
}

void
create_file (struct intr_frame *f)
{
  bool creation_status = false;
  char *file_name = ((char *) is_valid_address(f->esp));
  if (file_name != NULL)
    {
      f->esp += INT_SIZE;
      off_t initial_size = *((off_t *)(&f->esp));
      f->esp += INT_SIZE;
      creation_status = filesys_create (file_name, initial_size);
    }
  else
    {
      f->esp += (INT_SIZE * 2);
    }
   f->eax = creation_status;
   return;
}

/* Macro for incrementing ESP with SZ bytes.*/
//#define INCREMENT_ESP(ESP, SZ) ESP += SZ

void
remove_file (struct intr_frame *f)
{
  bool removal_status = false;
  char * file_name = ((char *) is_valid_address(f->esp));
  if (file_name != NULL)
    {
      f->esp += INT_SIZE;
      removal_status = filesys_remove (file_name);
    }
  else
    {
      f->esp += INT_SIZE;
    }
   f->eax = removal_status;
   return;
}

void
open_file (struct intr_frame *f)
{
    char* file_name = (char *) is_valid_address(f->esp);
    f->esp += INT_SIZE;
    struct file *fp = filesys_open (file_name);
    int fd = -1;
    if (fp != NULL)
      {
        for (int i = 3; i < FDS_MAX; i++)
          {
            lock_acquire (&fd_lock);
            if (file_descriptor_table[i].tid == EMPTY_ENTRY)
                {
                  fd = i;
                  file_descriptor_table[i].tid = thread_current ()->tid;
                  file_descriptor_table[i].fp = fp;
                  lock_release (&fd_lock);
                  break;
                }
            lock_release (&fd_lock);
          }
      }
    f->eax = fd;
    return;
}

void
get_file_length (struct intr_frame *f)
{
  int fd = *((int *)(&f->esp));
  f->esp += INT_SIZE;
  tid_t tid = thread_current()->tid;
  int file_size = 0;
  if (fd < FDS_MAX && fd >= 3 && file_descriptor_table[fd].tid == tid)
    {
      file_size = (int) file_length (file_descriptor_table[fd].fp);

    }
  f->eax = file_size;
}

void
read_file (struct intr_frame *f)
{
  int fd = *((int *)(&f->esp));
  f->esp += INT_SIZE;
  void *buffer = (is_valid_address(f->esp));
  f->esp += INT_SIZE;
  int read_size = *((int *)(&f->esp));
  f->esp += INT_SIZE;
  int bytes_read = -1;
  tid_t tid = thread_current() -> tid;
  if (fd == 0)
    {
        bytes_read = (int) input_getc();
    }
  else if (fd < FDS_MAX && fd >= 3 && file_descriptor_table[fd].tid == tid)
    {
      bytes_read = (int) file_read (file_descriptor_table[fd].fp,
         buffer, (off_t) read_size);
    }
  f->eax = bytes_read;
  return;
}

void
write_file (struct intr_frame *f)
{
  int fd = *((int *)(&f->esp));
  f->esp += INT_SIZE;
  void *buffer = (is_valid_address(f->esp));
  f->esp += INT_SIZE;
  int write_size = *((int *)(&f->esp));
  f->esp += INT_SIZE;
  int bytes_written = -1;
  tid_t tid = thread_current() -> tid;
  if (fd == 1)
    {
        if (write_size < BUFF_MAX_SIZE) {
          putbuf ((char *) buffer, (size_t) write_size);
        } else {
          int i = 0;
          while (write_size > BUFF_MAX_SIZE) {
            putbuf ((char *) (buffer + i * BUFF_MAX_SIZE), (size_t) BUFF_MAX_SIZE);
            write_size -= BUFF_MAX_SIZE;
            i++;
          }
          putbuf ((char *) (buffer + i * BUFF_MAX_SIZE), (size_t) write_size);
        }
        bytes_written = write_size;
    }
  else if (fd < FDS_MAX && fd >= 3 && file_descriptor_table[fd].tid == tid)
    {
      bytes_written = (int) file_write (file_descriptor_table[fd].fp,
         buffer, (off_t) write_size);
    }
  f->eax = bytes_written;
  return;
}

void
seek_file (struct intr_frame *f)
{
  int fd = *((int *)(&f->esp));
  f->esp += INT_SIZE;
  unsigned position = *((unsigned *)(&f->esp));
  f->esp += sizeof (unsigned);
  tid_t tid = thread_current() -> tid;
  if (fd < FDS_MAX && fd >= 3 && file_descriptor_table[fd].tid == tid)
    {
      file_seek (file_descriptor_table[fd].fp, (off_t) position);
    }
  return;
}

void
tell_file (struct intr_frame *f)
{
  int fd = *((int *)(&f->esp));
  f->esp += INT_SIZE;
  unsigned position = 0;
  tid_t tid = thread_current() -> tid;
  if (fd < FDS_MAX && fd >= 3 && file_descriptor_table[fd].tid == tid)
    {
      position = (unsigned) file_tell (file_descriptor_table[fd].fp);
    }
  f->eax = position;
  return;
}

void
close_file (struct intr_frame *f)
{
  int fd = *((int *)(&f->esp));
  f->esp += INT_SIZE;
  file_descriptor_table[fd].tid = EMPTY_ENTRY;
}

/////////////////////
static void
syscall_handler (struct intr_frame *f UNUSED)
{
  int sys_call_number = *((int *)(&f->esp));
  f->esp += INT_SIZE;
	switch (sys_call_number)
	{
		case SYS_HALT :
					shutdown_power_off ();
			    break;
		case SYS_EXIT :
          exit_process (f);
					break;
		case SYS_EXEC :
          if (!valid_exec_args (f))
            {
              /// EXIT
            }
					break;
		case SYS_WAIT :
					///TODO EAX = return value
					return;
		case SYS_CREATE :
					create_file (f);
					return;
		case SYS_REMOVE :
					remove_file (f);
					return;
		case SYS_OPEN :
					open_file (f);
					return;
		case SYS_FILESIZE :
					get_file_length (f);
					return;
		case SYS_READ :
					read_file (f);
					return;
		case SYS_WRITE :
					write_file (f);
					return;
		case SYS_SEEK :
          seek_file (f);
					return;
		case SYS_TELL :
					tell_file (f);
					return;
		case SYS_CLOSE :
          close_file (f);
					return;
  }
	//printf ("system call!\n");
  //thread_exit ();
}
