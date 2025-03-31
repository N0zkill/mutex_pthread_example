#include <iostream>
#include <pthread.h>
#include <mutex>
#include <unistd.h> 






std::mutex mtx;
int sharedData = 0;
void* writerThread(void* arg) {
    for (int i = 1; i <= 10; ++i) {
        mtx.lock();
        sharedData = i;
        std::cout << "Writer: wrote " << sharedData << std::endl;
        mtx.unlock();
        sleep(1); 
    } return nullptr;
}






void* readerThread(void* arg) {
    for (int i = 1; i <= 10; ++i) {
        mtx.lock();
        int value = sharedData;
        std::cout << "Reader: read " << value << std::endl;
        mtx.unlock();
        sleep(1); 
    } return nullptr;
}






int main() {
    pthread_t writer, reader;



    
    pthread_create(&writer, nullptr, writerThread, nullptr);
    pthread_create(&reader, nullptr, readerThread, nullptr);
    pthread_join(writer, nullptr);
    pthread_join(reader, nullptr);
    return 0;
}
