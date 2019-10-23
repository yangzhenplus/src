#include "threadpool.h"
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <unistd.h>

class MyTask: public thread::Task{
  public:
	void Run(){
		printf("%s\n", data.c_str());
	}
	void SetData(const std::string &task_data){
		data = task_data;
	}
  private:
	std::string data;
};

int main(int argc, char **argv)
{
	thread::ThreadPool thread_pool;
	thread_pool.ThreadpoolCreate(4);
	char str[32];
	for(int i = 0; i < 10; ++i){
		MyTask *task = new MyTask();
		memset(str, 0, 32);
		sprintf(str, "Task number %d", i);
		task->SetData(str);
		thread_pool.AddTaskToPoll(task);
	}

	sleep(1);
	return 0;
}
