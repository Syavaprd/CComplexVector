#include <bits/stdc++.h>
#include <omp.h>

using namespace std;
using namespace std::chrono; 


class CFabricData;
class CFabricData0;
class CFabricData1;

time_t t1, t2;

class CComplexVector
{
public:
    CComplexVector() {
        sz = 0;
        arr.resize(0);
    }

    CComplexVector(const vector <pair <int, int> > & mas) {
        sz = mas.size();
        arr.resize(sz);
        for (size_t i = 0; i < sz; ++i) {
            arr[i] = mas[i];
        }
    }

    CComplexVector(const CComplexVector& obj) {
        sz = obj.sz;
        arr.resize(sz);
        for (size_t i = 0; i < sz; ++i) {
            arr[i] = obj.arr[i];
        }
    }

    CComplexVector(int sz_, pair <int, int> comp) {
        sz = sz_;
        arr.resize(sz);
        for (size_t i = 0; i < sz; ++i) {
            arr[i] = comp;
        }
    }

    virtual ~CComplexVector() {
        arr.clear();
    }

    static CComplexVector* create (int Type, vector <pair <int, int> > vec, string Filename_, CFabricData** f);

    CComplexVector& operator=( const CComplexVector & obj) {
        if (this == &obj) {
            return *this;
        }
        sz = obj.sz;
        arr.resize(sz);
        for (size_t i = 0; i < sz; ++i)
            arr[i] = obj.arr[i];
        return *this;
    }

    friend ostream & operator << (ostream &out, const CComplexVector & obj) {
        out << obj.sz << endl;
        for (size_t i = 0; i < obj.sz; ++i) {
            out << obj.arr[i].first << ' ' << obj.arr[i].second << endl;
        }
        return out;
    }

    virtual void output (string Filename_) = 0;
    virtual string get_name() = 0;

protected:
    vector <pair <int, int> > arr;
    int sz;
};

class CComplexVector0:public CComplexVector {
public:
    CComplexVector0(const vector <pair <int, int> >&x, string Filename_) : CComplexVector(x), Filename(Filename_) {}
    CComplexVector0(string Filename_) : CComplexVector(), Filename(Filename_) {}
    CComplexVector0(const CComplexVector0& obj) : CComplexVector(obj.arr),  Filename{obj.Filename} {}
    CComplexVector0(int sz_, pair <int, int> comp, string Filename_) : CComplexVector(sz_, comp), Filename(Filename_) {}

    CComplexVector0 operator- (const CComplexVector0 &obj) {
        int new_sz = max(obj.sz, sz);
        vector <pair <int, int> > vec(new_sz);
        for (size_t i = 0; i < new_sz; ++i) {
            if (obj.sz > i && sz > i) {
                vec[i].first = arr[i].first - obj.arr[i].first;
                vec[i].second = arr[i].second - obj.arr[i].second;
            } else if (obj.sz > i) {
                vec[i].first = -obj.arr[i].first;
                vec[i].second = -obj.arr[i].second;
            } else {
                vec[i].first = arr[i].first;
                vec[i].second = arr[i].second;
            }
        }
        CComplexVector0 res(vec, this->Filename);
        return res;
    }

    CComplexVector0 operator+ (const CComplexVector0 &obj) {
        int new_sz = max(obj.sz, sz);
        vector <pair <int, int> > vec(new_sz);
        for (size_t i = 0; i < new_sz; ++i) {
            if (obj.sz > i && sz > i) {
                vec[i].first = obj.arr[i].first + arr[i].first;
                vec[i].second = obj.arr[i].second + arr[i].second;
            } else if (obj.sz > i) {
                vec[i].first = obj.arr[i].first;
                vec[i].second = obj.arr[i].second;
            } else {
                vec[i].first = arr[i].first;
                vec[i].second = arr[i].second;
            }
        }
        CComplexVector0 res(vec, this->Filename);
        return res;
    }

    CComplexVector0& operator+= (const CComplexVector0 &obj) {
        *this = *this + obj;
        return *this;
    }

    CComplexVector0& operator-= (const CComplexVector0 &obj) {
        *this = *this - obj;
        return *this;
    }

    CComplexVector0 operator* (const CComplexVector0 &obj) {
        int new_sz = max(obj.sz, sz);
        vector <pair <int, int> > vec(new_sz);
        {
        #pragma omp parallel for
        for (size_t i = 0; i < min(obj.sz, sz); ++i) {
            pair <int, int> tmp = obj.arr[i];
            vec[i].first = arr[i].first * tmp.first - arr[i].second * tmp.second;
            vec[i].second = arr[i].first * tmp.second + arr[i].second * tmp.first;
        }
        }
        for (size_t i = min(obj.sz, sz); i < max(obj.sz, sz); ++i)
            vec[i] = {0, 0};
        CComplexVector0 res(vec, this->Filename);
        return res;
    }

    CComplexVector0& operator*= (const CComplexVector0 &obj) {
        *this = *this * obj;
        return *this;
    }

    virtual string get_name() {
        return this->Filename;
    }

    virtual void output (string Filename_) {
        ofstream out;
        out.open(Filename_.c_str(), ofstream::out | ofstream::app);
        out << sz << ' ';
        for (size_t i = 0; i < sz; ++i) {
            out << arr[i].first << ' ' << arr[i].second << ' ';
        }
        out.close();
    }

private:
    string Filename;
};


class CComplexVector1:public CComplexVector {
public:
    CComplexVector1(const vector <pair <int, int> >&x, string Filename_) : CComplexVector(x), Filename(Filename_) {}
    CComplexVector1(string Filename_) : CComplexVector(), Filename(Filename_) {}
    CComplexVector1(const CComplexVector1& obj, string Filename_) : CComplexVector(obj), Filename(Filename_) {}
    CComplexVector1(int sz_, pair <int, int> comp, string Filename_) : CComplexVector(sz_, comp), Filename(Filename_) {}

    CComplexVector1 operator- (const CComplexVector1 &obj) {
        int new_sz = max(obj.sz, sz);
        vector <pair <int, int> > vec(new_sz);
        for (size_t i = 0; i < new_sz; ++i) {
            if (obj.sz > i && sz > i) {
                vec[i].first = arr[i].first - obj.arr[i].first;
                vec[i].second = arr[i].second - obj.arr[i].second;
            } else if (obj.sz > i) {
                vec[i].first = -obj.arr[i].first;
                vec[i].second = -obj.arr[i].second;
            } else {
                vec[i].first = arr[i].first;
                vec[i].second = arr[i].second;
            }
        }
        CComplexVector1 res(vec, this->Filename);
        return res;
    }

    CComplexVector1 operator+ (const CComplexVector1 &obj) {
        int new_sz = max(obj.sz, sz);
        vector <pair <int, int> > vec(new_sz);
        for (size_t i = 0; i < new_sz; ++i) {
            if (obj.sz > i && sz > i) {
                vec[i].first = obj.arr[i].first + arr[i].first;
                vec[i].second = obj.arr[i].second + arr[i].second;
            } else if (obj.sz > i) {
                vec[i].first = obj.arr[i].first;
                vec[i].second = obj.arr[i].second;
            } else {
                vec[i].first = arr[i].first;
                vec[i].second = arr[i].second;
            }
        }
        CComplexVector1 res(vec, this->Filename);
        return res;
    }

    CComplexVector1& operator+= (const CComplexVector1 &obj) {
        *this = *this + obj;
        return *this;
    }

    CComplexVector1& operator-= (const CComplexVector1 &obj) {
        *this = *this - obj;
        return *this;
    }

    CComplexVector1 operator* (const CComplexVector1 &obj) {
        int new_sz = max(obj.sz, sz);
        vector <pair <int, int> > vec(new_sz);
        for (size_t i = 0; i < min(obj.sz, sz); ++i) {
            pair <int, int> tmp = obj.arr[i];
            vec[i].first = arr[i].first * tmp.first - arr[i].second * tmp.second;
            vec[i].second = arr[i].first * tmp.second + arr[i].second * tmp.first;
        }
        for (size_t i = min(obj.sz, sz); i < max(obj.sz, sz); ++i)
            vec[i] = {0, 0};
        CComplexVector1 res(vec, this->Filename);
        return res;
    }

    CComplexVector1& operator*= (const CComplexVector1 &obj) {
        *this = *this * obj;
        return *this;
    }

    virtual string get_name() {
        return this->Filename;
    }

    virtual void output(string Filename_) {
        ofstream out;
        out.open(Filename_.c_str(), ofstream::app);
        out << sz << endl;
        for (size_t i = 0; i < sz; ++i) {
            out << arr[i].first << ' ' << arr[i].second << endl;
        }
        out.close();
    }
private:
    string Filename;
};

class CFabricData {
public:
    virtual CComplexVector* create(vector <pair<int, int> > vec, string Filename_) = 0;
};

class CFabricData0:public CFabricData {
public:
    virtual CComplexVector0* create(vector <pair <int, int> > vec, string Filename_) {
        return new CComplexVector0(vec, Filename_);
    }
};

class CFabricData1:public CFabricData {
public:
    virtual CComplexVector1* create(vector <pair <int, int> > vec, string Filename_) {
        return new CComplexVector1(vec, Filename_);
    }
};

CComplexVector* CComplexVector::create(int Type, vector <pair <int, int> > vec, string Filename_, CFabricData** f) {
        CComplexVector* t = f[Type]->create(vec, Filename_);
        return t;
}

void test_functions() {
    FILE* f;
    int Type;
    cout << "Do you want to read commands from test.txt (0) or from console (1)?\n";
    cin >> Type;
    if (!Type) {
        f = fopen("test.txt", "r");
    } else {
        f = stdin;
    }
    vector <CComplexVector1*> vector1;
    vector <CComplexVector0*> vector0;
    while(true) {
        int Type;
        cout << "Input 0 - to use CComplexVector0\n Input 1 - to use CComplexVector1\n";
        if (fscanf(f, "%d", &Type) == 1 && Type == 0 || Type == 1) {
            cout << "Enter the command:\n1) Create vector\n2) Add vector with # i to vector with # j\n"
             << "3) Subtract vector with # i from vector with number j\n4) Scalar multiplication of vector with # i to vector with # j\n"
             << "5) Print vector with # i\n6) Exit\n";
            int q;
            if (fscanf(f, "%d", &q) == 1 && q > 0 && q < 7) {
                if (q == 1 && Type == 0) {
                    int dim;
                    cout << "Input dimension\n";
                    fscanf(f, "%d", &dim);
                    vector <pair <int, int> > vec;
                    cout << "Input complex numbers\n";
                    for (size_t i = 0; i < dim; ++i) {
                        int x, y;
                        fscanf(f, "%d%d", &x, &y);
                        vec.push_back({x, y});
                    }
                    vector0.push_back(new CComplexVector0(vec, "x"));
                } else if (q == 1 && Type == 1) {
                    int dim;
                    cout << "Input dimension\n";
                    fscanf(f, "%d", &dim);
                    vector <pair <int, int> > vec;
                    cout << "Input complex numbers\n";
                    for (size_t i = 0; i < dim; ++i) {
                        int x, y;
                        fscanf(f, "%d%d", &x, &y);
                        vec.push_back({x, y});
                    }
                    vector1.push_back(new CComplexVector1(vec, "x"));
                } else if (q == 2 && Type == 0) {
                    int i, j;
                    cout << "Input i and j\n";
                    fscanf(f, "%d%d", &i, &j);
                    if (i >= 0 && i < vector0.size() && j >= 0 && j < vector0.size()) {
                        CComplexVector0 res = (*vector0[i] + *vector0[j]);
                        cout << "Answer\n" << res;
                        //delete &res;
                    } else {
                        cout << "Incorrect numbers\n";
                        continue;
                    }
                } else if (q == 2 && Type == 1) {
                    int i, j;
                    cout << "Input i and j\n";
                    fscanf(f, "%d%d", &i, &j);
                    if (i >= 0 && i < vector1.size() && j >= 0 && j < vector1.size()) {
                        CComplexVector1 res = (*vector1[i] + *vector1[j]);
                        cout << "Answer\n" << res;
                        //delete &res;
                    } else {
                        cout << "Incorrect numbers\n";
                        continue;
                    }
                } else if (q == 3 && Type == 0) {
                    int i, j;
                    cout << "Input i and j\n";
                    fscanf(f, "%d%d", &i, &j);
                    if (i >= 0 && i < vector0.size() && j >= 0 && j < vector0.size()) {
                        CComplexVector0 res = (*vector0[i] - *vector0[j]);
                        cout << "Answer\n" << res;
                        //delete &res;
                    } else {
                        cout << "Incorrect numbers\n";
                        continue;
                    }
                } else if (q == 3 && Type == 1) {
                    int i, j;
                    cout << "Input i and j\n";
                    fscanf(f, "%d%d", &i, &j);
                    if (i >= 0 && i < vector1.size() && j >= 0 && j < vector1.size()) {
                        CComplexVector1 res = *vector1[i] - *vector1[j];
                        cout << "Answer\n" << res;
                        //delete &res;
                    } else {
                        cout << "Incorrect numbers\n";
                        continue;
                    }
                } else if (q == 4 && Type == 0) {
                    int i, j;
                    cout << "Input i and j\n";
                    fscanf(f, "%d%d", &i, &j);
                    if (i >= 0 && i < vector0.size() && j >= 0 && j < vector0.size()) {
                        CComplexVector0 res = (*vector0[i]) * (*vector0[j]);
                        cout << "Answer\n" << res;
                        //delete &res;
                    } else {
                        cout << "Incorrect numbers\n";
                        continue;
                    }
                } else if (q == 4 && Type == 1) {
                    int i, j;
                    cout << "Input i and j\n";
                    fscanf(f, "%d%d", &i, &j);
                    if (i >= 0 && i < vector1.size() && j >= 0 && j < vector1.size()) {
                        CComplexVector1 res = (*vector1[i]) * (*vector1[j]);
                        cout << "Answer\n" << res;
                        //delete &res;
                    } else {
                        cout << "Incorrect numbers\n";
                        continue;
                    }
                } else if (q == 5 && Type == 0) {
                    int i;
                    cout << "Input i\n";
                    fscanf(f, "%d", &i);
                    if (i >= 0 && i < vector0.size()) {
                        cout << *vector0[i];
                    } else {
                        cout << "Incorrect numbers\n";
                    }
                } else if (q == 5 && Type == 1) {
                    int i;
                    cout << "Input i\n";
                    fscanf(f, "%d", &i);
                    if (i >= 0 && i < vector1.size()) {
                        cout << *vector1[i];
                    } else {
                        cout << "Incorrect numbers\n";
                    }
                } else if (q == 6) {
                    for (size_t i = 0; i < vector0.size(); ++i)
                        delete vector0[i];
                    for (size_t i = 0; i < vector1.size(); ++i)
                        delete vector1[i];
                    cout << "Functions test done!\n";
                    return ;
                }
            } else {
                cout << "Wrong command\n";
                continue;
            }
        }
        else {
            cout << "Wrong type\n";
            continue;
        }
    }
    return;
}

void test_output() {
    cout << "Output test started\n";
    CComplexVector** t;
    ifstream in;
    in.open("files.txt");
    int n;
    in >> n;
    t = new CComplexVector*[n];
    CFabricData* f[2] = {new CFabricData0(), new CFabricData1()};
    for (size_t i = 0; i < n; ++i) {
        int type, sz;
        string out_file;
        in >> type >> out_file >> sz;
        vector <pair <int, int> > tmp(sz);
        for (size_t j = 0; j < sz; ++j) {
            int x, y;
            in >> x >> y;
            tmp[j].first = x;
            tmp[j].second = y;
        }
        t[i] = CComplexVector::create(type, tmp, out_file, f);
    }
    for (size_t i = 0; i < n; ++i) {
        t[i]->output(t[i]->get_name());
    }
    for (size_t i = 0; i < n; ++i)
        delete t[i];
    delete [] t;
    t = NULL;
    for (size_t i = 0; i < 2; ++i) {
        delete f[i];
        f[i] = NULL;
    }
    cout << "Output test ended\n";
    return;
}

void test_openmp() {
    cout << "Input size of a vector\n";
    int N;
    cin >> N;
    cout << "multiplication without OpenMp\n";
    {
        CComplexVector1 a1(N, {1, 1}, "x"), b1(N, {1, 1}, "x");
        auto start = high_resolution_clock::now();
        a1 * b1;
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
    }
    cout << "multiplication with OpenMp\n";
    {
        omp_set_dynamic(2);
        omp_set_num_threads(8);
        CComplexVector0 a0(N, {1, 1}, "x"), b0(N, {1, 1}, "x");
        auto start = high_resolution_clock::now();
        a0 * b0;
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
    }
    return ;
}
void test() {
    while(1) {
        int Type;
        cout << "Input 1, if you want to test class functions.\n Input 2, if you want to test class CFabricData and virtual output function.\n"
            << "Input 3, if you want to test OpenMp\n Input 0 to exit";
        cin >> Type;
        if (Type == 0) {
            exit(0);
        } else if (Type == 1) {
            test_functions();
        } else if (Type == 2) {
            test_output();
        } else if (Type == 3) {
            test_openmp();
        } else continue;
    }
    return ;
}

int main()
{
    test();
    return 0;
}