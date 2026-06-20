# 學生成績管理系統 (Student Grade Management System)

> C++ Template 延伸自主練習作業 — 第 2 週整合應用小專題

本專題接續課堂 Chapter 16 Templates 的內容，從 function template / class template 的觀念延伸到
STL containers 與 STL algorithms，實作一個以選單操作的「學生成績管理系統」。

## GitHub Repository

```
https://github.com/your-account/your-repository
```

> ⚠️ 請將上面網址換成你自己的 **Public** repository 網址，並同步貼到 Ecourse 繳交欄位與報告第一頁。

## 專案檔案結構

```
.
├── main.cpp      # 主程式（所有功能與 template function 皆在此）
├── README.md     # 本說明檔（編譯與執行方式）
└── report.pdf    # 學習報告（或 report.md）
```

## 環境需求

- g++ 支援 C++17（建議 g++ 9 以上）
- 任何提供標準輸入的終端機環境

## 編譯方式

```bash
g++ -std=c++17 main.cpp -o main
```

本專題為單一 `main.cpp`，不需額外連結其他檔案。

## 執行方式

```bash
./main          # Linux / macOS
main.exe        # Windows
```

執行後會出現選單，依提示輸入數字選擇功能：

```
====== 學生成績管理系統 ======
1. Add student      (新增學生)
2. List all students(列出所有學生)
3. Sort by score    (依成績排序)
4. Search by id     (依學號查詢)
5. Show statistics  (成績統計)
0. Exit             (離開)
==============================
```

## 功能說明

| 選項 | 功能 | 說明 |
|------|------|------|
| 1 | 新增學生 | 輸入學號、姓名、成績；學號重複時會拒絕並提示錯誤；成績限制 0~100 |
| 2 | 列出所有學生 | 以對齊欄位輸出學號、姓名、成績 |
| 3 | 依成績排序 | 使用 `std::sort` + lambda，由高到低排序後列出 |
| 4 | 依學號查詢 | 輸入學號查詢；查無此人會提示訊息 |
| 5 | 成績統計 | 輸出平均、最高分、最低分、及格 / 不及格人數 |
| 0 | 離開 | 結束程式 |

## 使用到的 STL 與 Template

- `std::vector<Student>`：學生資料主要儲存容器（動態陣列）
- `std::string`：儲存學號與姓名
- `std::sort` + lambda：依成績由高到低排序
- `std::setw` / `std::fixed` / `std::setprecision`：輸出格式對齊與小數位數
- **Template function `getMax` / `getMin`**（固定挑戰題）：於「成績統計」功能中呼叫，
  用來求出最高分與最低分。

## 範例執行結果（節錄）

```
========== 成績統計結果 ==========
全班人數    ：5 人
全班平均    ：71.60 分
最高分      ：92 分
最低分      ：45 分
及格人數    ：3 人 (>= 60)
不及格人數  ：2 人 (<  60)
==================================
```
