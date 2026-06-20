#include <random>
#include <map>


int main() {
    std::random_device RandomObject{};
    std::mt19937 gen{RandomObject()};

    std::normal_distribution NormD{5.0,2.0};

    

    return  0;
}