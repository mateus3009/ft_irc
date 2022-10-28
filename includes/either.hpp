#ifndef EITHER_HPP
# define EITHER_HPP

# include "exceptions.hpp"

template <typename L, typename R>
class either
{
    public:
        virtual ~either() {};

        virtual L get_left(void) const = 0;

        virtual bool is_left(void) const = 0;

        virtual R get_right(void) const = 0;

        virtual bool is_right(void) const = 0;

};

template <typename L, typename R>
class left : public either<L, R>
{
    private:
        L _left;

    public:
        left(void) : _left() {}

        left(const L& left) : _left(left) {}

        left(const left& other) : _left(other._left) {}

        ~left() {}

        left& operator=(const left& other)
        {
            _left = other._left;
            return *this;
        }

        L get_left(void) const { return _left; }

        bool is_left(void) const { return true; }

        R get_right(void) const { throw illegal_access_exception("The right side is not available!"); }

        bool is_right(void) const { return false; }
};

template <typename L, typename R>
class right : public either<L, R>
{
    private:
        R _right;

    public:
        right(void) : _right() {}

        right(const R& right) : _right(right) {}

        right(const right& other) : _right(other._right) {}

        ~right() {}

        right& operator=(const right& other)
        {
            _right = other._right;
            return *this;
        }

        L get_left(void) const { throw illegal_access_exception("The left side is not available!"); }

        bool is_left(void) const { return false; }

        R get_right(void) const { return _right; }

        bool is_right(void) const { return true; }
};

#endif
