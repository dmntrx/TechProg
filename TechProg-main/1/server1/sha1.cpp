#include "sha1.h"
#include <QDataStream>
#include <QFile>
#include <QtEndian>

/* Макросы для вспомогательных операций */
#define SHA1_ROL(value, bits) (((value) << (bits)) | (((value) & 0xffffffff) >> (32 - (bits))))
#define SHA1_BLK(i) (block[i&15] = SHA1_ROL(block[(i+13)&15] ^ block[(i+8)&15] ^ block[(i+2)&15] ^ block[i&15],1))

/* Различные операции, используемые в SHA1 */
#define SHA1_R0(v,w,x,y,z,i) z += ((w&(x^y))^y) + block[i] + 0x5a827999 + SHA1_ROL(v,5); w=SHA1_ROL(w,30);
#define SHA1_R1(v,w,x,y,z,i) z += ((w&(x^y))^y) + SHA1_BLK(i) + 0x5a827999 + SHA1_ROL(v,5); w=SHA1_ROL(w,30);
#define SHA1_R2(v,w,x,y,z,i) z += (w^x^y) + SHA1_BLK(i) + 0x6ed9eba1 + SHA1_ROL(v,5); w=SHA1_ROL(w,30);
#define SHA1_R3(v,w,x,y,z,i) z += (((w|x)&y)|(w&x)) + SHA1_BLK(i) + 0x8f1bbcdc + SHA1_ROL(v,5); w=SHA1_ROL(w,30);
#define SHA1_R4(v,w,x,y,z,i) z += (w^x^y) + SHA1_BLK(i) + 0xca62c1d6 + SHA1_ROL(v,5); w=SHA1_ROL(w,30);

/* Конструктор */
SHA1::SHA1() {
    reset();
}


//010110011001
//100101001010

//110011010011

/* Обновление хеша на основе QByteArray */
void SHA1::update(const QByteArray &data) {
    QByteArray::const_iterator i = data.begin();
    QByteArray::const_iterator end = data.end();

    while (i != end) {
        buffer.append(*i++);
        // Если буфер заполнен до размера блока, преобразуем его
        if (buffer.size() == BLOCK_BYTES) {
            uint32 block[BLOCK_INTS];
            bufferToBlock(buffer, block);
            transform(block);
            buffer.clear();
        }
    }
}

/* Обновление хеша на основе QIODevice */
void SHA1::update(QIODevice &device) {
    QByteArray data;
    while (!device.atEnd()) {
        // Чтение данных из устройства и добавление в буфер
        read(device, data, BLOCK_BYTES - buffer.size());
        buffer.append(data);

        // Преобразуем данные, когда буфер заполнен до размера блока
        while (buffer.size() >= BLOCK_BYTES) {
            uint32 block[BLOCK_INTS];
            bufferToBlock(buffer, block);
            transform(block);
            buffer.remove(0, BLOCK_BYTES);
        }
    }
}

/* Финализация и получение хеша */
QByteArray SHA1::final() {
    /* Общее количество хешированных бит */
    uint64 total_bits = (transforms * BLOCK_BYTES + buffer.size()) * 8;

    /* Добавление паддинга */
    buffer.append(0x80); // Добавляем бит '1' после данных
    // Дополняем нулями до необходимого размера
    while (buffer.size() < BLOCK_BYTES - 8) {
        buffer.append('\0');
    }

    uint32 block[BLOCK_INTS];
    bufferToBlock(buffer, block);

    // Если буфер превышает размер блока, трансформируем его и очищаем
    if (buffer.size() > BLOCK_BYTES - 8) {
        transform(block);
        for (unsigned int i = 0; i < BLOCK_INTS - 2; i++) {
            block[i] = 0;
        }
    }

    /* Добавление длины сообщения в конец блока */
    block[BLOCK_INTS - 1] = qToBigEndian(static_cast<uint32>(total_bits));
    block[BLOCK_INTS - 2] = qToBigEndian(static_cast<uint32>(total_bits >> 32));
    transform(block);

    /* Преобразование в hex строку */
    QByteArray result;
    QDataStream stream(&result, QIODevice::WriteOnly);
    for (unsigned int i = 0; i < DIGEST_INTS; i++) {
        stream << qToBigEndian(digest[i]);
    }

    /* Сброс состояния для следующего использования */
    reset();

    return result.toHex();
}

/* Получение хеша из файла */
QByteArray SHA1::fromFile(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return QByteArray();
    }

    SHA1 checksum;
    checksum.update(file);
    return checksum.final();
}

/* Сброс состояния хеша */
void SHA1::reset() {
    /* Инициализационные константы SHA1 */
    digest[0] = 0x67452301;
    digest[1] = 0xefcdab89;
    digest[2] = 0x98badcfe;
    digest[3] = 0x10325476;
    digest[4] = 0xc3d2e1f0;

    /* Сброс счетчиков */
    transforms = 0;
    buffer.clear();
}

/* Основная трансформация SHA1 на одном блоке данных */
void SHA1::transform(uint32 block[BLOCK_INTS]) {
    /* Копирование digest в рабочие переменные */
    uint32 a = digest[0];
    uint32 b = digest[1];
    uint32 c = digest[2];
    uint32 d = digest[3];
    uint32 e = digest[4];

    /* 4 раунда по 20 операций */
    SHA1_R0(a,b,c,d,e, 0); SHA1_R0(e,a,b,c,d, 1); SHA1_R0(d,e,a,b,c, 2); SHA1_R0(c,d,e,a,b, 3);
    SHA1_R0(b,c,d,e,a, 4); SHA1_R0(a,b,c,d,e, 5); SHA1_R0(e,a,b,c,d, 6); SHA1_R0(d,e,a,b,c, 7);
    SHA1_R0(c,d,e,a,b, 8); SHA1_R0(b,c,d,e,a, 9); SHA1_R0(a,b,c,d,e,10); SHA1_R0(e,a,b,c,d,11);
    SHA1_R0(d,e,a,b,c,12); SHA1_R0(c,d,e,a,b,13); SHA1_R0(b,c,d,e,a,14); SHA1_R0(a,b,c,d,e,15);
    SHA1_R1(e,a,b,c,d,16); SHA1_R1(d,e,a,b,c,17); SHA1_R1(c,d,e,a,b,18); SHA1_R1(b,c,d,e,a,19);
    SHA1_R2(a,b,c,d,e,20); SHA1_R2(e,a,b,c,d,21); SHA1_R2(d,e,a,b,c,22); SHA1_R2(c,d,e,a,b,23);
    SHA1_R2(b,c,d,e,a,24); SHA1_R2(a,b,c,d,e,25); SHA1_R2(e,a,b,c,d,26); SHA1_R2(d,e,a,b,c,27);
    SHA1_R2(c,d,e,a,b,28); SHA1_R2(b,c,d,e,a,29); SHA1_R2(a,b,c,d,e,30); SHA1_R2(e,a,b,c,d,31);
    SHA1_R2(d,e,a,b,c,32); SHA1_R2(c,d,e,a,b,33); SHA1_R2(b,c,d,e,a,34); SHA1_R2(a,b,c,d,e,35);
    SHA1_R2(e,a,b,c,d,36); SHA1_R2(d,e,a,b,c,37); SHA1_R2(c,d,e,a,b,38); SHA1_R2(b,c,d,e,a,39);
    SHA1_R3(a,b,c,d,e,40); SHA1_R3(e,a,b,c,d,41); SHA1_R3(d,e,a,b,c,42); SHA1_R3(c,d,e,a,b,43);
    SHA1_R3(b,c,d,e,a,44); SHA1_R3(a,b,c,d,e,45); SHA1_R3(e,a,b,c,d,46); SHA1_R3(d,e,a,b,c,47);
    SHA1_R3(c,d,e,a,b,48); SHA1_R3(b,c,d,e,a,49); SHA1_R3(a,b,c,d,e,50); SHA1_R3(e,a,b,c,d,51);
    SHA1_R3(d,e,a,b,c,52); SHA1_R3(c,d,e,a,b,53); SHA1_R3(b,c,d,e,a,54); SHA1_R3(a,b,c,d,e,55);
    SHA1_R3(e,a,b,c,d,56); SHA1_R3(d,e,a,b,c,57); SHA1_R3(c,d,e,a,b,58); SHA1_R3(b,c,d,e,a,59);
    SHA1_R4(a,b,c,d,e,60); SHA1_R4(e,a,b,c,d,61); SHA1_R4(d,e,a,b,c,62); SHA1_R4(c,d,e,a,b,63);
    SHA1_R4(b,c,d,e,a,64); SHA1_R4(a,b,c,d,e,65); SHA1_R4(e,a,b,c,d,66); SHA1_R4(d,e,a,b,c,67);
    SHA1_R4(c,d,e,a,b,68); SHA1_R4(b,c,d,e,a,69); SHA1_R4(a,b,c,d,e,70); SHA1_R4(e,a,b,c,d,71);
    SHA1_R4(d,e,a,b,c,72); SHA1_R4(c,d,e,a,b,73); SHA1_R4(b,c,d,e,a,74); SHA1_R4(a,b,c,d,e,75);
    SHA1_R4(e,a,b,c,d,76); SHA1_R4(d,e,a,b,c,77); SHA1_R4(c,d,e,a,b,78); SHA1_R4(b,c,d,e,a,79);

    /* Добавление рабочих переменных обратно в digest */
    digest[0] += a;
    digest[1] += b;
    digest[2] += c;
    digest[3] += d;
    digest[4] += e;

    /* Увеличение счетчика трансформаций */
    transforms++;
}

/* Преобразование буфера в блок целых чисел */
void SHA1::bufferToBlock(const QByteArray &buffer, uint32 block[BLOCK_INTS]) {
    QDataStream stream(buffer);
    for (unsigned int i = 0; i < BLOCK_INTS; ++i) {
        quint32 temp;
        stream >> temp;
        block[i] = qFromBigEndian(temp);
    }
}

/* Чтение данных из устройства ввода-вывода */
void SHA1::read(QIODevice &device, QByteArray &data, int max) {
    data = device.read(max);
}

/* Функция для вычисления SHA1 хеша от QByteArray */
QByteArray sha1(const QByteArray &data) {
    SHA1 checksum;
    checksum.update(data);
    return checksum.final();
}
