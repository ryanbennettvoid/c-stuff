
// references:
// https://ops.tips/gists/a-minimal-tcp-client-in-c/
// https://www.csd.uoc.gr/~hy556/material/tutorials/cs556-3rd-tutorial.pdf
// https://www.binarytides.com/receive-full-data-with-recv-socket-function-in-c/
// https://stackoverflow.com/questions/5757290/http-header-line-break-style

#define HOST "93.184.216.34"
#define PORT 80
#define BUFFER_SIZE 256

#include <stdio.h>
#include <arpa/inet.h>  // internet/socket helpers
#include <unistd.h>     // `close` syscall
#include <string.h>     // string helpers

int main( int argc, char *argv[] )
{

  int fd,   // socket file descriptor
      ret;  // return value
  struct sockaddr_in addr = { 0 };
  char buf[ BUFFER_SIZE ];

  // AF_INET   IPV4
  // AF_INET6  IPV6
  // AF_UNIX   Local unix sockets
  addr.sin_family = AF_INET;

  // set byte order (little endian vs big endian)
  addr.sin_port = htons( PORT );

  // fill in address from string as bytes
  ret = inet_pton( AF_INET, HOST, &addr.sin_addr );
  if ( !ret )
  {
    fprintf( stderr, "failed to convert address: %s\n", HOST );
    return -1;
  }

  // open file descriptor
  if ( (fd = socket( AF_INET, SOCK_STREAM, 0 )) < 0 )
  {
    fprintf( stderr, "failed to open socket\n" );
  }

  printf( "connecting to %s:%d\n", HOST, PORT );

  // connect to host
  ret = connect( fd, (const struct sockaddr*) &addr, sizeof(addr) );
  if ( ret < 0 )
  {
    fprintf( stderr, "could not connect\n" );
    return -1;
  }

  char *msg = "\
GET / HTTP/1.1\r\n\
Host: example.com\r\n\
Connection: Close\r\n\
\r\n";
  
  // send message
  ret = send( fd, msg, strlen(msg), 0 );
  if ( ret < 0 )
  {
    fprintf( stderr, "could not send over socket\n" );
    return -1;
  }

  int n;
  // receive response
  int buflen = sizeof(buf) - 1;
  while ( (ret = recv( fd, buf, buflen, 0 )) > 0 )
  {
    // ret is number of bytes received
    int limit = ret < buflen ? ret : buflen;
    buf[ limit + 1 ] = '\0';
    puts( buf );
    memset( buf, 0, sizeof(buf) );
    n = 0;
  }

  if ( ret < 0 )
  {
    fprintf( stderr, "could not read from socket\n" );
  }

  // close file descriptor
  close( fd );

  return 0;
}