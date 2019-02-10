//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#ifndef INTERFACE_H
#define INTERFACE_H

#include <sys/time.h>
#include <string>

#include "rs_interface.h"
#include "paramsrs.h"


//! Класс соединения с абонентом по абстрактному интерфейсу
class Interface
{
    AbstractInterface *m_interfaceImpl = nullptr;
    bool m_opened = false;

    //int m_wordSize = 2;
    //int m_base = 2;

public:
    //! Конструктор по умолчанию - соединение не открыто
    Interface() {}

    //! Создать RS интерфейс
    /*!
     * \param devPath - название RS порта
     */
    void createRSInterface(ParamsRS _params);

    //! Деструктор - закрывает соединение
    ~Interface();

    //! Установка режима отладки
    /*!
     * \param debug признак установки режима отладки
     */
    //void setDebug(bool debug) { m_debug = debug; }
    //void setDebugFormat(int wordSize, int base) { m_wordSize = wordSize; m_base = base; }

    //! Открытие соединения
    /*!
     * \return Признак успешного завершения
     */
    bool open();

    //! Закрытие соединения
    /*!
     * \return Признак успешного завершения
     * \attention Вызывается автоматически при уничтожении объекта
     */
    bool close();

    //! Чтение данных
    /*!
     * \param data Указатель на буфер
     * \param size Размер буфера в байтах
     * \param timeout Таймаут соединения, микросекунды
     * \return Количество считанных байт
     */
    int read(char *data, int size, int timeout);

    //! Чтение данных
    /*!
     * \param data Указатель на буфер
     * \param size Размер буфера в байтах
     * \param timeout Указатель на значение таймаута соединения
     * \return Количество считанных байт
     * \attention Значение timeout уменьшается на время чтения
     */
    int read(char *data, int size, int *timeout);

    //! Запись данных
    /*!
     * \param data Указатель на данные
     * \param size Размер записываемых данных в байтах
     * \return Количество записанных байт
     */
    int write(const char *data, int size);

    //! Получение состояния соединения
    /*!
     * \return Признак открытия соединения
     */
    bool isOpened()
    {
        return m_opened;
    }

};


#endif // INTERFACE_H
