#ifndef _POUCH_HOLEY_POUCH_COMPACT_
#define _POUCH_HOLEY_POUCH_COMPACT_

#include "holey_pouch.hpp"

namespace pouch {
    template<class _T, unsigned long long __maxSize = 100, unsigned long long __expandSize = 5>
    class HoleyPouchCompact : public HoleyPouch<_T, __maxSize> {
        private:
            const u64 _expandSize;
        public:
            HoleyPouchCompact();

            inline void push_on_top(const _T& value) noexcept;
            inline void pop_top();

            inline const u64 expand_size() const noexcept; 
    };
}

namespace pouch {
    using u64 = unsigned long long;
    using u32 = unsigned long;
    using f32 = float;

    template<class _T, unsigned long long __maxSize, unsigned long long __expandSize>
    HoleyPouchCompact<_T, __maxSize, __expandSize>::HoleyPouchCompact() : HoleyPouch<_T, __maxSize>(), _expandSize(__expandSize)  {

    }

    template<class _T, unsigned long long __maxSize, unsigned long long __expandSize>
    inline void HoleyPouchCompact<_T, __maxSize, __expandSize>::push_on_top(const _T& value) noexcept {
        if(this->_size == this->_capacity)
            this->_resize(this->_capacity + _expandSize);

        this->_data[this->_size] = value;
        ++this->_size;
    }

    template<class _T, unsigned long long __maxSize, unsigned long long __expandSize>
    inline void HoleyPouchCompact<_T, __maxSize, __expandSize>::pop_top() {
        if(this->_size <= 0) throw std::out_of_range("holey pouch pop_top out of range");

        --this->_size;

        if((this->_size <= this->_capacity - this->_expandSize) && ((this->_capacity - this->_expandSize) > 1)) 
            this->_resize(this->_capacity - _expandSize);
    }

    template<class _T, unsigned long long __maxSize, unsigned long long __expandSize>
    inline const u64 HoleyPouchCompact<_T, __maxSize, __expandSize>::expand_size() const noexcept {
        return _expandSize;
    }

}
#endif
