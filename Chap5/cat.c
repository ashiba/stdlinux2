// p.86
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 2048

void doCat( char *file_path );
void die( char *msg );


int main( int argc, char *argv[] ){
    int i;

    if( argc < 2 ){
        fprintf( stderr, "arg error\n" );
        exit(1);
    }else{
        for( i=1; i<argc; ++i ){
            doCat( argv[i] );
        }
    }
    return 0;
}

void doCat( char *file_path ){
    char buf[BUFSIZE];
    ssize_t n;

    int fd = open( file_path, O_RDONLY );
    if( fd<0 ){
        die( file_path );
    }

    while(1){
        n = read( fd, buf, BUFSIZE );
        if( n == -1 ) die( file_path );
        if( n == 0 ) break;
        if( write( STDOUT_FILENO, buf, n ) == -1 ) die( file_path );
   }
   if( close(fd) < 0 ) die( file_path );
}


void die( char *msg ){
    printf( "%s\n", strerror(errno) );
    // perror( msg );
    exit(1);
}