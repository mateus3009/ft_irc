#ifndef SHAREDPTR_HPP
# define SHAREDPTR_HPP

# include "exceptions.hpp"
# include <cstddef>
# include <memory>

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
                throw illegal_access_exception("The pointer has a invalid value!");
            return _ref->value;
        }

        T* operator->()
        {
            if (_ref == NULL)
                throw illegal_access_exception("The pointer has a invalid value!");
            return _ref->value;
        }

        const T& operator*() const
        {
            if (_ref == NULL)
                throw illegal_access_exception("The pointer has a invalid value!");
            return *_ref->value;
        }

        T& operator*()
        {
            if (_ref == NULL)
                throw illegal_access_exception("The pointer has a invalid value!");
            return *_ref->value;
        }
};

#endif
