#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 6969
#define LENGTH 512


void error(const char *msg)
{
        perror(msg);
        exit(1);
}

int main(int argc, char *argv[])
{
        //Define the variable//
        int sockfd;
        int nsockfd;
        char revbuf[LENGTH];
        struct sockaddr_in server;

        // Get the Socket file descriptor //
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                fprintf(stderr, "ERROR! Can't obtain Socket Descriptor! (errno = %d)\n",errno);
                exit(1);
        }

        // Fill the socket address struct //
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        inet_pton(AF_INET, "192.168.65.8", &server.sin_addr);
        bzero(&(server.sin_zero), 8);
        
        // Try to connect the remote //
        if (connect(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
        {
                fprintf(stderr, "ERROR! Cannot connect to the host! (errno = %d)\n",errno);
                exit(1);
        }
        else
                printf("[+] Connected to server at port %d\n", PORT);

        FILE *fdr,*fdw;
        char filename[25],ch,sendline[100];
        int op;
        printf("\nEnter the desire file name to be sent to server :");
        scanf("%s",filename);

        fdr=fopen(filename,"r");
        fdw=fopen("sent.txt","w+");
        ch=fgetc(fdr);
        while(ch!=EOF){
                printf("%c",ch);
                op=(int)ch;
                        op=op-5;
                        fprintf(fdw,"%c",op);
                ch=fgetc(fdr);
        }
        fclose(fdw);
        fclose(fdr);

                char* fs_name = "sent.txt";
                char sdbuf[LENGTH];
                printf("\n[+]Sending %s to the Server.......... ", filename);
                FILE *fs = fopen(fs_name, "r");
                if(fs == NULL)
                {
                        printf("ERROR! File %s cannot be found.\n", filename);
                        exit(1);
                }

                bzero(sdbuf, LENGTH);
                int fs_block_sz;
                while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs)) > 0)
                {
                    if(send(sockfd, sdbuf, fs_block_sz, 0) < 0)
                    {
                        fprintf(stderr, "ERROR! Failed to send file %s. (errno = %d)\n", filename, errno);
                        break;
                    }
                    bzero(sdbuf, LENGTH);
                }
                printf("\n File %s from Client was successfully sent to the server!\n", filename);

        pclose;
        //printf("[Client] Connection lost.\n");
        return (0);
}
