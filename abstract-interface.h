//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#ifndef ABSTRACT_INTERFACE_H
#define ABSTRACT_INTERFACE_H

//! Интерфейсный класс унифицированной библиотеки канальных частей
class AbstractInterface
{
public:
    virtual ~AbstractInterface() { };

    //! Получить название интерфейса (например: RS, Ethernet и т.д.)
    virtual const char* name() = 0;

    //! Получить конфигурационный XML файл со значениями по умолчанию
    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual int read(char *data, int size, int timeout) = 0;
    virtual int write(const char *data, int size) = 0;
    //virtual AbstractInterface *createAnother() = 0;
};

#endif // ABSTRACT_INTERFACE_H
