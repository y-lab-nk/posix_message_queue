#include <mqueue.h>
#include <string.h>
#include <iostream>
#include "posix_mes_q.h"

int main(){
    const char * que_name = "/sample";
    struct mq_attr attr;
    mqd_t q;
    int error_check;
    
    SAMPLE_OBJ buf;

    // queue open (readonly) 
    q = mq_open(que_name, O_RDONLY | O_NONBLOCK);
    // error check
    if (q == -1){
        Error_execute(q,que_name,"Error : mq_open");
        return -1;
    }

    // queue get setting value
    error_check = mq_getattr( q ,&attr );
    // error check
    if (error_check == -1){
        Error_execute(q,que_name,"Error : mq_getattr");
        return -1;
    }
    
    // messeage get 
    error_check = mq_receive( q, (char*)&buf, attr.mq_msgsize,NULL);
    // error check
    if (error_check == -1){
        Error_execute(q,que_name,"Error : mq_receive");
        return -1;
    }
    
    // buf debug
    std::cout << "name =" << buf.name << std::endl;
    std::cout << "age  =" << buf.age << std::endl;
    std::cout << "score=" << buf.score << std::endl;
    
    // if queue don't closed, can't open new queue and can't unliunk
    mq_close(q);
    
    return 0;
}

