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
* @file Instance.hpp
**/

#ifndef VULKAN_INSTANCE_HPP
#define VULKAN_INSTANCE_HPP

#include <Utilities\containers\IntrusiveList.hpp>

#include "Device.hpp"

namespace Vulkan
{
    namespace Version_1_0_0
    {
        class Implementation;
        class Device;

        class Instance
            : public Containers::IntrusiveList::Node<Instance>
            , public Containers::IntrusiveList::List<Device>
        {
        public:
            struct Functions
            {
                PFN_vkDestroyInstance                        DestroyInstance;
                PFN_vkEnumeratePhysicalDevices               EnumeratePhysicalDevices;
                PFN_vkGetPhysicalDeviceFeatures              GetPhysicalDeviceFeatures;
                PFN_vkGetPhysicalDeviceFormatProperties      GetPhysicalDeviceFormatProperties;
                PFN_vkGetPhysicalDeviceImageFormatProperties GetPhysicalDeviceImageFormatProperties;
                PFN_vkGetPhysicalDeviceProperties            GetPhysicalDeviceProperties;
                PFN_vkGetPhysicalDeviceQueueFamilyProperties GetPhysicalDeviceQueueFamilyProperties;
                PFN_vkGetPhysicalDeviceMemoryProperties      GetPhysicalDeviceMemoryProperties;
                PFN_vkGetDeviceProcAddr                      GetDeviceProcAddr;
                PFN_vkCreateDevice                           CreateDevice;
                PFN_vkEnumerateDeviceExtensionProperties     EnumerateDeviceExtensionProperties;
                PFN_vkEnumerateDeviceLayerProperties         EnumerateDeviceLayerProperties;
            };

            struct VK_EXT_debug_report_functions
            {
                PFN_vkCreateDebugReportCallbackEXT  CreateDebugReportCallback;
                PFN_vkDestroyDebugReportCallbackEXT DestroyDebugReportCallback;
                PFN_vkDebugReportMessageEXT         DebugReportMessage;
            };

            Instance();

            virtual ~Instance();

            Platform::int32 Init(
                      VkInstance                 instance,
                const std::vector<std::string> & extensions,
                      Implementation           & parent);

            void Release();

            Platform::int32 Load_functions(
                VkInstance   instance,
                Functions  & out_functions) const;
            Platform::int32 Load_functions(
                VkInstance                      instance,
                VK_EXT_debug_report_functions & out_functions);
            Platform::int32 Load_functions(const std::vector<std::string> & extensions);


            /*  */
            Platform::int32 Enumerate_physical_devices(std::vector<VkPhysicalDevice> & out_devices) const;
            Platform::int32 Get_physical_device_properties(
                VkPhysicalDevice             physical_devices,
                VkPhysicalDeviceProperties & out_properties) const;
            Device * Create_device();


            /*  */
            Functions                     m_Functions;
            VK_EXT_debug_report_functions m_EXT_debug_report_functions;

            /*  */
            static const char * const VK_EXT_debug_report_name;

            static const char * const VK_LAYER_LUNARG_standard_validation_name;

        private:
            VkInstance m_instance;
        };
    }
}

#endif /* VULKAN_INSTANCE_HPP */
