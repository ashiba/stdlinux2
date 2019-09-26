// p.100
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 2048

void doCat( const int fd );
void die( char *msg );


int main( int argc, char *argv[] ){
    int i;
    int fd;

    if( argc < 2 ){
        doCat( STDIN_FILENO );
    }

    for( i=1; i<argc; ++i ){
        fd = open( argv[i], O_RDONLY );        
        if( fd<0 ){
            die( argv[i] );
        }
        doCat( fd );
        if( close( fd ) < 0 ) die( argv[i] );
    }

    return 0;
}

void doCat( const int fd ){
    char buf[BUFSIZE];
    ssize_t n;

    while(1){
        n = read( fd, buf, BUFSIZE );
        if( n == -1 ) die( "" );
        if( n == 0 ) break;
        if( write( STDOUT_FILENO, buf, n ) == -1 ) die( "" );
   }
}


void die( char *msg ){
    printf( "%s\n", strerror(errno) );
    // perror( msg );
    exit(1);
}