#ifndef TEAENCRYPTION_H
#define TEAENCRYPTION_H

#include <QObject>
#include <QFile>
#include <QByteArray>
#include <QDebug>

#define ITERATION_STEPS 32
#define PADDING_SIZE 19
#define KEY_1 62337407
#define KEY_2 23784542
#define KEY_3 14452371
#define KEY_4 31891856
#define DELTA 0x9E3779B9

class TEAEncryption : public QObject
{
    Q_OBJECT
public:
    explicit TEAEncryption(QObject *parent = nullptr);
    QByteArray encipher();
    QByteArray decipher();
    void setInput(QByteArray);

private:
    void addPadding();
    void removePadding();
    QByteArray inputArray;
    QByteArray encodedArray;
    QByteArray decodedArray;

signals:

public slots:
};

#endif // TEAENCRYPTION_H
