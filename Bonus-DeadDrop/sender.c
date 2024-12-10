#include"util.h"
// mman library to be used for hugepage allocations (e.g. mmap or posix_memalign only)
#include <sys/mman.h>

// [Bonus] TODO: define your own buffer size
#define BUFF_SIZE TODO

// Number of sets to access to count as a 1
#define NUM_SET 100
#define LINE_SIZE 64
#define L1_SIZE (32 * 1024)

void access_cache_set(char *base_addr, int idx) {
  char *address = base_addr + (idx * LINE_SIZE * WAY);

  address[0] = 1;

  // for (int i = 0; i < 4; i++) {
  //   asm volatile (
  //       "mov (%0), %%eax"
  //       :
  //       : "r" (address)
  //       : "eax"
  //   );
  // }
}

void evict_to_L2(char *array) {
  for (int i = 0; i < L1_SIZE; i += LINE_SIZE) {
    // asm volatile (
    //     "mov (%0), %%eax"
    //     :
    //     : "r" (&array[i])
    //     : "eax"
    // );
    array[i] = 1;
  }
}

int main(int argc, char **argv)
{
  void *buf= mmap(NULL, LINE_SIZE, PROT_READ | PROT_WRITE, MAP_POPULATE |
                  MAP_ANONYMOUS | MAP_PRIVATE | MAP_HUGETLB, -1, 0);
  
  if (buf == (void*) - 1) {
    perror("mmap() error\n");
    exit(EXIT_FAILURE);
  }

  *((char *)buf) = 1; // dummy write to trigger page allocation

  char eviction_buf[L1_SIZE];
  unsigned char message = 45;

  for (int sample = 0; sample < SAMPLES; sample++) {
    access_cache_set(buf, message);
    // evict_to_L2(eviction_buf);
  }

  return 0;
}


