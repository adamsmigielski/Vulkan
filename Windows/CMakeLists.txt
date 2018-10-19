GET_PROPERTY(DL_IMPL GLOBAL PROPERTY PROP_DL_IMPL)
SET_PROPERTY(GLOBAL PROPERTY PROP_VULKAN_IMPL "Vulkan_Windows")


PROJECT(Vulkan_Windows)

ADD_LIBRARY(Vulkan_Windows STATIC
			Loader.cpp
			Loader.hpp
			PCH.cpp
			PCH.hpp)

TARGET_LINK_LIBRARIES(Vulkan_Windows
					  DL
					  ${DL_IMPL}
					  Vulkan)