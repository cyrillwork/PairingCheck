//This is an open source non-commercial project. Dear PVS-Studio, please check it.
#ifndef ABSTRACT_INTERFACE_H
#define ABSTRACT_INTERFACE_H

#include "iparams.h"

#include <memory>

#if __cplusplus==201103L
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
std::unique_ptr<T> make_unique()
{
    return std::unique_ptr<T>(new T());
}

#endif

class IInterface;

using TypeParams = std::shared_ptr<IParams>;
using TypeInterface = std::shared_ptr<IInterface>;

//! Интерфейсный класс унифицированной библиотеки канальных частей
class IInterface
{
public:

    IInterface(TypeParams p): params(p) {}

    virtual ~IInterface() = default;

    //! Получить название интерфейса (например: RS, Ethernet и т.д.)
    virtual const std::string name() = 0;
    virtual const std::string getDevName() { return params->getDevPath(); }

    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual int read(char *data, int size, int timeout) = 0;
    virtual int write(const char *data, int size) = 0;

protected:
    //! All inferfaces have params refference
    TypeParams params;
};

#endif // ABSTRACT_INTERFACE_H
