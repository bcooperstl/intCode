#ifndef __RUNNER_H__
#define __RUNNER_H__

class Runner
{
protected:
    bool m_terminated;
    std::string m_name;
private:
    void init(std::string name);
public:
    Runner(std::string name);
    Runner();
    ~Runner();
    virtual int run()=0;
    bool isTerminated();
    std::string getName();
};

#endif
