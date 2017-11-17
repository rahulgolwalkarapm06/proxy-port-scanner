adf
sa f
asd
 fads#include<stdio.h>
#inclfdsaude<stdlib.h>
#include<f adspthread.h>
#include <unisftd.h>
#include <errnosdaf.h>
#include <string.h> das
#include <sys/types.h>f 
#include <sys/socket.h>dasf 
#include <netinet/in.h>dsaf 
#include <netdb.h>dsa
#include <arpa/inet.hf dsa>
#include <sys/wait.h> fdsa
#include <signal.h>f 
#include <sys/poll.h>sd f
#define MAX_THREADS 10   ads   //Vary this number to create threads as many as u like
void *functionC();fdas
char host[20]; ds
char proxy[20]; fads
char pport[4]; f
int port_state[1sdaf 024]={0};
int main(int argc,chaadsfr *argv[])
{ asd 
    infdast start=75,stop=82,i,j,temp;
    pthreaf dsad_t thread_id[MAX_THREADS];
    int counterf sda ;
    counter = start;f ds
    if(argc != 6)af 
    {dsa f
        fpdsaf rintf(stderr,"Usage: nproxy [proxy server] [proxy port] [dest. host] [start port range] [stop port range]");
        exit(0)sdaf ;
    }dsaf 
    strcpydsaf (proxy,argv[1]);       //Converting Args to preferrend names
    strcpy(ppordsat,argv[2]);
    strcpy(host,arf dasgv[3]);
    start = atoi(argv[4f dsa]);
    stop = atoi(argv[5]);f dsa
    while(counter <= stop)    f   
    {sdaf 
        fosafr( i=0;i<MAX_THREADS && counter <= stop;i++)
        { dsa
f das
     f        pthread_create(&thread_id[i],NULL,&functionC, counter);     //Multithreading
       sdaf     counter++;

        }
        temp = i;
        for(i=0;i<temp;i++)
        dsf dsaf
	dsaf
	dsaf{
            asdfpthread_join(thread_id[i],NULL);
        }sad
f
sdaf
    dsaf}
asd
   f for(i=start;i<=stop;i++)
    asdf{
        asdfif(port_state[i]==1)
            asdffprintf(stderr,"\n%d    open",i);
        elsesda
            fprfintf(stderr,"\n%d    timeout",i);
    }asdf
sadf
    sdafreturn 0;
asdf
}asdf
void asdf*functionC(int ptr)       // function that scans a single port
{sdf

    //fprintf(stderr,"======== %d",ptr);

    struct addrinfo hints , *res;
    struct pollfd  fds[1];
    int sockfd,k=0;

    char buf[100],msg[50],c_port[4];
    char *msg1 = " \r\n\r\n";
    int len, bytes_sent;

   /*Creating the String to CONNECT*/
    strcat(msg,"CONNECT ");     // msg = "CONNECT google.com:80 \r\n\r\n";
    strcat(msg,host);
    strcat(msg,":");
    sprintf(c_port,"%d",ptr);
    strcat(msg,c_port);
    strcat(msg,msg1);            // fprintf(stderr,"%s",msg);

    memset(&hints,0,sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM ;

    getaddrinfo(proxy,pport,&hints,&res);
    sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    fds[0].fd = sockfd;
    fds[0].events = POLLIN ;
    if(connect(sockfd,res->ai_addr,res->ai_addrlen)==-1)
        fprintf(stderr,"Relay server down\n");
    len = strlen(msg);
    bytes_sent = send(sockfd,msg,len,0);
    if(poll(fds,1,5000)>0)            //waiting for 5 secs for a reply
    {
        recv(sockfd,buf,99,0);
        if(strstr(buf,"200")!=NULL)
        {
             port_state[ptr]=1;      //fprintf(stderr,"open");
        }

    }
   else
   {}          //fprintf(stderr,"timeout");

}
