#ifndef _POUCH_HOLEY_POUCH_
#define _POUCH_HOLEY_POUCH_

namespace pouch {
    template<class _T, unsigned long long __maxSize>
    class HoleyPouch {
        protected:
            using u64 = unsigned long long;
            using u32 = unsigned long;

            u64 _capacity;
            const u64 _maxSize;
            u64 _size;

            _T* _data;

            inline void _resize(const u64& newCapacity) noexcept;
        public:
            HoleyPouch();
            ~HoleyPouch();

            inline void push_on_top(const _T& value) noexcept;
            inline _T& get_on_top();
            inline void pop_top();

            inline _T& get(const u64& index) const;
            inline void set(const u64& index, const _T& value);

            inline u64 capacity() const noexcept;
            inline u64 size() const noexcept;
            inline const u64 max_size() const noexcept;
    };
}

namespace pouch {
    using u64 = unsigned long long;
    using u32 = unsigned long;
    using f32 = float;

    /* Protected methods */
    template<class _T, unsigned long long __maxSize>
    inline void HoleyPouch<_T, __maxSize>::_resize(const u64& newCapacity) noexcept {
        _T* new_data = new _T[newCapacity];

        const u64 range = std::min(_capacity, newCapacity);
        
        for(u64 i = 0; i < range; ++i)
            new_data[i] = _data[i];

        delete [] _data;
        _capacity = newCapacity;
        _data = new_data;
    }

    /* Public methods */
    template<class _T, unsigned long long __maxSize>
    HoleyPouch<_T, __maxSize>::HoleyPouch() : _maxSize(__maxSize) {
        _data = new _T[1];
        _capacity = 1;
        _size = 0;
    }

    template<class _T, unsigned long long __maxSize>
    HoleyPouch<_T, __maxSize>::~HoleyPouch() {
        delete [] _data;
    }

    template<class _T, unsigned long long __maxSize>
    inline void HoleyPouch<_T, __maxSize>::push_on_top(const _T& value) noexcept {
        if(_size == _capacity)
            _resize(_capacity * 2);

        _data[_size] = value;
        ++_size;
    }

    template<class _T, unsigned long long __maxSize>
    inline _T& HoleyPouch<_T, __maxSize>::get_on_top() {
        return _data[_size - 1];
    }
    
    template<class _T, unsigned long long __maxSize>
    inline void HoleyPouch<_T, __maxSize>::pop_top() {
        if(_size <= 0) throw std::out_of_range("holey pouch pop_top out of range");

        --_size;

        if((_size <= _capacity / 2) && (_capacity / 2 > 1)) 
            _resize(_capacity / 2);
    }

    template<class _T, unsigned long long __maxSize>
    inline _T& HoleyPouch<_T, __maxSize>::get(const u64& index) const {
        if(index >= _size) throw std::out_of_range("holey pouch pop_top out of range");

        return _data[index];
    }

    template<class _T, unsigned long long __maxSize>
    inline void HoleyPouch<_T, __maxSize>::set(const u64& index, const _T& value) {
        if(index >= _size) throw std::out_of_range("holey pouch pop_top out of range");
        _data[index] = value;
    }

    template<class _T, unsigned long long __maxSize>
    inline u64 HoleyPouch<_T, __maxSize>::size() const noexcept {
        return _size;
    }

    template<class _T, unsigned long long __maxSize>
    inline u64 HoleyPouch<_T, __maxSize>::capacity() const noexcept {
        return _capacity;
    }

    template<class _T, unsigned long long __maxSize>
    inline const u64 HoleyPouch<_T, __maxSize>::max_size() const noexcept {
        return _maxSize;
    }
}
#endif
