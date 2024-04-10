#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <set>

#include <optional>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;


#pragma region ValidationLayers

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);


#pragma endregion

#pragma region DebugUtils

//create debug report
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator);


void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

#pragma endregion

#pragma region PhysicalDevices and FamilyQueue

VkPhysicalDevice PickPhysicalDevice(VkInstance& instance, VkSurfaceKHR& surface);
bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR &surface);

#pragma endregion

#pragma region LogicalDevices and Queue
void CreateLogicalDevice(VkPhysicalDevice& physicalDevice, VkDevice* device, VkQueue* graphicsQueue);

#pragma endregion

#pragma region Surface & SwapChain
void CreateSurface(VkInstance& instance, GLFWwindow* window, VkSurfaceKHR* surface);

const std::vector<const char*> deviceExtensions =
{
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


struct SwapChainSupportDetails//properties should check
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice& device, VkSurfaceKHR& surface);

#pragma endregion