#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
#include <iostream>
#endif

template <typename T>
class List
{
#ifdef _DEBUG
public:
#else
protected:
#endif
    T *buffer_head, *buffer_tail;

public:
    // members
    unsigned reallocation_step;

    // meta
    List(unsigned reallocation_step = 10);
    ~List();

    // methods
    T& operator [](unsigned index);
    const T& operator [](unsigned index) const;

    void operator+(const T& value);
    void operator+(const List<T>& other);

    void operator+=(const T& value);
    void operator+=(const List<T>& other);

    T& at(unsigned index);
    const T& at(unsigned index) const;

    unsigned size() const;

    void append(const T& value);

    void extend(const List<T>& other);
};

/*
 *  METHOD DEFINITIONS
*/

template <typename T>
List<T>::List(unsigned reallocation_step)
    : reallocation_step(reallocation_step)
{
    this->buffer_head = (T*)::malloc(this->reallocation_step * sizeof(T));
    this->buffer_tail = this->buffer_head;
}

template <typename T>
List<T>::~List()
{
    ::free(this->buffer_head);
}

template <typename T>
T& List<T>::operator[](unsigned index)
{
    return this->at(index);
}

template <typename T>
const T& List<T>::operator[](unsigned index) const
{
    return this->at(index);
}

template <typename T>
void List<T>::operator+(const T& value)
{
    this->append(value);
}

template <typename T>
void List<T>::operator+(const List<T>& other)
{
    this->extend(other);
}

template <typename T>
void List<T>::operator+=(const T& value)
{
    this->append(value);
}

template <typename T>
void List<T>::operator+=(const List<T>& other)
{
    this->append(other);
}

template <typename T>
T& List<T>::at(unsigned index)
{
    if (index > this->size())
        throw std::out_of_range("index is out of range of list");

    return *(this->buffer_head + index);
}

template <typename T>
const T& List<T>::at(unsigned index) const
{
    if (index > this->size())
        throw std::out_of_range("index is out of range of list");

    return *(this->buffer_head + index);
}

template <typename T>
unsigned List<T>::size() const
{
    return this->buffer_tail - this->buffer_head;
}

template <typename T>
void List<T>::append(const T& value)
{
    if (this->size() >= this->reallocation_step)
    {
        T* new_buffer_head = (T*)::malloc((this->size() + 1 + this->reallocation_step) * sizeof(T));

        ::memcpy(new_buffer_head, this->buffer_head, this->size() * sizeof(T));
        
        ::free(this->buffer_head);

        this->buffer_tail = new_buffer_head + this->size();
        this->buffer_head = new_buffer_head;

#ifdef _DEBUG
        std::cout << "reallocating" << std::endl;
#endif
    }

    *(this->buffer_tail++) = value;
}

template <typename T>
void List<T>::extend(const List<T>& other)
{
    if (this->size() + other.size() <= this->reallocation_step) // dont need to reallocate
    {
        ::memcpy(this->buffer_tail, other.buffer_head, other.size());

        this->buffer_tail += other.size();
    }
    else // need to reallocate
    {
        unsigned combined_size = this->size() + other.size();

        T* new_buffer_head = (T*)::malloc((combined_size + this->reallocation_step) * sizeof(T));

        ::memcpy(new_buffer_head, this, this->size() * sizeof(T));
        ::memcpy(new_buffer_head + this->size(), other.buffer_head, other.size() * sizeof(T));

        ::free(this->buffer_head);

        this->buffer_head = new_buffer_head;
        this->buffer_tail = this->buffer_head + combined_size;
    }
}
