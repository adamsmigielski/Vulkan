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
* @file Device.hpp
**/

#ifndef VULKAN_DEVICE_HPP
#define VULKAN_DEVICE_HPP


#include <Utilities\containers\IntrusiveList.hpp>


namespace Vulkan
{
    namespace Version_1_0_0
    {
        class Instance;

        class Device
            : public Containers::IntrusiveList::Node<Device>
        {
        public:
            struct Functions
            {
                PFN_vkDestroyDevice                                    DestroyDevice;
                PFN_vkGetDeviceQueue                                   GetDeviceQueue;
                PFN_vkQueueSubmit                                      QueueSubmit;
                PFN_vkQueueWaitIdle                                    QueueWaitIdle;
                PFN_vkDeviceWaitIdle                                   DeviceWaitIdle;
                PFN_vkAllocateMemory                                   AllocateMemory;
                PFN_vkFreeMemory                                       FreeMemory;
                PFN_vkMapMemory                                        MapMemory;
                PFN_vkUnmapMemory                                      UnmapMemory;
                PFN_vkFlushMappedMemoryRanges                          FlushMappedMemoryRanges;
                PFN_vkInvalidateMappedMemoryRanges                     InvalidateMappedMemoryRanges;
                PFN_vkGetDeviceMemoryCommitment                        GetDeviceMemoryCommitment;
                PFN_vkBindBufferMemory                                 BindBufferMemory;
                PFN_vkBindImageMemory                                  BindImageMemory;
                PFN_vkGetBufferMemoryRequirements                      GetBufferMemoryRequirements;
                PFN_vkGetImageMemoryRequirements                       GetImageMemoryRequirements;
                PFN_vkGetImageSparseMemoryRequirements                 GetImageSparseMemoryRequirements;
                PFN_vkGetPhysicalDeviceSparseImageFormatProperties     GetPhysicalDeviceSparseImageFormatProperties;
                PFN_vkQueueBindSparse                                  QueueBindSparse;
                PFN_vkCreateFence                                      CreateFence;
                PFN_vkDestroyFence                                     DestroyFence;
                PFN_vkResetFences                                      ResetFences;
                PFN_vkGetFenceStatus                                   GetFenceStatus;
                PFN_vkWaitForFences                                    WaitForFences;
                PFN_vkCreateSemaphore                                  CreateSemaphore;
                PFN_vkDestroySemaphore                                 DestroySemaphore;
                PFN_vkCreateEvent                                      CreateEvent;
                PFN_vkDestroyEvent                                     DestroyEvent;
                PFN_vkGetEventStatus                                   GetEventStatus;
                PFN_vkSetEvent                                         SetEvent;
                PFN_vkResetEvent                                       ResetEvent;
                PFN_vkCreateQueryPool                                  CreateQueryPool;
                PFN_vkDestroyQueryPool                                 DestroyQueryPool;
                PFN_vkGetQueryPoolResults                              GetQueryPoolResults;
                PFN_vkCreateBuffer                                     CreateBuffer;
                PFN_vkDestroyBuffer                                    DestroyBuffer;
                PFN_vkCreateBufferView                                 CreateBufferView;
                PFN_vkDestroyBufferView                                DestroyBufferView;
                PFN_vkCreateImage                                      CreateImage;
                PFN_vkDestroyImage                                     DestroyImage;
                PFN_vkGetImageSubresourceLayout                        GetImageSubresourceLayout;
                PFN_vkCreateImageView                                  CreateImageView;
                PFN_vkDestroyImageView                                 DestroyImageView;
                PFN_vkCreateShaderModule                               CreateShaderModule;
                PFN_vkDestroyShaderModule                              DestroyShaderModule;
                PFN_vkCreatePipelineCache                              CreatePipelineCache;
                PFN_vkDestroyPipelineCache                             DestroyPipelineCache;
                PFN_vkGetPipelineCacheData                             GetPipelineCacheData;
                PFN_vkMergePipelineCaches                              MergePipelineCaches;
                PFN_vkCreateGraphicsPipelines                          CreateGraphicsPipelines;
                PFN_vkCreateComputePipelines                           CreateComputePipelines;
                PFN_vkDestroyPipeline                                  DestroyPipeline;
                PFN_vkCreatePipelineLayout                             CreatePipelineLayout;
                PFN_vkDestroyPipelineLayout                            DestroyPipelineLayout;
                PFN_vkCreateSampler                                    CreateSampler;
                PFN_vkDestroySampler                                   DestroySampler;
                PFN_vkCreateDescriptorSetLayout                        CreateDescriptorSetLayout;
                PFN_vkDestroyDescriptorSetLayout                       DestroyDescriptorSetLayout;
                PFN_vkCreateDescriptorPool                             CreateDescriptorPool;
                PFN_vkDestroyDescriptorPool                            DestroyDescriptorPool;
                PFN_vkResetDescriptorPool                              ResetDescriptorPool;
                PFN_vkAllocateDescriptorSets                           AllocateDescriptorSets;
                PFN_vkFreeDescriptorSets                               FreeDescriptorSets;
                PFN_vkUpdateDescriptorSets                             UpdateDescriptorSets;
                PFN_vkCreateFramebuffer                                CreateFramebuffer;
                PFN_vkDestroyFramebuffer                               DestroyFramebuffer;
                PFN_vkCreateRenderPass                                 CreateRenderPass;
                PFN_vkDestroyRenderPass                                DestroyRenderPass;
                PFN_vkGetRenderAreaGranularity                         GetRenderAreaGranularity;
                PFN_vkCreateCommandPool                                CreateCommandPool;
                PFN_vkDestroyCommandPool                               DestroyCommandPool;
                PFN_vkResetCommandPool                                 ResetCommandPool;
                PFN_vkAllocateCommandBuffers                           AllocateCommandBuffers;
                PFN_vkFreeCommandBuffers                               FreeCommandBuffers;
                PFN_vkBeginCommandBuffer                               BeginCommandBuffer;
                PFN_vkEndCommandBuffer                                 EndCommandBuffer;
                PFN_vkResetCommandBuffer                               ResetCommandBuffer;
                PFN_vkCmdBindPipeline                                  CmdBindPipeline;
                PFN_vkCmdSetViewport                                   CmdSetViewport;
                PFN_vkCmdSetScissor                                    CmdSetScissor;
                PFN_vkCmdSetLineWidth                                  CmdSetLineWidth;
                PFN_vkCmdSetDepthBias                                  CmdSetDepthBias;
                PFN_vkCmdSetBlendConstants                             CmdSetBlendConstants;
                PFN_vkCmdSetDepthBounds                                CmdSetDepthBounds;
                PFN_vkCmdSetStencilCompareMask                         CmdSetStencilCompareMask;
                PFN_vkCmdSetStencilWriteMask                           CmdSetStencilWriteMask;
                PFN_vkCmdSetStencilReference                           CmdSetStencilReference;
                PFN_vkCmdBindDescriptorSets                            CmdBindDescriptorSets;
                PFN_vkCmdBindIndexBuffer                               CmdBindIndexBuffer;
                PFN_vkCmdBindVertexBuffers                             CmdBindVertexBuffers;
                PFN_vkCmdDraw                                          CmdDraw;
                PFN_vkCmdDrawIndexed                                   CmdDrawIndexed;
                PFN_vkCmdDrawIndirect                                  CmdDrawIndirect;
                PFN_vkCmdDrawIndexedIndirect                           CmdDrawIndexedIndirect;
                PFN_vkCmdDispatch                                      CmdDispatch;
                PFN_vkCmdDispatchIndirect                              CmdDispatchIndirect;
                PFN_vkCmdCopyBuffer                                    CmdCopyBuffer;
                PFN_vkCmdCopyImage                                     CmdCopyImage;
                PFN_vkCmdBlitImage                                     CmdBlitImage;
                PFN_vkCmdCopyBufferToImage                             CmdCopyBufferToImage;
                PFN_vkCmdCopyImageToBuffer                             CmdCopyImageToBuffer;
                PFN_vkCmdUpdateBuffer                                  CmdUpdateBuffer;
                PFN_vkCmdFillBuffer                                    CmdFillBuffer;
                PFN_vkCmdClearColorImage                               CmdClearColorImage;
                PFN_vkCmdClearDepthStencilImage                        CmdClearDepthStencilImage;
                PFN_vkCmdClearAttachments                              CmdClearAttachments;
                PFN_vkCmdResolveImage                                  CmdResolveImage;
                PFN_vkCmdSetEvent                                      CmdSetEvent;
                PFN_vkCmdResetEvent                                    CmdResetEvent;
                PFN_vkCmdWaitEvents                                    CmdWaitEvents;
                PFN_vkCmdPipelineBarrier                               CmdPipelineBarrier;
                PFN_vkCmdBeginQuery                                    CmdBeginQuery;
                PFN_vkCmdEndQuery                                      CmdEndQuery;
                PFN_vkCmdResetQueryPool                                CmdResetQueryPool;
                PFN_vkCmdWriteTimestamp                                CmdWriteTimestamp;
                PFN_vkCmdCopyQueryPoolResults                          CmdCopyQueryPoolResults;
                PFN_vkCmdPushConstants                                 CmdPushConstants;
                PFN_vkCmdBeginRenderPass                               CmdBeginRenderPass;
                PFN_vkCmdNextSubpass                                   CmdNextSubpass;
                PFN_vkCmdEndRenderPass                                 CmdEndRenderPass;
                PFN_vkCmdExecuteCommands                               CmdExecuteCommands;
            };

            struct WSI
            {
                PFN_vkDestroySurfaceKHR                                DestroySurfaceKHR;
                PFN_vkGetPhysicalDeviceSurfaceSupportKHR               GetPhysicalDeviceSurfaceSupportKHR;
                PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR          GetPhysicalDeviceSurfaceCapabilitiesKHR;
                PFN_vkGetPhysicalDeviceSurfaceFormatsKHR               GetPhysicalDeviceSurfaceFormatsKHR;
                PFN_vkCreateSwapchainKHR                               CreateSwapchainKHR;
                PFN_vkDestroySwapchainKHR                              DestroySwapchainKHR;
                PFN_vkGetSwapchainImagesKHR                            GetSwapchainImagesKHR;
                PFN_vkAcquireNextImageKHR                              AcquireNextImageKHR;
                PFN_vkGetPhysicalDeviceDisplayPropertiesKHR            GetPhysicalDeviceDisplayPropertiesKHR;
                PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR       GetPhysicalDeviceDisplayPlanePropertiesKHR;
                PFN_vkGetDisplayPlaneSupportedDisplaysKHR              GetDisplayPlaneSupportedDisplaysKHR;
                PFN_vkGetDisplayModePropertiesKHR                      GetDisplayModePropertiesKHR;
                PFN_vkCreateDisplayModeKHR                             CreateDisplayModeKHR;
                PFN_vkGetDisplayPlaneCapabilitiesKHR                   GetDisplayPlaneCapabilitiesKHR;
                PFN_vkCreateSharedSwapchainsKHR                        CreateSharedSwapchainsKHR;
#ifdef                                                     VK_USE_PLATFORM_XLIB_KHR
                PFN_vkCreateXlibSurfaceKHR                             CreateXlibSurfaceKHR;
                PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR      GetPhysicalDeviceXlibPresentationSupportKHR;
#endif                                                     /* VK_USE_PLATFORM_XLIB_KHR */
#ifdef                                                     VK_USE_PLATFORM_XCB_KHR
                PFN_vkCreateXcbSurfaceKHR                              CreateXcbSurfaceKHR;
                PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR       GetPhysicalDeviceXcbPresentationSupportKHR;
#endif                                                     /* VK_USE_PLATFORM_XCB_KHR */
#ifdef                                                     VK_USE_PLATFORM_WAYLAND_KHR
                PFN_vkCreateWaylandSurfaceKHR                          CreateWaylandSurfaceKHR;
                PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR   GetPhysicalDeviceWaylandPresentationSupportKHR;
#endif                                                     /* VK_USE_PLATFORM_WAYLAND_KHR */
#ifdef                                                     VK_USE_PLATFORM_MIR_KHR
                PFN_vkCreateMirSurfaceKHR                              CreateMirSurfaceKHR;
                PFN_vkGetPhysicalDeviceMirPresentationSupportKHR       GetPhysicalDeviceMirPresentationSupportKHR;
#endif                                                     /* VK_USE_PLATFORM_MIR_KHR */
#ifdef                                                     VK_USE_PLATFORM_ANDROID_KHR
                PFN_vkCreateAndroidSurfaceKHR                          CreateAndroidSurfaceKHR;
#endif                                                     /* VK_USE_PLATFORM_ANDROID_KHR */
#ifdef                                                     VK_USE_PLATFORM_WIN32_KHR
                PFN_vkCreateWin32SurfaceKHR                            CreateWin32SurfaceKHR;
                PFN_vkGetPhysicalDeviceFeatures2KHR                    GetPhysicalDeviceFeatures2KHR;
#endif                                                     /* VK_USE_PLATFORM_WIN32_KHR */
                PFN_vkGetPhysicalDeviceProperties2KHR                  GetPhysicalDeviceProperties2KHR;
                PFN_vkGetPhysicalDeviceFormatProperties2KHR            GetPhysicalDeviceFormatProperties2KHR;
                PFN_vkGetPhysicalDeviceImageFormatProperties2KHR       GetPhysicalDeviceImageFormatProperties2KHR;
                PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR       GetPhysicalDeviceQueueFamilyProperties2KHR;
                PFN_vkGetPhysicalDeviceMemoryProperties2KHR            GetPhysicalDeviceMemoryProperties2KHR;
                PFN_vkTrimCommandPoolKHR                               TrimCommandPoolKHR;
                PFN_vkCreateDebugReportCallbackEXT                     CreateDebugReportCallbackEXT;
                PFN_vkDestroyDebugReportCallbackEXT                    DestroyDebugReportCallbackEXT;
                PFN_vkDebugMarkerSetObjectTagEXT                       DebugMarkerSetObjectTagEXT;
                PFN_vkDebugMarkerSetObjectNameEXT                      DebugMarkerSetObjectNameEXT;
                PFN_vkCmdDebugMarkerBeginEXT                           CmdDebugMarkerBeginEXT;
                PFN_vkCmdDebugMarkerEndEXT                             CmdDebugMarkerEndEXT;
                PFN_vkCmdDrawIndirectCountAMD                          CmdDrawIndirectCountAMD;
                PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV GetPhysicalDeviceExternalImageFormatPropertiesNV;
#ifdef                                                     VK_USE_PLATFORM_VI_NN
                PFN_vkCreateViSurfaceNN                                CreateViSurfaceNN;
#endif                                                     /* VK_USE_PLATFORM_VI_NN */
                PFN_vkCmdProcessCommandsNVX                            CmdProcessCommandsNVX;
                PFN_vkCmdReserveSpaceForCommandsNVX                    CmdReserveSpaceForCommandsNVX;
                PFN_vkCreateIndirectCommandsLayoutNVX                  CreateIndirectCommandsLayoutNVX;
                PFN_vkDestroyIndirectCommandsLayoutNVX                 DestroyIndirectCommandsLayoutNVX;
                PFN_vkCreateObjectTableNVX                             CreateObjectTableNVX;
                PFN_vkDestroyObjectTableNVX                            DestroyObjectTableNVX;
                PFN_vkRegisterObjectsNVX                               RegisterObjectsNVX;
                PFN_vkUnregisterObjectsNVX                             UnregisterObjectsNVX;
                PFN_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX  GetPhysicalDeviceGeneratedCommandsPropertiesNVX;
                PFN_vkReleaseDisplayEXT                                ReleaseDisplayEXT;
#ifdef                                                     VK_USE_PLATFORM_XLIB_XRANDR_EXT
                PFN_vkAcquireXlibDisplayEXT                            AcquireXlibDisplayEXT;
#endif                                                     /* VK_USE_PLATFORM_XLIB_XRANDR_EXT */
                PFN_vkDisplayPowerControlEXT                           DisplayPowerControlEXT;
                PFN_vkRegisterDeviceEventEXT                           RegisterDeviceEventEXT;
                PFN_vkRegisterDisplayEventEXT                          RegisterDisplayEventEXT;
                PFN_vkGetSwapchainCounterEXT                           GetSwapchainCounterEXT;
            };

            Device();
            virtual ~Device();

            Platform::int32 Init(VkDevice device);
            void Release();

            Platform::int32 Load_functions(
                VkDevice    device,
                Functions & out_functions) const;
            Platform::int32 Load_functions();



            const Instance * Get_instance() const;
            Instance * Get_instance();

            VkDevice Get_device() const;


            Functions m_Functions;



            private:
                VkDevice m_device;
        };
    }
}

#endif /* VULKAN_DEVICE_HPP */