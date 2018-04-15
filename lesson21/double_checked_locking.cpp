Singleton* Singleton::m_instance;
std::mutex Singleton::m_mutex;

Singleton* Singleton::getInstance()
{
    // if (m_instance == nullptr) {
    // std::lock_guard<std::mutex> lock(m_mutex);
        if (m_instance == nullptr) {
            m_instance = new Singleton;
        }
    // }
    return m_instance;
}
