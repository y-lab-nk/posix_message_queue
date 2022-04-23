#define NAME_LENGTH_MAX 128

typedef struct {
    char name[NAME_LENGTH_MAX];
    int  age;
    double score;
} SAMPLE_OBJ;

void Error_execute(mqd_t q ,const char * que_name ,const char * mess){
    std::cout << mess << std::endl;
    mq_close(q);
    mq_unlink(que_name);
};