#include <mqueue.h>
#include <string.h>
#include <iostream>

int main(){
    const char * que_name = "/sample";
    struct mq_attr attr;
    mqd_t q;
    
    char *buf;

    // queue open (readonly) 
    q = mq_open(que_name, O_RDONLY);

    // queue get setting value
    mq_getattr( q ,&attr );

    // buf size reserve
    buf = (char *)malloc(attr.mq_msgsize);
    
    // messeage get 
    mq_receive( q, (char*)buf, attr.mq_msgsize,NULL);
    
    // buf debug
    std::cout << "buf = " << buf << std::endl;
    
    // malloc release
    free(buf);

    // if queue don't closed, can't open new queue and can't unliunk
    mq_close(q);

    return 0;
}