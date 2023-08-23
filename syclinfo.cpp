/*
 * This file is part of syclinfo, a simple program to query available 
 * SYCL platforms and devices.
 *
 * Copyright (C) 2018  Aksel Alpay
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <sycl/sycl.hpp>
#include <map>

#include <iostream>
#include <vector>
#include <boost/preprocessor/stringize.hpp>


std::map<sycl::info::device_type, std::string> device_type_representation {
  {sycl::info::device_type::cpu, "CPU"},
  {sycl::info::device_type::gpu, "GPU"},
  {sycl::info::device_type::accelerator, "Accelerator"},
  {sycl::info::device_type::custom, "Custom"},
  {sycl::info::device_type::automatic, "Automatic"},
  {sycl::info::device_type::host, "Host"},
  {sycl::info::device_type::all, "All"}
};
            
std::map<sycl::info::global_mem_cache_type, std::string> global_mem_cache_type_representation {
  {sycl::info::global_mem_cache_type::none, "None"},
  {sycl::info::global_mem_cache_type::read_only, "Read-only"},
  {sycl::info::global_mem_cache_type::read_write, "Write-only"}
};


std::map<sycl::info::local_mem_type, std::string> local_mem_type_representation {
  {sycl::info::local_mem_type::none, "None"},
  {sycl::info::local_mem_type::local, "Local"},
  {sycl::info::local_mem_type::global, "Global"}
};

std::map<sycl::info::fp_config, std::string> fp_config_representation {
  { sycl::info::fp_config::denorm, "denorm"},
  { sycl::info::fp_config::inf_nan, "inf_nan"},
  { sycl::info::fp_config::round_to_nearest, "round_to_nearest"},
  { sycl::info::fp_config::round_to_zero, "round_to_zero"},
  { sycl::info::fp_config::round_to_inf, "round_to_inf"},
  { sycl::info::fp_config::fma, "fma"},
  { sycl::info::fp_config::correctly_rounded_divide_sqrt, "correctly_rounded_divide_sqrt"},
  { sycl::info::fp_config::soft_float, "soft_float" }
};

std::map<sycl::info::execution_capability, std::string> exec_capability_representation{
  {sycl::info::execution_capability::exec_kernel, "exec_kernel"},
  {sycl::info::execution_capability::exec_native_kernel, "exec_native_kernel"}
};


std::map<sycl::info::partition_property, std::string>
                        partition_property_representation {
  {sycl::info::partition_property::no_partition, "no_partition"},
  {sycl::info::partition_property::partition_equally, "partition_equally"},
  {sycl::info::partition_property::partition_by_counts, "partition_by_counts"},
  {sycl::info::partition_property::partition_by_affinity_domain, "partition_by_affinity_domain"}
};

std::map<sycl::info::partition_affinity_domain, std::string>
                        partition_affinity_domain_representation {
  {sycl::info::partition_affinity_domain::not_applicable, "not_applicable"},
  {sycl::info::partition_affinity_domain::numa, "numa"},
  {sycl::info::partition_affinity_domain::L4_cache, "L4_cache"},
  {sycl::info::partition_affinity_domain::L3_cache, "L3_cache"},
  {sycl::info::partition_affinity_domain::L2_cache, "L2_cache"},
  {sycl::info::partition_affinity_domain::L1_cache, "L1_cache"},
  {sycl::info::partition_affinity_domain::next_partitionable, "next_partitionable"}
};

std::map<sycl::memory_order, std::string>
                        memory_order_representation {
  {sycl::memory_order::relaxed, "relaxed"},
  {sycl::memory_order::acquire, "acquire"},
  {sycl::memory_order::release, "release"},
  {sycl::memory_order::acq_rel, "acq_rel"},
  {sycl::memory_order::seq_cst, "seq_cst"},
};

std::map<sycl::memory_scope, std::string>
                        memory_scope_representation {
  {sycl::memory_scope::work_item, "work_item"},
  {sycl::memory_scope::sub_group, "sub_group"},
  {sycl::memory_scope::work_group, "work_group"},
  {sycl::memory_scope::device, "device"},
  {sycl::memory_scope::system, "system"},
};



template<class T>
std::ostream& operator<<(std::ostream& lhs, const std::vector<T>& rhs)
{
  for(std::size_t i = 0; i < rhs.size(); ++i)
  {
    lhs << rhs[i];
    if (i != rhs.size()-1)
      lhs << ", ";
  }
  return lhs;
}
namespace std{
std::ostream& operator<<(std::ostream& lhs, const sycl::id<3>& idx)
{
  lhs << idx[0] << " " << idx[1] << " " << idx[2];
  return lhs;
}


std::ostream& operator<<(std::ostream& lhs, sycl::info::device_type dtype)
{
  lhs << device_type_representation[dtype];
  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const std::vector<sycl::kernel_id>& rhs)
{

  for(std::size_t i = 0; i < rhs.size(); ++i)
  {
    lhs << rhs[i].get_name();
    if (i != rhs.size()-1)
      lhs << ", ";
  }

  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const std::vector<sycl::aspect>& rhs)
{

  for(std::size_t i = 0; i < rhs.size(); ++i)
  {
    lhs << std::to_string((uint32_t)rhs[i]);
    if (i != rhs.size()-1)
      lhs << ", ";
  }

  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const std::vector<sycl::memory_order>& rhs)
{

  for(std::size_t i = 0; i < rhs.size(); ++i)
  {
    lhs << memory_order_representation[rhs[i]];
    if (i != rhs.size()-1)
      lhs << ", ";
  }

  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const std::vector<sycl::memory_scope>& rhs)
{

  for(std::size_t i = 0; i < rhs.size(); ++i)
  {
    lhs << memory_scope_representation[rhs[i]];
    if (i != rhs.size()-1)
      lhs << ", ";
  }

  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, sycl::info::global_mem_cache_type cache_type)
{
  lhs << global_mem_cache_type_representation[cache_type];
  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, sycl::info::local_mem_type local_type)
{
  lhs << local_mem_type_representation[local_type];
  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, sycl::info::fp_config fpconfig)
{
  lhs << fp_config_representation[fpconfig];
  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, sycl::info::execution_capability ecap)
{
  lhs << exec_capability_representation[ecap];
  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, sycl::info::partition_property pprop)
{
  lhs << partition_property_representation[pprop];
  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, sycl::info::partition_affinity_domain domain)
{
  lhs << partition_affinity_domain_representation[domain];
  return lhs;
}
}

#define PRINT_PLATFORM_PROPERTY(plat, prop) \
  std::cout << BOOST_PP_STRINGIZE(prop) << ": " \
            << plat.get_info<sycl::info::platform::prop>() << std::endl;

#define PRINT_DEVICE_PROPERTY(dev, prop) \
  std::cout << BOOST_PP_STRINGIZE(prop) << ": " \
            << dev.get_info<sycl::info::device::prop>() << std::endl;

#define PRINT_DEVICE_PROPERTY_HAS(dev, name, prop) \
  std::cout << BOOST_PP_STRINGIZE(name) << ": " \
            << (dev.has(sycl::aspect::prop) == 1 ? "yes" : "no") << std::endl;


#define PRINT_DEVICE_PROPERTY_EXT(dev, prop, name) \
  if (dev.has(sycl::aspect::prop)) \
        std::cout << BOOST_PP_STRINGIZE(prop) << ": " \
           << dev.get_info<sycl::ext::intel::info::device::name>() << std::endl;

int main()
{

  std::vector<sycl::device> devices = sycl::device::get_devices();

  for(const auto& dev : devices)
  {
    std::cout << "***************************************" << std::endl;
    std::cout << "           Platform:                   " << std::endl;
    std::cout << "***************************************" << std::endl;

    sycl::platform plat = dev.get_platform();

    PRINT_PLATFORM_PROPERTY(plat, name);
    PRINT_PLATFORM_PROPERTY(plat, vendor);
    PRINT_PLATFORM_PROPERTY(plat, version);
    PRINT_PLATFORM_PROPERTY(plat, profile);

    std::cout << std::endl << "============ Found device: =============" << std::endl;
    PRINT_DEVICE_PROPERTY(dev, name);
    PRINT_DEVICE_PROPERTY(dev, vendor);
    PRINT_DEVICE_PROPERTY(dev, driver_version);
    PRINT_DEVICE_PROPERTY(dev, version);
    PRINT_DEVICE_PROPERTY(dev, opencl_c_version);
    PRINT_DEVICE_PROPERTY(dev, device_type);
    PRINT_DEVICE_PROPERTY(dev, vendor_id);
    PRINT_DEVICE_PROPERTY(dev, is_available);
    PRINT_DEVICE_PROPERTY(dev, max_compute_units);
    PRINT_DEVICE_PROPERTY(dev, max_work_item_dimensions);
    PRINT_DEVICE_PROPERTY(dev, max_work_group_size);
    PRINT_DEVICE_PROPERTY(dev, sub_group_sizes);
    PRINT_DEVICE_PROPERTY(dev, preferred_vector_width_char);
    PRINT_DEVICE_PROPERTY(dev, preferred_vector_width_short);
    PRINT_DEVICE_PROPERTY(dev, preferred_vector_width_int);
    PRINT_DEVICE_PROPERTY(dev, preferred_vector_width_long);
    PRINT_DEVICE_PROPERTY(dev, preferred_vector_width_float);
    PRINT_DEVICE_PROPERTY(dev, preferred_vector_width_double);
    PRINT_DEVICE_PROPERTY(dev, preferred_vector_width_half);
    PRINT_DEVICE_PROPERTY(dev, native_vector_width_char);
    PRINT_DEVICE_PROPERTY(dev, native_vector_width_short);
    PRINT_DEVICE_PROPERTY(dev, native_vector_width_int);
    PRINT_DEVICE_PROPERTY(dev, native_vector_width_long);
    PRINT_DEVICE_PROPERTY(dev, native_vector_width_float);
    PRINT_DEVICE_PROPERTY(dev, native_vector_width_double);
    PRINT_DEVICE_PROPERTY(dev, native_vector_width_half);
    PRINT_DEVICE_PROPERTY(dev, max_clock_frequency);
    PRINT_DEVICE_PROPERTY(dev, address_bits);
    PRINT_DEVICE_PROPERTY(dev, max_mem_alloc_size);
    PRINT_DEVICE_PROPERTY_HAS(dev, image_support, image);
    PRINT_DEVICE_PROPERTY(dev, max_read_image_args);
    PRINT_DEVICE_PROPERTY(dev, max_write_image_args);
    PRINT_DEVICE_PROPERTY(dev, image2d_max_height);
    PRINT_DEVICE_PROPERTY(dev, image2d_max_width);
    PRINT_DEVICE_PROPERTY(dev, image3d_max_height);
    PRINT_DEVICE_PROPERTY(dev, image3d_max_width);
    PRINT_DEVICE_PROPERTY(dev, image3d_max_depth);
    PRINT_DEVICE_PROPERTY(dev, image_max_buffer_size);
    PRINT_DEVICE_PROPERTY(dev, image_max_array_size);
    PRINT_DEVICE_PROPERTY(dev, max_samplers);
    PRINT_DEVICE_PROPERTY(dev, max_parameter_size);
    PRINT_DEVICE_PROPERTY(dev, mem_base_addr_align);
    PRINT_DEVICE_PROPERTY(dev, half_fp_config);
    PRINT_DEVICE_PROPERTY(dev, single_fp_config);
    PRINT_DEVICE_PROPERTY(dev, double_fp_config);
    PRINT_DEVICE_PROPERTY(dev, global_mem_cache_type);
    PRINT_DEVICE_PROPERTY(dev, global_mem_cache_line_size);
    PRINT_DEVICE_PROPERTY(dev, global_mem_cache_size);
    PRINT_DEVICE_PROPERTY(dev, global_mem_size);
    PRINT_DEVICE_PROPERTY(dev, local_mem_type);
    PRINT_DEVICE_PROPERTY(dev, local_mem_size);
    PRINT_DEVICE_PROPERTY_HAS(dev, usm_device_allocations, usm_device_allocations);
    PRINT_DEVICE_PROPERTY_HAS(dev, usm_host_allocations, usm_host_allocations);
    PRINT_DEVICE_PROPERTY_HAS(dev, usm_shared_allocations, usm_shared_allocations);
    PRINT_DEVICE_PROPERTY_HAS(dev, usm_system_allocations, usm_system_allocations);
    PRINT_DEVICE_PROPERTY(dev, atomic_memory_order_capabilities);
    PRINT_DEVICE_PROPERTY(dev, atomic_fence_order_capabilities);
    PRINT_DEVICE_PROPERTY(dev, atomic_memory_scope_capabilities);
    PRINT_DEVICE_PROPERTY(dev, atomic_fence_scope_capabilities);
    PRINT_DEVICE_PROPERTY(dev, error_correction_support);
    PRINT_DEVICE_PROPERTY(dev, profiling_timer_resolution);
    PRINT_DEVICE_PROPERTY_HAS(dev, is_compiler_available, online_compiler);
    PRINT_DEVICE_PROPERTY_HAS(dev, is_linker_available, online_linker);
    PRINT_DEVICE_PROPERTY(dev, execution_capabilities);
    PRINT_DEVICE_PROPERTY_HAS(dev, queue_profiling, queue_profiling);
    PRINT_DEVICE_PROPERTY(dev, built_in_kernel_ids);
    PRINT_DEVICE_PROPERTY(dev, partition_max_sub_devices);
    PRINT_DEVICE_PROPERTY(dev, partition_properties);
    PRINT_DEVICE_PROPERTY(dev, partition_affinity_domains);
    PRINT_DEVICE_PROPERTY(dev, partition_type_property);
    PRINT_DEVICE_PROPERTY(dev, partition_type_affinity_domain);
    PRINT_DEVICE_PROPERTY(dev, reference_count);               

    std::cout << std::endl << "============ Intel Extensions: =============" << std::endl;
    PRINT_DEVICE_PROPERTY_EXT(dev, ext_intel_gpu_slices, gpu_slices);
    PRINT_DEVICE_PROPERTY_EXT(dev, ext_intel_pci_address, pci_address);
    PRINT_DEVICE_PROPERTY_EXT(dev, ext_intel_gpu_eu_count, gpu_eu_count);
    PRINT_DEVICE_PROPERTY_EXT(dev, ext_intel_gpu_eu_simd_width, gpu_eu_simd_width);
    PRINT_DEVICE_PROPERTY_EXT(dev, ext_intel_gpu_subslices_per_slice, gpu_subslices_per_slice);
    PRINT_DEVICE_PROPERTY_EXT(dev, ext_intel_gpu_eu_count_per_subslice, gpu_eu_count_per_subslice);
    PRINT_DEVICE_PROPERTY_EXT(dev, ext_intel_gpu_hw_threads_per_eu, gpu_hw_threads_per_eu);
    PRINT_DEVICE_PROPERTY_EXT(dev, ext_intel_max_mem_bandwidth, max_mem_bandwidth);
    PRINT_DEVICE_PROPERTY_EXT(dev, ext_intel_free_memory, free_memory);

    std::cout << std::endl << std::endl;
  }
}
