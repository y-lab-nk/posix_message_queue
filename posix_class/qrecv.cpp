#include <mqueue.h>
#include <string.h>
#include <iostream>
#include "posix_mes_q.h"

int main(){
    int status;
    SAMPLE_OBJ message;
    My_Message_Queue<SAMPLE_OBJ> MQ("/sample");

    status = MQ.Recv_q(&message);
    std::cout << "status = " << status << std::endl;
    
    if(status == 0){
        std::cout << "name    = " << message.name << std::endl;
        std::cout << "age     = " << message.age << std::endl;
        std::cout << "score   = " << message.score << std::endl;
    }
    else{
        std::cout << "error_log = " << MQ.Get_error_log() << std::endl;
    }

    // error confirmation
    status = MQ.Recv_q(&message);
    std::cout << "status = " << status << std::endl;
    std::cout << "error_log = " << MQ.Get_error_log() << std::endl;

    MQ.Unlink_q();

    return 0;
}