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

#include <Utilities\DL\Library.hpp>

#include "Loader.hpp"


namespace Vulkan
{
    namespace Windows
    {
        Loader::Loader()
            : m_library(nullptr)
        {
        }

        Loader:: ~Loader()
        {
            Release();
        }

        Platform::int32 Loader::Init(const char * library_path)
        {
            m_library = Dynamic_library::Load(library_path);
            ASSERT(m_library);
            if (nullptr == m_library)
            {
                ERRLOG("Failed to load: " << library_path);
                return Utilities::Failed_to_load_library;
            }

            return Utilities::Success;
        }

        void Loader::Release()
        {
            if (nullptr != m_library)
            {
                delete m_library;
                m_library = nullptr;
            }
        }

        Platform::proc_t Loader::Get_proc_address(const char * name)
        {
            return m_library->GetFunctionAddress(name);
        }
    }

    ::Vulkan::Loader * Create_loader()
    {
        auto loader = new Vulkan::Windows::Loader;

        if (nullptr == loader)
        {
            ERRLOG("Failed to allocate memory");
            ASSERT(0);
        }

        return loader;
    }
}
