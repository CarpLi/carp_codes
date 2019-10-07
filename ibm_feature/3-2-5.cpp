
class Rule2{
public:
    Rule2() : Rule2(2){};
    Rule2(int i) : Rule2('a'){}
    Rule2(char c) : Rule2(){};

    int i;
    int c;
};