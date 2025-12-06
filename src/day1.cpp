#include "aoc.h"

const std::string path = "/home/saul/Work/aoc-cpp/input/";
const std::string example1 = path + "example1.txt";
const std::string example2 = path + "example2.txt";
const std::string example3 = path + "example3.txt";
const std::string example4 = path + "example4.txt";
const std::string day1_file = path + "day1.txt";
const std::string day3_file = path + "day3.txt";
const std::string day5_file = path + "day5.txt";
const std::string day6_file = path + "day6.txt";

void day1_part1();
void day1_part2();
void day3_part1();
void day3_part2();
void day5_part1();
void day5_part2();
void day6_part1();
void day6_part2();

int main() {
    day1_part1();
    day1_part2();
    day3_part1();
    day3_part2();
    day5_part1();
    day5_part2();
    day6_part1();
    day6_part2();

    return 0;
}

// (b + (a % b)) % b to handle negative módulo
int normalize(int x) {
    return (x % 100 + 100) % 100;
}

void day1_part1() {
    std::ifstream file(day1_file);
    std::string line;
    
    int index = 50;
    int zero_count = 0;

    if(file.is_open()) {
        while(std::getline(file, line)) {
            int op = line[0] == 'L' ? -1 : 1;

            std::string rest = line.substr(1);
            int value = std::stoi(rest);
            
            index = ((value * op) + index) % 100;

            if(index == 0) {
                zero_count++;
            }
        }
    }

    std::cout << "Day 1 part 1 result: " << zero_count << "\n";
}

void day1_part2() {
    std::ifstream file(day1_file);
    std::string line;

    int zero_count = 0;
    int index = 50;

    if(file.is_open()) {
        while(std::getline(file, line)) {
            int op = line[0] == 'L' ? -1 : 1;

            std::string rest = line.substr(1);
            int value = std::stoi(rest);

            // stupid solution :)
            for (int i = 0; i < value; i++) {
                index = normalize(index + op);
                if (index == 0) {
                    zero_count++;
                }
            }
        }
    }

    std::cout << "Day 1 part 2 result: " << zero_count << "\n";
}

void day3_part1() {
    std::ifstream file(day3_file);
    std::string line;

    int sum = 0;
    if(file.is_open()) {
        while(std::getline(file, line)) {
            int largest = 0;
            for(size_t i = 0; i < line.size(); i++){
                for(size_t j = i + 1; j < line.size(); j++){
                    int value = (line[i] - '0') * 10 + (line[j] - '0');

                    if(value > largest) {
                        largest = value;
                    }
                }
            }
            sum += largest;
        }
    }

    std::cout << "Day 2 part 1 result: " << sum << "\n";
}

void day3_part2() {
    std::ifstream file(day3_file);
    std::string line;

    int max_digits = 12;
    long long total_sum = 0;

    if(file.is_open()) {
        while(std::getline(file, line)) {
            std::vector<int> stack;
            int total_discards = line.size() - max_digits;

            for(size_t i = 0; i < line.size(); i++) {
                int value = aoc::char_to_int(line[i]);

                while(!stack.empty() && total_discards > 0 && stack.back() < value){
                    stack.pop_back();
                    total_discards--;
                }
            
                stack.push_back(value);
            }

            if((int)stack.size() > max_digits) stack.resize(max_digits);

            long long number = 0;
            for(int value : stack) {
                number = number * 10 + value;
            }

            total_sum += number;
        }
    }

    std::cout << "Day 3 part 2 result: " << total_sum << "\n";
}

void day5_part1() {
    std::ifstream file(day5_file);
    std::string line;
    std::vector<aoc::Range> ranges;

    bool swap = false;
    int fresh = 0;

    if(file.is_open()) {
        while(std::getline(file, line)) {
            if(line == "") {
                swap = true;
                continue;
            }

            if(swap) {
                long digit = std::stoll(line);
                for(aoc::Range r : ranges) {
                    if(digit >= r.lower && digit <= r.upper) {
                        fresh++;
                        break;
                    }
                }
            } else {
                long a;
                long b;

                std::stringstream ss(line);
                std::string tmp;

                getline(ss, tmp, '-');
                a = std::stoll(tmp);
                getline(ss, tmp, '-');
                b = std::stoll(tmp);
                
                aoc::Range tmp_range(a, b);
                ranges.push_back(tmp_range);
            }
        }
    }

    std::cout << "Day 5 part 1 result: " << fresh << "\n";
}

void day5_part2() {
    std::ifstream file(day5_file);
    std::string line;
    std::vector<aoc::Range> ranges;

    long fresh = 0;
    bool swap = false;

    if(file.is_open()) {
        while(std::getline(file, line)) {
            if(line == "") {
                swap = true;
                continue;
            }

            if(swap) {
                break;
            } else {
                long a;
                long b;

                std::stringstream ss(line);
                std::string tmp;

                getline(ss, tmp, '-');
                a = std::stoll(tmp);
                getline(ss, tmp, '-');
                b = std::stoll(tmp);
                
                aoc::Range tmp_range(a, b);
                ranges.push_back(tmp_range);
            }
        }


        std::sort(ranges.begin(), ranges.end(), [](aoc::Range &a, aoc::Range &b){ return a.lower < b.lower; });

        std::vector<aoc::Range> new_ranges;

        for(aoc::Range &r : ranges){
            if(new_ranges.empty()) {
                aoc::Range tmp(r.lower, r.upper);
                new_ranges.push_back(tmp);
                continue;
            }

            aoc::Range &back = new_ranges.back();

            if(r.lower <= back.upper) {
                back.upper = std::max(back.upper, r.upper);
            } else {
                new_ranges.push_back(r);
            }
        }
        for(aoc::Range r : new_ranges) {
            fresh += (r.upper - r.lower) + (long long)1;
        }
    }

    std::cout << "Day 5 part 2 result: " << fresh << "\n";
}

void day6_part1(){
    std::ifstream file(day6_file);
    std::string line;
    std::vector<long> numbers;
    std::vector<std::string> operators;

    if(file.is_open()) {
        while(std::getline(file, line)) {
            std::stringstream ss(line);
            std::string tmp;
            while(getline(ss, tmp, ' ')) {
                if(tmp == "*" || tmp == "+") {
                    operators.push_back(tmp);
                } else {
                    if(tmp != "") {
                        numbers.push_back(std::stoll(tmp));
                    }
                }
            }
        }
    }

    int modulo = operators.size();

    // very safe c++ :)
    long total = 0;
    for(size_t i = 1; i <= operators.size(); i++) {
        if(operators[i - 1] == "+") {
            total += numbers[i - 1] + numbers[i + modulo - 1] + numbers[i + modulo * 2 - 1] + numbers[i + modulo * 3 - 1];
        } else {
            total += numbers[i - 1] * numbers[i + modulo - 1] * numbers[i + modulo * 2 - 1] * numbers[i + modulo * 3 - 1];
        }
    }

    std::cout << "Day 6 part 1 result: " << total << "\n";
}

char get_or_zero(std::string number, int index) {
    if(index >= (int)number.size()) return '0';
    return number[index];
}

void day6_part2(){
    std::ifstream file(day6_file);

    std::vector<std::string> lines;
    if(file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            if (!line.empty()) lines.push_back(line);
        }
    }

    // all lines have same size ez pz
    char current_op = '-';
    long long result = 0;
    long long accumulator = 0;
    for(size_t i = 0; i < lines[0].size(); i++) {
        std::string token {lines[0][i], lines[1][i], lines[2][i], lines[3][i]};

        // skip columns
        if(token == "    ")continue;

        char tmp_op = lines[4][i];
        if(tmp_op == '+' || tmp_op == '*') {
            current_op = tmp_op;
            result += accumulator;
            accumulator = current_op == '*' ? 1 : 0;
        }
        
        int number = std::stoi(token);

        if(current_op == '*'){
            accumulator *= number;
        } else {
            accumulator += number;
        }
    }

    // sum the remaining thingy
    result += accumulator;

    std::cout << "Day 6 part 2 result: " << result << "\n";
}