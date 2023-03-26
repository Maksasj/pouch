# Pouch

Pouch - simple c++ library that introduces some containers, primary HashMap and stack style dynamic array. 

HashMap uses classical approach with array of linked lists, but there is also used rehashing technique to gain performance **(note that FrostWeaveBag, have almost O(n*2) space complexity)**.

On the another hand there is HoleyPouch that works similary with C++ **std::vector**, and it have two implementations one aimed for speed, HoleyPouch (space complexity O(n*2)), as well as HoleyPouchCompact which main idea is a best space complexity O(n). 

**Library was created only for studing purposes.**

## Performace

### Associative arrays (tested with 100k elements):
```txt
pouch::FrostWeaveBag<int, int>: 
    Insertion time for: 100000, took: 21.64[ms]
    Load factor: 0.976562 / 0.99
    Get time for: 100000, took: 14.3355[ms]
    Erase time for: 100000, took: 15.4833[ms]

C++ std::unordered_map<int, int>: 
    Insertion time for: 100000, took: 47.673[ms]
    Load factor: 0.762939 / 1
    Get time for: 100000, took: 18.2804[ms]
    Erase time for: 100000, took: 33.5546[ms]

C++ std::map<int, int>: 
    Insertion time for: 100000, took: 66.4885[ms]
    Get time for: 100000, took: 67.8043[ms]
    Erase time for: 100000, took: 84.75[ms]
```

### Dynamic arrays (tested with 1m elements):
```txt
pouch::HoleyPouch<int>
    Push back took: 6.0982[ms]
    Get at took: 2.2146[ms]
    Pop back took: 5.9695[ms]

pouch::HoleyPouchCompact<int>
    Push back took: 13171.5[ms]
    Get at took: 2.4255[ms]
    Pop back took: 12300.6[ms]

std::vector<int>
    Push back took: 23.9014[ms]
    Get at took: 2.6605[ms]
    Pop back took: 18.2546[ms]

std::deque<int>
    Push back took: 75.5544[ms]
    Get at took: 102.663[ms]
    Pop back took: 39.1867[ms]

std::list<int>
    Push back took: 152.267[ms]
    Pop back took: 128.308[ms]
```

## Building
```bash
cmake -B build -G Ninja

make.bat
```

## Test
```bash
test.bat
```

## Benchmark
```bash
bench.bat
```
