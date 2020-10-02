#include <stdio.h>
#include <winsock2.h>
#include <unistd.h>
#define close closesocket

//----------------------------------------------------------------------------------------------
const int black 	  = 0;
const int dark_blue   = 1;
const int dark_green  = 2;
const int dark_aqua   = 3;
const int dark_red 	  = 4;
const int dark_purple = 5;
const int dark_yellow = 6;
const int dark_white  = 7;
const int gray 		  = 8;
const int blue 		  = 9;
const int green 	  = 10;
const int aqua 		  = 11;
const int red 		  = 12;
const int purple 	  = 13;
const int yellow 	  = 14;
const int white 	  = 15;

void setTextColor(int backcolor, int forecolor) {
	HANDLE hConsole;
	int colorattribute;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	colorattribute = forecolor + backcolor * 16;
	SetConsoleTextAttribute(hConsole, colorattribute);
}
//----------------------------------------------------------------------------------------------


char ip[17];

init_winsock(void)
{
    WSADATA wsadata;
    int err;
    err=WSAStartup(MAKEWORD(2,2),&wsadata);
    if(err!=0)
    return 0;
    else
    return 1;
}

int main()
{
    system("title BATTAGLIA NAVALE - Server Host");
    int sock, clientsd1, clientvd1, clientsd2, clientvd2, port = 5000;
    char buffer[256];
    int flag;
    struct sockaddr_in saddr;
    
    if(!init_winsock())
    {
        setTextColor(black, red);
        printf("Errore durante l'inizializzazione di winsock2.\n");
        setTextColor(black, white);
        return -1;
    }
    
    if((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        setTextColor(black, red);
        printf("Errore durante la creazione del socket.\n");
        setTextColor(black, white);
        return -1;
    }
    
    saddr.sin_family = PF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(port);
    
    if((bind(sock, (struct sockaddr *) &saddr, sizeof(saddr))) < 0)
    {
        setTextColor(black, red);
        printf("Errore durante il binding del socket.\n");
        setTextColor(black, white);
        return -1;
    }
    
    if((listen(sock, 1)) < 0)
    {
        setTextColor(black, red);
        printf("Errore durante il settaggio del socket in listening.\n");
        setTextColor(black, white);
        return -1;
    }
    
    server_connect();
    setTextColor(black, aqua);
    printf("IP: %s",ip);
    printf("\nPORT: 5000");
    setTextColor(black, white);

    setTextColor(black, yellow);
    printf("\n\nIn attesa che un client si connetta...\n");
    clientsd1 = accept(sock, NULL, NULL);
    printf("\n\nCollegamento secondo schermo...\n");
    clientvd1 = accept(sock, NULL, NULL);
    setTextColor(black, green);
    printf("Si e' connesso il giocatore 1.\n\n");
    setTextColor(black, yellow);
    printf("In attesa che un'altro client si connetta...\n");
    clientsd2 = accept(sock, NULL, NULL);
    printf("\n\nCollegamento secondo schermo...\n");
    clientvd2 = accept(sock, NULL, NULL);
    setTextColor(black, green);
    printf("Si e' connesso il giocatore 2.\n\n"); 
    setTextColor(black, white);
    int band = 1;
    while(1)
    {
        if(band==1)
        {
            flag = 1;
            fflush(stdin);
            while (recv(clientsd1, buffer, 255, 0) >0 && flag == 1) 
            {
                send(clientsd2, buffer, sizeof(buffer), 0);
                printf("%s\a\n", buffer);
                flag = 0;
            }

            flag = 1;
            fflush(stdin);
            while (recv(clientsd2, buffer, 255, 0) >0 && flag == 1) 
            {
                send(clientvd1, buffer, sizeof(buffer), 0);
                printf("%s\a\n", buffer);
                flag = 0;
            }

            band=0;
        }
        else
        {
            flag = 1;
            fflush(stdin);
            while (recv(clientsd2, buffer, 255, 0) >0 && flag == 1) 
            {
                send(clientsd1, buffer, sizeof(buffer), 0);
                printf("%s\a\n", buffer);
                flag = 0;
            }

            flag = 1;
            fflush(stdin);
            while (recv(clientsd1, buffer, 255, 0) >0 && flag == 1) 
            {
                send(clientvd2, buffer, sizeof(buffer), 0);
                printf("%s\a\n", buffer);
                flag = 0;
            }

            band=1;
        }
        if(buffer[1]=='w')
        {
            send(clientsd2, buffer, sizeof(buffer), 0);
            send(clientsd1, buffer, sizeof(buffer), 0);
            send(clientvd2, buffer, sizeof(buffer), 0);
            send(clientvd1, buffer, sizeof(buffer), 0);

            sleep(2);
            
            return 0;
        }
    }
    
    setTextColor(black, red);
    printf("Connessione persa.\n");
    setTextColor(black, white);
    close(sock);
    WSACleanup();
    
    return 0;
}

int server_connect()
{
    int n,c;
    char vett[500];
    FILE *fd;
    int i,leng;
    system("(netsh interface ip show address | findstr 192.168.1) > ip.txt");
    fd=fopen("ip.txt", "r"); 
    if( fd==NULL ) 
    {
        perror("Errore in apertura del file");
        exit(1);
    }
    fscanf(fd, "%d", &n);
    c=0;
    for(i=0; i<=59; i++)
    {
        fscanf(fd, "    Indirizzo IP:                           %s", &vett[c]);
        c++;
    }
    leng=strlen(vett);
    for(c=0; c<leng; c++)
    {
        ip[c] = vett[c];
    }
    fclose(fd);
}