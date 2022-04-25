#define NAME_LENGTH_MAX 128
#define LOG_LENGTH_MAX 4096

typedef struct {
    char name[NAME_LENGTH_MAX];
    int  age;
    double score;
} SAMPLE_OBJ;

template <typename MESSAGE_TYPE>
class My_Message_Queue{
    private:
        const char * queue_name_;
        
    public:
        My_Message_Queue(const char * queue_name){
            queue_name_ = queue_name;
        }
        ~My_Message_Queue(){
        }

        int Send_q(MESSAGE_TYPE * message){
            mqd_t q;
            int error_check = 0;
            
            // queue open (writeonly or create)
            q = mq_open(queue_name_, O_WRONLY | O_CREAT | O_NONBLOCK, S_IRWXU, NULL);
            if(q == -1){
                Error_execute("mq_open", errno, q);
                return -1;
            }

            // queue set message
            error_check = mq_send(q, (const char *)(message) , sizeof(MESSAGE_TYPE) , 0);
            if(error_check == -1){
                Error_execute("mq_send", errno, q);
                return -1;
            }

            // if queue don't closed, can't open new queue and can't unliunk
            error_check = mq_close(q);
            if(error_check == -1){
                Error_execute("mq_close", errno, q);
                return -1;
            }

            return 0;
        };

        int Recv_q(MESSAGE_TYPE * buff){
            struct mq_attr attr;
            mqd_t q;            
            int error_check = 0;

            // queue open (readonly) 
            q = mq_open(queue_name_, O_RDONLY | O_NONBLOCK);
            if(q == -1){
                Error_execute("mq_open", errno, q);
                return -1;
            }

            // queue get setting value
            error_check = mq_getattr( q ,&attr );
            if (error_check == -1){
                Error_execute("mq_getattr", errno, q);
                return -1;
            }

            // messeage get 
            error_check = mq_receive( q, (char*)buff, attr.mq_msgsize, NULL);
            if (error_check == -1){
                Error_execute("mq_receive", errno, q);
                return -1;
            }

            // if queue don't closed, can't open new queue and can't unliunk
            error_check = mq_close(q);
            if(error_check == -1){
                Error_execute("mq_close", errno, q);
                return -1;
            }
            
            return 0;
        };

        const char * Get_error_log(){
            return error_log_;
        };

        int Unlink_q(){
            mq_unlink(queue_name_);
            return 0;
        };

    private:
        char error_log_[LOG_LENGTH_MAX] = "None";

        void Error_execute(const char * func_name, int error_id, mqd_t q){

            // make error log
            snprintf(error_log_, LOG_LENGTH_MAX, "func_name:%s, errno:%d", func_name, error_id);

            // if queue don't closed, can't open new queue and can't unliunk
            mq_close(q);
        }
};