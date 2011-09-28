#ifndef MSGNO_H
#define MSGNO_H

/* All message types */

#define DATA_TYPE      1
#define SWAP_TYPE      2

// for data server
#define DATA_ROWSIZE     1
#define DATA_ROWDATA     2
#define DATA_COLDATA     3
#define DATA_VALUE       4            
#define DATA_UPDATE      5

// for chat and role server
#define SWAP_JOIN        1
#define SWAP_LEAVE       2
#define SWAP_UNICAST     3
#define SWAP_BROADCAST   4

// for role client
#define ROLE_CREATE_ECHO    1
#define ROLE_CREATE_REPLY   2
#define ROLE_REMOVE         3
#define ROLE_ACTIVE         4 
#define ROLE_INTERACTIVE    5

#endif
