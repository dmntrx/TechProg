#ifndef SHA1_H
#define SHA1_H

#include <QByteArray>
#include <QIODevice>
#include <QString>

// Определение класса SHA1
class SHA1 {
public:
    // Конструктор
    SHA1();
    // Метод для обновления хеш-значения на основе массива байтов
    void update(const QByteArray &data);
    // Метод для обновления хеш-значения на основе данных из устройства ввода-вывода
    void update(QIODevice &device);
    // Метод для получения финального хеш-значения после всех обновлений
    QByteArray final();
    // Статический метод для получения хеш-значения файла
    static QByteArray fromFile(const QString &filename);

private:
    // Определение типов для 32-битных и 64-битных целых чисел
    typedef quint32 uint32;
    typedef quint64 uint64;

    // Константы, используемые в алгоритме SHA1
    static const unsigned int DIGEST_INTS = 5;  // Количество 32-битных целых чисел в SHA1-хеше
    static const unsigned int BLOCK_INTS = 16;  // Количество 32-битных целых чисел в SHA1-блоке
    static const unsigned int BLOCK_BYTES = BLOCK_INTS * 4;  // Размер блока в байтах

    // Массив для хранения текущего состояния хеша
    uint32 digest[DIGEST_INTS];
    // Буфер для хранения данных перед их обработкой
    QByteArray buffer;
    // Счетчик количества трансформаций
    uint64 transforms;

    // Метод для сброса состояния хеша к начальному значению
    void reset();
    // Метод для выполнения основной трансформации SHA1 на одном блоке данных
    void transform(uint32 block[BLOCK_BYTES]);

    // Статический метод для преобразования буфера байтов в блок целых чисел
    static void bufferToBlock(const QByteArray &buffer, uint32 block[BLOCK_BYTES]);
    // Статический метод для чтения данных из устройства ввода-вывода
    static void read(QIODevice &device, QByteArray &data, int max);
};

// Функция для вычисления SHA1-хеша от массива байтов
QByteArray sha1(const QByteArray &data);

#endif // SHA1_H
