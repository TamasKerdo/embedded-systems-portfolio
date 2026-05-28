#include <stdio.h>
#include <stddef.h>
typedef int (*func_ptr_type)(int);

int doubled(int);
int squared(int);
int apply(int, func_ptr_type);

int doubled(int a)
{
  return (2 * a);
}

int squared(int a)
{
  return (a * a);
}

int apply(int a, func_ptr_type ptr)
{
  int error = 0;

  if (ptr != NULL)
  {
    printf("Callback result: %d\n", ptr(a));
  }
  else
  {
    printf("Apply (function): callback pointer is NULL!\n");
    error = 1;
  }
  return error;
}

int main()
{
  apply(5, doubled);
  apply(5, squared);
  if (apply(5, NULL) != 0)
  {
    printf("Main (function): apply failed, handling error\n");
  }

  return 0;
}