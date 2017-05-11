PROJECT(Vulkan)

INCLUDE_DIRECTORIES(C:\\VulkanSDK\\1.0.39.1\\Include)

ADD_LIBRARY(Vulkan STATIC
			Implementation.cpp
			Implementation.hpp
			Instance.cpp
			Instance.hpp
			Loader.cpp
			Loader.hpp
			PCH.cpp
			PCH.hpp)
            
