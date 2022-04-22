#include <mqueue.h>
#include <string.h>
#include <iostream>

int main(){
    const char * que_name = "/sample";
    struct mq_attr attr;
    mqd_t q;
    
    char buf[] = "hoge";

    // queue open (writeonly or create)
    q = mq_open(que_name, O_WRONLY | O_CREAT, S_IRWXU, NULL);
    
    // queue set message
    mq_send( q, (const char *)(&buf) , sizeof(buf) , 0);
    
    // if queue don't closed, can't open new queue and can't unliunk
    mq_close(q);

    // process stop
    std::cout << "please Enter" << std::endl;
    std::cin.get();

    // queue kill
    mq_unlink(que_name);

    return 0;
}