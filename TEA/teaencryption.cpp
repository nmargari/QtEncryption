#include "teaencryption.h"

TEAEncryption::TEAEncryption(QObject *parent) : QObject(parent)
{

}

/*
 * Set Input Array
 */
void TEAEncryption::setInput(QByteArray inputBytes)
{
    inputArray = inputBytes;
}

/*
 * Adding padding to the inputArray
 */
void TEAEncryption::addPadding()
{
    if(inputArray.length() % 2 == 0)
    {
        return ;
    }
    else
    {
        for(int i = 0; i < PADDING_SIZE; i++)
        {
            inputArray.append(static_cast<char>(0));
        }

    }
}

/*
 * Remove padding from the decodedArray
 */
void TEAEncryption::removePadding()
{
    if(decodedArray.at(decodedArray.length() - PADDING_SIZE) == 0)
    {
        decodedArray.chop(PADDING_SIZE);
    }
}

/*
 * Encrypting inputArray with a variant of TEA
 */

QByteArray TEAEncryption::encipher()
{
    quint32 sum;
    quint8 v0, v1;
    int bytesLength;

    addPadding();
    bytesLength = inputArray.length();

    for(int j = 0; j < bytesLength; j += 2)
    {
        sum = 0;

        v0 = static_cast<quint8>(inputArray.at(j));
        v1 = static_cast<quint8>(inputArray.at(j + 1));

        for(int i = 0; i < ITERATION_STEPS; ++i)
        {
            sum += DELTA;
            v0 += ((v1 << 4) + KEY_1) ^ (v1 + sum) ^ (( v1 >> 5) + KEY_2);
            v1 += ((v0 << 4) + KEY_3) ^ (v0 + sum) ^ (( v0 >> 5) + KEY_4);

        }

        encodedArray.append(static_cast<char>(v0));
        encodedArray.append(static_cast<char>(v1));
    }

    return encodedArray;
}

/*
 * Decrypting encodedArray
 */
QByteArray TEAEncryption::decipher()
{
    quint32 sum;
    quint8 v0, v1;
    int bytesLength;

    bytesLength = encodedArray.length();

    for(int j = 0; j < bytesLength; j += 2)
    {
        sum = 0xC6EF3720;

        v0 = static_cast<quint8>(encodedArray.at(j));
        v1 = static_cast<quint8>(encodedArray.at(j + 1));

        for(int i = 0; i < ITERATION_STEPS; ++i)
        {

            v1 -= ((v0 << 4) + KEY_3) ^ (v0 + sum) ^ (( v0 >> 5) + KEY_4);
            v0 -= ((v1 << 4) + KEY_1) ^ (v1 + sum) ^ (( v1 >> 5) + KEY_2);
            sum -= DELTA;
        }

        decodedArray.append(static_cast<char>(v0));
        decodedArray.append(static_cast<char>(v1));
    }

    removePadding();

    return decodedArray;
}
