#include <mqueue.h>
#include <string.h>
#include <iostream>
#include "posix_mes_q.h"

int main(){
    int status;
    SAMPLE_OBJ message = {"taro yamada", 20, 75};
    My_Message_Queue<SAMPLE_OBJ> MQ("/sample");
    
    status = MQ.Send_q(&message);
    std::cout << "status = " << status << std::endl;

    return 0;
}