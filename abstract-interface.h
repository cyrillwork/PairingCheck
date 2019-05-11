//This is an open source non-commercial project. Dear PVS-Studio, please check it.
#ifndef ABSTRACT_INTERFACE_H
#define ABSTRACT_INTERFACE_H

#include <memory>
#include <string>

#if __cplusplus==201103L
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
#endif


//! Интерфейсный класс унифицированной библиотеки канальных частей
class AbstractInterface
{
public:
    virtual ~AbstractInterface() {}

    //! Получить название интерфейса (например: RS, Ethernet и т.д.)
    virtual const std::string name() = 0;

    //! Получить конфигурационный XML файл со значениями по умолчанию
    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual int read(char *data, int size, int timeout) = 0;
    virtual int write(const char *data, int size) = 0;
};

#endif // ABSTRACT_INTERFACE_H
