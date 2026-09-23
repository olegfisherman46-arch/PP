#include <iostream>
#include <queue>
#include <omp.h>
#include <chrono>
#include <thread>

int main() {
    std::queue<int> buffer;
    const int max_items = 5;
    bool producer_done = false;

    // Устанавливаем строго 2 потока
    omp_set_num_threads(2);

    #pragma omp parallel sections
    {
        // Секция Производителя
        #pragma omp section
        {
            for (int i = 1; i <= max_items; ++i) {
                std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Имитация работы
                #pragma omp critical
                {
                    buffer.push(i);
                    std::cout << "[Producer] Put: " << i << std::endl;
                }
            }
            #pragma omp critical
            {
                producer_done = true;
            }
        }

        // Секция Потребителя
        #pragma omp section
        {
            while (true) {
                bool is_empty = true;
                int item = -1;

                #pragma omp critical
                {
                    if (!buffer.empty()) {
                        item = buffer.front();
                        buffer.pop();
                        is_empty = false;
                    }
                }

                if (!is_empty) {
                    std::cout << "[Consumer] Got: " << item << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(400)); // Имитация обработки
                } else {
                    bool done;
                    #pragma omp critical
                    done = producer_done;
                    if (done && buffer.empty()) break;
                }
            }
        }
    }
    return 0;
}
