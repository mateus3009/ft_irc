#ifndef SHAREDPTR_HPP
# define SHAREDPTR_HPP

# include <cstddef>
# include <stdexcept>

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

    public:
        shared_ptr(void) : _ref(NULL) {}

        shared_ptr(T* value) : _ref(NULL)
        {
            if (value == NULL)
                return ;
            _ref = new counting_reference<T>();
            _ref->value = value;
            _ref->count = 1;
        }

        shared_ptr(const shared_ptr& other) : _ref(other._ref)
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

        shared_ptr& operator=(const shared_ptr& other)
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
                throw shared_ptr::IllegalAccessException("The pointer has a invalid value!");
            return _ref->value;
        }

        T* operator->()
        {
            if (_ref == NULL)
                throw shared_ptr::IllegalAccessException("The pointer has a invalid value!");
            return _ref->value;
        }

        const T& operator*() const
        {
            if (_ref == NULL)
                throw shared_ptr::IllegalAccessException("The pointer has a invalid value!");
            return *_ref->value;
        }

        T& operator*()
        {
            if (_ref == NULL)
                throw shared_ptr::IllegalAccessException("The pointer has a invalid value!");
            return *_ref->value;
        }

        struct IllegalAccessException : public std::runtime_error
        {
            IllegalAccessException(const char* str) : std::runtime_error(str) {}
        };

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
    return *left == *right;
};

template <typename T, typename R>
bool operator<(shared_ptr<T> left, T right)
{
    return *left == right;
};

#endif
