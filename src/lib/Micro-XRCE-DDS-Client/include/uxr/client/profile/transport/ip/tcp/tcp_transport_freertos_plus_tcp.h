// Copyright 2018 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#ifndef _UXR_CLIENT_TCP_TRANSPORT_FREERTOS_H_
#define _UXR_CLIENT_TCP_TRANSPORT_FREERTOS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "FreeRTOS.h"
#include "list.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"

typedef struct uxrTCPPlatform
{
    struct freertos_sockaddr remote_addr;
    SocketSet_t poll_fd;
    Socket_t fd;
    uint8_t use_ethernet;
} uxrTCPPlatform;

#ifdef __cplusplus
}
#endif

#endif //_UXR_CLIENT_TCP_TRANSPORT_FREERTOS_H_
