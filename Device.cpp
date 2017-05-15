/** License
*
* Copyright (c) 2015 Adam Œmigielski
*
*
*  Permission is hereby granted, free of charge, to any person obtaining a
*      copy of this software and associated documentation files (the
*      "Software"), to deal in the Software without restriction, including
*      without limitation the rights to use, copy, modify, merge, publish,
*      distribute, sublicense, and/or sell copies of the Software, and to
*      permit persons to whom the Software is furnished to do so, subject to
*      the following conditions: The above copyright notice and this permission
*      notice shall be included in all copies or substantial portions of the
*      Software.
*
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
*      OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*      MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
*      IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
*      CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
*      TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
*      SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
**/

/**
* @author Adam Œmigielski
* @file Device.cpp
**/

#include "PCH.hpp"

#include "Device.hpp"


namespace Vulkan
{
    namespace Version_1_0_0
    {
        Device::Device()
            : m_device(VK_NULL_HANDLE)
        {
        }

        Device::~Device()
        {
            Release();
        }

        Platform::int32 Device::Init(VkDevice device)
        {
            if (VK_NULL_HANDLE == device)
            {
                ASSERT(0);
                return Utilities::Invalid_parameter;
            }

            if (VK_NULL_HANDLE != m_device)
            {
                ASSERT(0);
                return Utilities::Invalid_object;
            }

            return Load_functions(m_device);
        }

        void Device::Release()
        {
            auto parent = Parent();
            if (nullptr != parent)
            {
                parent->Detach(this);
            }

            if (VK_NULL_HANDLE != m_device)
            {
                m_Functions.DestroyDevice(
                    m_device /* VkDevice                     device */,
                    nullptr  /* const VkAllocationCallbacks* pAllocator */);
                m_device = VK_NULL_HANDLE;
            }
        }
    }
}
