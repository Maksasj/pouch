#ifndef _POUCH_HOLEY_POUCH_
#define _POUCH_HOLEY_POUCH_

namespace pouch {
    template<class _T, unsigned long long __maxSize>
    class HoleyPouch {
        private:
            using u64 = unsigned long long;
            using u32 = unsigned long;

            u64 _capacity;
            u64 _maxSize;
            u64 _size;

            _T* _data;

            inline void _resize(const u64& newCapacity) noexcept {
                _T* new_data = new _T[newCapacity];

                for(u64 i = 0; i < _capacity; ++i) {
                    new_data[i] = _data[i];
                }

                delete [] _data;
                _capacity = newCapacity;
                _data = new_data;
            }

        public:
            HoleyPouch() : _maxSize(__maxSize) {
                _data = new _T[1];
                _capacity = 1;
                _size = 0;
            }

            ~HoleyPouch() {
                delete [] _data;
            }

            inline void push_on_top(const _T& value) noexcept {
                if(_size == _capacity)
                    _resize(_capacity * 2);

                _data[_size] = value;
                ++_size;
            }

            _T& get_on_top() {
                return _data[_size - 1];
            }
            
            inline void pop_top() noexcept {
                --_size;
            }

            inline _T& get(const u64& index) const noexcept; 

            inline u64 size() const noexcept {
                return _size;
            }

            inline u64 capacity() const noexcept {
                return _capacity;
            }

            inline u64 max_size() const noexcept {
                return _maxSize;
            }
    };
}

#endif
