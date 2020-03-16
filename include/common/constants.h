#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define MEM_PAGE_SIZE 1024*4 // 4 pages

#define INFILE_DELIM ','

// Error Codes below
#define SUCCESS 0
#define INPUT_WAIT 1

#define ERR_ADDRESS 100
#define ERR_NOFILE 101
#define ERR_NULL 102
#define ERR_INVALID_OPCODE 103
#define ERR_INVALID_MEM_MODE 104
#define ERR_NO_ELEMENT 105
#define ERR_NO_PAGE 106
#define ERR_DUP_PAGE 107

#define MEM_MODE_POSITION 0
#define MEM_MODE_IMMEDIATE 1
#define MEM_MODE_RELATIVE 2

#endif
