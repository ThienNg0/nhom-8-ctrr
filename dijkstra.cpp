#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

const int oo = 9999999; // Đánh dấu là vô cực
typedef pair<int, int> ii;
int pre[1812];
vector<int> path[1812]; // Lưu đường đi tới đỉnh i
vector<ii> a[1812];
int n;

int d[1812];

// Hàm Dijkstra để tìm đường đi ngắn nhất
void dijkstra(int source) {
    priority_queue<ii, vector<ii>, greater<ii>> pq; // Hàng đợi ưu tiên, giá trị second bé nhất cho lên đầu
    for (int i = 1; i <= n; i++)
        d[i] = oo; // gán giá trị d[i] bằng vô cực
    d[source] = 0;
    pq.push(ii(0, source));
    
    while (pq.size()) {
        int u = pq.top().second; // Lấy giá trị second của phần tử đỉnh của pq
        int du = pq.top().first;
        pq.pop();
        
        if (du != d[u]) { // Điều kiện để bỏ qua pair mà giá trị d[u] được cập nhật từ lần lặp trước.
            continue;
        }
        
        for (int i = 0; i < a[u].size(); i++) { // Xét đỉnh kề đỉnh u
            int v = a[u][i].second;
            int uv = a[u][i].first;
            
            if (d[v] > du + uv) { // Nếu tổng của đỉnh đang xét + trọng số của cạnh nối 2 đỉnh u và v nhỏ hơn thì cập nhật d[v] mới
                pre[v] = u; // Đỉnh trước v là đỉnh u
                d[v] = du + uv; // Lấy giá trị nhỏ hơn
                pq.push(ii(d[v], v)); // Thêm pair vào pq
            }
        }
    }
}

// Hàm đọc dữ liệu từ tệp
void readFromFile(const string& filename) {
    ifstream input(filename);
    if (!input) {
        cerr << "Khong the mo file " << filename << endl;
        return;
    }
    
    input >> n; // Đọc số đỉnh
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int weight;
            input >> weight; // Đọc trọng số
            if (weight != 0 && weight != oo) {
                a[i].push_back(ii(weight, j)); // Thêm cạnh vào danh sách kề
            }
        }
    }
    input.close();
}

// Hàm nhập dữ liệu từ bàn phím
void readFromInput() {
    cout << "Nhap so dinh: ";
    cin >> n;
    cout << "Nhap ma tran trong so (0 neu khong co canh, " << oo << " neu la vo cuc):" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int weight;
            cin >> weight;
            if (weight != 0 && weight != oo) {
                a[i].push_back(ii(weight, j));
            }
        }
    }
}

int main() {
    int source, choice;

    cout << "Chon chuc nang: \n1. Doc tu file\n2. Nhap tu ban phim\n";
    cin >> choice;

    switch (choice) {
        case 1:
            readFromFile("data/input.txt"); 
            cout << "Nhap dinh nguon: ";
            cin >> source;
            break;
        case 2:
            readFromInput();
            cout << "Nhap dinh nguon: ";
            cin >> source;
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            return 0;
    }

    dijkstra(source); // Chạy thuật toán Dijkstra

    // In kết quả ra màn hình
    for (int i = 1; i <= n; i++) {
        if (i == source) continue;
        cout << "=== Dinh " << i << endl;
        if (d[i] == oo) {
            cout << "Khong co duong di tu nguon toi dinh nay \n";
            continue;
        }
        cout << "d(" << source << " -> " << i << ") = " << d[i] << endl;
        
        for (int tmp = i; tmp != source; tmp = pre[tmp]) {
            path[i].push_back(tmp);
        }
        path[i].push_back(source);
        reverse(path[i].begin(), path[i].end());
        
        cout << "Duong di: ";
        for (int j = 0; j < path[i].size(); j++) {
            if (j == path[i].size() - 1) {
                cout << path[i][j];
                break;
            } else {
                cout << path[i][j] << " -> ";
            }
        }
        cout << endl;
    }
    return 0;
}
