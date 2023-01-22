#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

bool isNumber(std::string &arg)
{
    for (int i = 0; i < arg.size(); ++i)
    {
        if (arg.at(i) < 48 || arg.at(i) > 57)
            return false;
    }
    return true;
}

bool isCorrectFormaIp(std::vector<std::string> &arg)
{
    int pos = 0;
    for (auto it = arg.begin(); it != arg.end(); ++it)
    {
        if (*it == "" || it->length() > 3)
            if (!isNumber(*it))
                return 0;
        if (std::stoi(*it) > 255)
            return 0;
        ++pos;
    }
    if (pos != 4)
        return 0;
    return 1;
}

std::vector<std::string> split(std::string &str, char sep)
{
    std::string::size_type start = 0;
    std::string::size_type end = str.find_first_of(sep, start);
    std::vector<std::string> result;
    while (end != std::string::npos)
    {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find_first_of(sep, start);
    }
    result.push_back(str.substr(start));
    return result;
}

bool more(const std::vector<uint8_t> &left, const std::vector<uint8_t> &right)
{
    for (size_t i = 0; i < 4; ++i)
    {
        if (left.at(i) > right.at(i))
            return true;
        else if (left.at(i) < right.at(i))
            return false;
    }
    return false;
}

bool fullListAddresses(std::vector<uint8_t> &arg)
{
    return 1;
}

bool firstByteIsOne(std::vector<uint8_t> &arg)
{
    return arg.at(0) == 1;
}

bool firstByteFortySixSecondSeventy(std::vector<uint8_t> &arg)
{
    return (arg.at(0) == 46 && arg.at(1) == 70);
}

bool anyByteIsFortySix(std::vector<uint8_t> &arg)
{
    return (arg.at(0) == 46 or arg.at(1) == 46 or arg.at(2) == 46 or arg.at(3) == 46);
}

void outputListOfAddresses(std::vector<std::vector<uint8_t> > &arg, bool (*f)(std::vector<uint8_t> &))
{
    for (auto iter = arg.begin(); iter != arg.end(); ++iter)
    {
        if (f(*iter))
        {
            for (auto b = iter->begin(); b != iter->end(); ++b)
            {
                if (b != iter->begin())
                    std::cout << '.';
                std::cout << static_cast<int>(*b);
            }
            std::cout << std::endl;
        }
    }
}

std::vector<uint8_t> convertrIPAddress(std::vector<std::string> &arg)
{
    std::vector<uint8_t> result;
    for (int i = 0; i < 4; ++i)
        result.push_back(std::stoi(arg.at(i)));
    return result;
}

int main()
{
    std::vector<std::vector<uint8_t> > ip_pool;
    std::string line;
    std::getline(std::cin, line);
    while (line != "")
    {
        auto ip_line = split(line, '\t');
        auto temp_ip = split(ip_line.at(0), '.');
        // ip_pool.push_back(split(ip_line.at(0), '.'));
        if (!isCorrectFormaIp(temp_ip))
        {
            std::cout << "Invalid ip address format entered\n";
            exit(1);
        }
        ip_pool.push_back(convertrIPAddress(temp_ip));

        std::getline(std::cin, line);
    }
    std::sort(ip_pool.begin(), ip_pool.end(), more);
    outputListOfAddresses(ip_pool, fullListAddresses);
    outputListOfAddresses(ip_pool, firstByteIsOne);
    outputListOfAddresses(ip_pool, firstByteFortySixSecondSeventy);
    outputListOfAddresses(ip_pool, anyByteIsFortySix);
    return 0;
}