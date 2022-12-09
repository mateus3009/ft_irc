#ifndef SHARED_PTR_HPP
# define SHARED_PTR_HPP

# include "Error.hpp"

template <typename T>
struct counting_reference
{
    T*      value;
    size_t  count;
};

template <typename T>
class shared_ptr
{
    private:
        counting_reference<T>* _ref;

        shared_ptr(counting_reference<T>* ref) : _ref(ref) {}

    public:
        static shared_ptr<T> make_shared(T* value)
        {
            if (value == NULL)
                throw Error("The value provided is NULL");
            counting_reference<T>* ref = new counting_reference<T>();
            ref->value = value;
            ref->count = 1;
            return shared_ptr<T>(ref);
        }

        shared_ptr(void) : _ref(NULL) {}

        shared_ptr(const shared_ptr<T>& other) : _ref(other._ref)
        {
            if (_ref != NULL)
                ++_ref->count;
        }

        ~shared_ptr()
        {
            if (_ref != NULL && --_ref->count == 0)
            {
                delete _ref->value;
                delete _ref;
            }
        }

        shared_ptr<T>& operator=(const shared_ptr<T>& other)
        {
            if (_ref == other._ref)
                return *this;

            if (_ref != NULL && --_ref->count == 0)
            {
                delete _ref->value;
                delete _ref;
            }

            _ref = other._ref;

            if (_ref != NULL)
                ++_ref->count;

            return *this;
        }

        const T* operator->() const
        {
            if (_ref == NULL)
                throw Error("The pointer has a invalid value!");
            return _ref->value;
        }

        T* operator->()
        {
            if (_ref == NULL)
                throw Error("The pointer has a invalid value!");
            return _ref->value;
        }

        const T& operator*() const
        {
            if (_ref == NULL)
                throw Error("The pointer has a invalid value!");
            return *_ref->value;
        }

        T& operator*()
        {
            if (_ref == NULL)
                throw Error("The pointer has a invalid value!");
            return *_ref->value;
        }

};

template <typename T>
bool operator==(shared_ptr<T> left, shared_ptr<T> right)
{
    return *left == *right;
};

template <typename T, typename R>
bool operator==(shared_ptr<T> left, R right)
{
    return *left == right;
};

template <typename T>
bool operator<(shared_ptr<T> left, shared_ptr<T> right)
{
    return *left < *right;
};

template <typename T, typename R>
bool operator<(shared_ptr<T> left, T right)
{
    return *left < right;
};

#endif
