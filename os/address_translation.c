#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int vspace, psize, vaddr;
    vspace = atoi(argv[1]);
    psize = atoi(argv[2]);
    vaddr = atoi(argv[3]);

    // Conversion to bytes
    psize = psize * 1024;
    int npages = (vspace * 1024 * 1024) / psize;
    int *table = malloc(npages * sizeof(int));

    for (int i = 0; i < npages; i++) table[i] = i;  // Identity mapping

    int page = vaddr / psize;
    int offset = vaddr % psize;
    int paddr = table[page] * psize + offset;

    printf("Page: %d | Offset: %d | Physical Address: %d\n", page, offset, paddr);

    free(table);
}