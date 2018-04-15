// Адаптер (Adapter)

#include <iostream>

class mysql_client_native
{
public:
    void mysql_connect() {
        std::cout << "mysql connect" << std::endl;
    }
    void mysql_execute() {
        std::cout << "mysql execute" << std::endl;
    }
    void mysql_close() {
        std::cout << "mysql close" << std::endl;
    }
};

class postgres_client_native
{
public:
    void postgres_open() {
        std::cout << "postgres open" << std::endl;
    }
    void postgres_query() {
        std::cout << "postgres query" << std::endl;
    }
};

class IDatabase
{
public:
    virtual void connect() = 0;
    virtual void execute_query() = 0;
    virtual void close() = 0;
};

class MysqlDatabase : public IDatabase
{
    mysql_client_native client;

    void connect() override {
        client.mysql_connect();
    }
    void execute_query() override {
        client.mysql_execute();
    }
    void close() override {
        client.mysql_close();
    }
};

class PostgresDatabase : public IDatabase
{
    postgres_client_native client;

    void connect() override {
        client.postgres_open();
    }
    void execute_query() override {
        client.postgres_query();
    }
    void close() override {
    }
};

int main(int, char *[])
{
    IDatabase *db = new PostgresDatabase{};

    db->connect();
    db->execute_query();
    db->close();
}
