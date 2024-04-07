#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <cstring>
#include <optional>
#include <stdexcept>

//using namespace std;

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    bool isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class HelloTriangleApplication
{
private:
    GLFWwindow* window;
    VkInstance instance;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;;



    void pickPhysicalDevice()
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (deviceCount == 0)
        {
            throw std::runtime_error("no gpu");
        }

    }


    void initVulkan()
    {

    }
};