#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#define close closesocket
#include <conio.h>
#include <windows.h>
#include "client.c"


//Start the client
void client()
{   
    system("cls");
    system("title BATTAGLIA NAVALE - Giocatore 2");
    richiesta_ip();
    mainClient();
    fill();
    print();
    while(1)
    {
        todo();
    }
}

//Start the server and a client
void server()
{
    system("cls");
     system("title BATTAGLIA NAVALE - Giocatore 1");
    system("start server.exe");
    sleep(2);
    server_connect();
    mainClient();
    fill();
    print();
    while(1)
    {
        todo();
    }
}

//Menu
int main()
{
	system("title BATTAGLIA NAVALE - by David Agostini, Daniel Fontanari");
    int scelta;
    setTextColor(black, red);
    printf("\n\n\n\n\n\n\t\t\t\tBATTAGLIA NAVALE\n\n");
    setTextColor(black, white);
    printf("\t\tProgrammed by: David Agostini, Daniel Fontanari\n\n\n");
    setTextColor(black, yellow);
    printf("\t\t\t1. Crea una sessione\n");
    setTextColor(black, green);
    printf("\t\t\t2. Partecipa ad una sessione\n");
    setTextColor(black, white);
    printf("\n\t\t\tScelta:  ");
    scanf("%d",&scelta);

    if(scelta == 1)
    {
        server();
    }
    else if(scelta == 2)
    {
        client();
    }
    else
    {
        system("cls");
        main();
        
    }

}
