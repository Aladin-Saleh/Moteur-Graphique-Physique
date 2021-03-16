# Caps Engine
[![Build Status](https://dwarves.iut-fbleau.fr/git/carricom/PT2020-CASP/raw/master/passing.png)](https://dwarves.iut-fbleau.fr/git/carricom/)

## Introduction

Depot du code source C++ de Caps Engine : 
Notre projet consiste a developper un moteur graphique 3D en C++ et via l'API Vulkan, le but est de proposer un outil de developpement graphique 3d capable d'afficher des modeles plus ou moins complexes,
leur appliquer de la physique et cree un systeme de son spatial dans cet environnement.

## Exigences de Caps Engine

Un compilateur C++ (CXX17) GNU ou MSVC. Le moteur est testee sur Windows, Linux,
mais devrait probablement fonctionner sur n'importe quelle plate-forme avec le compilateur C++. 

Cmake VERSION 3.10 minimum

Le SDK Vulkan

## Exigences de Vulkan 

Une carte graphique tel qu'une AMD Radeon ou une NVIDIA GTX.

Nous avons teste avec succes le logiciel sous Windows et Linux.
Le logiciel ne fonctionne actuellement pas sur les appareils a CPU OpenCL.
Il pourrait fonctionner
sur le GPU d'un ordinateur portable, mais les performances ne seront probablement pas tres bonnes.

Carte Graphique teste:
- NVIDIA GeForce GTX 1660 (version du SDK 1.2.154 et 1.2.162)
- NVIDIA GeForce GTX 1050 Ti (version du SDK 1.2.154 et 1.2.170)
- NVIDIA GeForce GTX 1070
- NVIDIA GeForce GTX 1060
- Intel(R) HD Graphics (BDW GT1) (version du SDK 1.2.145)

## Instructions de construction de Caps Engine en utilisant Cmake

Installer le sdk vulkan : https://www.lunarg.com/vulkan-sdk/

```
git clone https://dwarves.iut-fbleau.fr/git/carricom/PT2020-CASP.git
git submodule update --init --recursive
```

**Windows**

Assurez-vous que cmake est installe: https://cmake.org

Installe Visual Studio pour la compilation MSVC et installe l'extention C++ et cmake.

Mettre a jour les variables d'environnement
```
VULKAN_SDK		C:\VulkanSDK\<Version>
Vulkan_INCLUDE_DIRS	C:\VulkanSDK\<Version>\Include
Vulkan_LIBRARIES	C:\VulkanSDK\<Version>\Lib
```

Ouvrir le dossier CapsEngine depuis Visual Studio et generer la solution

***Shader compilation***

```
cd PT2020-CAPS/CapsEngine/Shader
./make.bat
```

**Linux**

Assurez-vous que cmake est installe: https://cmake.org
```
sudo apt-get install cmake 
```

***Client Driver (ICD) Carte Graphique***

Pour vérifier si votre GPU est compatible avec notre moteur : http://vulkan.gpuinfo.org/listreports.php

INTEL HD graphics : Les Drivers
```
sudo apt-get install libvulkan1 libvulkan1:i386 mesa-vulkan-drivers mesa-vulkan-drivers:i386
sudo apt install vulkan-utils mesa-vulkan-drivers
sudo apt update
sudo apt upgrade
```

AMD graphics  : Les Drivers
```
sudo add-apt-repository ppa:oibaf/graphics-drivers
sudo apt update
sudo apt upgrade
```

Vulkan package pour AMD
```
sudo apt install libvulkan1 mesa-vulkan-drivers vulkan-utils
```

NVIDIA graphics : Les Drivers
```
sudo add-apt-repository ppa:graphics-drivers/ppa
sudo apt upgrade
```

Vulkan package for NVIDIA 
```
sudo apt install nvidia-graphics-drivers-396 nvidia-settings vulkan vulkan-utils
```

***Compilation GNU**

```
cd PT2020-CAPS/CapsEngine
export VULKAN_SDK="<chemin complet sdk vulkan>/<Version>/x86_64"
export VK_SDK_PATH="<chemin complet sdk vulkan>/<Version>/x86_64"
export Vulkan_INCLUDE_DIRS="<chemin complet sdk vulkan>/<Version>/x86_64/include"
export Vulkan_LIBRARIES="<chemin complet sdk vulkan>/<Version>/x86_64/lib"
```

**Compilation en mode Debug**  
Activation des Vulkan layers
```
cmake -DCMAKE_BUILD_TYPE=Debug .
make
cd Build
./CAPS
```

***Release**

```
cmake -DCMAKE_BUILD_TYPE=Release .
make
cd Build
./CAPS
```

***Shader compilation**

```
cd PT2020-CAPS/CapsEngine/Shader
./make.sh
```

## ThirdParty

Vulkan: https://www.lunarg.com/vulkan-sdk/

Bullet3: https://github.com/bulletphysics/bullet3

glfw: https://github.com/glfw/glfw

glm: https://github.com/g-truc/glm

imgui: https://github.com/ocornut/imgui

openal-soft: https://github.com/kcat/openal-soft/

stb-cmake: https://github.com/jschmidt42/stb-cmake

termcolor: https://github.com/ikalnytskyi/termcolor/ 

tinyobjloader: https://github.com/tinyobjloader/tinyobjloader

VulkanMemoryAllocator: https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator

# Documentation

Moteur: http://dwarves.iut-fbleau.fr/~albarell/DocumentationMoteur/html/