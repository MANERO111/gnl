*This project has been created as part of the 42 curriculum by aakioud.*

# Get Next Line

## Description

Get Next Line is a 42 School project that consists of implementing a function that reads a file descriptor line by line.

The function returns one line per call, including the newline character (`\n`) when present, until the end of the file is reached or an error occurs.

The main objective is to understand file descriptors, static variables, memory management, and the `read()` system call.

## Instructions

### Compilation

Compile the mandatory files using:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

`BUFFER_SIZE` determines the number of bytes read by each call to `read()`. If not defined, the project uses a default value.

### Usage

Include `get_next_line.h` in your source file and call:

```c
char *line;

line = get_next_line(fd);
while (line)
{
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
}
```

## Algorithm

The algorithm uses a static variable to preserve unread data between function calls.

1. **Reading:** Read data from the file descriptor into a temporary buffer using `read()`.
2. **Storing:** Append the newly read data to the static storage.
3. **Checking:** Continue reading until a newline character is found or EOF is reached.
4. **Extracting:** Return the line up to and including `\n`, if present.
5. **Preserving:** Keep the remaining data in static storage for the next call.
6. **Cleaning:** Free allocated memory when it is no longer needed.

This approach avoids reading the entire file at once and ensures that each call returns only one line.

## Bonus

The bonus part extends the mandatory implementation with:

- Support for multiple file descriptors simultaneously.
- Only one static variable to maintain the reading state of different file descriptors.

The implementation uses separate storage for each file descriptor, allowing independent reading without losing previously stored data.

## Resources

- [Linux read() Manual](https://man7.org/linux/man-pages/man2/read.2.html)
- [Linux open() Manual](https://man7.org/linux/man-pages/man2/open.2.html)
- [Static Variables in C](https://www.youtube.com/watch?v=MVeN3GDwjUg)

**AI Usage:** AI was used as a learning and educational assistant to understand file descriptors, static variables, memory management, and the reading algorithm. It also helped clarify concepts and review implementation logic.