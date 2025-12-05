#include <iostream>
#include <string>

class GLFWApplication
{
public:
    GLFWApplication(const std::string &name, const std::string &version)
        : _name(name), _version(version) {}
    GLFWApplication() = default;
    virtual ~GLFWApplication() = default;

    virtual unsigned Init();
    virtual unsigned Run() const = 0;
    virtual void Shutdown();

    std::string GetName() const { return _name; }
    std::string GetVersion() const { return _version; }

private:
    std::string _name;
    std::string _version;
};