#include <cstdio>
#include <string>
#include <unordered_map>
#include <utility>

extern "C"
{
#include <net/if.h>
#include <string.h>
}

#define ERR_STR_SIZE (64)

struct iface_t
{
    unsigned int m_ifindex = 0;
    std::string  m_ifname = "";

    iface_t(unsigned int ifindex, std::string ifname) : m_ifindex(ifindex),
            m_ifname(ifname)
    {
    }
};

class ifaces_t
{
private:
    std::unordered_map<unsigned int, struct iface_t> m_ifaces;

public:
    ifaces_t(void);
    std::string get_iface(unsigned int ifindex);
    void print(void);
};

ifaces_t :: ifaces_t(void)
{
    struct if_nameindex *if_ni = nullptr;
    struct if_nameindex *ptr = nullptr;
    int    count = 0;
    char   buff[ERR_STR_SIZE] = {'\0'};

    if_ni = if_nameindex();
    if (NULL == if_ni) {
        strerror_r(errno, buff, sizeof(buff));
        printf("if_nameindex failed with error(%d): %s\n", errno, buff);
        return;
    }

    for (ptr = if_ni; !((0 == ptr->if_index) && (NULL == ptr->if_name));
            ptr++) {
        this->m_ifaces.emplace(std::make_pair(ptr->if_index,
                                              iface_t{ptr->if_index,
                                                      ptr->if_name}));
    }

    if_freenameindex(if_ni);
}

std::string ifaces_t :: get_iface(unsigned int ifindex)
{
    auto it = this->m_ifaces.find(ifindex);
    if (it == this->m_ifaces.end())
        return {""};

    return it->second.m_ifname;
}

void ifaces_t :: print(void)
{
    printf("Number of interfaces: %lu\n", this->m_ifaces.size());
    for (const auto &it : this->m_ifaces) {
        printf("ifindex: %u  --  ifname: %s\n", it.first,
               it.second.m_ifname.c_str());
    }
}

int main(int argc, char *argv[])
{
    ifaces_t ifaces;

    ifaces.print();

    return 0;
}
