#ifndef _POUCH_FROSTWEAVE_BAG_H_
#define _POUCH_FROSTWEAVE_BAG_H_

#include <functional>
#include <optional>
#include <memory>

#define _POUCH_FROSTWEAVEBAG_MAX_LOAD_FACTOR_ 0.99
#define _POUCH_FROSTWEAVEBAG_MIN_LOAD_FACTOR_ 0.4
#define _POUCH_FROSTWEAVEBAG_DEFAULT_BUCKET_SIZE_ 100

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
            FrostWeaveBag();
            FrostWeaveBag(const u32& bucket_size);
            ~FrostWeaveBag();

            inline void put(const _K& key, const _V& value) noexcept;
            inline std::optional<std::reference_wrapper<_V>> get(const _K& key) const noexcept;
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
    FrostWeaveBag<_K, _V>::Pocket::Pocket() {}

    template<class _K, class _V>
    FrostWeaveBag<_K, _V>::Pocket::Pocket(const Pocket&) {}

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
        }

        Pocket* current = _data[hashKey];

        while (current->_next != nullptr) {
            if(current->_key == key) {
                current->_value = value;
                return;
            }

            current = current->_next;
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
    FrostWeaveBag<_K, _V>::FrostWeaveBag(const u32& bucket_size) : _size(0) , _bagSize(bucket_size) {
        _data = new Pocket*[bucket_size];
        
        for(u32 i = 0; i < _bagSize; ++i)
            _data[i] = nullptr;
    }

    template<class _K, class _V>
    FrostWeaveBag<_K, _V>::FrostWeaveBag() : _size(0) , _bagSize(_POUCH_FROSTWEAVEBAG_DEFAULT_BUCKET_SIZE_) {
        _data = new Pocket*[_POUCH_FROSTWEAVEBAG_DEFAULT_BUCKET_SIZE_];
        
        for(u32 i = 0; i < _bagSize; ++i)
            _data[i] = nullptr;
    }

    template<class _K, class _V>
    FrostWeaveBag<_K, _V>::~FrostWeaveBag() {
        for(u32 i = 0; i < _bagSize; ++i)
            delete _data[i];
    }

    template<class _K, class _V>
    inline void FrostWeaveBag<_K, _V>::put(const _K& key, const _V& value) noexcept {
        _put(key, value);

        if(load_factor() > max_load_factor()) {
            rehash(_bagSize*2);
        }
    }

    template<class _K, class _V>
    inline std::optional<std::reference_wrapper<_V>> FrostWeaveBag<_K, _V>::get(const _K& key) const noexcept {
        u32 hashKey = hash(key, _bagSize);

        if(_data[hashKey] == nullptr) {
            return std::nullopt;
        }

        Pocket* current = _data[hashKey];

        while (current->_key != key) {
            if(current->_next == nullptr) {
                return std::nullopt;
            }

            current = current->_next;
        }
        
        return std::optional<std::reference_wrapper<_V>>{current->_value};
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

        if(_bagSize > 20 && (load_factor() < min_load_factor())) {
            rehash(_bagSize / 2);
        }
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
