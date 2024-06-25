#define MSG_SIZE 256
#include <string.h>

struct Message{ //velikost paketka je 260 byte (MSG_SIZE + sizeof(int))
    int type;
    char content[MSG_SIZE];
};

int stringifyMessage(struct Message* msg, char* dest, int contentSize){
    int offset = 0;
    memcpy(dest + offset, &msg->type, sizeof(int));
    offset += sizeof(int);
    memcpy(dest + offset, &msg->content, contentSize);
    offset += contentSize;
    return offset;
}

int parseMessage(struct Message* msg, char*src, int contentSize){
    int offset = 0;
    memcpy(&msg->type, src + offset, sizeof(int));
    offset += sizeof(int);
    memcpy(&msg->content, src+offset, contentSize);
    return offset;
}

//stringifyMessage pretvori strukturo Message v format za prenos preko omrežja (polje bajtov)
//parseMessage pretvori polje bajtov v strukturo Message