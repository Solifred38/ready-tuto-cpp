#pragma once

#include <windows.h>
#include <dirent.h>
#include <sys/stat.h>

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <regex>

#include <sqlite3.h>

#include "common_object.h"
#include "db_sqlite.h"
#include "db_sqlite_run.h"

typedef unsigned char   uchar;
typedef unsigned int    uint;
typedef unsigned long   ulong;
