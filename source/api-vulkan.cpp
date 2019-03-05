/*
 * A Plugin that integrates the AMD AMF encoder into OBS Studio
 * Copyright (C) 2016 - 2018 Michael Fabian Dirks
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "api-vulkan.hpp"
#include <vector>

using namespace Plugin::API;

Plugin::API::Vulkan::Vulkan()
{
	// ToDo: Adapter enumeration needs to go by Display/Desktop.
	// - Nvidia is the only one that has GPU Affinity extension.
	// - Intel perhaps too since they used Nvidia technology. (Until recently at least)
}

Plugin::API::Vulkan::~Vulkan() {}

std::string Plugin::API::Vulkan::GetName()
{
	return std::string("Vulkan");
}

Plugin::API::Type Plugin::API::Vulkan::GetType()
{
	return Type::Vulkan;
}

std::vector<Adapter> Plugin::API::Vulkan::EnumerateAdapters()
{
	std::vector<Adapter> adapters;
	adapters.push_back(Adapter(0, 0, "Default"));
	return adapters;
}

std::shared_ptr<Instance> Plugin::API::Vulkan::CreateInstance(Adapter adapter)
{
	// Investigate how to do it with Vulkan
#if defined(WIN32) || defined(WIN64)
	return std::make_unique<VulkanInstance>();
#else
	VkResult vkres = VK_SUCCESS;
	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

	VkApplicationInfo applicationInfo = {};
	applicationInfo.sType               = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.apiVersion          = VK_API_VERSION_1_0;
	applicationInfo.applicationVersion  = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.engineVersion       = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.pApplicationName    = "AMF Vulkan application";
	applicationInfo.pEngineName         = "AMD Vulkan Sample Engine";

	return std::unique_ptr<VulkanInstance>(new VulkanInstance());
#endif
}

Plugin::API::VulkanInstance::VulkanInstance() {}

Plugin::API::VulkanInstance::~VulkanInstance() {}

Plugin::API::Adapter Plugin::API::VulkanInstance::GetAdapter()
{
	return Adapter(0, 0, "Default");
}

void* Plugin::API::VulkanInstance::GetContext()
{
	return nullptr;
}
