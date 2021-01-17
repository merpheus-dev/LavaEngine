#include <assert.h>
#include <vulkan/vulkan.h>
VkInstance instance = 0;

int main()
{
	const char* instance_layers[] = { "VK_LAYER_KHRONOS_validation" };
	const char* instance_extensions[] = { "VK_EXT_debug_report" };

	VkApplicationInfo applicationInfo = {};
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.pApplicationName = "Lava Application";
	applicationInfo.pEngineName = "LavaEngine";
	applicationInfo.engineVersion = VK_MAKE_VERSION(2,0,0);
	applicationInfo.applicationVersion = VK_MAKE_VERSION(0,1,0);

	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &applicationInfo;
	instanceCreateInfo.enabledExtensionCount = 1;
	instanceCreateInfo.ppEnabledExtensionNames = instance_extensions;
	instanceCreateInfo.enabledLayerCount = 1;
	instanceCreateInfo.ppEnabledLayerNames = instance_layers;

	VkResult result = vkCreateInstance(&instanceCreateInfo,NULL,&instance);
	assert(result==VK_SUCCESS);

	vkDestroyInstance(instance,NULL);
	return 0;
}