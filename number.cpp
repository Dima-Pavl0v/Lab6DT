#include "number.h"


uint2022_t from_uint(uint32_t i) {
    uint2022_t res = uint2022_t();
    if (i>=1e9){
        int b =i%1000000000;
        int c =i/1000000000;
        res.num[uint2022_t::size - 1] = b;
        res.num[uint2022_t::size - 2] = c;
    }
    else{
        res.num[uint2022_t::size - 1] = i;
    }
    return res;
}

uint2022_t from_string(const char* buff) {
    uint2022_t res = uint2022_t();
    std::string str(buff);
    int i = res.size-1;
    std::string s;
    while (str.length() > 0) {
        if (str.length() < 9) {
            s = str.substr(0);
            str = str.substr(0, 0);
        } else {
            s = str.substr(str.length() - 9);
            str = str.substr(0, str.length()-9);
        }
        int d = std::stoi(s);
        res.num[i]=d;
        i--;
        if(i<0){
            break;
        }
    }
    return res;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t res=uint2022_t();
    for (int i=uint2022_t::size-1; i>=0; i--){
        res.num[i]=lhs.num[i]+rhs.num[i];
    }
    for (int i=uint2022_t::size-1; i>=1; i--){
        if (res.num[i]>1e9){
            res.num[i]=res.num[i]-1e9;
            res.num[i-1]++;
        }
    }
    return res;
}


uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t res=uint2022_t();
    for (int i=uint2022_t::size-1; i>=0; i--){
        if(rhs.num[i]>lhs.num[i]){
            res.num[i]=lhs.num[i]+1e9 - rhs.num[i];
            res.num[i-1]--;
        }
        else{
            res.num[i]=lhs.num[i] - rhs.num[i];
        }
    }
    return res;
}



uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t res=uint2022_t();
    uint2022_t auxiliary;
    uint64_t s;
    for (int i=uint2022_t::size-1; i>=0; i--){
        for (int j=uint2022_t::size-1; j>=0; j--){
            uint64_t l=lhs.num[i];
            uint64_t r=rhs.num[j];
            s = l*r;
            std::string s_ch=std::to_string(s)+ std::string(9*(2*uint2022_t::size -2-j-i), '0');;
            const char *cstr = s_ch.c_str();
            auxiliary = from_string(cstr);
            res = res+auxiliary;
        }
    }
    return res;
}




bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i=0; i< uint2022_t::size; i++){
        if (lhs.num[i]!=rhs.num[i]){
            return false;
        }
    }
    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i=0; i< uint2022_t::size; i++){
        if (lhs.num[i]!=rhs.num[i]){
            return true;
        }
    }
    return false;
}

std::string to_bin(const uint2022_t value){
    std::string res;
    std::string str;
    uint2022_t value1=value;
    uint2022_t T;
    while (value1!= from_uint(0)){
        res = std::to_string(value1.num[uint2022_t::size-1]%2)+res;
        value1.num[uint2022_t::size-1]-=value1.num[uint2022_t::size-1]%2;
        for (int i=0; i<uint2022_t::size; i++){
            std::string s((67 - i) * 9, '0');
            s[0]=char(5*value1.num[i]%2);
            str = std::to_string(value1.num[i]/2) + s;
            const char *cstr = str.c_str();
            T = T + from_string(cstr);
        }
        value1=T;
        T= from_uint(0);
    }
    return res;
}

uint2022_t operator>>(const uint2022_t value, int n){
    std::string s_value = to_bin(value);
    uint2022_t res = uint2022_t();
    uint2022_t k = from_uint(1);
    for (int i=s_value.length()-n-1; i>=0; i--){
        res = res + from_uint(s_value[i]-'0')*k;
        k=k*from_uint(2);
    }
    return res;
}

uint2022_t operator<<(const uint2022_t value, int n){
    std::string s_value = to_bin(value);
    uint2022_t res = uint2022_t();
    uint2022_t k = from_uint(1);
    for (int i=s_value.length()-1; i>=n; i--){
        res = res + from_uint(s_value[i]-'0')*k;
        k=k*from_uint(2);
    }
    return res;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    std::string uint_str="0";
    std::string cont_str="";
    for (int i=0; i< uint2022_t::size; i++){
        if (value.num[i]!=0 && uint_str=="0"){
            cont_str=std::to_string( value.num[i]);
            uint_str=cont_str;
        }
        else if (uint_str!="0"){
            cont_str=std::to_string( value.num[i]);
            if (cont_str.length()<9){
                std::string s(9-cont_str.length(), '0');
                cont_str = s+cont_str;
            }
            uint_str=uint_str+cont_str;
        }
    }
    stream << uint_str << std::endl;

    return stream;
}


