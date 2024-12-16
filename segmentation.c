#include <stdio.h>

int main() {
    int num_segments;

    // Input number of segments
    printf("Enter the number of segments: ");
    scanf("%d", &num_segments);

    // Segment Table
    int base_address[num_segments], limit[num_segments];

    // Input base and limit for each segment
    printf("Enter the base address and limit for each segment:\n");
    for (int i = 0; i < num_segments; i++) {
        printf("Segment %d - Base Address: ", i);
        scanf("%d", &base_address[i]);
        printf("Segment %d - Limit: ", i);
        scanf("%d", &limit[i]);
    }

    // Logical Address Input
    int segment_number, offset;
    printf("\nEnter the logical address (in the format SegmentNumber:Offset): ");
    scanf("%d:%d", &segment_number, &offset);

    // Validate the segment number and offset
    if (segment_number < 0 || segment_number >= num_segments) {
        printf("Error: Invalid Segment Number!\n");
        return 1;
    }

    if (offset < 0 || offset >= limit[segment_number]) {
        printf("Error: Offset exceeds segment limit!\n");
        return 1;
    }

    // Calculate physical address
    int physical_address = base_address[segment_number] + offset;
    printf("Physical Address: %d\n", physical_address);

    return 0;
}
