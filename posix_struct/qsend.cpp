#include <mqueue.h>
#include <string.h>
#include <iostream>
#include "posix_mes_q.h"

int main(){
    const char * que_name = "/sample";
    struct mq_attr attr;
    mqd_t q;
    int error_check;

    SAMPLE_OBJ buf = {"taro yamada", 20, 75};

    // queue open (writeonly or create)
    q = mq_open(que_name, O_WRONLY | O_CREAT | O_NONBLOCK, S_IRWXU, NULL);
    // error check
    if (q == -1){
        Error_execute(q,que_name,"Error : mq_open");
        return -1;
    }
    
    // queue set message
    error_check = mq_send( q, (const char *)(&buf) , sizeof(SAMPLE_OBJ) , 0);
    // error check
    if (error_check == -1){
        Error_execute(q,que_name,"Error : mq_send");
        return -1;
    }

    // if queue don't closed, can't open new queue and can't unliunk
    error_check = mq_close(q);
    // error check
    if (error_check == -1){
        Error_execute(q,que_name,"Error : mq_check");
        return -1;
    }

    // process stop
    std::cout << "please Enter" << std::endl;
    std::cin.get();

    // queue kill
    mq_unlink(que_name);

    return 0;
}