#ifndef UOS_KEY_ENCODE_H
#define UOS_KEY_ENCODE_H

#include <string.h>
#include <string>
#include <vector>

class uos_key
{
public:
    explicit uos_key();

    std::vector<unsigned char> get_private_key() const
    {
        return private_key;
    }

    std::vector<unsigned char> get_public_key() const
    {
        return public_key;
    }

    std::string get_wif_private_key() const
    {
        return wif_private_key;
    }

    std::string get_uos_public_key() const
    {
        return uos_public_key;
    }

    static std::vector<unsigned char> get_public_key_by_pri(const std::vector<unsigned char> &pri);
    static std::string get_uos_public_key_by_wif(const std::string &wif);
    static std::vector<unsigned char> get_private_key_by_wif(const std::string& wif);
    static std::vector<unsigned char> get_public_key_char(const std::string &uoskey);
    static std::vector<unsigned char> get_public_key_by_uos_pub(const std::string& pub);

private:
    std::string wif_private_key;
    std::string uos_public_key;

    std::vector<unsigned char> private_key;
    std::vector<unsigned char> public_key;
};

#endif // UOS_KEY_ENCODE_H
