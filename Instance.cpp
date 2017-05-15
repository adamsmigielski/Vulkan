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
* @file Instance.cpp
**/

#include "PCH.hpp"

#include "Instance.hpp"

#include "Device.hpp"
#include "Implementation.hpp"


namespace Vulkan
{
    namespace Version_1_0_0
    {
        const char * const Instance::VK_EXT_debug_report_name = "VK_EXT_debug_report";

        const char * const Instance::VK_LAYER_LUNARG_standard_validation_name = "VK_LAYER_LUNARG_standard_validation";


        Instance::Instance()
            : m_instance(VK_NULL_HANDLE)
        {

        }

        Instance::~Instance()
        {
            Release();
        }

        Platform::int32 Instance::Init(
                  VkInstance                 instance,
            const std::vector<std::string> & extensions)
        {
            if (VK_NULL_HANDLE == instance)
            {
                ASSERT(0);
                return Utilities::Invalid_parameter;
            }

            if (VK_NULL_HANDLE != m_instance)
            {
                ASSERT(0);
                return Utilities::Invalid_object;
            }


            m_instance = instance;


            return Load_functions(extensions);
        }

        void Instance::Release()
        {
            auto parent = Parent();
            if (nullptr != parent)
            {
                parent->Detach(this);
            }

            if (VK_NULL_HANDLE != m_instance)
            {
                m_Functions.DestroyInstance(
                    m_instance /* VkInstance                   instance*/,
                    nullptr    /* const VkAllocationCallbacks* pAllocator */);
                m_instance = VK_NULL_HANDLE;
            }
        }

        static Platform::proc_t load_instance_function(
            const Implementation::Functions * functions,
                  VkInstance                  instance,
            const char                      * name,
                  bool                        check)
        {
            Platform::proc_t pointer = nullptr;

            pointer = (Platform::proc_t) functions->GetInstanceProcAddr(instance, name);

            if (nullptr == pointer)
            {
                ASSERT(0);
                ERRLOG("Failed to load function" << name);
                check = false;
            }
            else
            {
                DEBUGLOG("Loaded function: " << name);
            }

            return pointer;
        }

        Platform::int32 Instance::Load_functions(
            VkInstance   instance,
            Functions  & out_functions) const
        {
            bool check = true;

            auto parent      = (Implementation *) this->Parent(); /* Implementation is parent of Instance */
            auto & functions = parent->m_Functions;

            out_functions.DestroyInstance                        = (PFN_vkDestroyInstance)                        load_instance_function(&functions, instance, "vkDestroyInstance"                       , check);
            out_functions.EnumeratePhysicalDevices               = (PFN_vkEnumeratePhysicalDevices)               load_instance_function(&functions, instance, "vkEnumeratePhysicalDevices"              , check);
            out_functions.GetPhysicalDeviceFeatures              = (PFN_vkGetPhysicalDeviceFeatures)              load_instance_function(&functions, instance, "vkGetPhysicalDeviceFeatures"             , check);
            out_functions.GetPhysicalDeviceFormatProperties      = (PFN_vkGetPhysicalDeviceFormatProperties)      load_instance_function(&functions, instance, "vkGetPhysicalDeviceFormatProperties"     , check);
            out_functions.GetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties) load_instance_function(&functions, instance, "vkGetPhysicalDeviceImageFormatProperties", check);
            out_functions.GetPhysicalDeviceProperties            = (PFN_vkGetPhysicalDeviceProperties)            load_instance_function(&functions, instance, "vkGetPhysicalDeviceProperties"           , check);
            out_functions.GetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties) load_instance_function(&functions, instance, "vkGetPhysicalDeviceQueueFamilyProperties", check);
            out_functions.GetPhysicalDeviceMemoryProperties      = (PFN_vkGetPhysicalDeviceMemoryProperties)      load_instance_function(&functions, instance, "vkGetPhysicalDeviceMemoryProperties"     , check);
            out_functions.GetDeviceProcAddr                      = (PFN_vkGetDeviceProcAddr)                      load_instance_function(&functions, instance, "vkGetDeviceProcAddr"                     , check);
            out_functions.CreateDevice                           = (PFN_vkCreateDevice)                           load_instance_function(&functions, instance, "vkCreateDevice"                          , check);
            out_functions.EnumerateDeviceExtensionProperties     = (PFN_vkEnumerateDeviceExtensionProperties)     load_instance_function(&functions, instance, "vkEnumerateDeviceExtensionProperties"    , check);
            out_functions.EnumerateDeviceLayerProperties         = (PFN_vkEnumerateDeviceLayerProperties)         load_instance_function(&functions, instance, "vkEnumerateDeviceLayerProperties"        , check);


            if (false == check)
            {
                ASSERT(0);
                ERRLOG("Vulkan instance loading failed");
                return Utilities::Failure;
            }

            return Utilities::Success;
        }

        Platform::int32 Instance::Load_functions(VkInstance instance, VK_EXT_debug_report_functions & out_functions)
        {
            
            bool check = true;

            auto parent      = (Implementation *) this->Parent(); /* Implementation is parent of Instance */
            auto & functions = parent->m_Functions;

            out_functions.CreateDebugReportCallback  = (PFN_vkCreateDebugReportCallbackEXT)  load_instance_function(&functions, instance, "vkCreateDebugReportCallbackEXT" , check);
            out_functions.DestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT) load_instance_function(&functions, instance, "vkDestroyDebugReportCallbackEXT", check);
            out_functions.DebugReportMessage         = (PFN_vkDebugReportMessageEXT)         load_instance_function(&functions, instance, "vkDebugReportMessageEXT"        , check);

            if (false == check)
            {
                ASSERT(0);
                ERRLOG("VK_EXT_debug_report loading failed");
                return Utilities::Failure;
            }

            return Utilities::Success;
        }

        Platform::int32 Instance::Load_functions(const std::vector<std::string> & extensions)
        {
            auto err = Load_functions(m_instance, m_Functions);
            if (Utilities::Success != err)
            {
                return err;
            }

            for (const auto & name : extensions)
            {
                if (0 == name.compare(VK_EXT_debug_report_name))
                {
                    err = Load_functions(m_instance, m_EXT_debug_report_functions);
                }


                if (Utilities::Success != err)
                {
                    return err;
                }
            }

            return Utilities::Success;
        }
    }
}
