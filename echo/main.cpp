#include <iostream>
#include <cstdlib>  // exit() - для закрытия программы
#include <cstring>  // strcpy() - для копирования строки, strlen() - для определения длины строки
#include <unistd.h> // close() - для закрытия сокета
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

void errHandler(const char * why, const int exitCode = 1) {
    cerr << why << endl;
    exit(exitCode);
}

int main() {
    // структура с адресом (клиент)
    sockaddr_in selfAddr;
    selfAddr.sin_family = AF_INET; 
    selfAddr.sin_port = 0; // локальный порт может быть 0 (выбор системы)
    selfAddr.sin_addr.s_addr = INADDR_ANY; // любой локальный адрес

    // структура с адресом (сервер)
    sockaddr_in remoteAddr;
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(7); // используйте нужный порт сервера
    remoteAddr.sin_addr.s_addr = inet_addr("172.16.40.1"); // IP-адрес сервера

    // Буфер обмена для передачи и приема данных
    char buf[256];
    strcpy(buf, "Double RRn"); // Копируем строку
    int msgLen = strlen(buf); // Вычисляем длину строки

    // Создание сокета
    int mySocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mySocket == -1) {
        errHandler("Error open socket", 11);
    }

    // Связывание сокета с адресом
    int rc = bind(mySocket, (const sockaddr*) &selfAddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        errHandler("Error bind socket local address", 12);
    }

    // Установка соединения
    rc = connect(mySocket, (const sockaddr*) &remoteAddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        errHandler("Error connect socket with remote server", 13);
    }

    // Передача данных
    rc = send(mySocket, buf, msgLen, 0);
    if (rc == -1) {
        close(mySocket);
        errHandler("Error send message", 14);
    }
    cout << "Алабастер: " << buf << endl;

    // Прием данных
    rc = recv(mySocket, buf, sizeof(buf), 0);
    if (rc == -1) {
        close(mySocket);
        errHandler("Error receive answer", 15);
    }
    buf[rc] = '0';
    cout << "viperr: " << buf << endl;

    // Закрытие сокета
    close(mySocket);

    return 0;
}
