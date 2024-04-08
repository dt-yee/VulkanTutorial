#include "CommonHead.h"
#include "Structs.hpp"

VkPhysicalDevice PickPhysicalDevice(VkInstance& instance)
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
        if (isDeviceSuitable(device))
        {
            return device;
            break;
        }
    }

    return VK_NULL_HANDLE;
}

bool isDeviceSuitable(VkPhysicalDevice device)
{
    //VkPhysicalDeviceProperties deviceProperties;//gpu infomation: name, type, vulkan version
    //vkGetPhysicalDeviceProperties(device, &deviceProperties);

    //VkPhysicalDeviceFeatures deviceFeatures;//gpu features: compression, 64bit float, mrt
    //vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    QueueFamilyIndices indices = FindQueueFamilies(device);

    return indices.isComplete();
}



