// p.100
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 2048

void doCount( const int fd );
void die();

int main( int argc, char *argv[] ){
    if( argc!=2 ){
        fprintf( stderr, "arg error" );
        exit(1);
    }else{
        int fd = open( argv[1], O_RDONLY );
        if( fd<0 ){
            die();
        }else{
            doCount( fd );
        }

        if( close(fd)<0 ) die();
    }
    return 0;
}

void doCount( const int fd ){
    int nlines = 0;
    int n, i;
    char buf[BUFSIZE];

    while(1){
        n = read( fd, buf, BUFSIZE );
        if( n==-1 ) die();
        if( n==0 ) break;

        for( i=0; i<n; ++i ){
            if( buf[i] == '\n' ){
                nlines++;
            }
        }
    }
    printf( "Line num : %d\n", nlines );
}

void die(){
    strerror( errno );
    exit(1);
}
