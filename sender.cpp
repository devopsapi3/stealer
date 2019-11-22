#include "sender.h"

Sender::Sender(const TgBot::Bot &bot_)
    : bot(bot_)
    {}

void Sender::send(const long &chat_id, const std::string &message)
{
    this->bot.getApi().sendMessage(chat_id, message);
}