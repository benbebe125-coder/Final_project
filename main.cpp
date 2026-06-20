// ============================================================
//  學生成績管理系統 (Student Grade Management System)
//  C++ Template 延伸自主練習 - 第 2 週整合應用小專題
//
//  使用的 STL 元件：
//    - std::vector   ：動態陣列，作為學生資料主要儲存容器
//    - std::string   ：字串，儲存學號與姓名
//    - std::sort     ：演算法，依成績由高到低排序
//    - lambda        ：自訂排序比較規則
//
//  Template function：getMax / getMin（固定挑戰題）
//    於「統計成績」功能中實際呼叫，協助求出最高分與最低分。
//
//  編譯方式：
//    g++ -std=c++17 main.cpp -o main
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>   // std::sort
#include <iomanip>     // std::setw, std::fixed, std::setprecision
#include <limits>      // std::numeric_limits (用於清除輸入緩衝)

using namespace std;

// ------------------------------------------------------------
//  學生資料結構
// ------------------------------------------------------------
struct Student {
    string id;     // 學號
    string name;   // 姓名
    int    score;  // 成績 (0~100)
};

// ------------------------------------------------------------
//  Template function：通用最大值與最小值（固定挑戰題）
//  可套用於任何支援 > 與 < 運算子的相同型別資料，
//  本專題中用來比較 int 型別的成績。
// ------------------------------------------------------------
template <class T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

template <class T>
T getMin(T a, T b) {
    return (a < b) ? a : b;
}

// ------------------------------------------------------------
//  小工具：安全讀取整數，避免輸入非數字造成無窮迴圈
// ------------------------------------------------------------
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            // 清掉這一行剩餘的內容（例如多餘的空白或文字）
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        // 輸入失敗：清除錯誤狀態並丟棄整行
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "輸入格式錯誤，請重新輸入數字。\n";
    }
}

// ------------------------------------------------------------
//  功能 1：新增學生資料
//  若學號重複，採「拒絕新增並提示錯誤」策略。
// ------------------------------------------------------------
void addStudent(vector<Student>& students) {
    Student s;
    cout << "請輸入學號：";
    cin >> s.id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // 檢查學號是否重複
    for (const Student& exist : students) {
        if (exist.id == s.id) {
            cout << "[錯誤] 學號 " << s.id << " 已存在，無法重複新增。\n";
            return;
        }
    }

    cout << "請輸入姓名：";
    getline(cin, s.name);   // 姓名可能含空白，使用 getline

    s.score = readInt("請輸入成績 (0~100)：");
    while (s.score < 0 || s.score > 100) {
        cout << "[提示] 成績需介於 0 到 100 之間。\n";
        s.score = readInt("請重新輸入成績 (0~100)：");
    }

    students.push_back(s);
    cout << "[成功] 已新增學生：" << s.id << " " << s.name << " " << s.score << " 分\n";
}

// ------------------------------------------------------------
//  功能 2：列出所有學生
// ------------------------------------------------------------
void listStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "[提示] 目前沒有任何學生資料。\n";
        return;
    }

    cout << "\n========== 全班學生名單 ==========\n";
    cout << left << setw(12) << "學號"
         << setw(14) << "姓名"
         << right << setw(6) << "成績" << "\n";
    cout << "----------------------------------\n";
    for (const Student& s : students) {
        cout << left << setw(12) << s.id
             << setw(14) << s.name
             << right << setw(6) << s.score << "\n";
    }
    cout << "==================================\n";
    cout << "共 " << students.size() << " 位學生。\n";
}

// ------------------------------------------------------------
//  功能 3：依成績由高到低排序
//  使用 std::sort 搭配 lambda 自訂比較規則。
// ------------------------------------------------------------
void sortByScore(vector<Student>& students) {
    if (students.empty()) {
        cout << "[提示] 目前沒有任何學生資料，無法排序。\n";
        return;
    }

    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             return a.score > b.score;   // 大的在前 → 由高到低
         });

    cout << "[成功] 已依成績由高到低排序完成。\n";
    listStudents(students);
}

// ------------------------------------------------------------
//  功能 4：依學號查詢學生
// ------------------------------------------------------------
void searchById(const vector<Student>& students) {
    if (students.empty()) {
        cout << "[提示] 目前沒有任何學生資料。\n";
        return;
    }

    string target;
    cout << "請輸入要查詢的學號：";
    cin >> target;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (const Student& s : students) {
        if (s.id == target) {
            cout << "[找到] 學號：" << s.id
                 << "  姓名：" << s.name
                 << "  成績：" << s.score << " 分\n";
            return;
        }
    }
    cout << "[查無此人] 找不到學號為 " << target << " 的學生。\n";
}

// ------------------------------------------------------------
//  功能 5：統計成績
//  計算：平均、最高分、最低分、及格人數、不及格人數。
//  最高分與最低分透過 template function getMax / getMin 求得。
// ------------------------------------------------------------
void showStatistics(const vector<Student>& students) {
    if (students.empty()) {
        cout << "[提示] 目前沒有任何學生資料，無法統計。\n";
        return;
    }

    int    total    = 0;
    int    maxScore  = students[0].score;   // 初始值設為第一位學生
    int    minScore  = students[0].score;
    int    passCount = 0;
    int    failCount = 0;

    for (const Student& s : students) {
        total += s.score;

        // 呼叫固定挑戰題的 template function
        maxScore = getMax(maxScore, s.score);
        minScore = getMin(minScore, s.score);

        if (s.score >= 60) passCount++;
        else               failCount++;
    }

    double average = static_cast<double>(total) / students.size();

    cout << "\n========== 成績統計結果 ==========\n";
    cout << "全班人數    ：" << students.size() << " 人\n";
    cout << fixed << setprecision(2);
    cout << "全班平均    ：" << average << " 分\n";
    cout << "最高分      ：" << maxScore << " 分\n";
    cout << "最低分      ：" << minScore << " 分\n";
    cout << "及格人數    ：" << passCount << " 人 (>= 60)\n";
    cout << "不及格人數  ：" << failCount << " 人 (<  60)\n";
    cout << "==================================\n";
}

// ------------------------------------------------------------
//  顯示選單
// ------------------------------------------------------------
void printMenu() {
    cout << "\n====== 學生成績管理系統 ======\n";
    cout << "1. Add student      (新增學生)\n";
    cout << "2. List all students(列出所有學生)\n";
    cout << "3. Sort by score    (依成績排序)\n";
    cout << "4. Search by id     (依學號查詢)\n";
    cout << "5. Show statistics  (成績統計)\n";
    cout << "0. Exit             (離開)\n";
    cout << "==============================\n";
}

// ------------------------------------------------------------
//  主程式
// ------------------------------------------------------------
int main() {
    vector<Student> students;   // 學生資料主要儲存容器

    while (true) {
        printMenu();
        int choice = readInt("請選擇功能：");

        switch (choice) {
            case 1: addStudent(students);     break;
            case 2: listStudents(students);   break;
            case 3: sortByScore(students);    break;
            case 4: searchById(students);     break;
            case 5: showStatistics(students); break;
            case 0:
                cout << "感謝使用，程式結束。\n";
                return 0;
            default:
                cout << "[錯誤] 沒有此選項，請重新選擇。\n";
        }
    }
    return 0;
}
