#include "CommonHead.h"
#include "Structs.hpp"

VkPhysicalDevice PickPhysicalDevice(VkInstance& instance, VkSurfaceKHR& surface)
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);//find all available physical devices

    if (deviceCount == 0)
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices)//select a suitable device
    {
        if (isDeviceSuitable(device, surface))
        {
            return device;
            break;
        }
    }

    return VK_NULL_HANDLE;
}

bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR& surface)
{
    //VkPhysicalDeviceProperties deviceProperties;//gpu infomation: name, type, vulkan version
    //vkGetPhysicalDeviceProperties(device, &deviceProperties);

    //VkPhysicalDeviceFeatures deviceFeatures;//gpu features: compression, 64bit float, mrt
    //vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    QueueFamilyIndices indices = FindQueueFamilies(device,  surface);

    bool extensionSupported = checkDeviceExtensionSupport(device);

    bool swapChainAdequate = false;
    if (extensionSupported)
    {
        SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }
    

    return indices.isComplete() && extensionSupported && swapChainAdequate;
}


bool checkDeviceExtensionSupport(VkPhysicalDevice device)
{
    //get all available extensions
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    //check all extension
    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
    for (const auto& extension : availableExtensions)
    {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}
