#include "threadpool.h"
#include <iostream>
#include <assert.h>

namespace thread{
	
bool ThreadPool::ThreadpoolCreate(int pthread_num){
	assert(pthread_num > 0);
		
	//初始化锁条件变量
	pthread_mutex_init(&thread_lock, NULL);
	pthread_cond_init(&thread_cond, NULL);
	pthread_t pth_t;
	for (int i = 0; i < pthread_num; ++i){
		pthread_create(&pth_t, NULL, ThreadPool::RunTask, this);
	}
	return true;
}

void *ThreadPool::RunTask(void *argv){
	ThreadPool *pool_t = static_cast<ThreadPool *>(argv);
	pool_t->Working();
	return NULL;
}

void ThreadPool::Working(){
	//线程循环处理
	for( ; ; ){
		pthread_mutex_lock(&thread_lock);
		while (0 == task_list.size()){
			pthread_cond_wait(&thread_cond, &thread_lock);
		}
		
		Task *task = task_list.front();
		task_list.pop_front();
		pthread_mutex_unlock(&thread_lock);
		task->Run();
		delete task;
	}
}

void ThreadPool::AddTaskToPoll(Task *task){
	if (NULL == task){
		return;
	}
	pthread_mutex_lock(&thread_lock);
	task_list.push_back(task);
	pthread_mutex_unlock(&thread_lock);
	pthread_cond_signal(&thread_cond);
}

}





