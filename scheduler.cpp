#include "scheduler.hpp"
using namespace std;

Job::Job(Task task)
{
    desc = task.desc;
    type = task.type;
    data_size = task.data_size;
}

Scheduler::Scheduler(size_t buffer_size)
{
    buffer.buff_max = buffer_size;
}

void Scheduler::addTask(Task task)
{
    if(task.data_size<=0 || (task.type==rpipe_write && task.data_size>buffer.buff_max))
    {
        throw string("Invalid data size");
    }
    switch(task.type)
    {
        case rpipe_write:
            write_schedule.push(task); break;
        case rpipe_read:
            read_schedule.push(task); break;
        default:
            throw "Invalid task type";
    }
    printf("Adding task type %i\n",task.type);
}

int Scheduler::openDescriptor(Descriptor desc)
{
    int nxt=-1;
    for(u_int i=0;i<descriptors.size();i++)
    {
        if(descriptors[i]==0)
        {
            nxt=i;
            descriptors[i]=desc.type;
            break;
        }
    }
    if(nxt==-1)
    {
        descriptors.push_back(desc.type);
        nxt = descriptors.size()-1;
    }

    switch(desc.type)
    {
        case rpipe_write:
            write_table[nxt]=desc; break;
        case rpipe_read:
            read_table[nxt]=desc; break;
        default:
            printf("Illegal type\n"); exit(1);
    }

    Task t;
    t.desc = nxt;
    t.type = rpipe_open;
    open_schedule.push(t);

    return nxt;
}

void Scheduler::closeDescriptor(int desc)
{
    switch(descriptors[desc])
    {
        case rpipe_write:
            write_table.erase(desc); break;
        case rpipe_read:
            read_table.erase(desc); break;
        default:
            printf("Closing invalid descriptor.\n"); exit(1);
    }
}

int Scheduler::nextTask()
{
    if(!open_schedule.empty() && (!buffer.empty() || !write_table.empty()))
    {
        return rpipe_open;
    }
    if(!write_schedule.empty())
    {
        if(buffer.can_write(write_schedule.front().data_size))
        {
            return rpipe_write;
        }
    }
    if(!read_schedule.empty())
    {
        if(buffer.can_read(read_schedule.front().data_size))
            return rpipe_read;
        else if(buffer.empty() && write_table.empty())
            return rpipe_close;
    }
    return 0;
}

Job Scheduler::fetchJob(int type)
{
    if(type==rpipe_open)
    {
        Task task=open_schedule.front();
        open_schedule.pop();
        Job job(task);
        if(descriptors[task.desc]==rpipe_write) {
            job.target=write_table[task.desc];
            return job;
        }
        else if(descriptors[task.desc]==rpipe_read) {
            job.target=read_table[task.desc];
            return job;
        }
    }
    if(type==rpipe_write)
    {
        Task task = write_schedule.front();
        write_schedule.pop();
        Job job(task);
        job.target = write_table[task.desc];
        job.data = (u_char*)malloc(job.data_size);
        return job;
    }
    else if(type==rpipe_read)
    {
        Task task = read_schedule.front();
        read_schedule.pop();
        Job job(task);
        job.target = read_table[task.desc];
        job.data = (u_char*)malloc(job.data_size);
        job.data_size = buffer.get(job.data, job.data_size);
        return job;
    }
    else if(type==rpipe_close)
    {
        Task task = read_schedule.front();
        read_schedule.pop();
        Job job(task);
        job.target = read_table[task.desc];
        job.data = NULL;
        job.data_size = 0;
        job.type = rpipe_close;
        return job;
    }
    else
    {
        printf("Invalid job type\n");
        exit(1);
    }
}

void Scheduler::jobDone(Job job)
{
    if(job.type==rpipe_write)
    {
        buffer.put(job.data, job.data_size);
    }
    if(job.data!=NULL)
    {
        free(job.data);
        job.data = NULL;
    }
}
