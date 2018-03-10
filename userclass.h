#ifndef USERCLASS_H
#define USERCLASS_H

// User defined class Expenditure
class Expenditure {
    int quant1,
    rent1,
    quant2,
    rent2;
public:
    Expenditure(int q1 = 0, int r1 = 0, int q2 = 0, int r2 = 0) : quant1(q1), rent1(r1), quant2(q2), rent2(r2) {}
    void setQuant1(int val) { quant1 = val; }
    void setRent1(int val) { rent1 = val; }
    void setQuant2(int val) { quant2 = val; }
    void setRent2(int val) { rent2 = val; }
    int getQuant1() const { return quant1; }
    int getRent1() const { return rent1; }
    int getQuant2() const { return quant2; }
    int getRent2() const { return rent2; }
    size_t size() const { return 4; }
    
    Expenditure operator+ (Expenditure const &b){
        Expenditure result(getQuant1()+b.getQuant1(), getRent1()+b.getRent1(), getQuant2()+b.getQuant2(), getRent2()+b.getRent2());
        return result;
    }
    
    Expenditure& operator= (const Expenditure &newVal){
            this -> setQuant1(newVal.getQuant1());
            this -> setRent1(newVal.getRent1());
            this -> setQuant2(newVal.getQuant2());
            this -> setRent2(newVal.getRent2());
        return *this;
    }
    
    bool operator== ( Expenditure &obj2){
        return ((this -> getQuant1() == obj2.getQuant1()) &&
                (this -> getRent1() == obj2.getRent1()) &&
                (this -> getQuant2() == obj2.getQuant2()) &&
                (this -> getRent2() == obj2.getRent2()));
    }
};


Expenditure totalExpenditure(const vector<Expenditure> &vec, int l, int r){
    Expenditure result(0,0,0,0);
    for(int i = l; i <=r; ++i){
        result = result + vec[i];
    }
    return result;
}

void updateExpenditure(vector<Expenditure> &v, size_t index, const Expenditure &value){
    v[index] = value;
}

#endif
