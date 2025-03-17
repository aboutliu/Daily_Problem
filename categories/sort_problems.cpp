#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// 题目结构体
struct Problem {
    int difficulty;
    string problem;
    string hint;
    string solutions;

    // 排序规则（按照 difficulty 升序）
    bool operator<(const Problem &other) const {
        return difficulty < other.difficulty;
    }
};

// 解析 Markdown 表格的一行
Problem parseLine(const string &line) {
    stringstream ss(line);
    string temp, diffStr, problem, hint, solutions;

    getline(ss, temp, '|'); // 跳过第一个 '|'
    getline(ss, diffStr, '|');
    getline(ss, problem, '|');
    getline(ss, hint, '|');
    getline(ss, solutions, '|');

    // 去除字符串前后空格
    auto trim = [](string &s) {
        while (!s.empty() && isspace(s.front())) s.erase(s.begin());
        while (!s.empty() && isspace(s.back())) s.pop_back();
    };

    trim(diffStr);
    trim(problem);
    trim(hint);
    trim(solutions);

    return {stoi(diffStr), problem, hint, solutions};
}

// 读取 Markdown 文件并解析数据
vector<Problem> readMarkdownFile(const string &filename) {
    ifstream file(filename);
    vector<Problem> problems;
    string line;
    bool headerSkipped = false;

    if (!file) {
        cerr << "无法打开文件: " << filename << endl;
        exit(1);
    }

    while (getline(file, line)) {
        if (!headerSkipped) {
            // 跳过前两行（表头和分隔符）
            headerSkipped = true;
            getline(file, line);
            continue;
        }
        if (line.find('|') != string::npos) {
            problems.push_back(parseLine(line));
        }
    }

    file.close();
    return problems;
}

// 写入 Markdown 文件
void writeMarkdownFile(const string &filename, const vector<Problem> &problems) {
    ofstream file(filename);
    if (!file) {
        cerr << "无法写入文件: " << filename << endl;
        exit(1);
    }

    // 写入表头
    file << "| Difficulty | Problems | Hints | Solutions |\n";
    file << "|------------|------------|-----------|-----------|\n";

    // 写入题目数据
    for (const auto &p : problems) {
        file << "| " << p.difficulty << " | " << p.problem << " | " << p.hint << " | " << p.solutions << " |\n";
    }

    file.close();
}

// 插入新数据并排序
void insertAndSort(const string &filename, int newDifficulty, const string &newProblem, const string &newHint, const string &newsolutions) {
    vector<Problem> problems = readMarkdownFile(filename);

    // 插入新数据
    problems.push_back({newDifficulty, newProblem, newHint, newsolutions});

    // 按难度排序
    sort(problems.begin(), problems.end());

    // 写回 Markdown 文件
    writeMarkdownFile(filename, problems);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "用法: " << argv[0] << " <Markdown文件路径>" << endl;
        return 1;
    }
    string filename = argv[1]; // 你的 Markdown 文件
    int newDifficulty;
    string newProblem, newHint, newsolutions;

    cout << "请输入需要添加的题目数量: ";

    int t;
    cin >> t;

    while (t--) {   cout << "请输入新题目难度: ";
        cin >> newDifficulty;
        cin.ignore(); // 处理换行符
    
        cout << "请输入新题目链接[](): ";
        getline(cin, newProblem);
    
        cout << "请输入提示: ";
        getline(cin, newHint);
    
        cout << "请输入做法: ";
        getline(cin, newsolutions);
    
        insertAndSort(filename, newDifficulty, newProblem, newHint, newsolutions);
    
        cout << "题目已添加并排序，检查 " << filename << " 文件！" << endl;
    }
    return 0;
}