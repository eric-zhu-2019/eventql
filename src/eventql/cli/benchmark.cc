/**
 * Copyright (c) 2016 DeepCortex GmbH <legal@eventql.io>
 * Authors:
 *   - Paul Asmuth <paul@eventql.io>
 *   - Laura Schlimmer <laura@eventql.io>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License ("the license") as
 * published by the Free Software Foundation, either version 3 of the License,
 * or any later version.
 *
 * In accordance with Section 7(e) of the license, the licensing of the Program
 * under the license does not imply a trademark license. Therefore any rights,
 * title and interest in our trademarks remain entirely with us.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the license for more details.
 *
 * You can be released from the requirements of the license by purchasing a
 * commercial license. Buying such a license is mandatory as soon as you develop
 * commercial activities involving this program without disclosing the source
 * code of your own applications
 */
#include <eventql/cli/benchmark.h>

namespace eventql {
namespace cli {

Benchmark::Benchmark() :
    num_threads_(4),
    status_(ReturnCode::success()) {
  threads_.resize(num_threads_);
}

ReturnCode Benchmark::run() {
  for (size_t i = 0; i < num_threads_; ++i) {
    threads_[i] = std::thread(std::bind(&Benchmark::runThread, this, i));
  }

  for (auto& t : threads_) {
    if (t.joinable()) {
      t.join();
    }
  }

  return status_;
}

void Benchmark::kill() {
  std::unique_lock<std::mutex> lk(mutex_);
  stopWithError(ReturnCode::error("ERUNTIME", "Benchmark aborted..."));
}

void Benchmark::runThread(size_t idx) {
  while (getRequestSlot(idx)) {

    std::unique_lock<std::mutex> lk(mutex_);
    // check for exit conditions
    // increase num requests
    lk.unlock();

    runRequest();
    lk.lock();
  }
}

void Benchmark::runRequest() {
  printf("run request\n");
}

// PRECONDITION: must hold mutex_
void Benchmark::stopWithError(ReturnCode rc) {
  status_ = rc;
  cv_.notify_all();
}

bool Benchmark::getRequestSlot(size_t idx) {
  usleep(100000);
  return true;
}

} //cli
} //eventql
