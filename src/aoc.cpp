#include "aoc.h"

const std::string path = "/home/saul/Work/aoc-cpp/input/";
const std::string example1 = path + "example1.txt";
const std::string example3 = path + "example3.txt";
const std::string example5 = path + "example5.txt";
const std::string example6 = path + "example6.txt";
const std::string example7 = path + "example7.txt";
const std::string example8 = path + "example8.txt";
const std::string day1_file = path + "day1.txt";
const std::string day3_file = path + "day3.txt";
const std::string day5_file = path + "day5.txt";
const std::string day6_file = path + "day6.txt";
const std::string day7_file = path + "day7.txt";


void day1_part1();
void day1_part2();
void day3_part1();
void day3_part2();
void day5_part1();
void day5_part2();
void day6_part1();
void day6_part2();
void day7_part1();
void day7_part2();
void day8_part1();

int main() {
    day1_part1();
    day1_part2();
    day3_part1();
    day3_part2();
    day5_part1();
    day5_part2();
    day6_part1();
    day6_part2();
    day7_part1();
    day7_part2();
    day8_part1();

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

    std::cout << "Day 3 part 1 result: " << sum << "\n";
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

void day7_part1(){
    std::ifstream file(day7_file);
    std::vector<std::string> lines;
    long times_split = 0;

    if(file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            if (!line.empty()) lines.push_back(line);
        }
    }

    // init beams matrix all to false
    std::vector<std::vector<bool>> beams;
    for(size_t y = 0; y < lines.size(); y++){
        std::vector<bool> tmp;
        for(size_t x = 0; x < lines[y].size(); x++){
            tmp.push_back(false);
        }
        beams.push_back(tmp);
    }


    for(size_t y = 0; y < lines.size(); y++){
        for(size_t x = 0; x < lines[y].size(); x++){
            if(y == 0) continue;

            if((lines[y-1][x] == '|' && lines[y][x] != '^') || lines[y-1][x] == 'S'){
                lines[y][x] = '|';
            }

            char c = lines[y][x];

            // logic for setting beams
            if(c == '.') continue;

            if(c == '^' && lines[y-1][x] == '|') {
                times_split++;  
                lines[y][x-1] = '|';
                lines[y][x+1] = '|';
            }
        }
    }

    // for(std::string line : lines) {
    //     std::cout << line << "\n";
    // }

    std::cout << "Day 7 part 1 result: " << times_split <<"\n";
}

void day7_part2(){
    std::ifstream file(day7_file);
    std::vector<std::string> lines;

    if(file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            if (!line.empty()) lines.push_back(line);
        }
    }

    std::vector<std::vector<long>> beams;
    for(size_t y = 0; y < lines.size(); y++){
        std::vector<long> tmp;
        for(size_t x = 0; x < lines[y].size(); x++){
            tmp.push_back(0);
        }
        beams.push_back(tmp);
    }


    for(size_t y = 0; y < lines.size(); y++){
        for(size_t x = 0; x < lines[y].size(); x++){
            if(y == 0) {
                if(lines[y][x] == 'S') {
                    beams[y][x] = 1;
                }
                continue;
            }

            char c = lines[y][x];

            if(c == '.') {
                beams[y][x] += beams[y-1][x];
            }

            if(c == '^') {
                beams[y][x+1] += beams[y-1][x];
                beams[y][x-1] += beams[y-1][x];
            }
        }
    }

    long result = 0;
    for(long v : beams.back()) {
        result += v;
    }

    std::cout << "Day 7 part 2 result: " << result <<"\n";
}

void day8_part1() {
    std::ifstream file(example8);
    std::vector<std::string> lines;
    std::vector<aoc::JunctionBox> boxes;
    std::vector<aoc::Node> nodes;

    if(file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            if (!line.empty()) lines.push_back(line);
        }
    }

    std::vector<long> numbers;
    for(std::string s : lines) {
        std::stringstream ss(s);
        std::string tmp;
        
        while(getline(ss, tmp, ',')){
            numbers.push_back(std::stol(tmp));
        }

        long a = numbers[0];
        long b = numbers[1];
        long c = numbers[2];

        numbers.clear();
        nodes.push_back(aoc::Node(a,b,c));
    }

    std::vector<aoc::Edge> pairs;
    for(size_t i = 0; i < nodes.size(); i++){
        double shortest_distance = std::numeric_limits<double>::max();
        aoc::Node* closest = nullptr;

        for(size_t j = 0; j < nodes.size(); j++){
            if(i == j) continue;
            double dist = aoc::distance(&nodes[i], &nodes[j]);
            if(dist < shortest_distance){
                shortest_distance = dist;
                closest = &nodes[j];
            }

        }

        if(closest == nullptr) continue;

        // make sure this pair does not exist already
        // checked by references
        bool exist = false;
        for(aoc::Edge e : pairs) {
            bool node_ab = (e.a == &nodes[i] && e.b == closest);
            bool node_ba = (e.a == closest && e.b == &nodes[i]);
            if(node_ab || node_ba) {
                exist = true;
                break;
            }
        }

        if(!exist) {
            pairs.push_back(aoc::Edge(&nodes[i], closest, shortest_distance));
        }
    }

    std::sort(pairs.begin(), pairs.end(), [](const aoc::Edge &a, const aoc::Edge &b){ return a.distance < b.distance; });

    std::vector<aoc::Graph> circuits;

    for(size_t i = 0; i < pairs.size(); i++){
        if(circuits.empty()) {
            aoc::Graph circuit;
            circuit.add_edge(&pairs[i]);
            circuits.push_back(circuit);
            continue;
        }

        // now we need to check if any node of this edge
        // belongs to any other circuit
        bool a_exist = false;
        bool b_exist = false;
        for(size_t j = 0; j < circuits.size(); j++){
            for(size_t k = 0; k < circuits[j].nodes.size(); k++) {
                if(circuits[j].nodes[k] == pairs[i].a) a_exist = true;
                if(circuits[j].nodes[k] == pairs[i].b) b_exist = true;
                if(a_exist || b_exist) break;
            }
            if(a_exist && b_exist) break;
        }
    }

    for(aoc::Graph g : circuits) {
        std::cout << g.nodes.size() << "\n";
    }
}