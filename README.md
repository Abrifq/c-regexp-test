# RegExp Test

Little "hello-world" style project to test out `regcomp`, `regexec` and `fsetpos`.

Tech/libraries used: fsetpos/fgetpos from stdio, regcomp/regexec from regex.h

## main.c

The main function tries to [read a word](#getword) from stdin and check the word if it has "cat" inside of it.

### getWord

**Works with file/pipes but not with tty stdin reads for now.**

---

- Tries to consume the stdin until it finds a non-whitespace value,
- Saves the last position of stdin
- Counts how many non-space character there is (like strlen)
- Reverts stdin to the saved position
- Allocates just enough memory for the word
- Reads the word into the allocated memory, and then put the memory address of the word into the string pointer variable (`*((char**) stringPointer ) = (char*)word;` )

I can write the algorithm i had in my mind here but it's another beast to fight to implement it without bugs, lol.
