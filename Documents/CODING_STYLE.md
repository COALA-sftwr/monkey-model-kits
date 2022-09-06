# :koala: COALAs Coding Style :koala:

## Variables

Variables must be words, formatted in snake_case.

###### Examples:
* int this_integer;
* char this_character;
* bool this_boolean;

## Custom structures

Customisable structures, such as a struct in C, or a class in java must always have their first letter capitalized and be in a single word (if possible).

###### Examples:
* ```c
    typedef struct Strucutre {
        int this_integer;
        char this_character;
    } Structure_t;
  ```
* ```java
  public class Class {
    int this_integer;
    char this_character;
  }
  ```

## Functions

Function names have to be written in camelCase and must be as explicit as possible.
The opening bracket `{` has to be on the line following the name of the function, such as to be on the same line as the closing bracket `}`

###### Examples:

* ```c
  int thisFunction(void)
  {
    code...;
  }
  ```
* ```java
  static int thatFunction(void)
  {
    code...;
  }
  ``` 