/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "modules/prediction/common/feature_output.h"

#include <string>

#include "modules/common/log.h"
#include "modules/common/util/file.h"
#include "modules/prediction/common/prediction_gflags.h"

namespace apollo {
namespace prediction {

FeatureOutput::FeatureOutput() {}

FeatureOutput::~FeatureOutput() {
  Clear();
}

bool FeatureOutput::Open() {
  return true;
}

void FeatureOutput::Close() {
  ADEBUG << "Close feature output";
  Write();
  Clear();
}

void FeatureOutput::Clear() {
  count_ = 0;
  features_.Clear();
}

bool FeatureOutput::Ready() { return Open(); }

void FeatureOutput::Insert(const Feature& feature) {
  features_.add_feature()->CopyFrom(feature);
}

void FeatureOutput::Write() {
  if (features_.feature_size() <= 0) {
    ADEBUG << "Skip writing empty feature.";
    return;
  }
  std::string file_name = FLAGS_prediction_data_file_prefix +
                          std::to_string(count_) + ".bin";
  apollo::common::util::SetProtoToBinaryFile(features_, file_name);
  features_.Clear();
  ++count_;
}

}  // namespace prediction
}  // namespace apollo