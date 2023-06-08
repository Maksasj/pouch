#ifndef _TEST_H_
#define _TEST_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

#include "pouch.h"

#define ensure(EXP) if(!(EXP)) return 1;
#define ensure_throw(EXP, EXCEP) {bool t = false; try{ EXP; }catch(const EXCEP& e){t = true; } ensure(t) }
#define TEST_CASE

#endif