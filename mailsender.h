#ifndef MAILSENDER_H_
#define MAILSENDER_H_
#include <string>

class MailSender
{
public:
	explicit MailSender(std::string mailbox);
	bool send();
	~MailSender();
};

#endif /* MAILSENDER_H_ */
