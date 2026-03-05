// demo.cpp
// Build: g++ -std=c++20 -O2 -pthread demo.cpp -o demo
//
// example.txt (one object per line):
//   hello
//   world
//   this creates objects
//
// Run: ./demo example.txt

#include <chrono>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <string>
#include <thread>

class LineObject {
public:
    explicit LineObject(std::string content) : m_content(std::move(content)) {}

    // Method consumer will call before object is destroyed
    const std::string& getContent() const { return m_content; }

private:
    std::string m_content;
};

// A minimal thread-safe queue for unique_ptr<T>
template <typename T>
class UniquePtrQueue {
public:
    void push(std::unique_ptr<T> item) {
        {
            std::lock_guard<std::mutex> lock(m_mtx);
            m_q.push(std::move(item));
        }
        m_cv.notify_one();
    }

    // Blocks until:
    //  - an item is available -> returns it
    //  - stop() called and queue empty -> returns nullptr
    std::unique_ptr<T> popBlocking() {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cv.wait(lock, [&] { return m_stop || !m_q.empty(); });

        if (m_q.empty()) {
            return nullptr; // stop requested and no work left
        }

        auto item = std::move(m_q.front());
        m_q.pop();
        return item;
    }

    void stop() {
        {
            std::lock_guard<std::mutex> lock(m_mtx);
            m_stop = true;
        }
        m_cv.notify_all();
    }

private:
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::queue<std::unique_ptr<T>> m_q;
    bool m_stop{false};
};

void consumerWorker(UniquePtrQueue<LineObject>& queue) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> sleepMs(50, 400); // random event spacing

    // open fstream for writing lines into file
    std::ofstream outFStream("output.txt");

    std::cout << "Consumer started, writing to output.txt...\n";

    if (!outFStream) {
        std::cerr << "Failed to open output file.\n";
        return;
    }else
    {
        outFStream << "Lines consumed from queue:\n";
    }

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs(gen)));

        auto obj = queue.popBlocking();
        if (!obj) {
            // stop requested and queue empty
            break;
        }else
        {
            // Simulate "Event" writing content to file before object is destroyed
            outFStream << obj->getContent() << "\n";
        }   

        // "Event" calls getContent()
        std::cout << "Event consumed: " << obj->getContent() << "\n";

        // When obj goes out of scope, LineObject is destroyed automatically.
    }
}

void producerWorker(UniquePtrQueue<LineObject>& queue, const std::string& path) {
    std::ifstream inFStream(path);
    if (!inFStream) {
        std::cerr << "Failed to open file: " << path << "\n";
        queue.stop(); // unblock consumer
        return;
    }

    std::string line;
    while (std::getline(inFStream, line)) {
        if (line.empty())
            continue;

        auto obj = std::make_unique<LineObject>(line);
        queue.push(std::move(obj));
    }

    // Signal no more items will be produced
    queue.stop();
}

int main(int argc, char** argv) {
    const std::string path = (argc >= 2) ? argv[1] : "example.txt";

    UniquePtrQueue<LineObject> queue;

    // Producer: reads each line and creates a new object (dynamic allocation via make_unique)
    std::thread producer(producerWorker, std::ref(queue), std::cref(path));

    // Consumer: simulates an asynchronous "random-time event" that dequeues & destroys objects
    std::thread consumer(consumerWorker, std::ref(queue));

    producer.join();
    consumer.join();

    std::cout << "Done.\n";
    return 0;
}
