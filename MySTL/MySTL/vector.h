#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <initializer_list>

template <typename T> class vector {
public:
    vector();
    vector(const std::initializer_list<T>& list);
    vector(const vector<T>& rhs);
    ~vector();
    void push_back(const T& val);
    void pop_back();
    T& back();
    bool empty() const;
    size_t size() const;
    void clear();
    
    T& operator[](size_t index);
    bool operator==(const vector<T>& rhs) const;
    vector<T>& operator=(const vector<T>& rhs);

private:
    T* _container;
    size_t _size;
    size_t _capacity;
    void resize();
};

#endif // VECTOR_H
