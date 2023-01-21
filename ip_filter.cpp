#include <vector>
#include <iostream>
#include <string>

bool isNumber (std::string &arg) {
    for (int i = 0; i < arg.size(); ++i) {
        if (arg.at(i) < 48 || arg.at(i) > 57)
            return false;
    }
    return true;
}

bool isCorrectFormaIp(std::vector<std::string> &arg) {
    int pos = 0;
    for (std::vector<std::string>::iterator it = arg.begin(); it != arg.end(); ++it) {
        if (*it == "" || it->length() > 3)             
            return 0;
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

std::vector<std::string> split (std::string str, char sep) {
    std::string::size_type start = 0;
    std::string::size_type end = str.find_first_of(sep, start);
    std::vector<std::string> result;
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));        
        start = end + 1;
        end = str.find_first_of(sep, start);
    }
    result.push_back(str.substr(start));
    return result;
}

bool less(const std::vector<std::string> &left, const std::vector<std::string> &right) {
    for (size_t i = 0; i < 4; ++i) {         
        if (std::stoi(left.at(i)) < std::stoi(right.at(i)))        
            return true;  
        else if  (std::stoi(left.at(i)) > std::stoi(right.at(i))) 
            return false;
    }
    return false;
}

void  lexicographicallySort (std::vector<std::vector<std::string> > &arg, bool(*f)(const std::vector<std::string>&, const std::vector<std::string>&)) {   
    for (size_t i = 1; i < arg.size(); ++i) {
        for(size_t j = 0; j < arg.size() - i; j++) {
            if (f(arg.at(j), arg.at(j + 1)) == true)
                swap(arg.at(j), arg.at(j + 1));
        }        
    }
}

bool fullListAddresses(std::vector<std::string> &arg) {
    return 1;
}

bool firstByteIsOne(std::vector<std::string> &arg) {
    if (arg.at(0) == "1")
        return 1;
    return 0;
}

bool firstByteFortySixSecondSeventy(std::vector<std::string> &arg) {
    if (arg.at(0) == "46" && arg.at(1) == "70")
        return 1;
    return 0;
}

bool anyByteIsFortySix(std::vector<std::string> &arg) {
    if (arg.at(0) == "46" or arg.at(1) == "46" or arg.at(2) == "46" or arg.at(3) == "46")
        return 1;
    return 0;
}

void outputListOfAddresses (std::vector<std::vector<std::string> > &arg, bool(*f)(std::vector<std::string> &)) {
    for (std::vector<std::vector<std::string> >::iterator iter = arg.begin(); iter != arg.end(); ++iter) {
        if (f(*iter)) {
            for (std::vector<std::string>::iterator b = iter->begin(); b != iter->end(); ++b) {
                if (b != iter->begin())
                    std::cout << '.';
                std::cout << *b;
            }
            std::cout << std::endl;        
        }
    }   
}

int main () {
    std::vector<std::vector<std::string> > ip_pool;
    std::string line;
    std::getline(std::cin, line);
    while (line != "") {
        std::vector<std::string> ip_line = split(line, '\t');
        ip_pool.push_back(split(ip_line.at(0), '.'));   
         if (!isCorrectFormaIp(ip_pool.back())) {
            std::cout << "Invalid ip address format entered\n";
            exit(1);
        }     
        std::getline(std::cin, line);
    }

    lexicographicallySort(ip_pool, less);
    outputListOfAddresses(ip_pool, fullListAddresses);
    outputListOfAddresses(ip_pool, firstByteIsOne);
    outputListOfAddresses(ip_pool, firstByteFortySixSecondSeventy);
    outputListOfAddresses(ip_pool, anyByteIsFortySix);

    return 0;   
}