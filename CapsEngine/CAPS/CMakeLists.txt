# Parametre Repertoire

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Debug)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Setting)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Struct)

#User
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/User)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/User/Input)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/InterfaceDll)

#Rendue
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering/Window)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering/Vulkan)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering/Devices)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering/SwapChain)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering/Graphics)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering/Shape)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering/Shader)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering/Light)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering/Buffer)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering/Descriptor)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering/Semaphore)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering/ImGui)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering/Camera)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Rendering/Materials)

#Physics
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Physics)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Physics/CShape)

#SoundManager
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/SoundManager)

#Miscellaneous
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Miscellaneous)

#Struct
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CAPS/Header/Struct)

#bullet
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/ThirdParty/Bullet3/src)

# Fichier

FILE(GLOB_RECURSE ENGINE_SOURCES *.cpp *.c)
FILE(GLOB_RECURSE ENGINE_HEADERS *.hpp *.h *.inl)

ADD_EXECUTABLE(CAPS ${ENGINE_SOURCES} ${ENGINE_HEADERS})
FIND_PACKAGE(Vulkan)

IF (VULKAN_FOUND)
	IF(WIN32)
		TARGET_INCLUDE_DIRECTORIES(CAPS PRIVATE "${Vulkan_INCLUDE_DIRS}")
	ELSEIF(UNIX)
		TARGET_INCLUDE_DIRECTORIES(CAPS PRIVATE $ENV{Vulkan_INCLUDE_DIRS})
	ENDIF()
    TARGET_LINK_LIBRARIES(CAPS PRIVATE glfw glfw3 termcolor tinyobjloader stb glm OpenAL ImGUI BulletDynamics BulletCollision LinearMath BulletSoftBody BulletDynamics BulletCollision LinearMath ${Vulkan_LIBRARIES})
ELSE ()
    MESSAGE(FATAL_ERROR "Impossible de trouver Vulkan")
ENDIF ()