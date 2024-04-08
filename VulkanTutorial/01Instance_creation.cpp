//#include "CommonHead.h"
//#include "Structs.hpp"
//using namespace std;
//
//class HelloTriangleApplication_CreateInstance
//{
//public:
//    //void run()
//    //{
//    //    initWindow();
//    //    initVulkan();
//    //    mainLoop();
//    //    cleanup();
//    //}
//
//    HelloTriangleApplication_CreateInstance(GLFWwindow *windows, VkInstance &instance)
//    {
//        this->windows = windows;
//        this->instance = instance;
//    }
//
//    void setupInstance()
//    {
//
//    }
//
//
//private:
//
//    GLFWwindow *windows; //the window for diplay
//    VkInstance instance; // the vk instance
//
//    void setupDebugMessenger()
//    {
//        if (!enableValidationLayers)
//        {
//            return;
//        }
//
//        //set debug report create info
//        VkDebugUtilsMessengerCreateInfoEXT createInfo;
//        populateDebugMessengerCreateInfo(createInfo);
//
//        if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
//        {
//            throw std::runtime_error("failed to set up debug messenger!");
//        }
//
//    }
//
//    void initWindow()
//    {
//        glfwInit();
//    
//        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);//dont call opengl
//        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);//disable resize, not for this chapter
//        windows = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
//
//    }
//
//    void checkRequiredExtensionsSupported(const char** requiredExtensions, uint32_t requiredExtensionCount,
//        std::vector<VkExtensionProperties> supportedExtensions)
//    {
//        for (int i = 0; i < requiredExtensionCount; ++i)
//        {
//            bool found = false;
//            for (const auto& extension : supportedExtensions)
//            {
//                if (strcmp(requiredExtensions[i], extension.extensionName))
//                {
//                    found = true;
//                    break;
//                }
//            }
//
//            if (!found)
//            {
//                throw std::runtime_error("required extension not supported.");
//            }
//        }
//        std::cout << "All required extensions are supproted." << std::endl;
//    }
//
//
//
//    void createInstance()
//    {
//        //appinfo
//        VkApplicationInfo appInfo{};
//        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
//        appInfo.pApplicationName = "Hello Tri";
//        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
//        appInfo.pEngineName = "No Engine";
//        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
//        appInfo.apiVersion = VK_API_VERSION_1_0;
//
//        //createinfo
//        VkInstanceCreateInfo createInfo{};
//        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//        createInfo.pApplicationInfo = &appInfo;
//
//        //set the global extension
//        uint32_t glfwExtensionCount = 0;
//        const char** glfwExtensions;
//        glfwExtensions =
//            glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
//
//        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
//
//        if (enableValidationLayers)
//        {
//            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
//        }
//
//        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
//        createInfo.ppEnabledExtensionNames = extensions.data();
//        //create debug utils messenger
//        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
//        if (enableValidationLayers)
//        {
//            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
//            createInfo.ppEnabledLayerNames = validationLayers.data();
//
//            populateDebugMessengerCreateInfo(debugCreateInfo);
//            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
//        }
//        else
//        {
//            createInfo.enabledLayerCount = 0;
//        }
//
//        //check extensions support
//        uint32_t extensionCount = 0;
//        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
//        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
//        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());
//
//
//        std::cout << "available extensions\n";
//        for (const auto& extension : availableExtensions)
//        {
//            std::cout << "\t" << extension.extensionName << "\n";
//        }
//
//        checkRequiredExtensionsSupported(glfwExtensions, glfwExtensionCount, availableExtensions);
//
//        
//
//
//
//        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
//        {
//            throw runtime_error("failed to create instance");
//        }
//        cout << "vk success" << endl;
//    }
//
//    void initVulkan()
//    {
//        createInstance();
//
//        setupDebugMessenger();
//    }
//
//    void mainLoop()
//    {
//        while (!glfwWindowShouldClose(windows))
//        {
//            glfwPollEvents();
//        }
//    }
//
//    void cleanup()
//    {
//        if (enableValidationLayers)
//        {
//            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
//        }
//
//        vkDestroyInstance(instance, nullptr);
//
//        glfwDestroyWindow(windows);
//
//        glfwTerminate();
//    }
//};

//int main()
//{
//    HelloTriangleApplication app;
//    try {
//        app.run();
//    } catch (const std::exception& e) {
//        std::cerr << e.what() << std::endl;
//        return EXIT_FAILURE;
//    }
//    std::cout << "triangle" << endl;
//    return EXIT_SUCCESS;
//}