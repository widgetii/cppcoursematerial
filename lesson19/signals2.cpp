// Signals2

#include <vector>
#include <iostream>
#include <string>
#include <boost/signals2/signal.hpp>

namespace bs = boost::signals2;

template<typename T>
struct return_all {
    typedef T result_type;

    template<typename InputIterator>
    T operator()(InputIterator first, InputIterator last) const {
        return T(first, last);
    }
};

using m_update_signal_t = bs::signal<bool(const std::string &),
        return_all<std::vector<bool>>>;

class Document {
    m_update_signal_t m_update_signal;
    std::string m_text;

public:
    Document() {};

    bs::connection connect(const m_update_signal_t::slot_type &subscriber) {
        return m_update_signal.connect(subscriber);
    }

    void para(const std::string &p) {
        m_text += p + "\n";
        auto r = m_update_signal(p);
        for (auto i : r) {
            std::cout << i;
        }
        std::cout << std::endl;
    }

    const std::string &get() const {
        return m_text;
    }
};

class AutoSaver {
    std::string m_fname;
    Document &m_document;
    bs::connection m_connection;

public:
    AutoSaver(Document &doc, const std::string &fname) : m_fname(fname), m_document(doc) {
        m_connection = m_document.connect(std::bind(&AutoSaver::refresh, this, std::placeholders::_1));
    }

    ~AutoSaver() {
        m_connection.disconnect();
    }

    bool refresh(const std::string &p) const {
        std::cout << "=== " << m_fname << " === " << p << std::endl;
        std::cout << m_document.get() << std::endl;
        std::cout << "=== end ===" << std::endl;
        return true;
    }
};

class Renderer {
public:
    Renderer(Document &doc) : m_document(doc) {
        m_connection = m_document.connect(std::bind(&Renderer::refresh, this, std::placeholders::_1));
    }

    ~Renderer() {
        m_connection.disconnect();
    }

    bool refresh(const std::string &p) const {
        std::cout << "=== window update === " << p << std::endl;
        return false;
    }

private:
    Document &m_document;
    bs::connection m_connection;
};

int main(int, char *[]) {
    Document doc;

    AutoSaver as(doc, "tmp.txt");
    doc.para("Report");

    {
        Renderer r(doc);
        doc.para("Hello");
    }

    doc.para("World");

    return 0;
}
