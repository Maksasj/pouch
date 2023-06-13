#ifndef _POUCH_FROSTWEAVE_BAG_H_
#define _POUCH_FROSTWEAVE_BAG_H_

#include <functional>
#include <memory>

#define _POUCH_FROSTWEAVEBAG_MAX_LOAD_FACTOR_ 0.99
#define _POUCH_FROSTWEAVEBAG_MIN_LOAD_FACTOR_ 0.4
#define _POUCH_FROSTWEAVEBAG_DEFAULT_BUCKET_SIZE_ 10

namespace pouch {
    template<class _K, class _V>
    class FrostWeaveBag {
            using u64 = unsigned long long;
            using u32 = unsigned long;
            using f32 = float;

            struct Pocket {
                private:
                    _K _key;
                    _V _value;
                    Pocket *_next;

                    Pocket();
                    Pocket(const Pocket&);
                public:
                    Pocket(const _K& key, const _V& value);
                    ~Pocket();

                    friend class FrostWeaveBag;
            };

            u32 _bagSize;
            Pocket** _data;

            u32 _size;

            inline u32 hash(const _K& hashable, const u32& bounderie) const noexcept;
            inline void _put(const _K& key, const _V& value) noexcept;
            inline void rehash(const u32& newSize) noexcept;
        public:
            struct iterator {
                using iterator_category = std::forward_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = int;
                using pointer           = int*;  // or also value_type*
                using reference         = int&;  // or also value_type&

                const std::pair<_K, _V> operator*() const { return make_pair(_pocket->_key, _pocket->_value); }

                iterator& operator++() { 
                    if(_pocket != nullptr) {
                        if(_pocket->_next != nullptr) {
                            _pocket = _pocket->_next;
                        } else {
                            Pocket* p = nullptr;
                            while(p == nullptr && _bagId < _cont._bagSize) {
                                p = _cont._data[_bagId];
                                ++_bagId;
                            }

                            _pocket = p;
                        }
                    }

                    return *this; 
                }  
                
                iterator operator++(int) { 
                    iterator tmp = *this;
                    
                    ++(*this);

                    return tmp; 
                }

                friend bool operator==(const iterator& a, const iterator& b) { return (a._bagId == b._bagId) && (a._pocket == b._pocket); };
                friend bool operator!=(const iterator& a, const iterator& b) { return !(a == b); };     

                private:
                    iterator(FrostWeaveBag<_K, _V>& c, u32 bagId) : _cont(c) {
                        _bagId = bagId;

                        Pocket* p = nullptr;
                        while(p == nullptr) {
                            p = _cont._data[_bagId];

                            if(_bagId >= _cont._bagSize) {
                                p = nullptr;
                                break;
                            }

                            ++_bagId;
                        }

                        _pocket = p;
                    }

                    friend class FrostWeaveBag;

                    u32 _bagId;
                    Pocket* _pocket;
                
                    FrostWeaveBag<_K, _V>& _cont;
            };

            friend struct iterator;

            iterator begin() {
                return iterator(*this, 0);
            }

            iterator end() {
                return iterator(*this, _bagSize);   
            }

            FrostWeaveBag();
            FrostWeaveBag(const u32& bucket_size);
            ~FrostWeaveBag();

            void trace() {
                Pocket* p = nullptr;
                for(u32 i = 0; i < _bagSize; ++i) {
                    p = _data[i];

                    cout << i << ": ";

                    while (p != nullptr) {
                        cout << p << "(" << p->_value << ") ";
                        p = p->_next;
                    }

                    cout << "\n";
                }
            }

            inline void put(const _K& key, const _V& value) noexcept;
            inline _V* get(const _K& key) const noexcept;
            inline bool has(const _K& key) const noexcept;
            inline void erase(const _K& key) noexcept;

            inline f32 load_factor() noexcept;
            inline f32 max_load_factor() noexcept;
            inline f32 min_load_factor() noexcept;
            inline u64 size() const noexcept;
    };
}

/* Implemetations */
namespace pouch {
    using u64 = unsigned long long;
    using u32 = unsigned long;
    using f32 = float;

    /* Private */
    template<class _K, class _V>
    FrostWeaveBag<_K, _V>::Pocket::Pocket() {
        _next = nullptr;
    }

    template<class _K, class _V>
    FrostWeaveBag<_K, _V>::Pocket::Pocket(const Pocket&) {
        _next = nullptr;
    }

    template<class _K, class _V>
    FrostWeaveBag<_K, _V>::Pocket::Pocket(const _K& key, const _V& value) : _key(key), _value(value), _next(nullptr) {}

    template<class _K, class _V>
    FrostWeaveBag<_K, _V>::Pocket::~Pocket() {
        //if(_next != nullptr)
        //    delete _next;
    }

    template<class _K, class _V>
    inline u32 FrostWeaveBag<_K, _V>::hash(const _K& hashable, const u32& bounderie) const noexcept { // Todo implement my own hash function
        std::hash<_K> h;
        return h(hashable) % bounderie;
    }

    template<class _K, class _V>
    inline void FrostWeaveBag<_K, _V>::_put(const _K& key, const _V& value) noexcept {
        u32 hashKey = hash(key, _bagSize);

        if(_data[hashKey] == nullptr) {
            _data[hashKey] = new Pocket(key , value);
            ++_size;
            return;
        } else if(_data[hashKey]->_key == key) {
            _data[hashKey]->_value = value;
            return;
        }

        Pocket* current = _data[hashKey];

        while (current->_next != nullptr) {
            current = current->_next;

            if(current->_key == key) {
                current->_value = value;
                return;
            }
        }

        ++_size;
        current->_next = new Pocket(key, value);
    }

    template<class _K, class _V>
    inline void FrostWeaveBag<_K, _V>::rehash(const u32& newSize) noexcept {
        Pocket** newData = new Pocket*[newSize]();
        u32 oldSize = _bagSize;

        for(u32 i = 0; i < oldSize; ++i) {
            Pocket* current = _data[i];
            while(current != nullptr) {
                Pocket* _next = current->_next;

                u32 newHash = hash(current->_key, newSize);
                
                current->_next = newData[newHash];
                newData[newHash] = current;
                current = _next;
            }
        }

        delete[] _data;

        _data = newData;
        _bagSize = newSize;
    }

    /* Public */
    template<class _K, class _V>
    FrostWeaveBag<_K, _V>::FrostWeaveBag(const u32& bucket_size) : _bagSize(bucket_size), _size(0) {
        _data = new Pocket*[bucket_size];

        for(u64 i = 0; i < _bagSize; ++i) {
            _data[i] = nullptr; 
        }
    }

    template<class _K, class _V>
    FrostWeaveBag<_K, _V>::FrostWeaveBag() : _bagSize(_POUCH_FROSTWEAVEBAG_DEFAULT_BUCKET_SIZE_), _size(0) {
        _data = new Pocket*[_POUCH_FROSTWEAVEBAG_DEFAULT_BUCKET_SIZE_];
        
        for(u64 i = 0; i < _bagSize; ++i) {
            _data[i] = nullptr; 
        }
    }

    template<class _K, class _V>
    FrostWeaveBag<_K, _V>::~FrostWeaveBag() {
        for(u32 i = 0; i < _bagSize; ++i)
            delete _data[i];
    }

    template<class _K, class _V>
    inline void FrostWeaveBag<_K, _V>::put(const _K& key, const _V& value) noexcept {
        _put(key, value);

        // if(load_factor() > max_load_factor()) {
        //     rehash(_bagSize*2);
        // }
    }

    template<class _K, class _V>
    inline _V* FrostWeaveBag<_K, _V>::get(const _K& key) const noexcept {
        u32 hashKey = hash(key, _bagSize);

        if(_data[hashKey] == nullptr) {
            return nullptr;
        }

        Pocket* current = _data[hashKey];

        while (current->_key != key) {
            if(current->_next == nullptr) {
                return nullptr;
            }

            current = current->_next;
        }
        
        return &current->_value;
    }

    template<class _K, class _V>
    inline bool FrostWeaveBag<_K, _V>::has(const _K& key) const noexcept {
        u32 hashKey = hash(key, _bagSize);

        if(_data[hashKey] == nullptr) {
            return false;
        }

        Pocket* current = _data[hashKey];

        while (current->_key != key) {
            if(current->_next == nullptr) {
                return false;
            }

            current = current->_next;
        }
        
        return true;
    }

    template<class _K, class _V>
    inline void FrostWeaveBag<_K, _V>::erase(const _K& key) noexcept {
        u32 hashKey = hash(key, _bagSize);

        if(_data[hashKey] == nullptr)
            return;

        Pocket* current = _data[hashKey];
        Pocket* prev = nullptr;

        while (current != nullptr) {
            if(current->_key == key) {
                if(prev == nullptr) {
                    _data[hashKey] = current->_next;
                } else {
                    prev->_next = current->_next;
                }

                current->_next = nullptr;
                delete current;
                --_size;

                return;
            }

            prev = current;
            current = current->_next;
        }

        // if(_bagSize > 20 && (load_factor() < min_load_factor())) {
        //     rehash(_bagSize / 2);
        // }
    }

    template<class _K, class _V>
    inline f32 FrostWeaveBag<_K, _V>::load_factor() noexcept {
        return _size / (f32)_bagSize;
    }

    template<class _K, class _V>
    inline f32 FrostWeaveBag<_K, _V>::max_load_factor() noexcept {
        return _POUCH_FROSTWEAVEBAG_MAX_LOAD_FACTOR_;
    }

    template<class _K, class _V>
    inline f32 FrostWeaveBag<_K, _V>::min_load_factor() noexcept {
        return _POUCH_FROSTWEAVEBAG_MIN_LOAD_FACTOR_;
    }

    template<class _K, class _V>
    inline u64 FrostWeaveBag<_K, _V>::size() const noexcept {
        return _size;
    }
}

#endif
