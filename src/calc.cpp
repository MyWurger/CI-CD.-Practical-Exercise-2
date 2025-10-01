#include "calc.h"
#include <sstream>

int add(int a, int b){ return a + b; }
int sub(int a, int b){ return a - b; }
int mul(int a, int b){ return a * b; }
std::optional<int> divi(int a, int b){ if(b==0) return std::nullopt; return a / b; }
std::optional<int> mod(int a, int b){ if(b==0) return std::nullopt; return a % b; }
std::optional<int> powi(int base, int exponent){
    if(exponent < 0) return std::nullopt;
    int result = 1;
    for(int i = 0; i < exponent; ++i){
        result *= base;
    }
    return result;
}

std::optional<int> eval_line(const std::string& line){
    std::istringstream is(line);
    int a=0,b=0; char op=0;
    if(!(is>>a>>op>>b)) return std::nullopt;

    char extra=0;
    if(is>>extra) return std::nullopt;

    switch(op){
        case '+': return add(a,b);
        case '-': return sub(a,b);
        case '*': return mul(a,b);
        case '/': return divi(a,b);
        case '%': return mod(a,b);
        case '^': return powi(a,b);
        default: return std::nullopt;
    }
}
