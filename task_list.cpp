#include "task_list.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

// 若新添加的任务的name或begin_time与已存在的矛盾,则返回false
bool TaskList::Add(pair<int, Other> task)
{
  for (int i = 0; i < task_list_.size(); i++)
  {
    if (task_list_[i].second.begin_time == task.second.begin_time || task_list_[i].second.name == task.second.name)
      return false;
  }

  int i;
  for (i = 0; i < task_list_.size(); i++)
  {
    if (task_list_[i].second.remind_time < task.second.remind_time) // 找到task在按remind_time_从大到小排序的vector task_list_中的位置
      break;
  }

  task_list_.insert(task_list_.begin() + i, task); // 完成插入,此时vector是有序的

  ofstream write;
  write.open(file_, ios::app); // 打开文件,文件指针在文件尾部,将新增的信息保存在文件最后一行

  // 将int类型的begin_time和remind_time转化为可写入文件的字符串begin_time_str和remind_time_str
  time_t begin_time_ = static_cast<time_t>(task.second.begin_time);
  time_t remind_time_ = static_cast<time_t>(task.second.remind_time);
  char begin_time_str[80];
  char remind_time_str[80];
  strftime(begin_time_str, sizeof(begin_time_str), "%Y-%m-%d %H:%M:%S", localtime(&begin_time_));
  strftime(remind_time_str, sizeof(remind_time_str), "%Y-%m-%d %H:%M:%S", localtime(&remind_time_));

  write << task.first << task.second.name << '\t' << begin_time_str << '\t' << task.second.priority << '\t' << task.second.type << '\t' << remind_time_str << '\n';

  write.close();

  return true;
}
