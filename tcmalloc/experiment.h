// Copyright 2019 The TCMalloc Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TCMALLOC_EXPERIMENT_H_
#define TCMALLOC_EXPERIMENT_H_

#include <stddef.h>

#include <map>
#include <string>

#include "absl/strings/string_view.h"
#include "absl/types/optional.h"
#include "tcmalloc/experiment_config.h"
#include "tcmalloc/internal/logging.h"
#include "tcmalloc/malloc_extension.h"

// TCMalloc Experiment Controller
//
// This consumes environment variables to decide whether to activate experiments
// to control TCMalloc behavior.  It avoids memory allocations when making
// experiment decisions to allow experiments to be used in critical TCMalloc
// initialization paths.
//
// If an experiment is causing difficulty, all experiments can be disabled by
// setting the environment variable:
//     BORG_DISABLE_EXPERIMENTS=all *or*
//     BORG_DISABLE_EXPERIMENTS=BAD_EXPERIMENT_LABEL

namespace tcmalloc {
namespace internal {

constexpr size_t kNumExperiments =
    static_cast<size_t>(Experiment::kMaxExperimentID);

// SelectExperiments parses the experiments enumerated by active and disabled
// and updates buffer[experiment_id] accordingly.
//
// buffer must be sized for kMaxExperimentID entries.
//
// This is exposed for testing purposes only.
const bool* SelectExperiments(bool* buffer, absl::string_view active,
                              absl::string_view disabled);

}  // namespace internal

bool IsExperimentActive(Experiment exp);

void FillExperimentProperties(
    std::map<std::string, MallocExtension::Property>* result);

absl::optional<Experiment> FindExperimentByName(absl::string_view name);

void PrintExperiments(TCMalloc_Printer* printer);

}  // namespace tcmalloc

#endif  // TCMALLOC_EXPERIMENT_H_
