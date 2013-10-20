/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "Ticker.h"

#include "TimerEvent.h"
#include "FunctionPointer.h"

namespace mbed {

void Ticker::detach() {
    remove();
    _chain.clear();
}

void Ticker::setup(unsigned int t) {
    remove();
    _delay = t;
    insert(_delay + us_ticker_read());
}

void Ticker::handler() {
    insert(event.timestamp + _delay);
    _chain.call();
}

pFunctionPointer_t Ticker::add_function_helper(void (*fptr)(void), bool front) {
    if (_chain.size() == 0)
        return NULL;
    return front ? _chain.add_front(fptr) : _chain.add(fptr);
}

} // namespace mbed
