#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <windows.h>


int fastpow(int a, int n) {
    int res = 1;
	while(n){
		if (n%2) res = (res * a);
		a *= a;
		n >>= 1;
	}
	return res;
}

int find_mistake(std::string& input) {
    int i, mistake = 0;
    for (i = 0; i < 15; ++i)
        if (input[i] == '1')
            mistake ^= i + 1;
    return mistake;
}

bool check_the_digits(std::string& input) {
    for (int i = 0; i < 15; ++i)
        if (input[i] != '0' && input[i] != '1')
            return false;
    return true;
}

void out_res(int b, std::string& input, std::string& res) {
    std::string info;
    for (int i = 0; i < 15; ++i) {
        if (i + 1 == b) b <<= 1;
        else info += input[i];
    }
    std::cout << info << " ";
    res += info;
}

void fix(int& mistake, std::string& input) {
    if (mistake) {
        input[mistake - 1] ^= '0' ^ '1';
        mistake = find_mistake(input);
        if (mistake) std::cout << "Invalid code";
    }
}

void Split_in_parts(std::vector<std::string>& parts, std::string& input) {
    std::pair<int, int> iters(0,0);    //i,j
    for(;iters.first < input.length();iters.first += 15) {
        std::string tmp(input, iters.first, 15);
        parts[iters.second++] = tmp;
        ++iters.first;
    }
}

void prepare_code(std::vector<std::string>& parts, std::string& input) {
    std::cout << "Are there any separating spaces: y/n?\n";
    char c;std::cin >> c;
    if (c == 'n')
        for (int i = 15; i < input.length(); i += 16)  input.insert(i, " ");

    Split_in_parts(parts, input);
}

void input_code(std::string& input) {
    std::getline(std::cin, input);
}

int main() {
    std::ios::sync_with_stdio(false);
    SetConsoleCP(1251); SetConsoleOutputCP(1251);

    int mistake = 0;
    std::string input, res;
    input_code(input);
    std::vector<std::string> parts(input.length() / 15);

    prepare_code(parts, input);
    for (auto it = parts.begin(); it < parts.end(); ++it) {
        mistake = find_mistake(*it);
        if (check_the_digits(*it)) {
            fix(mistake, *it);
            out_res(1, *it, res);
        }
        else std::cout << "Invalid code";
    }

    std::cout << "\nSplit in eights(8): y/n?\n";
    char c; std::cin >> c;
    if (c == 'y') {
        for (int i = 8; i < res.length(); i += 9) res.insert(i, " ");
        std::cout << "Output the result in file: y/n?\n";
        char c; std::cin >> c;
        if (c == 'y') freopen("res.txt", "w", stdout);
    }
    std::cout << std::endl;
    for (int i = 0; i < res.length(); ++i) {
        int pow = 7, code = 0;
        while (res[i] != ' ' && i < res.length()) code += fastpow(2, pow--) * static_cast<int>(res[i++] - 48);
        std::cout << static_cast<unsigned char>(code);
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
