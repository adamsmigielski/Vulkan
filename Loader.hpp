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
* @file YYY.hpp
**/

#ifndef VULKAN_LOADER_HPP
#define VULKAN_LOADER_HPP

#include <vulkan\vulkan.h>

namespace Vulkan
{
    struct Entry_functions
    {
        PFN_vkGetInstanceProcAddr                  GetInstanceProcAddr;
        PFN_vkCreateInstance                       CreateInstance;
        PFN_vkEnumerateInstanceExtensionProperties EnumerateInstanceExtensionProperties;
        PFN_vkEnumerateInstanceLayerProperties     EnumerateInstanceLayerProperties;
    };

    struct Instance_functions
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

    class Loader
    {
    public:
        virtual Platform::proc_t Get_proc_address(const char * name) = 0;

        Platform::int32 Load_entry_functions(
            Entry_functions & out_functions) const;

        Platform::int32 Load_instance_functions(
                  VkInstance           instance,
            const Entry_functions    & entry_functions,
                  Instance_functions & out_functions) const;
    };

#if 0

    /* Callbacks */
    extern PFN_vkAllocationFunction AllocationFunction;
    extern PFN_vkReallocationFunction ReallocationFunction;
    extern PFN_vkFreeFunction FreeFunction;
    extern PFN_vkInternalAllocationNotification InternalAllocationNotification;
    extern PFN_vkInternalFreeNotification InternalFreeNotification;

    /* Global entry points */

    /* Instance entry points */
    
    extern PFN_vkDestroyDevice DestroyDevice;
    extern PFN_vkGetDeviceQueue GetDeviceQueue;
    extern PFN_vkQueueSubmit QueueSubmit;
    extern PFN_vkQueueWaitIdle QueueWaitIdle;
    extern PFN_vkDeviceWaitIdle DeviceWaitIdle;
    extern PFN_vkAllocateMemory AllocateMemory;
    extern PFN_vkFreeMemory FreeMemory;
    extern PFN_vkMapMemory MapMemory;
    extern PFN_vkUnmapMemory UnmapMemory;
    extern PFN_vkFlushMappedMemoryRanges FlushMappedMemoryRanges;
    extern PFN_vkInvalidateMappedMemoryRanges InvalidateMappedMemoryRanges;
    extern PFN_vkGetDeviceMemoryCommitment GetDeviceMemoryCommitment;
    extern PFN_vkBindBufferMemory BindBufferMemory;
    extern PFN_vkBindImageMemory BindImageMemory;
    extern PFN_vkGetBufferMemoryRequirements GetBufferMemoryRequirements;
    extern PFN_vkGetImageMemoryRequirements GetImageMemoryRequirements;
    extern PFN_vkGetImageSparseMemoryRequirements GetImageSparseMemoryRequirements;
    extern PFN_vkGetPhysicalDeviceSparseImageFormatProperties GetPhysicalDeviceSparseImageFormatProperties;
    extern PFN_vkQueueBindSparse QueueBindSparse;
    extern PFN_vkCreateFence CreateFence;
    extern PFN_vkDestroyFence DestroyFence;
    extern PFN_vkResetFences ResetFences;
    extern PFN_vkGetFenceStatus GetFenceStatus;
    extern PFN_vkWaitForFences WaitForFences;
    extern PFN_vkCreateSemaphore CreateSemaphore;
    extern PFN_vkDestroySemaphore DestroySemaphore;
    extern PFN_vkCreateEvent CreateEvent;
    extern PFN_vkDestroyEvent DestroyEvent;
    extern PFN_vkGetEventStatus GetEventStatus;
    extern PFN_vkSetEvent SetEvent;
    extern PFN_vkResetEvent ResetEvent;
    extern PFN_vkCreateQueryPool CreateQueryPool;
    extern PFN_vkDestroyQueryPool DestroyQueryPool;
    extern PFN_vkGetQueryPoolResults GetQueryPoolResults;
    extern PFN_vkCreateBuffer CreateBuffer;
    extern PFN_vkDestroyBuffer DestroyBuffer;
    extern PFN_vkCreateBufferView CreateBufferView;
    extern PFN_vkDestroyBufferView DestroyBufferView;
    extern PFN_vkCreateImage CreateImage;
    extern PFN_vkDestroyImage DestroyImage;
    extern PFN_vkGetImageSubresourceLayout GetImageSubresourceLayout;
    extern PFN_vkCreateImageView CreateImageView;
    extern PFN_vkDestroyImageView DestroyImageView;
    extern PFN_vkCreateShaderModule CreateShaderModule;
    extern PFN_vkDestroyShaderModule DestroyShaderModule;
    extern PFN_vkCreatePipelineCache CreatePipelineCache;
    extern PFN_vkDestroyPipelineCache DestroyPipelineCache;
    extern PFN_vkGetPipelineCacheData GetPipelineCacheData;
    extern PFN_vkMergePipelineCaches MergePipelineCaches;
    extern PFN_vkCreateGraphicsPipelines CreateGraphicsPipelines;
    extern PFN_vkCreateComputePipelines CreateComputePipelines;
    extern PFN_vkDestroyPipeline DestroyPipeline;
    extern PFN_vkCreatePipelineLayout CreatePipelineLayout;
    extern PFN_vkDestroyPipelineLayout DestroyPipelineLayout;
    extern PFN_vkCreateSampler CreateSampler;
    extern PFN_vkDestroySampler DestroySampler;
    extern PFN_vkCreateDescriptorSetLayout CreateDescriptorSetLayout;
    extern PFN_vkDestroyDescriptorSetLayout DestroyDescriptorSetLayout;
    extern PFN_vkCreateDescriptorPool CreateDescriptorPool;
    extern PFN_vkDestroyDescriptorPool DestroyDescriptorPool;
    extern PFN_vkResetDescriptorPool ResetDescriptorPool;
    extern PFN_vkAllocateDescriptorSets AllocateDescriptorSets;
    extern PFN_vkFreeDescriptorSets FreeDescriptorSets;
    extern PFN_vkUpdateDescriptorSets UpdateDescriptorSets;
    extern PFN_vkCreateFramebuffer CreateFramebuffer;
    extern PFN_vkDestroyFramebuffer DestroyFramebuffer;
    extern PFN_vkCreateRenderPass CreateRenderPass;
    extern PFN_vkDestroyRenderPass DestroyRenderPass;
    extern PFN_vkGetRenderAreaGranularity GetRenderAreaGranularity;
    extern PFN_vkCreateCommandPool CreateCommandPool;
    extern PFN_vkDestroyCommandPool DestroyCommandPool;
    extern PFN_vkResetCommandPool ResetCommandPool;
    extern PFN_vkAllocateCommandBuffers AllocateCommandBuffers;
    extern PFN_vkFreeCommandBuffers FreeCommandBuffers;
    extern PFN_vkBeginCommandBuffer BeginCommandBuffer;
    extern PFN_vkEndCommandBuffer EndCommandBuffer;
    extern PFN_vkResetCommandBuffer ResetCommandBuffer;
    extern PFN_vkCmdBindPipeline CmdBindPipeline;
    extern PFN_vkCmdSetViewport CmdSetViewport;
    extern PFN_vkCmdSetScissor CmdSetScissor;
    extern PFN_vkCmdSetLineWidth CmdSetLineWidth;
    extern PFN_vkCmdSetDepthBias CmdSetDepthBias;
    extern PFN_vkCmdSetBlendConstants CmdSetBlendConstants;
    extern PFN_vkCmdSetDepthBounds CmdSetDepthBounds;
    extern PFN_vkCmdSetStencilCompareMask CmdSetStencilCompareMask;
    extern PFN_vkCmdSetStencilWriteMask CmdSetStencilWriteMask;
    extern PFN_vkCmdSetStencilReference CmdSetStencilReference;
    extern PFN_vkCmdBindDescriptorSets CmdBindDescriptorSets;
    extern PFN_vkCmdBindIndexBuffer CmdBindIndexBuffer;
    extern PFN_vkCmdBindVertexBuffers CmdBindVertexBuffers;
    extern PFN_vkCmdDraw CmdDraw;
    extern PFN_vkCmdDrawIndexed CmdDrawIndexed;
    extern PFN_vkCmdDrawIndirect CmdDrawIndirect;
    extern PFN_vkCmdDrawIndexedIndirect CmdDrawIndexedIndirect;
    extern PFN_vkCmdDispatch CmdDispatch;
    extern PFN_vkCmdDispatchIndirect CmdDispatchIndirect;
    extern PFN_vkCmdCopyBuffer CmdCopyBuffer;
    extern PFN_vkCmdCopyImage CmdCopyImage;
    extern PFN_vkCmdBlitImage CmdBlitImage;
    extern PFN_vkCmdCopyBufferToImage CmdCopyBufferToImage;
    extern PFN_vkCmdCopyImageToBuffer CmdCopyImageToBuffer;
    extern PFN_vkCmdUpdateBuffer CmdUpdateBuffer;
    extern PFN_vkCmdFillBuffer CmdFillBuffer;
    extern PFN_vkCmdClearColorImage CmdClearColorImage;
    extern PFN_vkCmdClearDepthStencilImage CmdClearDepthStencilImage;
    extern PFN_vkCmdClearAttachments CmdClearAttachments;
    extern PFN_vkCmdResolveImage CmdResolveImage;
    extern PFN_vkCmdSetEvent CmdSetEvent;
    extern PFN_vkCmdResetEvent CmdResetEvent;
    extern PFN_vkCmdWaitEvents CmdWaitEvents;
    extern PFN_vkCmdPipelineBarrier CmdPipelineBarrier;
    extern PFN_vkCmdBeginQuery CmdBeginQuery;
    extern PFN_vkCmdEndQuery CmdEndQuery;
    extern PFN_vkCmdResetQueryPool CmdResetQueryPool;
    extern PFN_vkCmdWriteTimestamp CmdWriteTimestamp;
    extern PFN_vkCmdCopyQueryPoolResults CmdCopyQueryPoolResults;
    extern PFN_vkCmdPushConstants CmdPushConstants;
    extern PFN_vkCmdBeginRenderPass CmdBeginRenderPass;
    extern PFN_vkCmdNextSubpass CmdNextSubpass;
    extern PFN_vkCmdEndRenderPass CmdEndRenderPass;
    extern PFN_vkCmdExecuteCommands CmdExecuteCommands;
    extern PFN_vkDestroySurfaceKHR DestroySurfaceKHR;
    extern PFN_vkGetPhysicalDeviceSurfaceSupportKHR GetPhysicalDeviceSurfaceSupportKHR;
    extern PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR GetPhysicalDeviceSurfaceCapabilitiesKHR;
    extern PFN_vkGetPhysicalDeviceSurfaceFormatsKHR GetPhysicalDeviceSurfaceFormatsKHR;
    extern PFN_vkCreateSwapchainKHR CreateSwapchainKHR;
    extern PFN_vkDestroySwapchainKHR DestroySwapchainKHR;
    extern PFN_vkGetSwapchainImagesKHR GetSwapchainImagesKHR;
    extern PFN_vkAcquireNextImageKHR AcquireNextImageKHR;
    extern PFN_vkGetPhysicalDeviceDisplayPropertiesKHR GetPhysicalDeviceDisplayPropertiesKHR;
    extern PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR GetPhysicalDeviceDisplayPlanePropertiesKHR;
    extern PFN_vkGetDisplayPlaneSupportedDisplaysKHR GetDisplayPlaneSupportedDisplaysKHR;
    extern PFN_vkGetDisplayModePropertiesKHR GetDisplayModePropertiesKHR;
    extern PFN_vkCreateDisplayModeKHR CreateDisplayModeKHR;
    extern PFN_vkGetDisplayPlaneCapabilitiesKHR GetDisplayPlaneCapabilitiesKHR;
    extern PFN_vkCreateSharedSwapchainsKHR CreateSharedSwapchainsKHR;
#ifdef VK_USE_PLATFORM_XLIB_KHR
    extern PFN_vkCreateXlibSurfaceKHR CreateXlibSurfaceKHR;
    extern PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR GetPhysicalDeviceXlibPresentationSupportKHR;
#endif /* VK_USE_PLATFORM_XLIB_KHR */
#ifdef VK_USE_PLATFORM_XCB_KHR
    extern PFN_vkCreateXcbSurfaceKHR CreateXcbSurfaceKHR;
    extern PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR GetPhysicalDeviceXcbPresentationSupportKHR;
#endif /* VK_USE_PLATFORM_XCB_KHR */
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
    extern PFN_vkCreateWaylandSurfaceKHR CreateWaylandSurfaceKHR;
    extern PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR GetPhysicalDeviceWaylandPresentationSupportKHR;
#endif /* VK_USE_PLATFORM_WAYLAND_KHR */
#ifdef VK_USE_PLATFORM_MIR_KHR
    extern PFN_vkCreateMirSurfaceKHR CreateMirSurfaceKHR;
    extern PFN_vkGetPhysicalDeviceMirPresentationSupportKHR GetPhysicalDeviceMirPresentationSupportKHR;
#endif /* VK_USE_PLATFORM_MIR_KHR */
#ifdef VK_USE_PLATFORM_ANDROID_KHR
    extern PFN_vkCreateAndroidSurfaceKHR CreateAndroidSurfaceKHR;
#endif /* VK_USE_PLATFORM_ANDROID_KHR */
#ifdef VK_USE_PLATFORM_WIN32_KHR
    extern PFN_vkCreateWin32SurfaceKHR CreateWin32SurfaceKHR;
    extern PFN_vkGetPhysicalDeviceFeatures2KHR GetPhysicalDeviceFeatures2KHR;
#endif /* VK_USE_PLATFORM_WIN32_KHR */
    extern PFN_vkGetPhysicalDeviceProperties2KHR GetPhysicalDeviceProperties2KHR;
    extern PFN_vkGetPhysicalDeviceFormatProperties2KHR GetPhysicalDeviceFormatProperties2KHR;
    extern PFN_vkGetPhysicalDeviceImageFormatProperties2KHR GetPhysicalDeviceImageFormatProperties2KHR;
    extern PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR GetPhysicalDeviceQueueFamilyProperties2KHR;
    extern PFN_vkGetPhysicalDeviceMemoryProperties2KHR GetPhysicalDeviceMemoryProperties2KHR;
    extern PFN_vkTrimCommandPoolKHR TrimCommandPoolKHR;
    extern PFN_vkCreateDebugReportCallbackEXT CreateDebugReportCallbackEXT;
    extern PFN_vkDestroyDebugReportCallbackEXT DestroyDebugReportCallbackEXT;
    extern PFN_vkDebugMarkerSetObjectTagEXT DebugMarkerSetObjectTagEXT;
    extern PFN_vkDebugMarkerSetObjectNameEXT DebugMarkerSetObjectNameEXT;
    extern PFN_vkCmdDebugMarkerBeginEXT CmdDebugMarkerBeginEXT;
    extern PFN_vkCmdDebugMarkerEndEXT CmdDebugMarkerEndEXT;
    extern PFN_vkCmdDrawIndirectCountAMD CmdDrawIndirectCountAMD;
    extern PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV GetPhysicalDeviceExternalImageFormatPropertiesNV;
#ifdef VK_USE_PLATFORM_VI_NN
    extern PFN_vkCreateViSurfaceNN CreateViSurfaceNN;
#endif /* VK_USE_PLATFORM_VI_NN */
    extern PFN_vkCmdProcessCommandsNVX CmdProcessCommandsNVX;
    extern PFN_vkCmdReserveSpaceForCommandsNVX CmdReserveSpaceForCommandsNVX;
    extern PFN_vkCreateIndirectCommandsLayoutNVX CreateIndirectCommandsLayoutNVX;
    extern PFN_vkDestroyIndirectCommandsLayoutNVX DestroyIndirectCommandsLayoutNVX;
    extern PFN_vkCreateObjectTableNVX CreateObjectTableNVX;
    extern PFN_vkDestroyObjectTableNVX DestroyObjectTableNVX;
    extern PFN_vkRegisterObjectsNVX RegisterObjectsNVX;
    extern PFN_vkUnregisterObjectsNVX UnregisterObjectsNVX;
    extern PFN_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX GetPhysicalDeviceGeneratedCommandsPropertiesNVX;
    extern PFN_vkReleaseDisplayEXT ReleaseDisplayEXT;
#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
    extern PFN_vkAcquireXlibDisplayEXT AcquireXlibDisplayEXT;
#endif /* VK_USE_PLATFORM_XLIB_XRANDR_EXT */
    extern PFN_vkDisplayPowerControlEXT DisplayPowerControlEXT;
    extern PFN_vkRegisterDeviceEventEXT RegisterDeviceEventEXT;
    extern PFN_vkRegisterDisplayEventEXT RegisterDisplayEventEXT;
    extern PFN_vkGetSwapchainCounterEXT GetSwapchainCounterEXT;

#endif /* 0 */
}

#endif VULKAN_LOADER_HPP
