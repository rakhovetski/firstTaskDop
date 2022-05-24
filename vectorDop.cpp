#include <iostream>

class Vector {
private:
    size_t sz = 0;
    size_t cap = 0;
    int* arr = nullptr;
public:
    Vector();
    Vector(size_t);
    Vector(size_t, int);
    Vector(const Vector&);
    Vector(std::initializer_list<int>);
    Vector(Vector&&);
    ~Vector();

    size_t size() const { return sz; }
    size_t capacity()const { return cap; }
    void push_back(int);
    void pop_back();
    void reserve(int);
    void resize(int);

    int& operator[](int i) { return arr[i]; }
    const int& operator[](int i) const { return arr[i]; }
    Vector& operator=(const Vector&);
    Vector& operator+=(const Vector&);
    Vector operator+(const Vector&);

    bool operator==(const Vector&) const;
    bool operator!=(const Vector&) const;

    friend std::ostream& operator<<(std::ostream&, const Vector&);
    friend std::istream& operator>>(std::istream&, Vector&);

};

Vector::Vector() {}

Vector::Vector(size_t n) : sz(n), cap(n), arr(new int[n]) {
    for (size_t i = 0; i < cap; ++i) {
        arr[i] = 0;
    }
}

Vector::Vector(size_t n, int x) : Vector(n) {
    for (size_t i = 0; i < cap; ++i) {
        arr[i] = x;
    }
}

Vector::Vector(const Vector& v) : Vector(v.cap) {
    sz = v.sz;
    for (size_t i = 0; i < sz; ++i) {
        arr[i] = v.arr[i];
    }
}

Vector::Vector(std::initializer_list<int> list) : sz(list.size()), cap(sz), arr(new int[cap]) {
    std::copy(list.begin(), list.end(), arr);
}

Vector::Vector(Vector&& v) : sz(v.sz), cap(v.cap), arr(v.arr) {
    v.arr = nullptr;
}

Vector::~Vector() {
    delete[] arr;
    arr = nullptr;
}

void Vector::reserve(int n) {
    cap = n;
    int* newarr = new int[n];
    for (size_t i = 0; i < sz; ++i) {
        newarr[i] = arr[i];
    }
    delete[] arr;
    arr = newarr;
}

void Vector::resize(int n) {
    sz = n;
    cap = n;
    int* newarr = new int[n];
    for (size_t i = 0; i < n; ++i) {
        newarr[i] = arr[i];
    }
    delete[] arr;
    arr = newarr;
}

void Vector::push_back(int x) {
    if (sz == cap) reserve(2 * cap);
    arr[sz] = x;
    ++sz;
}

void Vector::pop_back() {
    --sz;
}

Vector& Vector::operator=(const Vector& v) {
    sz = v.sz;
    cap = v.cap;
    delete[] arr;
    arr = new int[cap];
    for (size_t i = 0; i < sz; ++i) {
        arr[i] = v.arr[i];
    }
    return *this;
}

Vector& Vector::operator+=(const Vector& v) {
    cap += v.cap;
    int* newarr = new int[cap];
    for (size_t i = 0; i < sz; ++i) {
        newarr[i] = arr[i];
    }
    for (size_t i = sz; i < sz + v.sz; ++i) {
        newarr[i] = v.arr[i - sz];
    }
    sz += v.sz;
    return *this;
}

Vector Vector::operator+(const Vector& v) {
    Vector copy = *this;
    copy += v;
    return copy;
}

bool Vector::operator==(const Vector& v) const {
    if (sz != v.sz || cap != v.cap) return false;
    for (size_t i = 0; i < sz; ++i) {
        if (arr[i] != v.arr[i]) return false;
    }
    return true;
}

bool Vector::operator!=(const Vector& v) const {
    return !(*this == v);
}

std::ostream& operator<<(std::ostream& out, const Vector& v) {
    for (size_t i = 0; i < v.sz; ++i) {
        out << v.arr[i] << " ";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Vector& v) {
    for (size_t i = 0; i < v.cap; ++i) {
        in >> v.arr[i];
    }
    return in;
}

int main()
{
    Vector v = { 1, -25, 2 };
    Vector k = { 7, 8, 9 };
    Vector l = k += v;
    v.push_back(-5);
    std::cout << v << v.size() << " " << v.capacity();
    v.pop_back();
    v.pop_back();
    std::cout << l;
}