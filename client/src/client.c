//
// Created by Igor Khanenko on 12/20/20.
//

#include "client.h"

void *read_server(void *data) {
    char buff[MAX];
    t_client *cli = (t_client *) data;

    while (read(cli->sockfd, buff, sizeof(buff))) {
        write(1, buff, strlen(buff));
        if ((strncmp(buff, "exit", 4)) == 0) {
            write(1, "Client Exit\n", 12);
            break;
        }
        bzero(buff, sizeof(buff));
    }
    return 0;
}

void func(int sockfd, t_client *cli) {
    char buff[MAX];
    int n;
    cJSON *LOGIN = cJSON_CreateString(cli->login);

    for (;;) {
        cJSON *send = cJSON_CreateObject();
        write(1, "\nEnter the string: ", 19);
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        cJSON *MASSAGE = cJSON_CreateString(buff);
        cJSON_AddItemToObject(send, "LOGIN", LOGIN);
        cJSON_AddItemToObject(send, "massage", MASSAGE);
        write(sockfd, cJSON_Print(send), sizeof(buff));
        bzero(buff, sizeof(buff));
    }
}

static void registration(t_client *cli) {
    char buff[20];

    write(1, "Please enter your login: ", 25);
    scanf("%s", buff);
    cli->login = strdup(buff);
    memset(buff, '\0', 20);
    write(1, "\nPlease enter your password: ", 29);
    scanf("%s", buff);
    cli->password = strdup(buff);
    memset(buff, '\0', 20);
    write(1, "\nPlease enter your nickname: ", 29);
    scanf("%s", buff);
    cli->nick = strdup(buff);
    memset(buff, '\0', 20);
    write(1, "\nPlease enter your birthday: ", 29);
    scanf("%s", buff);
    cli->birth = strdup(buff);
    memset(buff, '\0', 20);
}

int main(int argc, char *argv[]) {
    t_client *cli = (t_client *)malloc(sizeof(t_client));
    struct sockaddr_in servaddr;
    pthread_t thread;
    char *login_json;

    registration(cli);
    login_json = mx_create_json_profile(cli);

    // socket create and varification
    cli->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cli->sockfd == -1) {
        write(2, "ERROR, socket creation failed\n", 30);
        exit(0);
    }
    else
        write(1, "Socket successfully created...\n", 31);
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    if (argc == 2) {
        servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    }
    else {
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    }
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(cli->sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        write(2, "ERROR, connection with the server failed!\n", 42);
        exit(0);
    }
    else
        write(1, "Successfully connected to the server...\n", 40);

    write(cli->sockfd, login_json, mx_strlen(login_json));

    // function for chat
    pthread_create(&thread, NULL, read_server, cli);
    func(cli->sockfd, cli);

    // close the socket
    close(cli->sockfd);
}



//int main(int argc, char *argv[]) {
//    int sockfd;
//    int port_num;
//    int n;
//    struct sockaddr_in serv_addr;
//    struct hostent *server;
//    char buffer[1024];
//
//    if (argc < 3) {
//        printf("usage %s hostname port\n", argv[0]);
//    }
//
//    port_num = atoi(argv[2]);
//
//    sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (sockfd < 0)
//        write(2, "ERROR opening socket\n", 21);
//
//    server = gethostbyname(argv[1]);
//    if (server == NULL) {
//        write(2, "ERROR, no such host\n", 20);
//        exit(1);
//    }
//
//    memset((char *) &serv_addr, '\0', sizeof(serv_addr));
//    serv_addr.sin_family = AF_INET;
//
//    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
//
//    serv_addr.sin_port = htons(port_num);
//
//    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
//        write(2, "ERROR connecting\n", 17);
//
//    printf("Please enter the message: ");
//    memset(buffer, '\0', 256);
//    fgets(buffer, 255, stdin);
//
//    n = write(sockfd, buffer, strlen(buffer));
//    if (n < 0)
//        write(2, "ERROR writing to socket\n", 24);
//
//    memset(buffer, '\0', 256);
//
//    n = read(sockfd, buffer, 255);
//    if (n < 0)
//        write(2, "ERROR reading from socket\n", 26);
//    printf("%s\n", buffer);
//
//    close(sockfd);
//    return 0;
//}




//int main(int argc, char *argv[]) {
//    int sockfd = 0, n = 0;
//    char recvBuff[1024];
//    struct sockaddr_in serv_addr;
//
//    if(argc != 2) {
//        printf("\n Usage: %s <ip of server> \n",argv[0]);
//        return 1;
//    }
//
//    memset(recvBuff, '0',sizeof(recvBuff));
//    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//    {
//        printf("\n Error : Could not create socket \n");
//        return 1;
//    }
//
//    memset(&serv_addr, '0', sizeof(serv_addr));
//
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_port = htons(5000);
//
//    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
//    {
//        printf("\n inet_pton error occured\n");
//        return 1;
//    }
//
//    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
//    {
//        printf("\n Error : Connect Failed \n");
//        return 1;
//    }
//
//    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
//    {
//        recvBuff[n] = 0;
//        if(fputs(recvBuff, stdout) == EOF)
//        {
//            printf("\n Error : Fputs error\n");
//        }
//    }
//
//    if(n < 0)
//    {
//        printf("\n Read error \n");
//    }
//
//    return 0;
//}
