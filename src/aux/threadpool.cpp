#include"aux/threadpool.hpp"

worker::worker(threadPool& s) : pool(s) {}

void worker::operator()(){
   std::function<void()> task;
   while(true){
      {
         std::unique_lock<std::mutex> lock(pool.queue_mtx);

         while(!pool.stop && pool.tasks.empty()){
            pool.cond.wait(lock);
         }

         if(pool.stop)
            return;

         task = pool.tasks.front();
         pool.tasks.pop_front();
      }
      task();
   }
}

threadPool::threadPool(unsigned threads) : stop(false){
   for(unsigned i=0;i<threads;i++)
      workers.push_back(std::threads(worker(*this)));
}

threadPool::~threadPool(){
   stop = true;
   cond.notify_all();

   for(unsigned i=0;i<workers.size();i++)
      workers[i].join();
}

template<class F>
void threadPool::enqueue(F f){
   {
      std::unique_lock<std::mutex> lock(queue_mtx);

      tasks.push_back(std::function<void()>(f));
   }

   cond.notify_one();
}
