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
* @file YYY.cpp
**/

#include "PCH.hpp"

#include "Implementation.hpp"
#include "Loader.hpp"
#include "Instance.hpp"

namespace Vulkan
{
    namespace Version_1_0_0
    {
        Implementation::Implementation()
        {
        }

        Implementation::~Implementation()
        {
        
        }

        Platform::int32 Implementation::Init(::Vulkan::Loader & loader)
        {
            if (nullptr != m_loader.get())
            {
                ASSERT(0);
                return Utilities::Invalid_object;
            }

            m_loader.reset(&loader);

            return Load_functions();
        }

        void Implementation::Release()
        {
            m_loader.release();
        }
    
        Platform::proc_t load_library_function(Loader * loader, const char * name, bool check)
        {
            Platform::proc_t pointer = nullptr;

            pointer = loader->Get_proc_address(name);

            if (nullptr == pointer)
            {
                ASSERT(0);
                ERRLOG("Failed to load function" << name);
                check = false;
            }

            return pointer;
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

        Platform::int32 Implementation::Load_functions(Functions & out_functions) const
        {
            bool check = true;

            out_functions.GetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) load_library_function(m_loader.get(), "vkGetInstanceProcAddr", check);

            out_functions.CreateInstance                       = (PFN_vkCreateInstance)                       load_instance_function(&out_functions, nullptr, "vkCreateInstance"                      , check);
            out_functions.EnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties) load_instance_function(&out_functions, nullptr, "vkEnumerateInstanceExtensionProperties", check);
            out_functions.EnumerateInstanceLayerProperties     = (PFN_vkEnumerateInstanceLayerProperties)     load_instance_function(&out_functions, nullptr, "vkEnumerateInstanceLayerProperties"    , check);


            if (false == check)
            {
                ASSERT(0);
                ERRLOG("Vulkan loading failed");
                return Utilities::Failure;
            }

            return Utilities::Success;
        }

        Platform::int32 Implementation::Load_functions()
        {
            return Load_functions(m_Functions);
        }


        Platform::int32 Implementation::Enumerate_implementation_extensions(std::vector<VkExtensionProperties>& out_extensions) const
        {
            VkResult result;
            uint32_t n_extesions = 0;

            /* Get number */
            result = m_Functions.EnumerateInstanceExtensionProperties(
                nullptr,
                &n_extesions,
                nullptr);
            if (VK_SUCCESS != result)
            {
                ERRLOG("Failed to get extension number: " << VkEnum_to_string(result));
                return Utilities::Failure;
            }

            out_extensions.resize(n_extesions);

            result = m_Functions.EnumerateInstanceExtensionProperties(
                nullptr,
                &n_extesions,
                out_extensions.data());
            if (VK_SUCCESS != result)
            {
                ERRLOG("Failed to get extension: " << VkEnum_to_string(result));
                return Utilities::Failure;
            }

            return Utilities::Success;
        }

        Platform::int32 Implementation::Enumerate_layers(std::vector<VkLayerProperties>& out_layers) const
        {
            VkResult result;
            uint32_t n_layer_properties = 0;

            result = m_Functions.EnumerateInstanceLayerProperties(&n_layer_properties, nullptr);
            if (VK_SUCCESS != result)
            {
                ERRLOG("Failed to get layer properties number: " << VkEnum_to_string(result));
                return result;
            }

            out_layers.resize(n_layer_properties);
            result = m_Functions.EnumerateInstanceLayerProperties(&n_layer_properties, out_layers.data());
            if (VK_SUCCESS != result)
            {
                ERRLOG("Failed to get layer properties: " << VkEnum_to_string(result));
                return result;
            }

            return Utilities::Success;
        }

        Platform::int32 Implementation::Enumerate_layer_extensions(
            const char                               * layer_name,
                  std::vector<VkExtensionProperties> & out_extensions) const
        {
            VkResult result;
            uint32_t n_extesions = 0;

            /* Get number */
            result = m_Functions.EnumerateInstanceExtensionProperties(
                layer_name,
                &n_extesions,
                nullptr);
            if (VK_SUCCESS != result)
            {
                ERRLOG("Failed to get layer: " << layer_name << " extension number: " << VkEnum_to_string(result));
                return Utilities::Failure;
            }

            out_extensions.resize(n_extesions);

            result = m_Functions.EnumerateInstanceExtensionProperties(
                layer_name,
                &n_extesions,
                out_extensions.data());
            if (VK_SUCCESS != result)
            {
                ERRLOG("Failed to get layer: " << layer_name << " extension: " << VkEnum_to_string(result));
                return Utilities::Failure;
            }

            return Utilities::Success;
        }

        Instance * Implementation::Create_instance(
            const char                     * application_name,
                  Platform::uint32           application_version,
            const char                     * engine_name,
                  Platform::uint32           engine_version,
                  Platform::uint32           requested_vulkan_version,
                  std::vector<std::string> & layers_to_enable,
                  std::vector<std::string> & extensions_to_enable)
        {
            /* Allocate memory */
            std::auto_ptr<Instance> instance(new Instance);
            if (nullptr == instance.get())
            {
                ASSERT(0);
                ERRLOG("Failed to allocate memory");
                return nullptr;
            }

            this->Attach(instance.get());


            VkApplicationInfo application_info = {
                VK_STRUCTURE_TYPE_APPLICATION_INFO /* sType */,
                nullptr                            /* next */,
                application_name                   /* AppName */,
                application_version                /* App version */,
                engine_name                        /* Engine name */,
                engine_version                     /* Engine version*/,
                requested_vulkan_version           /* Requested version */
            };

            std::vector<const char *> layers;
            std::vector<const char *> extensions;

            uint32_t enabledLayerCount     = uint32_t(layers_to_enable.size());
            uint32_t enabledExtensionCount = uint32_t(layers_to_enable.size());

            const char* const* ppEnabledLayerNames     = nullptr;
            const char* const* ppEnabledExtensionNames = nullptr;


            if (0 != enabledLayerCount)
            {
                layers.reserve(enabledLayerCount);
                for (const auto & name : layers_to_enable)
                {
                    layers.push_back(name.c_str());
                }
                ppEnabledLayerNames = layers.data();
            }

            if (0 != enabledExtensionCount)
            {
                extensions.reserve(enabledExtensionCount);
                for (const auto & name : extensions_to_enable)
                {
                    extensions.push_back(name.c_str());
                }
                ppEnabledExtensionNames = extensions.data();
            }


            VkInstanceCreateInfo instance_create_info = {
                VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO /* VkStructureType             sType; */,
                nullptr                                /* const void*                 pNext; */,
                0                                      /* VkInstanceCreateFlags       flags; */,
                &application_info                      /* const VkApplicationInfo*    pApplicationInfo; */,
                enabledLayerCount                      /* uint32_t                    enabledLayerCount; */,
                ppEnabledLayerNames                    /* const char* const*          ppEnabledLayerNames; */,
                enabledExtensionCount                  /* uint32_t                    enabledExtensionCount; */,
                ppEnabledExtensionNames                /* const char* const*          ppEnabledExtensionNames; */
            };

            VkInstance vulkan_instance;
            VkResult result = m_Functions.CreateInstance(
                &instance_create_info,
                nullptr /* VkAllocationCallbacks* pAllocator */,
                &vulkan_instance);
            if (VK_SUCCESS != result)
            {
                ERRLOG("Failed to create vulkan instance: " << VkEnum_to_string(result));
                return nullptr;
            }

            auto err = instance->Init(
                vulkan_instance,
                extensions_to_enable);
            if (Utilities::Success != err)
            {
                ERRLOG("Failed to initialize instance: " << VkEnum_to_string(result));
                return nullptr;
            }


            return instance.release();
        }

        Platform::int32 Implementation::Select_layers(
            const std::vector<std::string>       & requested_layers_names,
            const std::vector<VkLayerProperties> & layers,
                  std::vector<std::string>       & out_layers_names)
        {
            bool found_all = true;

            out_layers_names.reserve(requested_layers_names.size());

            for (const auto & layer : layers)
            {
                bool found = false;

                for (const auto & name : requested_layers_names)
                {
                    const int compare_result = name.compare(layer.layerName);

                    if (0 == compare_result)
                    {
                        found = true;
                        out_layers_names.push_back(name);
                        break;
                    }
                }

                /* Not found will set found_all to false */
                found_all = found_all && found;
            }

            if (true == found_all)
            {
                return Utilities::Success;
            }
            else
            {
                return Utilities::Failure;
            }
        }

        Platform::int32 Implementation::Select_extensions(
            const std::vector<std::string>           & requested_extensions_names,
            const std::vector<VkExtensionProperties> & extensions,
                  std::vector<std::string>           & out_extension_names)
        {
            bool found_all = true;

            out_extension_names.reserve(requested_extensions_names.size());

            for (const auto & name : requested_extensions_names)
            {
                bool found = false;

                for (const auto & extension : extensions)
                {
                    const int compare_result = name.compare(extension.extensionName);

                    if (0 == compare_result)
                    {
                        found = true;
                        out_extension_names.push_back(name);
                        break;
                    }
                }

                /* Not found will set found_all to false */
                found_all = found_all && found;
            }

            if (true == found_all)
            {
                return Utilities::Success;
            }
            else
            {
                return Utilities::Failure;
            }
        }

        const char * Implementation::VkEnum_to_string(VkResult result)
        {
            const char * str = "Unkown";

            switch (result)
            {
                case VK_SUCCESS:                        str = "VK_SUCCESS";                        break;
                case VK_NOT_READY:                      str = "VK_NOT_READY";                      break;
                case VK_TIMEOUT:                        str = "VK_TIMEOUT";                        break;
                case VK_EVENT_SET:                      str = "VK_EVENT_SET";                      break;
                case VK_EVENT_RESET:                    str = "VK_EVENT_RESET";                    break;
                case VK_INCOMPLETE:                     str = "VK_INCOMPLETE";                     break;
                case VK_ERROR_OUT_OF_HOST_MEMORY:       str = "VK_ERROR_OUT_OF_HOST_MEMORY";       break;
                case VK_ERROR_OUT_OF_DEVICE_MEMORY:     str = "VK_ERROR_OUT_OF_DEVICE_MEMORY";     break;
                case VK_ERROR_INITIALIZATION_FAILED:    str = "VK_ERROR_INITIALIZATION_FAILED";    break;
                case VK_ERROR_DEVICE_LOST:              str = "VK_ERROR_DEVICE_LOST";              break;
                case VK_ERROR_MEMORY_MAP_FAILED:        str = "VK_ERROR_MEMORY_MAP_FAILED";        break;
                case VK_ERROR_LAYER_NOT_PRESENT:        str = "VK_ERROR_LAYER_NOT_PRESENT";        break;
                case VK_ERROR_EXTENSION_NOT_PRESENT:    str = "VK_ERROR_EXTENSION_NOT_PRESENT";    break;
                case VK_ERROR_FEATURE_NOT_PRESENT:      str = "VK_ERROR_FEATURE_NOT_PRESENT";      break;
                case VK_ERROR_INCOMPATIBLE_DRIVER:      str = "VK_ERROR_INCOMPATIBLE_DRIVER";      break;
                case VK_ERROR_TOO_MANY_OBJECTS:         str = "VK_ERROR_TOO_MANY_OBJECTS";         break;
                case VK_ERROR_FORMAT_NOT_SUPPORTED:     str = "VK_ERROR_FORMAT_NOT_SUPPORTED";     break;
                case VK_ERROR_FRAGMENTED_POOL:          str = "VK_ERROR_FRAGMENTED_POOL";          break;
                case VK_ERROR_SURFACE_LOST_KHR:         str = "VK_ERROR_SURFACE_LOST_KHR";         break;
                case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: str = "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR"; break;
                case VK_SUBOPTIMAL_KHR:                 str = "VK_SUBOPTIMAL_KHR";                 break;
                case VK_ERROR_OUT_OF_DATE_KHR:          str = "VK_ERROR_OUT_OF_DATE_KHR";          break;
                case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: str = "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR"; break;
                case VK_ERROR_VALIDATION_FAILED_EXT:    str = "VK_ERROR_VALIDATION_FAILED_EXT";    break;
                case VK_ERROR_INVALID_SHADER_NV:        str = "VK_ERROR_INVALID_SHADER_NV";        break;
                case VK_ERROR_OUT_OF_POOL_MEMORY_KHR:   str = "VK_ERROR_OUT_OF_POOL_MEMORY_KHR";   break;
                default:
                    ASSERT(0);
                    break;
            }

            return str;
        }

        const Loader * Implementation::Loader() const
        {
            return m_loader.get();
        }
    }
}
