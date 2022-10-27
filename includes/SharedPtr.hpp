#ifndef SHAREDPTR_HPP
# define SHAREDPTR_HPP

# include "Exceptions.hpp"
# include <cstddef>
# include <memory>

template <typename T>
struct counting_reference
{
    T*      value;
    size_t  count;
};

template <typename T>
class SharedPtr
{
    private:
        counting_reference<T>* _ref;

    public:
        SharedPtr(void) : _ref(NULL) {}

        SharedPtr(T* value) : _ref(NULL)
        {
            if (value == NULL)
                return ;
            _ref = new counting_reference<T>();
            _ref->value = value;
            _ref->count = 1;
        }

        SharedPtr(const SharedPtr& other) : _ref(other._ref)
        {
            if (_ref != NULL)
                ++_ref->count;
        }

        ~SharedPtr()
        {
            if (_ref != NULL && --_ref->count == 0)
            {
                delete _ref->value;
                delete _ref;
            }
        }

        SharedPtr& operator=(const SharedPtr& other)
        {
            if (_ref == other._ref)
                return ;

            if (_ref != NULL && --_ref->count == 0)
            {
                delete _ref->value;
                delete _ref;
            }

            _ref = other._ref;

            if (_ref != NULL)
                ++_ref->count;
        }

        const T* operator->() const
        {
            if (_ref == NULL)
                throw IllegalAccessException("The pointer has a invalid value!");
            return _ref->value;
        }

        T* operator->()
        {
            if (_ref == NULL)
                throw IllegalAccessException("The pointer has a invalid value!");
            return _ref->value;
        }

        const T& operator*() const
        {
            if (_ref == NULL)
                throw IllegalAccessException("The pointer has a invalid value!");
            return *_ref->value;
        }

        T& operator*()
        {
            if (_ref == NULL)
                throw IllegalAccessException("The pointer has a invalid value!");
            return *_ref->value;
        }
};

#endif
