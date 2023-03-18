#ifndef _FROSTWEAVE_BAG_H_
#define _FROSTWEAVE_BAG_H_

namespace pouch {
    template<class _K, class _V>
    class FrostWeaveBag {
            using u64 = unsigned long long;

        public:
            FrostWeaveBag();
            
            void put(const _K& key, const _V& value);
            _V& get(const _K& key) const;
            void erase(const _K& key);

            u64 size();
    };
}

#endif
