#ifndef SENDER_H_
#define SENDER_H_

#include <string>
#include <tgbot/tgbot.h>

class Sender
{
public:
    Sender(const TgBot::Bot &bot_);
    void send(const std::string &chat_id, const std::string &message);

private:
    TgBot::Bot bot;
};

#endif