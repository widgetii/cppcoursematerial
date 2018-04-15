// Команда (Command)

#include <iostream>
#include <vector>

class Document
{
    std::string text;

public:
    void create()
    {
        std::cout << "new document" << std::endl;
    }

    void new_para(const std::string &para)
    {
        text += para + "\n";
        std::cout << "new para " << para << std::endl;
    }

    void save_as(const std::string &name)
    {
        std::cout << "--- " << name << "---" << std::endl;
        std::cout << text << std::endl;
    }
};

class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() {}

protected:
    Command(Document *d): document(d) {}
    Document * document;
};

class NewDocumentCommand: public Command
{
public:
    NewDocumentCommand(Document * d) : Command(d) {}
    void execute() override
    {
        document->create();
    }
};

class ParaCommand: public Command
{
    std::string text;
public:
    ParaCommand(Document * d, const std::string &text_) : Command(d), text(text_) {}
    void execute() override
    {
        document->new_para(text);
    }
};

class SaveAsCommand: public Command
{
    std::string fname;
public:
    SaveAsCommand(Document * d, const std::string &fname_) : Command(d), fname(fname_) {}
    void execute() override
    {
        document->save_as(fname);
    }
};

int main(int, char *[])
{
    Document doc;

    std::vector<Command *> history;
    history.push_back(new NewDocumentCommand(&doc));
    history.push_back( new ParaCommand(&doc, "Manual"));
    history.push_back( new ParaCommand(&doc, ""));
    history.push_back( new ParaCommand(&doc, "Hello, World!"));
    history.push_back( new SaveAsCommand(&doc, "hello.doc"));

    for(auto c: history)
    {
        c->execute();
    }

    return 0;
}
