#include <cstdio>
#include <string>
#include <iostream>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "rocksdb/iostats_context.h"
#include "rocksdb/perf_context.h"
#include <pthread.h>
#include <unistd.h>


using namespace std;
using namespace rocksdb;

const std::string PATH = "/tmp/rocksdb_tmp";

DB* db;
Options options;

int main() {
    options.create_if_missing = true;
    Status s = DB::Open(options, PATH, &db);
    assert(s.ok());

    s = db->Put(WriteOptions(),"key01","value");
    assert(s.ok());

    std::string value;
    s = db->Get(ReadOptions(),"key01", &value);

    cout << value << endl;
    return 0;
}
