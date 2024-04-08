#pragma once
#include "CommonHead.h"

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    bool isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device)
{
    //get all available queue family on the physical device
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    QueueFamilyIndices indices;

    int index = 0;
    for (const auto& queueFamily : queueFamilies)//find queuefamily that support vk_queue_graphics_bit
    {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indices.graphicsFamily = index;
            break;
        }
        ++index;
    }
    return indices;
}

class VK_DebugAndValidationLayer
{
public:
    VK_DebugAndValidationLayer(GLFWwindow* windows, VkInstance& instance);

    void EnableValidationLayer(std::vector<const char*>& extensions, VkInstanceCreateInfo& createInfo);

    ~VK_DebugAndValidationLayer();

private:
    GLFWwindow* windows; //the window for diplay
    VkInstance instance; // the vk instance

    //create debug utils messenger
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

    bool enableValidationLayers = false;
};


