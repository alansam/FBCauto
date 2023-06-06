#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>
#include <cxxabi.h>

template<typename T>
std::string type_name() {
    int status = 0;

    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(typeid(T).name(), NULL, NULL, &status),
        std::free
    };

    if (status != 0) throw status; // stub

    return res.get();
}

int main(int argc, char const * argv[]) {
    auto pcol = [](auto const & coll) {
        std::cout << std::fixed << std::setprecision(3);
        for (auto lv : coll) {
            std::cout << std::setw(8) << lv;
        }
        std::cout << std::endl;
    };
    std::cout << __cplusplus << '\n';
    auto teste = 10.78;
    std::cout << "Testing auto => " << teste << std::endl;

    auto l1 = { 0.0, 1.0, 0.1, };
    pcol(l1);
    auto v1 = std::vector<decltype(0.0)> { 0.0 + teste, 1.0 + teste, 0.1 + teste, };
    pcol(v1);

    std::cout << std::endl;

    std::cout << "A: " << typeid(teste).name()
              << " = "
              << type_name<decltype(teste)>()
              << '\n';
    std::cout << "B: " << typeid(l1).name()
              << " = "
              << type_name<decltype(l1)>()
              << '\n';
    std::cout << "C: " << typeid(std::begin(l1)).name()
              << " = "
              << type_name<decltype(std::begin(l1))>()
              << '\n';
    std::cout << "D: " << typeid(*std::begin(l1)).name()
              << " = "
              << type_name<decltype(*std::begin(l1))>()
              << '\n';
    std::cout << "E: " << typeid(v1).name()
              << " = "
              << type_name<decltype(v1)>()
              << '\n';
    std::cout << "F: " << typeid(v1[0]).name()
              << " = "
              << type_name<decltype(v1[0])>()
              << '\n';
    std::cout << "G: " << typeid(std::begin(v1)).name()
              << " = "
              << type_name<decltype(std::begin(v1))>()
              << '\n';
    std::cout << "H: " << typeid(*std::begin(v1)).name()
              << " = "
              << type_name<decltype(*std::begin(v1))>()
              << '\n';
    std::cout << "I: " << typeid(pcol).name()
              << " = "
              << type_name<decltype(pcol)>()
              << '\n';

    return 0;
}
