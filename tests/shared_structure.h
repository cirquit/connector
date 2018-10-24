// Copyright 2018 municHMotorsport e.V. <info@munichmotorsport.de>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SHARED_STRUCTURE_H
#define SHARED_STRUCTURE_H

namespace structure 
{
    // a "complex" struct to send and receive
    struct complex_struct
    {
        int i;
        double d;
        char message[255];
    };

    // create a default set complex_struct
    struct complex_struct init_complex_struct()
    {
        struct complex_struct cs;
        cs.i = 0;
        cs.d = 0.0;
        sprintf(cs.message, "");
        return cs;
    }

} // namespace structure

#endif // SHARED_STRUCTURE_H