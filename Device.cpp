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
#include "Instance.hpp"


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

            return Load_functions();
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

        static Platform::proc_t load_device_function(
            const Instance::Functions & functions,
            VkDevice                    device,
            const char *                name,
            bool                        check)
        {
            Platform::proc_t function = (Platform::proc_t) functions.GetDeviceProcAddr(device, name);

            if (nullptr == function)
            {
                ASSERT(0);
                ERRLOG("Failed to load function: " << name);
                check = false;
            }
            else
            {
                DEBUGLOG("Loaded function: " << name);
            }

            return function;
        }

        Platform::int32 Device::Load_functions(
            VkDevice            device,
            Device::Functions & out_functions) const
        {
            bool check = true;

            auto instance = Get_instance();
            if (nullptr == instance)
            {
                ASSERT(0);
                ERRLOG("Invliad object");
                return Utilities::Invalid_object;
            }
            const auto & functions = instance->m_Functions;

            out_functions.DestroyDevice                                = (PFN_vkDestroyDevice)                                load_device_function(functions, device, "vkDestroyDevice",                                check);
            out_functions.GetDeviceQueue                               = (PFN_vkGetDeviceQueue)                               load_device_function(functions, device, "vkGetDeviceQueue",                               check);
            out_functions.QueueSubmit                                  = (PFN_vkQueueSubmit)                                  load_device_function(functions, device, "vkQueueSubmit",                                  check);
            out_functions.QueueWaitIdle                                = (PFN_vkQueueWaitIdle)                                load_device_function(functions, device, "vkQueueWaitIdle",                                check);
            out_functions.DeviceWaitIdle                               = (PFN_vkDeviceWaitIdle)                               load_device_function(functions, device, "vkDeviceWaitIdle",                               check);
            out_functions.AllocateMemory                               = (PFN_vkAllocateMemory)                               load_device_function(functions, device, "vkAllocateMemory",                               check);
            out_functions.FreeMemory                                   = (PFN_vkFreeMemory)                                   load_device_function(functions, device, "vkFreeMemory",                                   check);
            out_functions.MapMemory                                    = (PFN_vkMapMemory)                                    load_device_function(functions, device, "vkMapMemory",                                    check);
            out_functions.UnmapMemory                                  = (PFN_vkUnmapMemory)                                  load_device_function(functions, device, "vkUnmapMemory",                                  check);
            out_functions.FlushMappedMemoryRanges                      = (PFN_vkFlushMappedMemoryRanges)                      load_device_function(functions, device, "vkFlushMappedMemoryRanges",                      check);
            out_functions.InvalidateMappedMemoryRanges                 = (PFN_vkInvalidateMappedMemoryRanges)                 load_device_function(functions, device, "vkInvalidateMappedMemoryRanges",                 check);
            out_functions.GetDeviceMemoryCommitment                    = (PFN_vkGetDeviceMemoryCommitment)                    load_device_function(functions, device, "vkGetDeviceMemoryCommitment",                    check);
            out_functions.BindBufferMemory                             = (PFN_vkBindBufferMemory)                             load_device_function(functions, device, "vkBindBufferMemory",                             check);
            out_functions.BindImageMemory                              = (PFN_vkBindImageMemory)                              load_device_function(functions, device, "vkBindImageMemory",                              check);
            out_functions.GetBufferMemoryRequirements                  = (PFN_vkGetBufferMemoryRequirements)                  load_device_function(functions, device, "vkGetBufferMemoryRequirements",                  check);
            out_functions.GetImageMemoryRequirements                   = (PFN_vkGetImageMemoryRequirements)                   load_device_function(functions, device, "vkGetImageMemoryRequirements",                   check);
            out_functions.GetImageSparseMemoryRequirements             = (PFN_vkGetImageSparseMemoryRequirements)             load_device_function(functions, device, "vkGetImageSparseMemoryRequirements",             check);
            out_functions.GetPhysicalDeviceSparseImageFormatProperties = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties) load_device_function(functions, device, "vkGetPhysicalDeviceSparseImageFormatProperties", check);
            out_functions.QueueBindSparse                              = (PFN_vkQueueBindSparse)                              load_device_function(functions, device, "vkQueueBindSparse",                              check);
            out_functions.CreateFence                                  = (PFN_vkCreateFence)                                  load_device_function(functions, device, "vkCreateFence",                                  check);
            out_functions.DestroyFence                                 = (PFN_vkDestroyFence)                                 load_device_function(functions, device, "vkDestroyFence",                                 check);
            out_functions.ResetFences                                  = (PFN_vkResetFences)                                  load_device_function(functions, device, "vkResetFences",                                  check);
            out_functions.GetFenceStatus                               = (PFN_vkGetFenceStatus)                               load_device_function(functions, device, "vkGetFenceStatus",                               check);
            out_functions.WaitForFences                                = (PFN_vkWaitForFences)                                load_device_function(functions, device, "vkWaitForFences",                                check);
            out_functions.CreateSemaphore                              = (PFN_vkCreateSemaphore)                              load_device_function(functions, device, "vkCreateSemaphore",                              check);
            out_functions.DestroySemaphore                             = (PFN_vkDestroySemaphore)                             load_device_function(functions, device, "vkDestroySemaphore",                             check);
            out_functions.CreateEvent                                  = (PFN_vkCreateEvent)                                  load_device_function(functions, device, "vkCreateEvent",                                  check);
            out_functions.DestroyEvent                                 = (PFN_vkDestroyEvent)                                 load_device_function(functions, device, "vkDestroyEvent",                                 check);
            out_functions.GetEventStatus                               = (PFN_vkGetEventStatus)                               load_device_function(functions, device, "vkGetEventStatus",                               check);
            out_functions.SetEvent                                     = (PFN_vkSetEvent)                                     load_device_function(functions, device, "vkSetEvent",                                     check);
            out_functions.ResetEvent                                   = (PFN_vkResetEvent)                                   load_device_function(functions, device, "vkResetEvent",                                   check);
            out_functions.CreateQueryPool                              = (PFN_vkCreateQueryPool)                              load_device_function(functions, device, "vkCreateQueryPool",                              check);
            out_functions.DestroyQueryPool                             = (PFN_vkDestroyQueryPool)                             load_device_function(functions, device, "vkDestroyQueryPool",                             check);
            out_functions.GetQueryPoolResults                          = (PFN_vkGetQueryPoolResults)                          load_device_function(functions, device, "vkGetQueryPoolResults",                          check);
            out_functions.CreateBuffer                                 = (PFN_vkCreateBuffer)                                 load_device_function(functions, device, "vkCreateBuffer",                                 check);
            out_functions.DestroyBuffer                                = (PFN_vkDestroyBuffer)                                load_device_function(functions, device, "vkDestroyBuffer",                                check);
            out_functions.CreateBufferView                             = (PFN_vkCreateBufferView)                             load_device_function(functions, device, "vkCreateBufferView",                             check);
            out_functions.DestroyBufferView                            = (PFN_vkDestroyBufferView)                            load_device_function(functions, device, "vkDestroyBufferView",                            check);
            out_functions.CreateImage                                  = (PFN_vkCreateImage)                                  load_device_function(functions, device, "vkCreateImage",                                  check);
            out_functions.DestroyImage                                 = (PFN_vkDestroyImage)                                 load_device_function(functions, device, "vkDestroyImage",                                 check);
            out_functions.GetImageSubresourceLayout                    = (PFN_vkGetImageSubresourceLayout)                    load_device_function(functions, device, "vkGetImageSubresourceLayout",                    check);
            out_functions.CreateImageView                              = (PFN_vkCreateImageView)                              load_device_function(functions, device, "vkCreateImageView",                              check);
            out_functions.DestroyImageView                             = (PFN_vkDestroyImageView)                             load_device_function(functions, device, "vkDestroyImageView",                             check);
            out_functions.CreateShaderModule                           = (PFN_vkCreateShaderModule)                           load_device_function(functions, device, "vkCreateShaderModule",                           check);
            out_functions.DestroyShaderModule                          = (PFN_vkDestroyShaderModule)                          load_device_function(functions, device, "vkDestroyShaderModule",                          check);
            out_functions.CreatePipelineCache                          = (PFN_vkCreatePipelineCache)                          load_device_function(functions, device, "vkCreatePipelineCache",                          check);
            out_functions.DestroyPipelineCache                         = (PFN_vkDestroyPipelineCache)                         load_device_function(functions, device, "vkDestroyPipelineCache",                         check);
            out_functions.GetPipelineCacheData                         = (PFN_vkGetPipelineCacheData)                         load_device_function(functions, device, "vkGetPipelineCacheData",                         check);
            out_functions.MergePipelineCaches                          = (PFN_vkMergePipelineCaches)                          load_device_function(functions, device, "vkMergePipelineCaches",                          check);
            out_functions.CreateGraphicsPipelines                      = (PFN_vkCreateGraphicsPipelines)                      load_device_function(functions, device, "vkCreateGraphicsPipelines",                      check);
            out_functions.CreateComputePipelines                       = (PFN_vkCreateComputePipelines)                       load_device_function(functions, device, "vkCreateComputePipelines",                       check);
            out_functions.DestroyPipeline                              = (PFN_vkDestroyPipeline)                              load_device_function(functions, device, "vkDestroyPipeline",                              check);
            out_functions.CreatePipelineLayout                         = (PFN_vkCreatePipelineLayout)                         load_device_function(functions, device, "vkCreatePipelineLayout",                         check);
            out_functions.DestroyPipelineLayout                        = (PFN_vkDestroyPipelineLayout)                        load_device_function(functions, device, "vkDestroyPipelineLayout",                        check);
            out_functions.CreateSampler                                = (PFN_vkCreateSampler)                                load_device_function(functions, device, "vkCreateSampler",                                check);
            out_functions.DestroySampler                               = (PFN_vkDestroySampler)                               load_device_function(functions, device, "vkDestroySampler",                               check);
            out_functions.CreateDescriptorSetLayout                    = (PFN_vkCreateDescriptorSetLayout)                    load_device_function(functions, device, "vkCreateDescriptorSetLayout",                    check);
            out_functions.DestroyDescriptorSetLayout                   = (PFN_vkDestroyDescriptorSetLayout)                   load_device_function(functions, device, "vkDestroyDescriptorSetLayout",                   check);
            out_functions.CreateDescriptorPool                         = (PFN_vkCreateDescriptorPool)                         load_device_function(functions, device, "vkCreateDescriptorPool",                         check);
            out_functions.DestroyDescriptorPool                        = (PFN_vkDestroyDescriptorPool)                        load_device_function(functions, device, "vkDestroyDescriptorPool",                        check);
            out_functions.ResetDescriptorPool                          = (PFN_vkResetDescriptorPool)                          load_device_function(functions, device, "vkResetDescriptorPool",                          check);
            out_functions.AllocateDescriptorSets                       = (PFN_vkAllocateDescriptorSets)                       load_device_function(functions, device, "vkAllocateDescriptorSets",                       check);
            out_functions.FreeDescriptorSets                           = (PFN_vkFreeDescriptorSets)                           load_device_function(functions, device, "vkFreeDescriptorSets",                           check);
            out_functions.UpdateDescriptorSets                         = (PFN_vkUpdateDescriptorSets)                         load_device_function(functions, device, "vkUpdateDescriptorSets",                         check);
            out_functions.CreateFramebuffer                            = (PFN_vkCreateFramebuffer)                            load_device_function(functions, device, "vkCreateFramebuffer",                            check);
            out_functions.DestroyFramebuffer                           = (PFN_vkDestroyFramebuffer)                           load_device_function(functions, device, "vkDestroyFramebuffer",                           check);
            out_functions.CreateRenderPass                             = (PFN_vkCreateRenderPass)                             load_device_function(functions, device, "vkCreateRenderPass",                             check);
            out_functions.DestroyRenderPass                            = (PFN_vkDestroyRenderPass)                            load_device_function(functions, device, "vkDestroyRenderPass",                            check);
            out_functions.GetRenderAreaGranularity                     = (PFN_vkGetRenderAreaGranularity)                     load_device_function(functions, device, "vkGetRenderAreaGranularity",                     check);
            out_functions.CreateCommandPool                            = (PFN_vkCreateCommandPool)                            load_device_function(functions, device, "vkCreateCommandPool",                            check);
            out_functions.DestroyCommandPool                           = (PFN_vkDestroyCommandPool)                           load_device_function(functions, device, "vkDestroyCommandPool",                           check);
            out_functions.ResetCommandPool                             = (PFN_vkResetCommandPool)                             load_device_function(functions, device, "vkResetCommandPool",                             check);
            out_functions.AllocateCommandBuffers                       = (PFN_vkAllocateCommandBuffers)                       load_device_function(functions, device, "vkAllocateCommandBuffers",                       check);
            out_functions.FreeCommandBuffers                           = (PFN_vkFreeCommandBuffers)                           load_device_function(functions, device, "vkFreeCommandBuffers",                           check);
            out_functions.BeginCommandBuffer                           = (PFN_vkBeginCommandBuffer)                           load_device_function(functions, device, "vkBeginCommandBuffer",                           check);
            out_functions.EndCommandBuffer                             = (PFN_vkEndCommandBuffer)                             load_device_function(functions, device, "vkEndCommandBuffer",                             check);
            out_functions.ResetCommandBuffer                           = (PFN_vkResetCommandBuffer)                           load_device_function(functions, device, "vkResetCommandBuffer",                           check);
            out_functions.CmdBindPipeline                              = (PFN_vkCmdBindPipeline)                              load_device_function(functions, device, "vkCmdBindPipeline",                              check);
            out_functions.CmdSetViewport                               = (PFN_vkCmdSetViewport)                               load_device_function(functions, device, "vkCmdSetViewport",                               check);
            out_functions.CmdSetScissor                                = (PFN_vkCmdSetScissor)                                load_device_function(functions, device, "vkCmdSetScissor",                                check);
            out_functions.CmdSetLineWidth                              = (PFN_vkCmdSetLineWidth)                              load_device_function(functions, device, "vkCmdSetLineWidth",                              check);
            out_functions.CmdSetDepthBias                              = (PFN_vkCmdSetDepthBias)                              load_device_function(functions, device, "vkCmdSetDepthBias",                              check);
            out_functions.CmdSetBlendConstants                         = (PFN_vkCmdSetBlendConstants)                         load_device_function(functions, device, "vkCmdSetBlendConstants",                         check);
            out_functions.CmdSetDepthBounds                            = (PFN_vkCmdSetDepthBounds)                            load_device_function(functions, device, "vkCmdSetDepthBounds",                            check);
            out_functions.CmdSetStencilCompareMask                     = (PFN_vkCmdSetStencilCompareMask)                     load_device_function(functions, device, "vkCmdSetStencilCompareMask",                     check);
            out_functions.CmdSetStencilWriteMask                       = (PFN_vkCmdSetStencilWriteMask)                       load_device_function(functions, device, "vkCmdSetStencilWriteMask",                       check);
            out_functions.CmdSetStencilReference                       = (PFN_vkCmdSetStencilReference)                       load_device_function(functions, device, "vkCmdSetStencilReference",                       check);
            out_functions.CmdBindDescriptorSets                        = (PFN_vkCmdBindDescriptorSets)                        load_device_function(functions, device, "vkCmdBindDescriptorSets",                        check);
            out_functions.CmdBindIndexBuffer                           = (PFN_vkCmdBindIndexBuffer)                           load_device_function(functions, device, "vkCmdBindIndexBuffer",                           check);
            out_functions.CmdBindVertexBuffers                         = (PFN_vkCmdBindVertexBuffers)                         load_device_function(functions, device, "vkCmdBindVertexBuffers",                         check);
            out_functions.CmdDraw                                      = (PFN_vkCmdDraw)                                      load_device_function(functions, device, "vkCmdDraw",                                      check);
            out_functions.CmdDrawIndexed                               = (PFN_vkCmdDrawIndexed)                               load_device_function(functions, device, "vkCmdDrawIndexed",                               check);
            out_functions.CmdDrawIndirect                              = (PFN_vkCmdDrawIndirect)                              load_device_function(functions, device, "vkCmdDrawIndirect",                              check);
            out_functions.CmdDrawIndexedIndirect                       = (PFN_vkCmdDrawIndexedIndirect)                       load_device_function(functions, device, "vkCmdDrawIndexedIndirect",                       check);
            out_functions.CmdDispatch                                  = (PFN_vkCmdDispatch)                                  load_device_function(functions, device, "vkCmdDispatch",                                  check);
            out_functions.CmdDispatchIndirect                          = (PFN_vkCmdDispatchIndirect)                          load_device_function(functions, device, "vkCmdDispatchIndirect",                          check);
            out_functions.CmdCopyBuffer                                = (PFN_vkCmdCopyBuffer)                                load_device_function(functions, device, "vkCmdCopyBuffer",                                check);
            out_functions.CmdCopyImage                                 = (PFN_vkCmdCopyImage)                                 load_device_function(functions, device, "vkCmdCopyImage",                                 check);
            out_functions.CmdBlitImage                                 = (PFN_vkCmdBlitImage)                                 load_device_function(functions, device, "vkCmdBlitImage",                                 check);
            out_functions.CmdCopyBufferToImage                         = (PFN_vkCmdCopyBufferToImage)                         load_device_function(functions, device, "vkCmdCopyBufferToImage",                         check);
            out_functions.CmdCopyImageToBuffer                         = (PFN_vkCmdCopyImageToBuffer)                         load_device_function(functions, device, "vkCmdCopyImageToBuffer",                         check);
            out_functions.CmdUpdateBuffer                              = (PFN_vkCmdUpdateBuffer)                              load_device_function(functions, device, "vkCmdUpdateBuffer",                              check);
            out_functions.CmdFillBuffer                                = (PFN_vkCmdFillBuffer)                                load_device_function(functions, device, "vkCmdFillBuffer",                                check);
            out_functions.CmdClearColorImage                           = (PFN_vkCmdClearColorImage)                           load_device_function(functions, device, "vkCmdClearColorImage",                           check);
            out_functions.CmdClearDepthStencilImage                    = (PFN_vkCmdClearDepthStencilImage)                    load_device_function(functions, device, "vkCmdClearDepthStencilImage",                    check);
            out_functions.CmdClearAttachments                          = (PFN_vkCmdClearAttachments)                          load_device_function(functions, device, "vkCmdClearAttachments",                          check);
            out_functions.CmdResolveImage                              = (PFN_vkCmdResolveImage)                              load_device_function(functions, device, "vkCmdResolveImage",                              check);
            out_functions.CmdSetEvent                                  = (PFN_vkCmdSetEvent)                                  load_device_function(functions, device, "vkCmdSetEvent",                                  check);
            out_functions.CmdResetEvent                                = (PFN_vkCmdResetEvent)                                load_device_function(functions, device, "vkCmdResetEvent",                                check);
            out_functions.CmdWaitEvents                                = (PFN_vkCmdWaitEvents)                                load_device_function(functions, device, "vkCmdWaitEvents",                                check);
            out_functions.CmdPipelineBarrier                           = (PFN_vkCmdPipelineBarrier)                           load_device_function(functions, device, "vkCmdPipelineBarrier",                           check);
            out_functions.CmdBeginQuery                                = (PFN_vkCmdBeginQuery)                                load_device_function(functions, device, "vkCmdBeginQuery",                                check);
            out_functions.CmdEndQuery                                  = (PFN_vkCmdEndQuery)                                  load_device_function(functions, device, "vkCmdEndQuery",                                  check);
            out_functions.CmdResetQueryPool                            = (PFN_vkCmdResetQueryPool)                            load_device_function(functions, device, "vkCmdResetQueryPool",                            check);
            out_functions.CmdWriteTimestamp                            = (PFN_vkCmdWriteTimestamp)                            load_device_function(functions, device, "vkCmdWriteTimestamp",                            check);
            out_functions.CmdCopyQueryPoolResults                      = (PFN_vkCmdCopyQueryPoolResults)                      load_device_function(functions, device, "vkCmdCopyQueryPoolResults",                      check);
            out_functions.CmdPushConstants                             = (PFN_vkCmdPushConstants)                             load_device_function(functions, device, "vkCmdPushConstants",                             check);
            out_functions.CmdBeginRenderPass                           = (PFN_vkCmdBeginRenderPass)                           load_device_function(functions, device, "vkCmdBeginRenderPass",                           check);
            out_functions.CmdNextSubpass                               = (PFN_vkCmdNextSubpass)                               load_device_function(functions, device, "vkCmdNextSubpass",                               check);
            out_functions.CmdEndRenderPass                             = (PFN_vkCmdEndRenderPass)                             load_device_function(functions, device, "vkCmdEndRenderPass",                             check);
            out_functions.CmdExecuteCommands                           = (PFN_vkCmdExecuteCommands)                           load_device_function(functions, device, "vkCmdExecuteCommands",                           check);


            if (false == check)
            {
                ASSERT(0);
                ERRLOG("Vulkan device loading failed");
                return Utilities::Failed_to_load_function;
            }

            return Utilities::Success;
        }

        Platform::int32 Device::Load_functions()
        {
            return Load_functions(m_device, m_Functions);
        }
        
        const Instance * Device::Get_instance() const
        {
            return (Instance *) Parent();
        }

        Instance * Device::Get_instance()
        {
            return (Instance *) Parent();
        }

        VkDevice Device::Get_device() const
        {
            return m_device;
        }
    }
}
