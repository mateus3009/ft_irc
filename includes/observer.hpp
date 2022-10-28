#ifndef observer_HPP
# define observer_HPP

# include <set>
# include <iostream>

template <typename T>
struct observer
{
    virtual void handle(T& value) = 0;
};

template <typename T>
class publisher
{
    private:
        std::set<observer<T>*>  _subscribers;

    public:
        publisher(void);

        publisher(const publisher<T>& other);

        ~publisher();

        publisher<T>& operator=(const publisher<T>& other);

        void subscribe(observer<T>* observer);

        void unsubscribe(observer<T>* observer);

        void notify(T value);

};

template <typename T>
publisher<T>::publisher(void) : _subscribers() {}

template <typename T>
publisher<T>::publisher(const publisher& other) : _subscribers(other._subscribers) {}

template <typename T>
publisher<T>::~publisher() {}

template <typename T>
publisher<T>& publisher<T>::operator=(const publisher<T>& other)
{
    _subscribers = other._subscribers;
    return _subscribers;
}

template <typename T>
void publisher<T>::subscribe(observer<T>* observer)
{
    _subscribers.insert(observer);
}

template <typename T>
void publisher<T>::unsubscribe(observer<T>* observer)
{
    _subscribers.erase(observer);
}

template <typename T>
void publisher<T>::notify(T value)
{
    for (typename std::set<observer<T>*>::iterator it = _subscribers.begin(); it != _subscribers.end(); ++it)
        (*it)->handle(value);
}

#endif
