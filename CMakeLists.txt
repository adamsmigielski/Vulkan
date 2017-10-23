PROJECT(Vulkan)

INCLUDE_DIRECTORIES(C:\\VulkanSDK\\1.0.61.1\\Include)

ADD_LIBRARY(Vulkan STATIC
			Device.cpp
			Device.hpp
			Implementation.cpp
			Implementation.hpp
			Instance.cpp
			Instance.hpp
			Loader.cpp
			Loader.hpp
			PCH.cpp
			PCH.hpp)

