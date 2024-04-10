#include "CommonHead.h"
#include "Structs.hpp"
using namespace std;

class HelloTriangleApplication
{
public:
    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }


private:
    void initWindow() 
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);//dont call opengl
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);//disable resize, not for this chapter
        windows = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan()
    {
        createInstance();

        CreateSurface(instance, windows, &surface);
        physicalDevice = PickPhysicalDevice(instance);
        CreateLogicalDevice(physicalDevice, &logicalDevice, &graphicQueue);
    }

    void mainLoop()
    {
        while (!glfwWindowShouldClose(windows))
        {
            glfwPollEvents();
        }
    }

    void cleanup()
    {
        if (DebugValidationLayer != nullptr)
        {
            delete(DebugValidationLayer);
        }

        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(windows);

        glfwTerminate();
    }

    void checkRequiredExtensionsSupported(const char** requiredExtensions, uint32_t requiredExtensionCount,
        std::vector<VkExtensionProperties> supportedExtensions)
    {
        for (uint32_t i = 0; i < requiredExtensionCount; ++i)
        {
            bool found = false;
            for (const auto& extension : supportedExtensions)
            {
                if (strcmp(requiredExtensions[i], extension.extensionName))
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                throw std::runtime_error("required extension not supported.");
            }
        }
        std::cout << "All required extensions are supproted." << std::endl;
    }

    void createInstance()
    {
        //appinfo
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Vulkan";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        //createinfo
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        //set the global extension
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions =
            glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (m_bEnableDebug)
        {
            DebugValidationLayer = new VK_DebugAndValidationLayer(windows, instance);
            DebugValidationLayer->EnableValidationLayer(extensions, createInfo);
        }
        
        //check extension support
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());
    
        std::cout << "available extensions\n";
        for (const auto& extension : availableExtensions)
        {
            std::cout << "\t" << extension.extensionName << "\n";
        }

        checkRequiredExtensionsSupported(glfwExtensions, glfwExtensionCount, availableExtensions);
    
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            throw runtime_error("failed to create instance");
        }
        cout << "vk success" << endl;
    }

    GLFWwindow* windows = nullptr;
    VkInstance instance = VK_NULL_HANDLE;

    bool m_bEnableDebug = false;
    VK_DebugAndValidationLayer *DebugValidationLayer = nullptr;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice logicalDevice = VK_NULL_HANDLE;

    VkQueue graphicQueue = VK_NULL_HANDLE;
    VkQueue presentQueue = VK_NULL_HANDLE;

    VkSurfaceKHR surface = VK_NULL_HANDLE;
};

int main()
{
    HelloTriangleApplication app;
    
    try {
        app.run();
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }

    cout << "Vulkan Tutorial" << endl;
    return EXIT_SUCCESS;

}
