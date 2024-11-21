#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char buffer[256] = {0}, trace_info[12][16] = {0}, *token;
    int packets_received = 0, packets_dropped = 0;

    if(argc != 3) {
        printf("Usage: ./packet_calculator <Tracer File> <Node Number>\n");
        return -1;
    }

    FILE *tracer_file = fopen(argv[1], "r");
    if(tracer_file == NULL) return -1;
    
    while(fgets(buffer, sizeof(buffer), tracer_file) != NULL) {
        token = strtok(buffer, " ");
        if((strcmp(token, "r") == 0) || (strcmp(token, "d") == 0)) {
            int i = 0;
            while((token != NULL) || (i < 12)) {
                strcpy(trace_info[i], token);
                token = strtok(NULL, " ");
                i++;
            }

            if((strcmp(trace_info[3], argv[2]) == 0) && (strcmp(trace_info[0], "r") == 0)) {
                packets_received++;
            }

            if((strcmp(trace_info[3], argv[2]) == 0) && (strcmp(trace_info[0], "d") == 0)) {
                packets_dropped++;
            }
        }
        else {
            continue;
        }
    }
    fclose(tracer_file);

    printf("Packets received at node %s: %d\n", argv[2], packets_received);
    printf("Packets dropped at node %s: %d\n", argv[2], packets_dropped);
    printf("Packet loss rate: %.2f%%\n", (float)packets_dropped / packets_received * 100);

    return 0;
}