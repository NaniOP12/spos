#include <stdio.h>

int main() {
    int page_size, num_pages, num_frames, logical_address;
    int page_table[50], frame_no;

    // Input page size
    printf("Enter the page size (in bytes): ");
    scanf("%d", &page_size);

    // Input number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &num_pages);

    // Input number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);

    // Input page table
    printf("Enter the page table (use -1 for pages not in memory):\n");
    for (int i = 0; i < num_pages; i++) {
        printf("Page %d: ", i);
        scanf("%d", &page_table[i]);
    }

    // Input logical address
    printf("Enter the logical address (in the format PageNumber:Offset): ");
    int page_number, offset;
    scanf("%d:%d", &page_number, &offset);

    // Validate the logical address
    if (page_number < 0 || page_number >= num_pages) {
        printf("Invalid Page Number!\n");
        return 1;
    }
    if (offset < 0 || offset >= page_size) {
        printf("Invalid Offset!\n");
        return 1;
    }

    // Check if the page is in memory
    frame_no = page_table[page_number];
    if (frame_no == -1) {
        printf("Page Fault! Page %d is not in memory.\n", page_number);
        return 1;
    }

    // Calculate physical address
    int physical_address = frame_no * page_size + offset;
    printf("Physical Address: %d\n", physical_address);

    return 0;
}
