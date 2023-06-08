#ifndef _ROTTEN_SNAG_POUCH_H_
#define _ROTTEN_SNAG_POUCH_H_

#include <functional>

namespace pouch {
    using u64 = unsigned long long;
    using u32 = unsigned long;
    using i32 = signed long;
    using f32 = float;

    template<typename T>
    class RottenSnag {
        private:
            using ComparisonLambda = std::function<bool(const T&, const T&)>;

            struct Stick {
                T _value;
                i32 _height;
                Stick* _left;
                Stick* _right;
                
                Stick(const T& value);

                inline void _iternal_free() noexcept;
            };
            
            u64 _size;
            Stick* _root;
            const ComparisonLambda _lambda;
            const ComparisonLambda _equalLambda;
            
            inline i32 _iternal_height(Stick* stick) const noexcept;
            inline i32 _iternal_balance_factor(Stick* stick) const noexcept;
            inline void _iternal_update_height(Stick* stick) noexcept;
            
            inline Stick* _iternal_rotate_left(Stick* stick) noexcept;
            inline Stick* _iternal_rotate_right(Stick* stick) noexcept;
            
            inline Stick* _iternal_balance(Stick* stick) noexcept;
            inline Stick* _iternal_find_min(Stick* stick) const noexcept;
            inline Stick* _iternal_erase_min(Stick* stick) noexcept;
            
            inline Stick* _iternal_put(Stick* stick, const T& value) noexcept;
            inline Stick* _iternal_erase(Stick* stick, const T& value) noexcept;
            
        public:
            RottenSnag(const ComparisonLambda& lambda = [](const T& a, const T& b) { return a < b; }, const ComparisonLambda& equalLambda = [](const T& a, const T& b) { return a == b; });
            ~RottenSnag();

            inline T* get(const T& value) const noexcept;
            inline void put(const T& value) noexcept;
            inline void erase(const T& value) noexcept;

            inline u64 size() const;
    };
}

namespace pouch {
    using u64 = unsigned long long;
    using u32 = unsigned long;
    using i32 = signed long;
    using f32 = float;

    template<typename T>
    inline RottenSnag<T>::Stick::Stick(const T& value) : _value(value), _height(1), _left(nullptr), _right(nullptr) {}

    template<typename T>
    inline void RottenSnag<T>::Stick::_iternal_free() noexcept {
        if(_left != nullptr)
            delete _left;

        if(_right != nullptr)
            delete _right;
    }

    template<typename T>
    inline i32 RottenSnag<T>::_iternal_height(Stick* stick) const noexcept {
        return stick ? stick->_height : 0;
    }
    
    template<typename T>
    inline i32 RottenSnag<T>::_iternal_balance_factor(Stick* stick) const noexcept {
        return _iternal_height(stick->_right) - _iternal_height(stick->_left);
    }
    
    template<typename T>
    inline void RottenSnag<T>::_iternal_update_height(Stick* stick) noexcept {
        stick->_height = std::max(_iternal_height(stick->_left), _iternal_height(stick->_right)) + 1;
    }
    
    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::_iternal_rotate_left(Stick* stick) noexcept {
        Stick* right = stick->_right;
        Stick* rightLeft = right->_left;
        
        right->_left = stick;
        stick->_right = rightLeft;

        _iternal_update_height(stick);
        _iternal_update_height(right);

        return right;
    }
    
    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::_iternal_rotate_right(Stick* stick) noexcept {
        Stick* left = stick->_left;
        Stick* leftRight = left->_right;
        
        left->_right = stick;
        stick->_left = leftRight;

        _iternal_update_height(stick);
        _iternal_update_height(left);
        
        return left;
    }
    
    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::_iternal_balance(Stick* stick) noexcept {
        _iternal_update_height(stick);
        const i32 bf = _iternal_balance_factor(stick);

        if (bf == 2) {
            if (_iternal_balance_factor(stick->_right) < 0)
                stick->_right = _iternal_rotate_right(stick->_right);

            return _iternal_rotate_left(stick);
        } else if (bf == -2) {
            if (_iternal_balance_factor(stick->_left) > 0)
                stick->_left = _iternal_rotate_left(stick->_left);

            return _iternal_rotate_right(stick);
        }

        return stick;
    }
    
    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::_iternal_put(Stick* stick, const T& value) noexcept {
        if (stick == nullptr) {
            ++_size;
            return new Stick(value);
        }
            
        if (_lambda(value, stick->_value))
            stick->_left = _iternal_put(stick->_left, value);
        else
            stick->_right = _iternal_put(stick->_right, value);

        return _iternal_balance(stick);
    }
    
    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::_iternal_find_min(Stick* stick) const noexcept {
        return stick->_left ? _iternal_find_min(stick->_left) : stick;
    }

    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::_iternal_erase_min(Stick* stick) noexcept {
        if (!stick->_left) return stick->_right;

        stick->_left = _iternal_erase_min(stick->_left);
        
        return _iternal_balance(stick);
    }
    
    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::_iternal_erase(Stick* stick, const T& value) noexcept {
        if (!stick) return nullptr;

        if(_equalLambda(value, stick->_value)) {
            Stick* left = stick->_left;
            Stick* right = stick->_right;

            --_size;

            delete stick;

            if (!right) return left;

            Stick* min = _iternal_find_min(right);
            min->_right = _iternal_erase_min(right);
            min->_left = left;
        
            return _iternal_balance(min);
        } else if(_lambda(value, stick->_value))
            stick->_left = _iternal_erase(stick->_left, value);
        else
            stick->_right = _iternal_erase(stick->_right, value);

        return _iternal_balance(stick);
    }

    template<typename T>
    inline RottenSnag<T>::RottenSnag(const ComparisonLambda& lambda, const ComparisonLambda& equalLambda) 
        : _root(nullptr), _lambda(lambda), _equalLambda(equalLambda) {}

    template<typename T>
    inline RottenSnag<T>::~RottenSnag() {
        if(_root == nullptr) return;

        _root->_iternal_free();

        delete _root;
    }

    template<typename T>
    inline T* RottenSnag<T>::get(const T& value) const noexcept {
        Stick* currentStick = _root;
        
        while (currentStick != nullptr) {
            if (_equalLambda(value, currentStick->_value))
                return &currentStick->_value;
            else if (_lambda(value, currentStick->_value))
                currentStick = currentStick->_left;
            else
                currentStick = currentStick->_right;
        }

        return nullptr;
    }

    template<typename T>
    inline void RottenSnag<T>::put(const T& value) noexcept {
        _root = _iternal_put(_root, value);
    }

    template<typename T>
    inline void RottenSnag<T>::erase(const T& value) noexcept {
        _root = _iternal_erase(_root, value);
    }

    template<typename T>
    inline u64 RottenSnag<T>::size() const {
        return _size;
    }   
};

#endif
