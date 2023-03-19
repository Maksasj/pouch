#ifndef _POUCH_HOLEY_POUCH_
#define _POUCH_HOLEY_POUCH_

namespace pouch {
    template<class _T, unsigned long long __maxSize>
    class HoleyPouch {
        private:
            using u64 = unsigned long long;
            using u32 = unsigned long;

            u64 _maxSize;
            u64 _size;

            void _resize(const u64& newSize);
        public:
            HoleyPouch();
            ~HoleyPouch();

            void push_on_top();
            _T& get_on_top(const u64& index); 
            void pop_top();

            _T& get(const u64& index); 

            u64 size();
            u64 max_size();
    };
}

#endif
