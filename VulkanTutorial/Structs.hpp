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
