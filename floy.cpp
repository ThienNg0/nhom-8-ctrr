#include <bits/stdc++.h>
using namespace std;
const int oo = 99999;

// Hàm đọc ma trận từ file
void readGraphFromFile(const string& fileName, vector<vector<int>>& graph, int& n) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Khong the mo file " << fileName << endl;
        exit(1);
    }
    file >> n; // Đọc số đỉnh
    graph.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> graph[i][j];
        }
    }
    file.close();
}

// Hàm Floyd-Warshall
void floydWarshall(const vector<vector<int>>& graph, vector<vector<int>>& dist, vector<vector<int>>& next) {
    int n = graph.size();
    dist = graph; // Sao chép ma trận trọng số ban đầu
    next.resize(n, vector<int>(n, -1));

    // Khởi tạo đường đi
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] != oo && i != j) {
                next[i][j] = j;
            }
        }
    }

    // Thuật toán Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != oo && dist[k][j] != oo && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

// Hàm in ma trận khoảng cách
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            if (value == oo)
                cout << "oo ";
            else
                cout << value << " ";
        }
        cout << endl;
    }
}

// Hàm in đường đi từ i đến j
void printPath(int i, int j, const vector<vector<int>>& next) {
    if (next[i][j] == -1) {
        cout << "Khong co duong di tu " << i + 1 << " toi " << j + 1 << endl;
        return;
    }
    cout << "Duong di tu " << i + 1 << " toi " << j + 1 << ": ";
    while (i != j) {
        cout << i + 1 << " ";
        i = next[i][j];
    }
    cout << j + 1 << endl;
}

int main() {
    vector<vector<int>> graph;
    vector<vector<int>> dist, next;
    int n;
    int choice;

    // Yêu cầu người dùng chọn loại đồ thị
    cout << "Chon loai do thi:\n";
    cout << "1. Co huong\n";
    cout << "2. Vo huong\n";
    cout << "Nhap lua chon cua ban (1/2): ";
    cin >> choice;

    // Đọc đồ thị từ file
    readGraphFromFile("input.txt", graph, n);

    // Xử lý đồ thị không có hướng
    if (choice == 2) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (graph[i][j] != oo || graph[j][i] != oo) {
                    // Lấy trọng số nhỏ hơn nếu có cả 2 hướng
                    int weight = min(graph[i][j], graph[j][i]);
                    graph[i][j] = weight;
                    graph[j][i] = weight; // Đặt trọng số như nhau
                }
            }
        }
    }

    // Chạy thuật toán Floyd-Warshall
    floydWarshall(graph, dist, next);

    // In kết quả
    cout << "Ma tran khoang cach ngan nhat:\n";
    printMatrix(dist);

    cout << "\nCac duong di ngan nhat:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                printPath(i, j, next);
            }
        }
    }

    return 0;
}
