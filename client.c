#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
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

int t[12][12]; // matrice della tabella :P
char letterc; //variabile letter in char
int number,letter,rotation; //cose che vengono richieste
int B4=1,B3=2,B2=3,B1=4; //barche
int richiestabarchecontatore=11; // questa si spiega da sola
int sock, port = 5000, flag = 1;
char ip[17];
char buffer[256];
char buffer2[256];
struct sockaddr_in saddr;
int c,r;
int ruolo = 1;
int blocchinave = 21;
int mk;

int todo()
{
	setTextColor(black, white);
    fflush(stdout);
    fflush(stdin);
    request();
    fflush(stdout);
    fflush(stdin);
    place();
    fflush(stdout);
    fflush(stdin);
    system("cls");
    update();
}

int place()
{
    int c=0;
    int nnum=number,llet=letter;
    if(rotation==1)
    {
        if(B4>0)
        {
            if(controlboat(B4,number,letter,4,1)==1)
            {
                for(c=0;c!=4;c++)
                {
                    t[number][letter]=1;
                    number++;
                }
                B4--;
                fflush(stdin);
                fflush(stdout);
            }
            else
            {
                richiestabarchecontatore++;
                system("cls");
                update();
                todo();
                fflush(stdin);
                fflush(stdout);
            }
        }
        else if(B3>0)
        {
            if(controlboat(B3,number,letter,3,1)==1)
            {
                nnum--;
                llet--;
                c=1;
                while(c<14)
                {
                    if(t[nnum][llet]==1)
                    {
                        richiestabarchecontatore++;
                        system("cls");
                        update();
                        todo();
                        fflush(stdin);
                        fflush(stdout);
                    }                                               
                    if(c<3)
                    {
                        llet++;
                    }
                    if(c>=3&&c<=6)
                    {
                        nnum++;
                    }
                    if(c>6&&c<9)
                    {
                        llet--;
                    }
                    if(c>=9)
                    {
                        nnum--;
                    }
                    c++;
                }
                for(c=0;c!=3;c++)
                {
                    t[number][letter]=1;
                    number++;
                    fflush(stdin);
                    fflush(stdout);
                }
                B3--;
            }
            else
            {
                richiestabarchecontatore++;
                system("cls");
                update();
                todo();
                fflush(stdin);
                fflush(stdout);
            }
        }
        else if(B2>0)
        {
            if(controlboat(B2,number,letter,2,1)==1)
            {
                 nnum--;
                llet--;
                c=1;
                while(c<11)
                {
                    if(t[nnum][llet]==1)
                    {
                        richiestabarchecontatore++;
                        system("cls");
                        update();
                        todo();
                        fflush(stdin);
                        fflush(stdout);
                    }
                    if(c<3)
                    {
                        llet++;
                    }
                    if(c>=3&&c<=5)
                    {
                        nnum++;
                    }
                    if(c>5&&c<8)
                    {
                        llet--;
                    }
                    if(c>=8)
                    {
                        nnum--;
                    }
                    c++;
                }
                for(c=0;c!=2;c++)
                {
                    t[number][letter]=1;
                    number++;
                    fflush(stdin);
                    fflush(stdout);
                }
                B2--;
                fflush(stdin);
                fflush(stdout);
            }
            else
            {
                richiestabarchecontatore++;
                system("cls");
                update();
                todo();
                fflush(stdin);
                fflush(stdout);
            }
        }
        else
        {
            nnum--;
            llet--;
            c=1;
            while(c<9)
            {
                if(t[nnum][llet]==1)
                {
                    richiestabarchecontatore++;
                    system("cls");
                    update();
                    todo();
                    fflush(stdin);
                    fflush(stdout);
                }
                if(c<3)
                {
                    llet++;
                }
                if(c>=3&&c<=4)
                {
                    nnum++;
                }
                if(c>4&&c<7)
                {
                    llet--;
                }
                if(c>=7)
                {
                    nnum--;
                }
                c++;
            }
            for(c=0;c!=1;c++)
            {
                t[number][letter]=1;
                number++;
                fflush(stdin);
                fflush(stdout);
            }
            B1--;
        }
    }
    else if (rotation==2)
    {
        if(B4>0)
        {
            if(controlboat(B4,number,letter,4,2)==1)
            {
                for(c=0;c!=4;c++)
                {
                    t[number][letter]=1;
                    letter++;
                    fflush(stdin);
                    fflush(stdout);
                }
                B4--;
            }
            else
            {
                richiestabarchecontatore++;
                update();
                todo();
                fflush(stdin);
                fflush(stdout);
            }
        }
        else if(B3>0)
        {
            nnum--;
            llet--;
            c=1;
            while(c<14)
            {
                if(t[nnum][llet]==1)
                {
                    richiestabarchecontatore++;
                    system("cls");
                    update();
                    todo();
                    fflush(stdin);
                    fflush(stdout);
                }
                if(c<3)
                {
                    nnum++;
                }
                if(c>=3&&c<=6)
                {
                    llet++;
                }
                if(c>6&&c<9)
                {
                    nnum--;
                }
                if(c>=9)
                {
                    llet--;
                }
                c++;
            }
            if(controlboat(B3,number,letter,3,2)==1)
            {
                for(c=0;c!=3;c++)
                {
                    t[number][letter]=1;
                    letter++;
                    fflush(stdin);
                    fflush(stdout);
                }
                B3--;
            }
            else
            {
                richiestabarchecontatore++;
                system("cls");
                update();
                todo();
                fflush(stdin);
                fflush(stdout);
            }
        }
        else if(B2>0)
        {
            nnum--;
            llet--;
            c=1;
            while(c<11)
            {
                if(t[nnum][llet]==1)
                {
                    richiestabarchecontatore++;
                    system("cls");
                    update();
                    todo();
                    fflush(stdin);
                    fflush(stdout);
                }
                if(c<3)
                {
                    nnum++;
                }
                if(c>=3&&c<=5)
                {
                    llet++;
                }
                if(c>5&&c<8)
                {
                    nnum--;
                }
                if(c>=8)
                {
                    llet--;
                }
                c++;
            }
            if(controlboat(B2,number,letter,2,2)==1)
            {
                for(c=0;c!=2;c++)
                {
                    t[number][letter]=1;
                    letter++;
                    fflush(stdin);
                    fflush(stdout);
                }
                B2--;
            }
            else
            {
                richiestabarchecontatore++;
                system("cls");
                update();
                todo();
                fflush(stdin);
                fflush(stdout);
            }
        }
        else
        {
            nnum--;
            llet--;
            c=1;
            while(c<9)
            {
                if(t[nnum][llet]==1)
                {
                    richiestabarchecontatore++;
                    system("cls");
                    update();
                    todo();
                    fflush(stdin);
                    fflush(stdout);
                }
                if(c<3)
                {
                    nnum++;
                }
                if(c>=3&&c<=4)
                {
                    llet++;
                }
                if(c>4&&c<7)
                {
                    nnum--;
                }
                if(c>=7)
                {
                    llet--;
                }
                c++;
            }
            if(controlboat(B1,number,letter,1,2)==1)
            {
                for(c=0;c!=1;c++)
                {
                    t[number][letter]=1;
                    letter++;
                    fflush(stdin);
                    fflush(stdout);
                }
                B1--;
            }
            else
            {
                richiestabarchecontatore++;
                system("cls");
                update();
                todo();
                fflush(stdin);
                fflush(stdout);
            }
        }
    }
}

int request()
{
    richiestabarchecontatore--;
    letterc=' ';
    number=0;

    
    /*richiestabarchecontatore = 0;
    t[1][1]=1;
    t[1][2]=1;
    t[1][3]=1;
    t[1][4]=1;

    t[3][1]=1;
    t[3][2]=1;
    t[3][3]=1;

    t[5][1]=1;
    t[5][2]=1;
    t[5][3]=1;

    t[7][1]=1;
    t[7][2]=1;

    t[9][1]=1;
    t[9][2]=1;

    t[1][6]=1;
    t[1][7]=1;

    t[1][6]=1;

    t[3][6]=1;

    t[5][6]=1;

    t[7][6]=1;

    blocchinave=2;*/
    

    if(richiestabarchecontatore==10)
    {
        printf("(barca da 4)");
    }
    else if(richiestabarchecontatore>7)
    {
        printf("(barca da 3)");
    }
    else if(richiestabarchecontatore>4)
    {
        printf("(barca da 2)");
    }
    else if(richiestabarchecontatore>0)
    {
        printf("(barca da 1)");
    }
    else if(richiestabarchecontatore==0)
    {
        game();
    }
    setTextColor(black, yellow);
    printf("\n\nInserisci le coordinate: ");
    fflush(stdin);
    fflush(stdout);
    scanf("%c,%d",&letterc,&number);
    setTextColor(black, white);
    translate(1);
    numcontrol(2);
    if(richiestabarchecontatore>4)
    {
        fflush(stdout);
        fflush(stdout);
        setTextColor(black, green);
        printf("\n\n\n1.Verticale\n2.Orrizzontale\n\nInserisci la rotazione:  ");
        fflush(stdin);
        scanf("%d",&rotation);
        setTextColor(black, white);
    }
}

int translate(int x)
{
    fflush(stdout);
    if(letterc=='A'||letterc=='a')
    {
        letter=1;
    }
    else if(letterc=='B'||letterc=='b')
    {
        letter=2;
    }
    else if(letterc=='C'||letterc=='c')
    {
        letter=3;
    }
    else if(letterc=='D'||letterc=='d')
    {
        letter=4;
    }
    else if(letterc=='E'||letterc=='e')
    {
        letter=5;
    }
    else if(letterc=='F'||letterc=='f')
    {
        letter=6;
    }
    else if(letterc=='G'||letterc=='g')
    {
        letter=7;
    }
    else if(letterc=='H'||letterc=='h')
    {
        letter=8;
    }
    else if(letterc=='I'||letterc=='i')
    {
        letter=9;
    }
    else if(letterc=='J'||letterc=='j')
    {
        letter=10;
    }
    else
    {
        if(x != 0)
        {
            system("cls");
            richiestabarchecontatore++;
            update();
            todo();
        }
        else 
        {
            system("cls");
            game();
        }
    }
}

int print()
{
    int c,r,n=1;
    printf("  |-A---B---C---D---E---F---G---H---I---J-|");
    for(c=1;c!=11;c++)
    {
        printf("\n  |---------------------------------------|\n");
        if(n==10)
        {
            printf("%d ",n);
            fflush(stdout);
        }
        else
        {
            printf("%d  ",n);
        }
        n++;
        for(r=1;r!=11;r++)
        {
            if(t[c][r]==0)
            {
                printf("   |");
            }
            else if(t[c][r]==1)
            {
                setTextColor(black, yellow);
                printf(" + ");
                setTextColor(black, white);
                printf("|");
            }
            else if(t[c][r]==2)
            {
                setTextColor(black, red);
                printf(" x ");
                setTextColor(black, white);
                printf("|");
            }
            else
            {
                setTextColor(black, aqua);
                printf(" O ");
                setTextColor(black, white);
                printf("|");
            }
        }
    }
    printf("\n  |---------------------------------------|\n");
    fflush(stdout);
}

int fill()
{
    fflush(stdout);
    for(c=0;c!=11;c++)
    {
        for(r=0;r!=11;r++)
        {
            t[c][r]=0;
        }
    }
}

int update()
{
    print();
    todo();
}

int controlboat(int boat,int num,int let,int n,int rot)
{
    int c;
    if(rot==1)
    {
        if(boat>0)
        {
            int backup;
            fflush(stdout);
            backup = num;
            for(c=0;c!=n;c++)
            {
                if(num<1)
                {
                    return 0;
                }
                else if(num>10)
                {
                    return 0;
                }
                num++;
            }
            num = backup;
            return 1;
        }
    }
    if(rot==2)
    {
        if(boat>0)
        {
            int backup;
            fflush(stdout);
            backup = let;
            for(c=0;c!=n;c++)
            {
                if(let<1)
                {
                    return 0;
                }
                else if(let>10)
                {
                    return 0;
                }
                let++;
            }
            let = backup;
            return 1;
        }
    }
    fflush(stdout);
}

int numcontrol(int hand)
{
    if(number<1 || number>10)
    {
        system("cls");
        if(hand==0)
        {
            if(ruolo==2)
            {
                game();
            }
            else if(ruolo==1)
            {
                game();
            }
            
        }
        else
        {
            richiestabarchecontatore++;
            update();
            fflush(stdout);
            todo(); 
        }
    }
}

int richiesta_ip()
{
    ruolo = 2;
    printf("Server IP: ");
    scanf("%16s", ip);
}


int server_connect()
{
    int n,c;
    char vett[100];
    FILE *fd;
    int i,leng;
    system("(netsh interface ip show address | findstr 192.168.1) > result.txt");
    fd=fopen("result.txt", "r"); 
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

int Hit(int f,int s)
{
    if(t[s][f]==0)
    {
        //colpo a vuoto
        t[s][f]=3;
        mk=3;
    }
    else if(t[s][f]==1)
    {
        //colpito
        t[s][f]=2;
        mk=2;
        blocchinave--;
        if(blocchinave==1)
        {
            defeat();
        }
    }  
}

int game()
{
    system("del ip.txt");
    system("del result.txt");
    system("del gmon.out");
    system("cls");
    print();
    if(ruolo == 1)
    {//clientsd1
        while(1)
        {
            fflush(stdin);
            fflush(stdout);
            setTextColor(black, green);
            printf("ATTACCA il nemico!");
            setTextColor(black, yellow);
            printf("\n\nInserisci le coordinate: ");
            scanf("%c,%d",&letterc,&number);
            setTextColor(black, white);
            translate(0);
            numcontrol(0);
            buffer[1] = letter;
            buffer[2] = number;
            send(sock, buffer, sizeof(buffer), 0);
            flag = 0;
            system("cls");
            fflush(stdin);
            fflush(stdout);
            print();
            printf("\n\nTurno dell'avversario...");
            while(flag == 0)
            {
                while (recv(sock, buffer, 255, 0) > 0 && flag == 0) 
                {
                    if(buffer[1]=='w')
                    {
                        victory();
                    }
                    Hit(buffer[1],buffer[2]);
                    buffer[3] = mk;
                    send(sock, buffer, sizeof(buffer), 0);
                    flag = 1;
                }
            }
            system("cls");
            print();
        }
    }
    else if(ruolo == 2)
    {//clientsd2
        while(1)
        {
            flag = 0;
            system("cls");
            print();
            printf("\n\nTurno dell'avversario...");
            while(flag == 0)
            {
                while (recv(sock, buffer, 255, 0) > 0 && flag == 0) 
                {
                    if(buffer[1]=='w')
                    {
                        victory();
                    }
                    Hit(buffer[1],buffer[2]);
                    buffer[3] = mk;
                    send(sock, buffer, sizeof(buffer), 0);
                    flag = 1;
                }
            }
            system("cls");
            print();
            fflush(stdin);
            fflush(stdout);
            setTextColor(black, yellow);
            printf("\n\nInserisci le coordinate: ");
            scanf("%c,%d",&letterc,&number);
            setTextColor(black, white);
            translate(0);
            numcontrol(0);
            buffer[1] = letter;
            buffer[2] = number;
            send(sock, buffer, sizeof(buffer), 0);
        }
    }
}

int victory()
{
    system("cls");
    fflush(stdin);
    fflush(stdout);
    print();
    setTextColor(black, green);
    printf("Complimenti! Hai vinto.\n");
    system("pause");
    exit(0);
}

int defeat()
{
    system("cls");
    buffer[1] = 'w';
    send(sock, buffer, sizeof(buffer), 0);
    fflush(stdin);
    fflush(stdout);
    print();
    setTextColor(black, green);
    printf("Peccato! Hai perso.\n");
    system("pause");
    exit(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int init_winsock(void)
{
    WSADATA wsadata;
    int err;
    err=WSAStartup(MAKEWORD(2,2),&wsadata);
    if(err!=0)
    return 0;
    else
    return 1;
}

int mainClient()
{
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
    saddr.sin_addr.s_addr = inet_addr(ip);
    saddr.sin_port = htons(port);

    if(connect(sock, (struct sockaddr *) &saddr, sizeof(saddr)) < 0)
    {
        setTextColor(black, red);
        printf("Errore durante la connessione a %s:%d\n", ip, port);
        setTextColor(black, white);
        return -1;
    }
    setTextColor(black, green);
    printf("Connessione correttamente stabilita con %s:%d\n\n", ip, port);

    int n,c;
    char vett[100];
    FILE *fd;
    int i,leng;
    system("echo > vd.txt");
    fd=fopen("vd.txt", "w"); 
    if( fd==NULL ) 
    {
        perror("Errore in apertura del file");
        exit(1);
    }
    fputs(ip,fd);
    fclose(fd);    
    system("start client_vd.exe");
    setTextColor(black, white);
    return 0;
}

int sendMSG()
{
    while(1)
    {
        while (recv(sock, buffer2, 255, 0) > 0 && flag ==1) 
        {
            printf("%s\a\n", buffer2);
            flag = 0;
        }
        fflush(stdin);
        printf("> ");
        fgets(buffer,256,stdin);
        send(sock, buffer, sizeof(buffer), 0);
        flag = 1;
    }
}
