#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        printf("%s", line);
        free(line);
    }
    line = get_next_line(fd);
    if (!line)
        printf("%s", line);
    free(line);
    close (fd);
    return (0);
}
