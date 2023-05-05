#ifndef _ROTTEN_SNAG_POUCH_H_
#define _ROTTEN_SNAG_POUCH_H_

namespace pouch {
    using u64 = unsigned long long;
    using u32 = unsigned long;
    using i32 = signed long;
    using f32 = float;

    template<typename T>
    class RottenSnag {
        private:
            struct Stick {
                T _value;
                i32 _height;
                Stick* _left;
                Stick* _right;
                
                Stick(const T& value);
            };
            
            Stick* _root;
            
            inline i32 height(Stick* stick) const noexcept;
            inline i32 balance_factor(Stick* stick) const noexcept;
            inline void update_height(Stick* stick) noexcept;
            
            inline Stick* rotate_left(Stick* stick) noexcept;
            inline Stick* rotate_right(Stick* stick) noexcept;
            
            inline Stick* balance(Stick* stick) noexcept;
            inline Stick* find_min(Stick* stick) const noexcept;
            inline Stick* erase_min(Stick* stick) noexcept;
            
            inline Stick* put(Stick* stick, const T& value) noexcept;
            inline Stick* erase(Stick* stick, const T& value) noexcept;
            
        public:
            RottenSnag();

            inline Stick* get(const T& value) const noexcept;
            inline void put(const T& value) noexcept;
            inline void erase(const T& value) noexcept;
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
    inline i32 RottenSnag<T>::height(Stick* stick) const noexcept {
        return stick ? stick->_height : 0;
    }
    
    template<typename T>
    inline i32 RottenSnag<T>::balance_factor(Stick* stick) const noexcept {
        return height(stick->_right) - height(stick->_left);
    }
    
    template<typename T>
    inline void RottenSnag<T>::update_height(Stick* stick) noexcept {
        stick->_height = std::max(height(stick->_left), height(stick->_right)) + 1;
    }
    
    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::rotate_left(Stick* stick) noexcept {
        Stick* right = stick->_right;
        Stick* rightLeft = right->_left;
        right->_left = stick;
        stick->_right = rightLeft;
        update_height(stick);
        update_height(right);
        return right;
    }
    
    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::rotate_right(Stick* stick) noexcept {
        Stick* left = stick->_left;
        Stick* leftRight = left->_right;
        left->_right = stick;
        stick->_left = leftRight;
        update_height(stick);
        update_height(left);
        return left;
    }
    
    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::balance(Stick* stick) noexcept {
        update_height(stick);
        i32 bf = balance_factor(stick);
        if (bf == 2) {
            if (balance_factor(stick->_right) < 0) {
                stick->_right = rotate_right(stick->_right);
            }
            return rotate_left(stick);
        } else if (bf == -2) {
            if (balance_factor(stick->_left) > 0) {
                stick->_left = rotate_left(stick->_left);
            }
            return rotate_right(stick);
        }
        return stick;
    }
    
    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::put(Stick* stick, const T& value) noexcept {
        if (!stick) {
            return new Stick(value);
        }
        if (value < stick->_value) {
            stick->_left = put(stick->_left, value);
        } else {
            stick->_right = put(stick->_right, value);
        }
        return balance(stick);
    }
    
    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::find_min(Stick* stick) const noexcept {
        return stick->_left ? find_min(stick->_left) : stick;
    }

    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::erase_min(Stick* stick) noexcept {
        if (!stick->_left) {
            return stick->_right;
        }
        stick->_left = erase_min(stick->_left);
        return balance(stick);
    }
    
    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::erase(Stick* stick, const T& value) noexcept {
        if (!stick) {
            return nullptr;
        }
        if (value < stick->_value) {
            stick->_left = erase(stick->_left, value);
        } else if (value > stick->_value) {
            stick->_right = erase(stick->_right, value);
        } else {
            Stick* left = stick->_left;
            Stick* right = stick->_right;
            delete stick;
            if (!right) {
                return left;
            }
            Stick* min = find_min(right);
            min->_right = erase_min(right);
            min->_left = left;
            return balance(min);
        }
        return balance(stick);
    }

    template<typename T>
    inline RottenSnag<T>::RottenSnag() : _root(nullptr) {}

    template<typename T>
    inline typename RottenSnag<T>::Stick* RottenSnag<T>::get(const T& value) const noexcept {
        Stick* currentStick = _root;
        
        while (currentStick != nullptr) {
            if (value == currentStick->_value) {
                return currentStick;
            } else if (value < currentStick->_value) {
                currentStick = currentStick->_left;
            } else {
                currentStick = currentStick->_right;
            }
        }

        return nullptr;
    }

    template<typename T>
    inline void RottenSnag<T>::put(const T& value) noexcept {
        _root = put(_root, value);
    }

    template<typename T>
    inline void RottenSnag<T>::erase(const T& value) noexcept {
        _root = erase(_root, value);
    }
};

#endif
