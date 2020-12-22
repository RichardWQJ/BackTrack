#ifndef SINGLETON_H
#define SINGLETON_H

template<class T>
class Singleton
{
protected:
    Singleton(){}
    virtual ~Singleton(){}

private:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static T* GetInstance()
    {
        static T m_Instance;
        return &m_Instance;
    }
};

#endif // SINGLETON_H
