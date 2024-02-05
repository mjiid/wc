# Word Count Utility

This project is my own reimplementation of the Unix command-line utility wc. It provides word count statistics for a given file. The program supports counting bytes, lines, words, and characters. It can also handle multi-byte characters based on the locale of the computer.

## Features

- Count bytes (-c)
- Count lines (-l)
- Count words (-w)
- Count characters (-m) [depends on the locale](https://docs.oracle.com/cd/E19253-01/817-2521/overview-39/index.html)

## Usage

```bash
$ ./wc [OPTION] [FILE]
```


## Options:
**-c**: Outputs the number of bytes.  
**-l**: Outputs the number of lines.  
**-w**: Outputs the number of words.  
**-m**: Outputs the number of characters (handles multi-byte characters based on the locale).  


## Example:
This command will display counts for all metrics.
```bash
$ ./wc sample.txt
42      67      1337    sample.txt
```


## Build and Run
To build the program, you can use a standard C compiler:
```bash
$ gcc wc.c helper.c -o wc
```

To run the program:
```bash
$ ./wc [OPTION] [FILE]
```


