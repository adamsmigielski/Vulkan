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
* @file YYY.hpp
**/

#ifndef VULKAN_LOADER_HPP
#define VULKAN_LOADER_HPP

namespace Vulkan
{
    class Loader
    {
    public:
        virtual Platform::int32 Init   (const char * library_path) = 0;
        virtual void            Release() = 0;


        virtual Platform::proc_t Get_proc_address(const char * name) = 0;
    };

    Loader * Create_loader();

#if 0

    /* Callbacks */
    extern PFN_vkAllocationFunction AllocationFunction;
    extern PFN_vkReallocationFunction ReallocationFunction;
    extern PFN_vkFreeFunction FreeFunction;
    extern PFN_vkInternalAllocationNotification InternalAllocationNotification;
    extern PFN_vkInternalFreeNotification InternalFreeNotification;

    /* Global entry points */

    /* Instance entry points */



#endif /* 0 */
}

#endif VULKAN_LOADER_HPP
