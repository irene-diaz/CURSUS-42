#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void print_maze(int height, int width, char **maze)
{
    int i = 0;
    while (i < height)
    {
        int j = 0;
        while (j < width)
        {
            putchar(maze[i][j]);
            j++;
        }
        putchar('\n');
        i++;
    }
}

char **next_gen(int height, int width, char **maze)
{
    // Allocate and zero-initialize `next`
    int i = 0;
    char **next = malloc(height * sizeof(char *));
    while (i < height)
    {
        int j = 0;
        next[i] = malloc(width * sizeof(char)); // fix: next[i], not maze[i]
        while (j < width)
        {
            next[i][j] = ' ';                   // fix: next[i][j]
            j++;
        }
        i++;
    }

    i = 0;
    while (i < height)
    {
        int j = 0;
        while (j < width)
        {
            int row_offset = -1;
            int neighbors = 0;
            while (row_offset <= 1)
            {
                int col_offset = -1;
                while (col_offset <= 1)
                {
                    if (!(row_offset == 0 && col_offset == 0))
                    {
                        int row_neighbors = row_offset + i;
                        int col_neighbors = col_offset + j;
                        if (row_neighbors >= 0 && row_neighbors < height
                            && col_neighbors >= 0 && col_neighbors < width)
                            if (maze[row_neighbors][col_neighbors] == '0')
                                neighbors++;
                    }
                    col_offset++;
                }
                row_offset++;
            }
            if (maze[i][j] == '0' && (neighbors == 2 || neighbors == 3))
                next[i][j] = '0';
            else if (maze[i][j] == ' ' && neighbors == 3)
                next[i][j] = '0';
            j++;
        }
        i++;
    }
    return next;
}

int main(int argc, char **argv)
{
    if (argc != 4)
        return 1;

    int width  = atoi(argv[1]);
    int height = atoi(argv[2]);
    int N      = atoi(argv[3]);

    char **maze = malloc(height * sizeof(char *));
    int i = 0;
    while (i < height)
    {
        maze[i] = malloc(width * sizeof(char));
        int j = 0;
        while (j < width)
        {
            maze[i][j] = ' ';
            j++;
        }
        i++;
    }

    int px = 0, py = 0, drawing = 0;
    char cmd;
    while (read(0, &cmd, 1) == 1)
    {
        if      (cmd == 'x')                  drawing = !drawing;
        else if (cmd == 'w' && py > 0)        py--;
        else if (cmd == 's' && py < height-1) py++;
        else if (cmd == 'a' && px > 0)        px--;
        else if (cmd == 'd' && px < width-1)  px++;
        if (drawing)
            maze[py][px] = '0';
    }

    i = 0;
    while (i < N)
    {
        char **next = next_gen(height, width, maze);
        // fix: free each row once, then the array once
        int j = 0;
        while (j < height)
        {
            free(maze[j]);
            j++;
        }
        free(maze);
        maze = next;
        i++;   // fix: was missing entirely
    }

    print_maze(height, width, maze);

    // fix: same correct pattern for final cleanup
    i = 0;
    while (i < height)
    {
        free(maze[i]);
        i++;
    }
    free(maze);

    return 0;
}