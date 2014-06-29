#ifndef _SCHEDULER_HPP
#define _SCHEDULER_HPP

#include "rpipe_cmd.h"
#include<map>
#include<vector>
#include<string>
#include<queue>
using namespace std;

class Descriptor
{
public:
    string host;
    u_long prognum;
    int type;
};

class Task
{
public:
    int desc;
    int type;
    size_t data_size;
};

class Job: public Task
{
public:
    u_char *data=NULL;
    Descriptor target;
    Job(Task task);
};

class Buffer
{
    size_t buff_curr=0;
    queue <u_char> in_buff;
public:
    size_t buff_max;
    Buffer();
    Buffer(size_t capacity);
    bool empty();
    bool can_read(size_t data_size);
    bool can_write(size_t data_size);
    size_t get(u_char *data, size_t data_size);
    void put(u_char *data, size_t data_size);
};

class Scheduler
{
    vector<int> descriptors;
    map <int, Descriptor> read_table;
    map <int, Descriptor> write_table;
    queue<Task> read_schedule;
    queue<Task> write_schedule;
    queue<Task> open_schedule;
public:
    Buffer buffer;
    Scheduler(size_t buffer_size);
    void addTask(Task task);
    int openDescriptor(Descriptor desc);
    void closeDescriptor(int desc);
    int nextTask();
    Job fetchJob(int type);
    void jobDone(Job job);
};

#endif
