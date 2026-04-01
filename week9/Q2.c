#include <stdio.h>
#include <math.h>

int main() {
    int page_size = 32;   // bytes
    int num_pages = 8;
    int total_mem = page_size * num_pages;  // 256 bytes

    // Number of bits needed: log2(256) = 8 bits
    int total_bits  = (int)(log2(total_mem));   // 8 bits
    int offset_bits = (int)(log2(page_size));   // 5 bits (2^5 = 32)
    int page_bits   = total_bits - offset_bits; // 3 bits

    printf("Page Size    : %d bytes\n", page_size);
    printf("Total Pages  : %d\n", num_pages);
    printf("Total Memory : %d bytes\n", total_mem);
    printf("Address bits : %d bits total (%d page bits + %d offset bits)\n\n",
           total_bits, page_bits, offset_bits);

    int addresses[] = {204, 56};
    int n = 2;

    printf("%-20s %-15s %-15s\n", "Logical Address", "Page Number", "Page Offset");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int addr   = addresses[i];
        int page   = addr / page_size;
        int offset = addr % page_size;
        printf("%-20d %-15d %-15d\n", addr, page, offset);
    }

    return 0;
}

