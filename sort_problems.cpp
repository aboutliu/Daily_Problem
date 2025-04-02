#include <bits/stdc++.h>

using i64 = long long;

template<class T>
struct ArrangeCategories {
    ArrangeCategories() {}
    // 解析 Markdown 表格的一行
    T parseLine(const std::string &line) {
        std::stringstream ss(line);
        std::string temp, diffStr, problem, hint, solutions;

        std::getline(ss, temp, '|'); // 跳过第一个 '|'
        std::getline(ss, diffStr, '|');
        std::getline(ss, problem, '|');
        std::getline(ss, hint, '|');
        std::getline(ss, solutions, '|');

        // 去除字符串前后空格
        auto trim = [](std::string &s) {
            while (!s.empty() && isspace(s.front())) s.erase(s.begin());
            while (!s.empty() && isspace(s.back())) s.pop_back();
        };

        trim(diffStr);
        trim(problem);
        trim(hint);
        trim(solutions);
        return {std::stoi(diffStr), problem, hint, solutions};
    }
    // 读取 Markdown 文件并解析数据
    std::pair<int, std::vector<T>> readMarkdownFile(const std::string &filename) {
        std::ifstream file(filename);
        std::vector<T> problems;
        std::string line;
        bool headerSkipped = false;
        if (!file) {
            std::cerr << "无法打开文件 ->: " << filename << "\n";
            std::cerr << "请重新输入: \n";
            return std::pair {-1, problems};
        }
        while (std::getline(file, line)) {
            if (!headerSkipped) {
                // 跳过前两行（表头和分隔符）
                headerSkipped = true;
                std::getline(file, line);
                continue;
            }
            if (line.find('|') != std::string::npos) {
                problems.push_back(parseLine(line));
            }
        }

        file.close();
        return std::pair {1, problems};
    }

    // 写入 Markdown 文件
    int writeMarkdownFile(const std::string &filename, const std::vector<T> &problems) {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "无法写入文件: " << filename << "\n";
            return 0;
        }

        // 写入表头
        file << "| Difficulty | Problems | Hints | Solutions |\n";
        file << "|------------|------------|-----------|-----------|\n";

        // 写入题目数据
        for (const auto &p : problems) {
            file << "| " << p.difficulty << " | " << p.problem << " | " << p.hint << " | " << p.solutions << " |\n";
        }

        file.close();
        return 1;
    }
    // 插入新数据并排序
    int insertAndSort(const std::string &filename, int newDifficulty, const std::string &newProblem, const std::string &newHint, const std::string &newsolutions) {
        auto [o, problems] = readMarkdownFile(filename);
        if (o == -1) {
            return 0;
        }

        // 插入新数据
        problems.push_back({newDifficulty, newProblem, newHint, newsolutions});

        // 按难度排序
        std::sort(problems.begin(), problems.end());

        // 写回 Markdown 文件
        return writeMarkdownFile(filename, problems);
    }
    int checkname(std::string a, std::string b) {
        for (int i = 0; i < a.size(); ++i) {
            if (a[i + 1] == ']') {
                return a.substr(1, i) == b;
            }
        }
        return 0;
    }
    int del(const std::string &filename, const std::string problemname) {
        auto [u, problems] = readMarkdownFile(filename);
        if (u == -1) {
            return 0;
        }
        std::vector<T> tproblems;
        for (auto [a, b, c, d] : problems) {
            if (checkname(b, problemname)) {
                continue;
            }
            tproblems.push_back({a, b, c});
        }
        writeMarkdownFile(filename, tproblems);
        return tproblems.size() < problems.size();
    }
};

template<class T>
struct ArrangeProblmes {
    ArrangeProblmes() {}
    T parseLine(const std::string &line) {
        std::stringstream ss(line);
        std::string temp, diffStr, problem, hint, solutions;

        getline(ss, temp, '|'); // 跳过第一个 '|'
        getline(ss, diffStr, '|');
        getline(ss, problem, '|');
        getline(ss, hint, '|');

        // 去除字符串前后空格
        auto trim = [](std::string &s) {
            while (!s.empty() && isspace(s.front())) s.erase(s.begin());
            while (!s.empty() && isspace(s.back())) s.pop_back();
        };

        trim(diffStr);
        trim(problem);
        trim(hint);

        return {std::stoi(diffStr), problem, hint};
    }
    std::pair<int, std::vector<T>> readMarkdownFile(const std::string &filename) {
        std::ifstream file(filename);
        std::vector<T> problems;
        std::string line;
        bool headerSkipped = false;
        if (!file) {
            std::cerr << "无法打开文件 ->: " << filename << "\n";
            std::cerr << "请重新输入: \n";
            return std::pair {-1, problems};
        }
        while (std::getline(file, line)) {
            if (!headerSkipped) {
                // 跳过前两行（表头和分隔符）
                headerSkipped = true;
                getline(file, line);
                continue;
            }
            if (line.find('|') != std::string::npos) {
                problems.push_back(parseLine(line));
            }
        }

        file.close();
        return std::pair {0, problems};
    }
    int writeMarkdownFile(const std::string &filename, const std::vector<T> &problems) {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "无法写入文件: " << filename << "\n";
            return 0;
        }

        // 写入表头
        file << "| Difficulty | Problems | Hints |\n";
        file << "|------------|------------|-----------|\n";

        // 写入题目数据
        for (const auto &p : problems) {
            file << "| " << p.difficulty << " | " << p.problem << " | " << p.hint << " |\n";
        }

        file.close();
        return 1;
    }
    int insertAndSort(const std::string &filename, int newDifficulty, const std::string &newProblem, const std::string &newHint) {
        auto [u, problems] = readMarkdownFile(filename);
        if (u == -1) {
            return 0;
        }

        // 插入新数据
        problems.push_back({newDifficulty, newProblem, newHint});

        // 按难度排序
        std::sort(problems.begin(), problems.end());

        // 写回 Markdown 文件
        return writeMarkdownFile(filename, problems);
    }
    int checkname(std::string a, std::string b) {
        for (int i = 0; i < a.size(); ++i) {
            if (a[i + 1] == ']') {
                return a.substr(1, i) == b;
            }
        }
        return 0;
    }
    int del(const std::string &filename, const std::string problemname) {
        auto [u, problems] = readMarkdownFile(filename);
        if (u == -1) {
            return 0;
        }
        std::vector<T> tproblems;
        for (auto [a, b, c] : problems) {
            if (checkname(b, problemname)) {
                continue;
            }
            tproblems.push_back({a, b, c});
        }
        writeMarkdownFile(filename, tproblems);
        return tproblems.size() < problems.size();
    }
};


// 题目结构体
struct CategoriesProblem {
    int difficulty;
    std::string problem;
    std::string hint;
    std::string solutions;

    // 排序规则（按照 difficulty 升序）
    bool operator<(const CategoriesProblem &other) const {
        return difficulty < other.difficulty;
    }
};

struct Problem {
    int difficulty;
    std::string problem;
    std::string hint;

    // 排序规则（按照 difficulty 升序）
    bool operator<(const Problem &other) const {
        return difficulty < other.difficulty;
    }
};

ArrangeProblmes<Problem> arrangeproblmes;

ArrangeCategories<CategoriesProblem> arrangecategories;


std::pair<int, std::string> checknumber(std::string s, int limit) {
    std::string res {};
    if (s[0] == '0') {
        res = "请输入合法的数字";
        return std::pair {-1, res};
    }
    for (auto i : s) {
        if (!std::isdigit(i)) {
            res = "请输入合法的数字";
            return std::pair {-1, res};
        }
    }
    if (s.size() > std::to_string(limit).size() || std::stoi(s) > limit) {
        res = "请输入小于等于 " + std::to_string(limit) + " 的数字";
        return std::pair {-1, res};
    }
    return std::pair {0, res};
}

void checkfile(std::string filename, std::string s) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "你的 " << s << " 文件并不存在，请检查！";
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "用法: " << argv[0] << " <Markdown文件路径>" << "\n";
        return 1;
    }
    std::string filename = argv[1]; // 你的 Markdown 地址
    std::string categories_path = argv[2]; // 你的 categories 地址
    std::string solution_path = argv[3]; // 你的 solution 地址
    int newDifficulty;
    std::string problemname, newProblem, newHint, newsolutions, categories;

    int c = 0;
    std::string op;
    while (1) {
        std::cout << "1. insert problem. 2. insert categories. 3. 1 and 2\n";
        std::cout << "4. delete problem. 5. delete categories. 6. 4 and 5\n";
        std::getline(std::cin, op);
        auto [u, v] = checknumber(op, 6);
        if (u == -1) {
            std::cout << v << "\n";
        } else {
            if (op == "1" || op == "4") {
                checkfile(filename, "markdown");
            } else if (op == "2" || op == "5") {
                checkfile(filename, "categories");
            } else {
                checkfile(filename, "markdown");
                checkfile(filename, "categories");
            }
            break;
        }
        c++;
        if (c > 2) {
            std::cout << "🤡\n";
            exit(1);
        }
    }


    c = 0;
    std::string T;
    while (1) {
        std::cout << "请输入需要添加的题目数量: ";
        std::getline(std::cin, T);
        auto [u, v] = checknumber(T, 5);
        if (u == -1) {
            std::cout << v << "\n";
        } else {
            break;
        }
        c++;
        if (c > 2) {
            std::cout << "🤡\n";
            exit(1);
        }
    }

    int t = std::stoi(T);

    auto add1 = [&]() -> int {
        return arrangeproblmes.insertAndSort(filename, newDifficulty, newProblem, newHint);
    };
    auto add2 = [&]() -> int {
        int res = 0;
        std::cout << "每行一个 categories，最后单独一行以 over 结束\n";
        while (1) {
            std::cout << "请输入categories: ";
            std::getline(std::cin, categories);
            if (categories.empty()) {
                continue;
            }
            if (categories == "over") {
                break;
            }
            auto tcategories_path = categories_path + "/" + categories + ".md";
            newsolutions = "[Editorial](" + solution_path + problemname + ")";
            res |= arrangecategories.insertAndSort(tcategories_path, newDifficulty, newProblem, newHint, newsolutions);
        }
        return res;
    };
    auto insert = [&]() -> int {
        std::cout << "请输入题目名称: ";
        std::getline(std::cin, problemname);
        auto tname = problemname;
        problemname += ".md";

        c = 0;
        std::string ts {};
        while (1) {
            std::cout << "请输入新题目难度: ";
            std::getline(std::cin, ts);
            auto [u, v] = checknumber(ts, 4000);
            if (u == -1) {
                std::cout << v << "\n";
            } else {
                newDifficulty = std::stoi(ts);
                break;
            }
            c++;
            if (c > 2) {
                std::cout << "🤡\n";
                exit(1);
            }
        }
    
        std::cout << "请输入新题目链接: ";
        std::getline(std::cin, newProblem);
        newProblem = "[" + tname + "](" + newProblem + ")";
    
        std::cout << "请输入提示: ";
        std::getline(std::cin, newHint);

        int res = 0;
        if (op == "1") {
            res = add1();
        } else if (op == "2") {
            res = add2();
        } else {
            res |= add1();
            res |= add2();
        }
        return res;
    };

    auto del1 = [&]() -> int {
        return arrangeproblmes.del(filename, problemname);
    };
    auto del2 = [&]() -> int {
        int res = 0;
        std::cout << "每行一个 categories，最后单独一行以 over 结束\n";
        while (1) {
            std::cout << "请输入categories: ";
            std::getline(std::cin, categories);
            if (categories.empty()) {
                continue;
            }
            if (categories == "over") {
                break;
            }
            auto tcategories_path = categories_path + "/" + categories + ".md";
            res |= arrangecategories.del(tcategories_path, problemname);
        }
        return res;
    };
    auto del = [&]() -> int {
        std::cout << "请输入题目名称: ";
        std::getline(std::cin, problemname);

        int res = 0;
        if (op == "4") {
            res = del1();
        } else if (op == "2") {
            res = del2();
        } else {
            res |= del1();
            res |= del2();
        }
        return res;
    };

    while (t && std::stoi(op) < 4) { 
        int res = insert();
        if (res) {
            std::cout << "题目已添加并排序\n";
            t--;
        } else {
            std::cout << "题目添加失败\n";
        }
    }
    while (t && std::stoi(op) > 3) {
        int res = del();
        if (res) {
            std::cout << "题目已删除\n";
            t--;
        } else {
            std::cout << "题目删除失败\n";
        }
    }

    return 0;
}