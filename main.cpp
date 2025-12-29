#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

// --- THE HEARTBEAT SERVER ---
void healthCheck() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5000); 

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) return;
    listen(server_fd, 3);

    while (true) {
        int new_socket = accept(server_fd, NULL, NULL);
        std::string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 2\n\nOK";
        send(new_socket, response.c_str(), response.length(), 0);
        close(new_socket);
    }
}

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

bool isTargetTime() {
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);
    return (ltm->tm_year + 1900 == 2025 && ltm->tm_mon + 1 == 12 && 
            ltm->tm_mday == 31 && ltm->tm_hour == 23 && 
            ltm->tm_min == 59 && ltm->tm_sec == 50);
}

int main() {
    std::thread hb(healthCheck);
    hb.detach();

    while (true) {
        clearScreen();
        
        while (!isTargetTime()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        clearScreen();

        for (int i = 10; i >= 1; i--) {
            std::cout << "\n\n\n\n\n";
            std::cout << "             🎆 PROJECT_OMEGA: COUNTDOWN 🎆" << std::endl;
            std::cout << "        -----------------------------------" << std::endl;
            std::cout << "                        " << i << "          " << std::endl;
            std::cout << "        -----------------------------------" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            clearScreen();
        }

        // FIXED TYPO ON LINE 76
        std::cout << "\n\n" << std::endl;
        std::cout << "  ██╗  ██╗ █████╗ ██████╗ ██████╗ ██╗   ██╗" << std::endl;
        std::cout << "  ██║  ██║██╔══██╗██╔══██╗██╔══██╗╚██╗ ██╔╝" << std::endl;
        std::cout << "  ███████║███████║██████╔╝██████╔╝ ╚████╔╝ " << std::endl;
        std::cout << "  ██╔══██║██╔══██║██╔═══╝ ██╔═══╝   ╚██╔╝  " << std::endl;
        std::cout << "  ██║  ██║██║  ██║██║     ██║        ██║   " << std::endl;
        std::cout << "  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝        ╚═╝   " << std::endl;
        std::cout << "\n" << std::endl;
        std::cout << "  ███╗   ██╗███████╗██╗    ██╗" << std::endl;
        std::cout << "  ████╗  ██║██╔════╝██║    ██║" << std::endl;
        std::cout << "  ██╔██╗ ██║█████╗  ██║ █╗ ██║" << std::endl;
        std::cout << "  ██║╚██╗██║██╔══╝  ██║███╗██║" << std::endl;
        std::cout << "  ██║ ╚████║███████╗╚███╔███╔╝" << std::endl;
        std::cout << "  ╚═╝  ╚═══╝╚══════╝ ╚══╝╚══╝ " << std::endl;
        std::cout << "\n" << std::endl;
        std::cout << "  ██╗   ██╗███████╗ █████╗ ██████╗ " << std::endl;
        std::cout << "  ╚██╗ ██╔╝██╔════╝██╔══██╗██╔══██╗" << std::endl;
        std::cout << "   ╚████╔╝ █████╗  ███████║██████╔╝" << std::endl;
        std::cout << "    ╚██╔╝  ██╔══╝  ██╔══██║██╔══██╗" << std::endl;
        std::cout << "     ██║   ███████╗██║  ██║██║  ██║" << std::endl;
        std::cout << "     ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝" << std::endl;
        std::cout << "\n" << std::endl;
        std::cout << "           🎉 2026! 🎉" << std::endl;
        std::cout << "\n  May this year be better than the last!" << std::endl;
        std::cout << "   Wishing you joy, success, and happiness!" << std::endl;
        std::cout << " __________________________________________" << std::endl;   
        std::cout << "__________________ by TX __________________  " << std::endl;

        std::this_thread::sleep_for(std::chrono::hours(1));
    }
    return 0;
}
