#include "scheduler.hpp"
using namespace std;

Buffer::Buffer()
{
    buff_max = 0;
}

Buffer::Buffer(size_t capacity): Buffer()
{
    buff_max = capacity;
}

bool Buffer::empty()
{
    return in_buff.empty();
}

bool Buffer::can_read(size_t data_size)
{
    return buff_curr>0;
}

bool Buffer::can_write(size_t data_size)
{
    return (buff_curr+data_size)<=buff_max;
}

size_t Buffer::get(u_char *data, size_t data_size)
{
    size_t len=0;
    while(!in_buff.empty() && data_size>0)
    {
        data[len]=in_buff.front();
        in_buff.pop();
        buff_curr--;
        len++;
        data_size--;
    }
    float perc = 100.00*float(buff_curr)/float(buff_max);
    printf("Buffer %lu/%lu (%f%%)\n",buff_curr,buff_max,perc);
    return len;
}

void Buffer::put(u_char *data, size_t data_size)
{
    size_t len=0;
    while(data_size>0)
    {
        in_buff.push(data[len]);
        buff_curr++;
        len++;
        data_size--;
    }
    float perc = 100.00*float(buff_curr)/float(buff_max);
    printf("Buffer %lu/%lu (%f%%)\n",buff_curr,buff_max,perc);
}
