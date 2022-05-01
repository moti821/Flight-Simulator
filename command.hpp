

class Command
{
public:
    virtual void do_command() = 0;

};

class Openservercommand : public Command
{
public:
    void do_command();
};