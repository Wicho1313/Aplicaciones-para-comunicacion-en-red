/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    FILE *arch1, *arch2, *arch3;
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     char envia[200];
     char dd[2];//es para mas adelante saber la dificultad enviada por el cliente
     char aux[200];//GUardara la palabra o palabras extraidas de los txt
     int a=1, b=1, num_palabras=0, aleatorio=0; //Variables para determinar alaeatoriedad
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     
     int * p_int;
     p_int = (int *)malloc(sizeof(int));
     *p_int = 1;
     if((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,(char*)p_int, sizeof(int))== -1)||
        (setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE,(char*)p_int, sizeof(int))== -1)){
        printf("Error al intentar establecer opciones de socket.. %d",errno);
        exit (1);
       }
       free(p_int);

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);     
while(1){
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     //escogiendo el arreglo adecuado de acuerdo a la eleccion del cliente:
     printf("Here is the message: %s\n",buffer);
     dd[0] = buffer[0];
     dd[1] = '\0';
     if (strcmp(dd,"1")==0)//Para dificultad facil:
     {
         arch1 = fopen("facil.txt", "r");
         if (arch1 == NULL)
         {
             printf("No se pudo abrir facil.txt\n");
         }
         //Determinando numero de palabras del archivo:
         while(!feof(arch1)) {
             fgets(aux, 20, arch1);
             printf("%s   ",aux);
             printf("%d\n",a);
             a++;
         }
         num_palabras = a-3;
         srand(time(NULL));
         aleatorio = 1 + rand() % ((num_palabras+1) - 1);
         printf("palabras: %d Aleatorio: %d \n", num_palabras, aleatorio);
         fclose(arch1);//Cerramos porque fgets ya esta en uso y se debe restablecer para volver a usar
         arch1 = fopen("facil.txt", "r");
         //Encontrado la palabra aleatoria en el archivo:
         while(!feof(arch1)) {
            if (b == aleatorio)
            {
                fgets(envia, 20, arch1);
                printf("%s\n",envia);
                n = write(newsockfd,envia,strlen(envia)+1);
                printf("%d\n",b);
            }
                fgets(envia, 20, arch1);
             b++;
         }
      //   n = write(newsockfd,"jajaja",18);
         fclose(arch1);
         a = 1;num_palabras = 0; aleatorio = 0; b = 1;
     }
     if (strcmp(dd,"2")==0)//Para dificultad media:
     {
         arch2 = fopen("medio.txt", "r");
         if (arch2 == NULL)
         {
             printf("No se pudo abrir medio.txt\n");
         }
         //Determinando numero de palabras del archivo:
         while(!feof(arch2)) {
             fgets(aux, 40, arch2);
             printf("%s   ",aux);
             printf("%d\n",a);
             a++;
         }
         num_palabras = a-4;
         srand(time(NULL));
         aleatorio = 1 + rand() % ((num_palabras+1) - 1);
         printf("palabras: %d Aleatorio: %d \n", num_palabras, aleatorio);
         fclose(arch2);//Cerramos porque fgets ya esta en uso y se debe restablecer para volver a usar
         arch2 = fopen("medio.txt", "r");
         //Encontrado la palabra aleatoria en el archivo:
         while(!feof(arch2)) {
            if (b == aleatorio)
            {
                fgets(envia, 40, arch2);
                printf("%s\n",envia);
                n = write(newsockfd,envia,strlen(envia)+1);
                printf("%d\n",b);
            }
                fgets(envia, 40, arch2);
             b++;
         }
     //    n = write(newsockfd,"Dif medio",18);
         fclose(arch2);
         a = 1;num_palabras = 0; aleatorio = 0; b = 1;
     }
     if (strcmp(dd,"3")==0)
     {
         arch3 = fopen("dificil.txt", "r");
         if (arch3 == NULL)
         {
             printf("No se pudo abrir dificil.txt\n"); 
         }
         //Determinando numero de palabras del archivo:
         while(!feof(arch3)) {
             fgets(aux, 100, arch3);
             printf("%s   ",aux);
             printf("%d\n",a);
             a++;
         }
         num_palabras = a-2;
         srand(time(NULL));
         aleatorio = 1 + rand() % ((num_palabras+1) - 1);
         printf("palabras: %d Aleatorio: %d \n", num_palabras, aleatorio);
         fclose(arch3);//Cerramos porque fgets ya esta en uso y se debe restablecer para volver a usar
         arch3 = fopen("dificil.txt", "r");
         //Encontrado la palabra aleatoria en el archivo:
         while(!feof(arch3)) {
            if (b == aleatorio)
            {
                fgets(envia, 100, arch3);
                printf("%s\n",envia);
                n = write(newsockfd,envia,strlen(envia)+1);
                printf("%d\n",b);
            }
                fgets(envia, 100, arch3);
             b++;
         }
     //    n = write(newsockfd,"Dif dificil",18);
         fclose(arch3);
         a = 1;num_palabras = 0; aleatorio = 0; b = 1;
     }
         if (n < 0) error("ERROR writing to socket");
         close(newsockfd);

     
}//while
     close(sockfd);
     return 0; 
}
