#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

//�̳߳�ͷ�ļ�
#include <pthread.h>
#include <iostream>
#include <string>
#include <list>

namespace thread{
	
//��װ�̳߳��еĶ�����Ҫִ�е��������
class Task{
  public:
    virtual void Run() = 0;  //����ָ�룬��Ҫִ�е�����
    virtual ~Task() {};
};

class ThreadPool{
  public:
	//��ʼ���̳߳�
	bool ThreadpoolCreate(int pthread_num);
	// ��������̳߳�
	void AddTaskToPoll(Task *task);
	
  private:
	static void *RunTask(void *argv);
	void Working();

  private:
	pthread_mutex_t thread_lock;
	pthread_cond_t thread_cond;
	std::list<Task*> task_list; //�������
};

} // namespace thread
#endif

