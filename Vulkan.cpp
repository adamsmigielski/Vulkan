/** License
*
* Copyright (c) 2015 Adam �migielski
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
* @author Adam �migielski
* @file YYY.cpp
**/

#include "PCH.hpp"

#include "Vulkan.hpp"
#include "Loader.hpp"

namespace Vulkan
{
    Vulkan::Vulkan()
        : Entry_functions(&m_entry_functions)
    {
    }

    Vulkan::~Vulkan()
    {
        
    }

    Platform::int32 Vulkan::Init(::Vulkan::Loader & loader)
    {
        if (nullptr != m_loader.get())
        {
            ASSERT(0);
            return Utilities::Invalid_object;
        }

        m_loader.reset(&loader);

        return Utilities::Success;
    }

    void Vulkan::Release()
    {
        m_loader.release();
    }

    const Loader * Vulkan::Loader() const
    {
        return m_loader.get();
    }

}
