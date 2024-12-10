#include"util.h"
// mman library to be used for hugepage allocations (e.g. mmap or posix_memalign only)
#include <sys/mman.h>

#define L1_SIZE (32 * 1024)
#define L2_SIZE (256 * 1024)
#define LINE_SIZE 64
#define SENSITIVITY 50

void prime(char *array) {
    for (int i = 0; i < L2_SIZE + L1_SIZE; i += LINE_SIZE) {
        // asm volatile (
        //     "mov (%0), %%eax"
        //     :
        //     : "r" (&array[i])
        //     : "eax"
        // );
      array[i] = 1;
    }
}

int probe(char *array) {
    int i;
    int result = -1;
    int highest_clk = SENSITIVITY;
    for (i = 255; i >= 0; i--) {
      CYCLES delay = measure_one_block_access_time((uint64_t)(array + (i * LINE_SIZE * WAY)));
      if (delay > highest_clk && delay < 100) {
          result = i;
      }
    }
    // if (measure_one_block_access_time((uint64_t)(array + (i * LINE_SIZE * 4))) > SENSITIVITY) {
    //   return i;
    // }
    return result;
}

int main(int argc, char **argv)
{
  int results[SAMPLES];
  // Allocate a buffer using huge page
  // See the handout for details about hugepage management
  void *buf= mmap(NULL, L1_SIZE + L2_SIZE, PROT_READ | PROT_WRITE, MAP_POPULATE |
                  MAP_ANONYMOUS | MAP_PRIVATE | MAP_HUGETLB, -1, 0);
  
  if (buf == (void*) - 1) {
      perror("mmap() error\n");
      exit(EXIT_FAILURE);
  }
  // The first access to a page triggers overhead associated with
  // page allocation, TLB insertion, etc.
  // Thus, we use a dummy write here to trigger page allocation
  // so later access will not suffer from such overhead.
  *((char *)buf) = 1; // dummy write to trigger page allocation

  prime(buf);

  for (int sample = 0; sample < SAMPLES; sample++) {
    for (int i = 0; i < DELAY; i++) {
      asm volatile("nop"); 
    }
    results[sample] = probe(buf);
  }

  for (int i = 0; i < SAMPLES; i++) {
    printf("%d\n", results[i]);
  }

  return 0;
}


