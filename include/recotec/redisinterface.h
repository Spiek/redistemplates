#ifndef REDISMAPPRIVATE_H
#define REDISMAPPRIVATE_H

// qt core
#include <QString>
#include <QByteArray>
#include <QMutex>
#include <list>

// redis
#include "recotec/redisconnectionmanager.h"

class RedisInterface
{
    public:
        enum class Position {
            Begin,
            End
        };

        // General Redis Functions
        static bool ping(RedisServer& server, QByteArray data = "", bool async = false);

        // Key-Value Redis Functions
        static bool del(RedisServer& server, QByteArray key, bool async = true);
        static bool exists(RedisServer& server, QByteArray key);
        static std::list<QByteArray> keys(RedisServer& server, QByteArray pattern = "*");

        // List Redis Functions
        static int push(RedisServer& server, QByteArray key, QByteArray value, RedisInterface::Position direction = Position::Begin, bool waitForAnswer = false);
        static int push(RedisServer& server, QByteArray key, std::list<QByteArray> values, RedisInterface::Position direction = Position::Begin, bool waitForAnswer = false);
        static bool bpop(QTcpSocket *socket, std::list<QByteArray> lists, RedisInterface::Position direction = Position::Begin, int timeout = 0);

        // Hash Redis Functions
        static int hlen(RedisServer& server, QByteArray list);
        static bool hset(RedisServer& server, QByteArray list, QByteArray key, QByteArray value, bool waitForAnswer = false, bool onlySetIfNotExists = false);
        static bool hmset(RedisServer& server, QByteArray list, std::list<QByteArray> keys, std::list<QByteArray> values, bool waitForAnswer = false);
        static bool hexists(RedisServer& server, QByteArray list, QByteArray key);
        static bool hdel(RedisServer& server, QByteArray list, QByteArray key, bool waitForAnswer = true);
        static QByteArray hget(RedisServer& server, QByteArray list, QByteArray key);
        static std::list<QByteArray> hmget(RedisServer& server, QByteArray list, std::list<QByteArray> keys);
        static int hstrlen(RedisServer& server, QByteArray list, QByteArray key);
        static void hkeys(RedisServer& server, QByteArray list, std::list<QByteArray>& result);
        static void hvals(RedisServer& server, QByteArray list, std::list<QByteArray>& result);
        static void hgetall(RedisServer& server, QByteArray list, std::list<QByteArray>& result);
        static void hgetall(RedisServer& server, QByteArray list, QMap<QByteArray, QByteArray>& keyValues);
        static void hgetall(RedisServer& server, QByteArray list, QHash<QByteArray, QByteArray>& keyValues);

        // Scan Redis Functions
        static void scan(RedisServer& server, QByteArray list, std::list<QByteArray>* keys, std::list<QByteArray>* values, int count = 100, int pos = 0, int *newPos = 0);
        static void scan(RedisServer& server, QByteArray list, std::list<QByteArray>& keyValues, int count = 100, int pos = 0, int *newPos = 0);
        static void scan(RedisServer& server, QByteArray list, QMap<QByteArray, QByteArray> &keyValues, int count = 100, int pos = 0, int *newPos = 0);

        // Public helpers
        static bool parseResponse(QTcpSocket* socket, QByteArray* result = 0, std::list<QByteArray> *resultArray = 0, std::list<std::list<QByteArray>>* result2dArray = 0);

    private:
        // command simplifier
        static void simplifyHScan(RedisServer& server, QByteArray list, std::list<QByteArray> *lstKeyValues, std::list<QByteArray> *keys, std::list<QByteArray> *values, QMap<QByteArray, QByteArray> *keyValues, int count, int pos, int *newPos);

        // Private helpers
        static bool execRedisCommand(RedisServer& server, std::list<QByteArray> cmd, QByteArray* result = 0, std::list<QByteArray> *resultArray = 0, std::list<std::list<QByteArray>>* result2dArray = 0);
        static bool execRedisCommand(QTcpSocket* socket, std::list<QByteArray> cmd, QByteArray* result = 0, std::list<QByteArray> *resultArray = 0, std::list<std::list<QByteArray>>* result2dArray = 0, bool waitForAnswer = true);
};

#endif // REDISMAPPRIVATE_H
