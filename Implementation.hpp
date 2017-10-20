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
* @file Implementation.hpp
**/

#ifndef VULKAN_IMPLEMENTATION_HPP
#define VULKAN_IMPLEMENTATION_HPP


#include <Utilities\containers\IntrusiveList.hpp>

#include "Instance.hpp"


namespace Vulkan
{
    class Loader;

    namespace Version_1_0_0
    {
        class Implementation : public Containers::IntrusiveList::List<Instance>
        {
        public:
            struct Functions
            {
                PFN_vkGetInstanceProcAddr                  GetInstanceProcAddr;
                PFN_vkCreateInstance                       CreateInstance;
                PFN_vkEnumerateInstanceExtensionProperties EnumerateInstanceExtensionProperties;
                PFN_vkEnumerateInstanceLayerProperties     EnumerateInstanceLayerProperties;
            };


            Implementation();
            virtual ~Implementation();

            Platform::int32 Init(Vulkan::Loader & loader);
            void            Release();

            Platform::int32 Load_functions(Functions & out_functions) const;
            Platform::int32 Load_functions();

            Platform::int32 Enumerate_implementation_extensions(std::vector<VkExtensionProperties> & out_extensions) const;
            Platform::int32 Enumerate_layers(std::vector<VkLayerProperties> & out_layers) const;
            Platform::int32 Enumerate_layer_extensions(
                const char                               * layer_name,
                      std::vector<VkExtensionProperties> & out_extensions) const;

            Instance * Create_instance(
                const char                     * application_name,
                      Platform::uint32           application_version,
                const char                     * engine_name,
                      Platform::uint32           engine_version,
                      Platform::uint32           requested_vulkan_version,
                      std::vector<std::string> & layers_to_enable,
                      std::vector<std::string> & extensions_to_enable);
            

            /*  */
            const Loader * Loader() const;


            /*  */
            static Platform::int32 Select_layers(
                const std::vector<std::string>       & requested_layers_names,
                const std::vector<VkLayerProperties> & layers,
                      std::vector<std::string>       & out_layers_names);
            static Platform::int32 Select_extensions(
                const std::vector<std::string>           & requested_extensions_names,
                const std::vector<VkExtensionProperties> & extensions,
                      std::vector<std::string>           & out_extension_names);

            /*  */
            static const char * VkEnum_to_string(VkResult result);





            Functions m_Functions;


        private:
            ::Vulkan::Loader * m_loader;
        };
    }
}

#endif /* VULKAN_IMPLEMENTATION_HPP */
