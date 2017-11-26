#include<thread>
#include<mutex>
#include<condition_variable>
#include<functional>
#include<vector>

// Based on http://progsch.net/wordpress/?p=81

class threadPool;

class worker{
   public:
      worker(threadPool& s);
      void operator()();
   private:
      threadPool& pool;
};

class threadPool{
   public:
      threadPool(unsigned threads);
      template<class F>
      void enqueue(F f);
      ~threadPool();
   private:
      friend class worker;

      std::vector<std::thread> workers;
      std::deque<std::function<void()>> tasks;

      std::mutex queue_mtx;
      std::condition_variable cond;
      bool stop;
};
