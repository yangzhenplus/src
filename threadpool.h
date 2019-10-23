#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

//线程池头文件
#include <pthread.h>
#include <iostream>
#include <string>
#include <list>

namespace thread{
	
//封装线程池中的对象需要执行的任务对象
class Task{
  public:
    virtual void Run() = 0;  //函数指针，需要执行的任务
    virtual ~Task() {};
};

class ThreadPool{
  public:
	//初始化线程池
	bool ThreadpoolCreate(int pthread_num);
	// 添加任务到线程池
	void AddTaskToPoll(Task *task);
	
  private:
	static void *RunTask(void *argv);
	void Working();

  private:
	pthread_mutex_t thread_lock;
	pthread_cond_t thread_cond;
	std::list<Task*> task_list; //任务队列
};

} // namespace thread
#endif

