#include "net_common.h"
#include "net_message.h"
#include <iostream>


enum class CustomMsgTypes : uint32_t {
    FireBullet,
    MovePlayer
};

int main() {
    message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::FireBullet;

    int a = 1;
    bool b = true;
    float c = 3.14159f;
    struct {
        float x;
        float y;
    } d[5];

    msg << a << b << c << d;
    std::cout << "msg is now " << msg.size() << " bytes\n";

    a = 99;
    b = false;
    c = 2.71828f;

    
    
    msg >> d >> c >> b >> a;
    std::cout << "msg is now " << msg.size() << " bytes\n";

    return 0;
}