#pragma once
#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
  using Task = std::function<void()>;
  explicit ThreadPool(size_t size) {
    // auto size = std::thread::hardware_concurrency();
    start(size);
  };
  ~ThreadPool() { stop(); }
  template <class T> auto enqueue(T task) -> std::future<decltype(task())> {
    auto wrapper = std::make_shared<std::packaged_task<decltype(task())()>>(
        std::move(task));
    {
      std::unique_lock<std::mutex> lock{vEvenMutex};
      vTask.emplace([=] { (*wrapper)(); });
    }
    vEvenVar.notify_all();
    return wrapper->get_future();
  }

private:
  std::queue<Task> vTask;
  std::vector<std::thread> vThread;
  std::condition_variable vEvenVar;
  std::mutex vEvenMutex;
  bool vStoping = false;
  void start(size_t size) {
    for (auto i = 0u; i < size; ++i) {
      vThread.emplace_back([=] {
        while (true) {
          Task task;
          {
            std::unique_lock<std::mutex> lock{vEvenMutex};
            vEvenVar.wait(lock, [=] { return vStoping || !vTask.empty(); });
            if (vStoping && vTask.empty()) {
              break;
            }
            task = std::move(vTask.front());
            vTask.pop();
          }
          task();
        }
      });
    }
  }
  void stop() noexcept {
    {
      std::unique_lock<std::mutex> lock{vEvenMutex};
      vStoping = true;
    }
    vEvenVar.notify_all();
    for (auto &v : vThread) {
      v.join();
    }
  }
};
